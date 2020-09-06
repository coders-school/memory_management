## Wykrywanie problemów pamięci

* <!-- .element: class="fragment fade-in" --> Address Sanitizer (ASAN)
  * <!-- .element: class="fragment fade-in" --> dodaj flagi kompilacji:
    * <!-- .element: class="fragment fade-in" --> <code>–fsanitize=address -g</code>
    * <!-- .element: class="fragment fade-in" --> <code>–fsanitize=leak -g</code>
  * <!-- .element: class="fragment fade-in" --> uruchom binarkę
* <!-- .element: class="fragment fade-in" --> Valgrind
  * <!-- .element: class="fragment fade-in" --> skompiluj binarkę
  * <!-- .element: class="fragment fade-in" --> uruchom binarkę pod valgrindem:
    * <!-- .element: class="fragment fade-in" --> <code>valgrind /path/to/binary</code>
  * <!-- .element: class="fragment fade-in" --> dodatkowe sprawdzenia:
    * <!-- .element: class="fragment fade-in" --> <code>valgrind --leak-check=full /path/to/binary</code>

Oba narzędzia nie działają w systemie Windows 😕
<!-- .element: class="fragment fade-in" -->
