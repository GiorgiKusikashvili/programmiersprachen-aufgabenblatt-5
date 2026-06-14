#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP

#include "list_node.hpp"
#include "list_iterator.hpp"

#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

// forward declaration of template list class
template <typename T>
class List;

// forward declaration of free function "reverse"
template <typename T>
List<T> reverse(List<T> const& list_to_reverse);

template <typename T>
List<T> operator+(List<T> const& lhs, List<T> const& rhs);

template <typename T>
class List {
  public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* 
      get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* 
      get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    /* Declaration of Default Constructor */
    List();
    
    /* Declaration of Copy Constructor using Deep-Copy Semantics */
    List(List const& rhs);

    /* Declaration of Move Constructor */
    List(List&& rhs);

    /* Declaration of Initializer-List-based Constructor */
    List(std::initializer_list<T> ini_list);

    /* Declaration of Destructor */
    ~List();

    /* Declaration of Unifying Assignment Operator - see: Vorlesung 10, pp. 11-13, watch video explanation!*/
    List& operator=(List rhs);

    /* Declaration of built-in Member-Swap method used by Unifying Assignment Operator */
    void swap(List& rhs);

    /* Declaration of list-comparison-operator in terms of equality */
    bool operator==(List const& rhs) const;

    /* Declaration of list-comparison-operator in terms of inequality */
    bool operator!=(List const& rhs) const;
    
    /* Declaration of size-Method */
    std::size_t size() const;

    /* Declaration of empty-Method */
    bool empty() const;

    /* Declaration of push_front-Method */
    void push_front(T const& element);

    /* Declaration of pop_front-Method */
    void pop_front();

    /* Declaration of push_front-Method */
    void push_back(T const& element);

    /* Declaration of push_front-Method */
    void pop_back();

    /* Declaration of emplace_front-Method */
    template <class... Args>
    void emplace_front(Args&&... args);

    /* Declaration of emplace_back-Method */
    template <class... Args>
    void emplace_back(Args&&... args);

    /* Declaration of front-Method */
    T& front();

    /* Declaration of back-Method */
    T& back();

    /* Declaration of clear-Method */
    void clear();

    /* Declaration of reverse-Method*/
    void reverse();

    /* Declaration of begin-Method returning a ListIterator refering to the first list_node */
    ListIterator<T> begin();
    /* Declaration of end-Method returning a ListIterator refering to the past-the-end-element which marks the end of the list*/
    ListIterator<T> end();

    /* Declaration of insert-Method */
    ListIterator<T> insert(ListIterator<T> const& position, T const& value);
    /* Declaration of emplace-Method */
    template <class... Args>
    ListIterator<T> emplace(ListIterator<T> const& position, Args&&... args);
    /* Declaration of erase-Method */
    ListIterator<T> erase(ListIterator<T> const& position);

  // list members
  private: 
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/* ======================================== *
 * BEGIN COMMENTING AND IMPLEMENTATION HERE *
 * ======================================== */

 //=========================
// not fully implemented yet
/* Aufgabe 5.2 - Teil 1 */
/*Standard-Konstruktor: Initialisiert eine leere Liste */
template <typename T>
List<T>::List() : size_{0}, first_{nullptr}, last_{nullptr} {}

//=========================
// test and implement
/* Aufgabe 5.2 - Teil 2 */
/* Gibt die Anzahl der Elemente in der Liste in O(1) zurück */
template <typename T>
std::size_t List<T>::size() const {
    //TODO: return value of member variable insteaf of 27
    return size_;
};

//=========================
// test and implement
/* Aufgabe 5.2 - Teil 3 */
/* Prüft, ob die Liste leer ist (Größe == 0) */
template <typename T>
bool List<T>::empty() const {
    // check whether size member variable is zero -- this should be a one line implementation
    return size_ == 0;
};

//=========================
/* Aufgabe 5.3 - Teil 1 */
/* Ein Element wird am Anfang hingefügt */
template <typename T>
void List<T>::push_front(T const& element) {
    // TODO: push_front-method (Aufgabe 5.3)
    //wir erstellen ein neuen knoten mit "new ListNode<T>"
    // Wert = element, prev = nullptr, next = bisheriges first_
    ListNode<T>* new_node = new ListNode<T>{element, nullptr, first_};

    if (empty()) {
        last_ = new_node;  // Wenn leer, ist es auch das letzte Element. also das Element ist erste  und letzte
    } else {
        first_->prev = new_node; // Altes erstes Element zeigt rückwärts auf das neue
    }

    first_ = new_node; // Das neue Element ist jetzt das erste
    ++size_;           // Größe inkrementieren

    /*ERKLÄRUNG:
     *Also was ist pasiert: Die Liste hat ein Anfangsknote und ein Endknote.
     *[Anfang]<->[Ende]
     * mit push_front, rütschen wir der Anfangsknote eins rechts, und an seiner stellen fügen wir ein neues Element ein
     *[neues Element]<->[Anfang]<->[Ende]
     *und nun aktualisieren wir die Liste
     *[Anfang]<->[neues Element]<->[Ende]
     */
}

//=========================
/* Aufgabe 5.3 - Teil 2 */
/* das erste Element wird entfernt */
template <typename T>
void List<T>::pop_front() {
    if (empty()) {
        throw "List is empty";
    }

    // TODO: remainder of pop_front-method (Aufgabe 5.3)
    ListNode<T>* to_delete = first_; // Wir merken uns den alten ersten Knoten

    if (size_ == 1) {
        // Wenn es das einzige Element war, ist die Liste danach leer
        //deswegen mussen wir firs und last auf nullpoiter setzten damit wir "Memory Leak" vermeiden
        first_ = nullptr;
        last_ = nullptr;
    } else {
        first_ = first_->next; // Das zweite Element wird das neue erste
        first_->prev = nullptr; // Es gibt nichts mehr davor
    }

    delete to_delete; // Speicher sauber freigeben!
    --size_;          // Größe dekrementieren

    /* ERKLÄRUNG:
     * das erste Element wird entfernt
     * [first]<->[ein Element (z.b name: a)]<->[last]
     *  wird zu:
     * [ein Element]<->[last]
     * jetzt wird das ein Element names a, das erte Elemen
     * [first (also a)]<->[last]
     */
}

//=========================
/* Aufgabe 5.3 - Teil 3 */
/* Ein Element wird am Ende der Liste hingefügt */
template <typename T>
void List<T>::push_back(T const& element) {
    // TODO: push_back-method (Aufgabe 5.3)
    // Neuen Knoten erstellen
    //Wert = element, prev = bisheriges last_, next = nullptr
    ListNode<T>* new_node = new ListNode<T>{element, last_, nullptr};

    if (empty()) {
        first_ = new_node; // Wenn leer, ist es auch das erste Element
    } else {
        last_->next = new_node; // Altes letztes Element zeigt vorwärts auf das neue
    }

    last_ = new_node; // Das neue Element ist jetzt das letzte
    ++size_;          // Größe inkrementieren

    /*ERKLÄRUNG:
     *Also was ist pasiert: Die Liste hat ein Anfangsknote und ein Endknote.
     *[Anfang]<->[Ende]
     * mit push_back, rütschen wir der Endknote eins links, und an seiner stellen fügen wir ein neues Element ein
     *[Anfang]<->[Ende]<->[neues Element]
     *und nun aktualisieren wir die Liste
     *[Anfang]<->[neues Element]<->[Ende]
     */
}

//=========================
/* Aufgabe 5.3 - Teil 4 */
/* das letzte Element wird entfernt */
template <typename T>
void List<T>::pop_back() {
    if (empty()) {
        throw "List is empty";
    }

    // TODO: remainder of pop_back-method (Aufgabe 5.3)
    ListNode<T>* to_delete = last_; // Wir merken uns den alten letzten Knoten

    if (size_ == 1) {
        first_ = nullptr;
        last_ = nullptr;
    } else {
        last_ = last_->prev; // Das vorletzte Element wird das neue letzte
        last_->next = nullptr; // Es gibt nichts mehr danach
    }

    delete to_delete; // Speicher sauber freigeben!
    --size_;          // Größe dekrementieren

        /* ERKLÄRUNG:
         * das letzte Element wird entfernt
         * [first]<->[ein Element (z.b name: b)]<->[last]
         *  wird zu:
         * [first]<->[ein Element]
         * jetzt wird das ein Element namens b das letzte Element
         * [first]<->[last (also b)]
         */
}

//UNTERSCHIED: PUSH vs EMPLACE
/*
 * Push: es wird ein Element bzw. ein object in der Liste bzw in der Knoten kopiert oder verschoben
 * Emplace: es wird ein Argument übergeben womit das object direkt in knoten gebaut wird.
 *          damit wird unnötige Kopie gespart
 */


//=========================
/* Aufgabe 5.3 - Teil 5 */
/* Baut ein Element direkt am Anfang der Liste */
template <typename T>
template <class... Args>
void List<T>::emplace_back(Args&&... args)
{
    // TODO: emplace_back-method (Aufgabe 5.3)
    // Es wird ein neuen Knoten erstellt, dessen "value" direkt mit den Argumenten konstruiert wird
    ListNode<T>* new_node = new ListNode<T>{T(std::forward<Args>(args)...), last_, nullptr};

    if (empty()) {
        first_ = new_node;
    } else {
        last_->next = new_node;
    }
    last_ = new_node;
    ++size_;

}

//=========================
/* Aufgabe 5.3 - Teil 6 */
/* Baut ein Element direkt am Ende der Liste */
template <typename T>
template <class... Args>
void List<T>::emplace_front(Args&&... args)
{
    // TODO: emplace_front-method (Aufgabe 5.3)
    ListNode<T>* new_node = new ListNode<T>{T(std::forward<Args>(args)...), nullptr, first_};

    if (empty()) {
        last_ = new_node;
    } else {
        first_->prev = new_node;
    }
    first_ = new_node;
    ++size_;
}


//=========================
/* Aufgabe 5.3 - Teil 6 */
/* Das erste Element wird zurückgegeben */
template <typename T>
T& List<T>::front() {
    if (empty()) {
        throw "List is empty";
    }

    // TODO: remainder of front-method (Aufgabe 5.3)
    return first_->value; // Value (den Wert) des erten Knoten wird zurückgegeben (also das erste Element)

}

//=========================
/* Aufgabe 5.3 - Teil 8 */
/* ... */
template <typename T>
T& List<T>::back() {
    if (empty()) {
        throw "List is empty";
    }

    // TODO: remainder of back-method (Aufgabe 5.3)
    return last_->value;  //Value (den Wert) des letzten Knoten wird zurückgegeben (also das letzte Element).
}

//=========================
// test and implement:
// TODO: clear 
// Aufgabe 5.4 - Teil 1
/* Löscht alle Elemente der Liste nacheinander, um den Speicher freizugeben */
template <typename T>
void List<T>::clear() {
    //also while-Schleife durchläuft bis die liste leer ist, bei jedem durchlauf wird pop_front() geführt, womit die elemente nacheinander entfernt werden
    while (!empty()) {
        pop_front();
    }
}

//=========================
// test and implement:
// TODO: List Destructor implemented by calling clear
// Aufgabe 5.4 - Teil 2
/*Destruktor: Ruft clear() auf, um beim Löschen der Liste alle Ressourcen freizugeben. Also Die Speicher wird freigegeben */
template <typename T>
List<T>::~List() {
    //TODO: Implement via clear-Method (Aufgabe 5.4)
    clear();
} //can not be tested with unit tests

//=========================
// test and implement:
// TODO: Copy-Konstruktor using Deep-Copy semantics
// Aufgabe 5.5
/* Copy-Konstruktor: es wird eine tiefe Kopie der Liste erzeugt*/
template <typename T>
//neue leere Liste erstellen
List<T>::List(List<T> const& rhs):size_{0}, first_{nullptr}, last_{nullptr} {
    // Zeiger auf den Anfang der zu kopierenden Liste setzen
    ListNode<T>* current = rhs.first_;

    // Die originale Liste von vorne nach hinten durchlaufen
    while (current != nullptr) {
        push_back(current->value); // Element hinten an unsere neue Liste anhängen
        current = current->next;   // Zum nächsten Knoten wandern
    }


}

//=========================
// test and implement:
// TODO: helper-swap-method for bultin-types used by unifying assignment operator (see Vorlesung 10, pp. 11-13)
// Aufgabe 5.6 - Teil 1
/* Tauscht den Inhalt (die Pointer und die Größe) dieser Liste mit einer anderen Liste aus */
template <typename T>
void List<T>::swap(List<T>& rhs) {
    //wir tauschen die firs, last und size von origineller Liste mit der Liste von rhs aus.
    std::swap(first_, rhs.first_);
    std::swap(last_, rhs.last_);
    std::swap(size_, rhs.size_);
}

//=========================
// test and implement:
// TODO: unyfing assignment operator (see Vorlesung 10, pp. 11-13)
// Aufgabe 5.6 - Teil 2
/* Zuweisungsoperator mittels Copy-and-Swap-Idiom */
template <typename T>
List<T>& List<T>::operator=(List<T> rhs) {
    swap(rhs); // Unsere Daten mit den kopierten Daten von rhs tauschen
    return *this; // Eine Referenz auf uns selbst zurückgeben
}

//=========================
// Aufgabe 5.7 - Teil 1
/* Die aktuelle (originale) Liste umdrehen */
template <typename T>
void List<T>::reverse() {

    if (empty() || size_ == 1) {
        return; //weil ine leere Liste oder eine Liste mit 1 Element ist schon "umgedreht"
    }

    ListNode<T>* current = first_;
    ListNode<T>* temp = nullptr;

    // Durch die Liste gehen und bei jedem Knoten "next" und "prev" vertauschen
    while (current != nullptr) {
        temp = current->prev;       // Alten prev-Zeiger merken
        current->prev = current->next; // prev zeigt jetzt auf den Nachfolger
        current->next = temp;          // next zeigt jetzt auf den Vorgänger

        // Da wir die Zeiger vertauscht haben, wandert "current->prev"
        // in der originalen Liste zum nächsten Element
        current = current->prev;
    }

    // Am Ende müssen wir noch die globalen first_ und last_ Zeiger der Liste tauschen
    temp = first_;
    first_ = last_;
    last_ = temp;
}

//=========================
// Aufgabe 5.7 - Teil 2
/* Gibt eine neue Liste zurück, die eine umgedrehte Kopie der übergebenen Liste ist */
template <typename T>
List<T> reverse(List<T> const& list_to_reverse) {
    List<T> result{list_to_reverse}; // Tiefe Kopie erstellen
    result.reverse();                // Die Kopie umdrehen
    return result;                   // Umgedrehte Kopie zurückgeben
}

//=========================
// Aufgabe 5.8 - Teil 1
/* Vergleicht zwei Listen auf Gleichheit (gleiche Größe und gleiche Werte) */
template <typename T>
bool List<T>::operator==(List const& rhs) const {
    //TODO: operator== (Aufgabe 5.8)
    //beide Liste müsssen gleiche Anzhahl von Elemente an gleicher Stellen haben

    //Wenn die originale und kopie Listen nicht gleich sind "false" zurückgeben
    if (size_ != rhs.size_) {
        return false;
    }

    // Zeiger auf den Anfang beider Listen setzen
    ListNode<T>* current_lhs = first_;
    ListNode<T>* current_rhs = rhs.first_;

    // Parallel durch beide Listen gehen
    while (current_lhs != nullptr && current_rhs != nullptr) {
        // Wenn sich ein Wert unterscheidet, sind die Listen ungleich
        if (current_lhs->value != current_rhs->value) {
            return false;
        }
        current_lhs = current_lhs->next;
        current_rhs = current_rhs->next;
    }

    // Wenn die Schleife ohne Unterschiede durchgelaufen ist, sind sie komplett gleich also return true
    return true;
}

//=========================
// Aufgabe 5.8 - Teil 2
/* Vergleicht zwei Listen auf Ungleichheit */
template <typename T>
bool List<T>::operator!=(List const& rhs) const {
    //TODO: operator!= (Aufgabe 5.8)
    // make use of operator== you implemented

    //wir verwenden (rufen auf) operator== um zu vergleichen. wenn operator== "falsch" liefert dann return true
    return !(*this == rhs);
}

//=========================
// Aufgabe 5.9 - Teil 1
/* Gibt einen Iterator auf das erste Element zurück */
template <typename T>
ListIterator<T> List<T>::begin() {
    //TODO: begin-Method returning an Iterator to the 
    //      first element in the List (Aufgabe 5.9)
    return ListIterator<T>{first_};
}

//=========================
// Aufgabe 5.9 - Teil 2
/* Gibt einen Iterator auf das Element hinter dem letzten Element zurück (nullptr) */
template <typename T>
ListIterator<T> List<T>::end() {
    //TODO: end-Method returning an Iterator to element after (!) 
    //      the last element in the List (Aufgabe 5.9)

    return ListIterator<T>{nullptr};
}

//=========================
// Aufgabe 5.11
/* ... */
template <typename T>
ListIterator<T> List<T>::insert(ListIterator<T> const& position, T const& value) {

}

template <typename T>
template <class... Args>
ListIterator<T> List<T>::emplace(ListIterator<T> const& position, Args&&... args)
{

}

//=========================
// Aufgabe 5.12
/* ... */
template <typename T>
ListIterator<T> List<T>::erase(ListIterator<T> const& position) {

}

//=========================
// Aufgabe 5.13 is a copy test and should be implemented in a cpp file

//=========================
// test and implement:
// TODO: Move-Konstruktor (Aufgabe 5.14)
/* ... */
template <typename T>
List<T>::List(List<T>&& rhs) {}

//=========================
// test and implement:
//TODO: Initializer - List Konstruktor (5.15 - Teil 1)
/* ...  */
template <typename T>
List<T>::List(std::initializer_list<T> ini_list) {
    //not implemented yet
}

//=========================
// Aufgabe 5.15 - Teil 2
/* ... */
template <typename T>
List<T> operator+(List<T> const& lhs, List<T> const& rhs) {

}


#endif // #ifndef BUW_LIST_HPP