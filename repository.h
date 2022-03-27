//
// Created by Daniel on 25.03.2022.
//

#ifndef LAB6_REPOSITORY_H
#define LAB6_REPOSITORY_H

#include <type_traits>
#include <vector>
#include <algorithm>
#include "exceptions.h"
using std::vector;

template<typename T>
class Repository{
private:
    vector<T> elements;
    typename vector<T>::iterator getIterator(T*);
public:
    Repository() = default;
    Repository(const Repository&);
    Repository(const std::initializer_list<T>&);

    // operator de atribuire
    // Repository& operator=(const Repository&);

    // indexator, returnez o referinta la obiect
    // arunc RepoException daca pozitia este invalida
    T& operator[](const int&);

    // returneaza numarul de elemente continute
    int size() const;

    // adaug un element la finalul containerului
    // arunc RepoException daca operatia esueaza
    // arunc RepoException daca elementul se afla in container
    void add(const T&);

    // returnez o referinta catre primul element egal cu cel dat
    // sau NULL altfel
    // primul iterator indica pozitia de inceput
    // al doilea indica pozitia de final
    // implicit, cautarea de face pe tot containerul
    T* find(const T&, T* = NULL, T* = NULL);

    // returnez un iterator catre primul element care respecta proprietatea data
    // daca elementul nu este gasit, returnez NULL
    // primul iterator indica pozitia de inceput
    // al doilea indica pozitia de final
    // implicit, cautarea de face pe tot containerul
    template<class UnaryPredicate>
    T* find(UnaryPredicate, T* = NULL, T* = NULL);

    // sterg prima aparitie a elementului dat din container
    // arunc o exceptie daca nu exista in container
    void remove(const T&);

    // sterg primul element care respecta proprietatea
    // returnez elementul sters
    // arunc o exceptie daca nu exista in container
    template<class UnaryPredicate>
    T remove(UnaryPredicate);

    // sortez repository-ul dupa operatorul < sau dupa functie
    template<class Compare=std::less<T>>
    void sort(Compare compare = Compare{});

    // implementez iteratorii de begin si end pentru a putea intera
    T* begin();
    const T* cbegin() const;
    T* end();
    const T* cend() const;
};

#endif //LAB6_REPOSITORY_H

// static_assert(std::is_convertible_v<Callable&&, std::function<Signature>>, "Wrong Signature!");
