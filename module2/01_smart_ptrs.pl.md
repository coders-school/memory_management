﻿<!-- .slide: data-background="#111111" -->

# Inteligentne wskaźniki

___

## Inteligentne wskaźniki

* <!-- .element: class="fragment fade-in" --> Inteligentny wskaźnik zarządza wskaźnikiem na obiekt zaalokowany na stercie

  * <!-- .element: class="fragment fade-in" --> Usuwa wskazany obiekt we właściwym czasie
  * <!-- .element: class="fragment fade-in" --> <code>operator->()</code> wywołuje metody obiektów zarządzanych
  * <!-- .element: class="fragment fade-in" --> <code>operator.()</code> wywołuje metody inteligentnych wskaźników
  * <!-- .element: class="fragment fade-in" --> inteligentny wskaźnik na klasę bazową może zawierać wskaźnik na klasę pochodną

* <!-- .element: class="fragment fade-in" --> Inteligentne wskaźniki STL:

  * <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr<></code>
  * <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr<></code>
  * <!-- .element: class="fragment fade-in" --> <code>std::weak_ptr<></code>
  * <!-- .element: class="fragment fade-in" --> <code>std::auto_ptr<></code> - usunięte w C++17
