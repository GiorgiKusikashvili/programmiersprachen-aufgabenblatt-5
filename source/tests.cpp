#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

#include "list.hpp"


// Hilfsfunktionen, um indirekt auf die Member der Klasse List zuzugreifen (nur für die Tests!)
template <typename T>
size_t get_size(List<T> const& list_to_test) {return list_to_test.size_;}

template <typename T>
ListNode<T>* get_first_pointer(List<T> const& list_to_test) {return list_to_test.first_;}

template <typename T>
ListNode<T>* get_last_pointer(List<T> const& list_to_test) {return list_to_test.last_;}

template <typename T>
ListNode<T>* get_node_pointer(ListIterator<T> const& list_iterator_to_test) { return list_iterator_to_test.node_; }


//test case definitions for default constructor of list as well as empty and size for empty list
#include "sub_tests/default_constructed_list.test"

//test case definitions for push methods of list
#include "sub_tests/push_front.test"
#include "sub_tests/push_back.test"
#include "sub_tests/emplace_front.test"
#include "sub_tests/emplace_back.test"

//test case definitions for pop methods of list
#include "sub_tests/pop_front.test"
#include "sub_tests/pop_back.test"

//test case definitions for 

//test cases for element access of list
#include "sub_tests/front.test"
#include "sub_tests/back.test"

//test cases for retrieving iterators
#include "sub_tests/begin.test"
#include "sub_tests/end.test"

//iterator tests
#include "sub_tests/iterators/operator_star.test"
#include "sub_tests/iterators/operator_arrow.test"
#include "sub_tests/iterators/operator_equals.test"
#include "sub_tests/iterators/operator_does_not_equal.test"
#include "sub_tests/iterators/operator_iterate_forward.test"

TEST_CASE("List - Aufgabe 5.4 - Testing clear()")
{
  List<int> meine_liste;

  // 1. Überprüfen, ob clear() bei einer bereits leeren Liste kein Problem macht
  meine_liste.clear();
  REQUIRE(meine_liste.empty());
  REQUIRE(meine_liste.size() == 0);

  // 2. Elemente hinzufügen und Größe Überprufen
  meine_liste.push_back(1);
  meine_liste.push_back(2);
  meine_liste.push_back(3);
  REQUIRE(meine_liste.size() == 3);

  // 3. clear() ausführen und kontrollieren
  meine_liste.clear();
  REQUIRE(meine_liste.empty());
  REQUIRE(meine_liste.size() == 0);
}

TEST_CASE("List - Aufgabe 5.5 - Testing Copy Constructor")
{
  // 1. Eine Originalliste erstellen und befüllen
  List<int> original;
  original.push_back(10);
  original.push_back(20);
  original.push_back(30);

  // 2. Den Copy-Konstruktor aufrufen
  List<int> kopie{original};

  // Beide Listen müssen die gleiche Größe und die gleichen Werte haben
  REQUIRE(kopie.size() == 3);
  REQUIRE(kopie.front() == 10);
  REQUIRE(kopie.back() == 30);

  // 3. Sicherstellen, dass es eine Tiefe Kopie ist
  kopie.pop_front(); // Löscht die 10 aus der KOPIE

  // In der Kopie sollte das erste Element jetzt 20 sein
  REQUIRE(kopie.front() == 20);
  REQUIRE(kopie.size() == 2);

  // Das Original darf sich NICHT verändert haben
  REQUIRE(original.front() == 10);
  REQUIRE(original.size() == 3);
}

#include <map>

int main(int argc, char *argv[])
{
  doctest::Context ctx;
  ctx.applyCommandLine(argc, argv);
  return ctx.run();
}




