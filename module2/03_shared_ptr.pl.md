﻿<!-- .slide: data-background="#111111" -->

# `std::shared_ptr<>`

___

### `std::shared_ptr<>`

### Cechy

* <!-- .element: class="fragment fade-in" --> jeden obiekt == wielu właścicieli
* <!-- .element: class="fragment fade-in" --> ostatnia strona odsyłająca usuwa obiekt
* <!-- .element: class="fragment fade-in" --> kopiowanie dozwolone
* <!-- .element: class="fragment fade-in" --> przenoszenie dozwolone
* <!-- .element: class="fragment fade-in" --> możliwe użycie niestandardowego deletera
* <!-- .element: class="fragment fade-in" --> możliwe użycie niestandardowego alokatora

<img data-src="img/sharedptr1inverted.png" alt="shared pointers" class="plain fragment fade-in">

___
<!-- .slide: style="font-size: 0.85em" -->

### użycie `std::shared_ptr<>`

* Kopiowanie i przenoszenie jest dozwolone

<div class="multicolumn">
<div class="col">

```cpp
std::shared_ptr<MyData> source();
void sink(std::shared_ptr<MyData> ptr);

void simpleUsage() {
    source();
    sink(source());
    auto ptr = source();
    sink(ptr);
    sink(std::move(ptr));
    auto p1 = source();
    auto p2 = p1;
    p2 = std::move(p1);
    p1 = p2;
    p1 = std::move(p2);
}

```

</div>

<div class="col">

```cpp
std::shared_ptr<MyData> source();
void sink(std::shared_ptr<MyData> ptr);

void collections() {
    std::vector<std::shared_ptr<MyData>> v;

    v.push_back(source());

    auto tmp = source();
    v.push_back(tmp);
    v.push_back(std::move(tmp));

    sink(v[0]);
    sink(std::move(v[0]));
}
```

</div>

___
<!-- .slide: style="font-size: 0.85em" -->

### użycie `std::shared_ptr<>` cd

```cpp
#include <memory>
#include <map>
#include <string>

class Gadget {};
std::map<std::string, std::shared_ptr<Gadget>> gadgets;
// above wouldn't compile with C++03. Why?

void foo() {
    std::shared_ptr<Gadget> p1{new Gadget()};   // reference counter = 1
    {
        auto p2 = p1;                           // copy (reference counter == 2)
        gadgets.insert(make_pair("mp3", p2));   // copy (reference counter == 3)
        p2->use();
    }                                           // destruction of p2, reference counter = 2
}                                               // destruction of p1, reference counter = 1

int main() {
    foo();
    gadgets.clear();                            // reference counter = 0 - gadget is removed
}
```

___

### Zależności cykliczne `std::shared_ptr<>`

* co się tutaj stało?

<div class="multicolumn" style="position: relative">
<div class="col" style="width: 65%; flex: none">

```cpp
#include <memory>

struct Node {
    std::shared_ptr<Node> child;
    std::shared_ptr<Node> parent;
};

int main () {
    auto root = std::shared_ptr<Node>(new Node);
    auto child = std::shared_ptr<Node>(new Node);

    root->child = child;
    child->parent = root;
}


```

</div>

<div class="col fragment fade-in">
    Wyciek pamięci!
    <img data-src="img/kot.jpg" alt="kot" class="plain" style="height: 50%">

</div>
