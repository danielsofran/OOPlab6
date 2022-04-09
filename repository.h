//
// Created by Daniel on 25.03.2022.
//

#ifndef LAB6_REPOSITORY_H
#define LAB6_REPOSITORY_H

#include <type_traits>
#include <vector>
#include <algorithm>
#include <memory>

#include "exceptions.h"
using std::vector;
using std::unique_ptr;

template<typename T>
class Repository{
    friend class TestRepository;
private:
    T* elements;
    int dim;
    int capacity;
    void delete_poz(int poz) {
        for(int i=poz;i<dim-1;++i)
            elements[i] = elements[i+1];
        --dim;
    }
    void adaug(T elem) {
        if(dim>=capacity) realoc();
        elements[dim++] = elem;
    }
    void realoc(){
        T* newelements = new T[2*capacity];
        for(int i=0;i<capacity;++i)
            newelements[i] = elements[i];
        delete[] elements;
        elements = newelements;
        capacity *= 2;
    }
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    Repository(){
        dim = 0;
        capacity = 1;
        elements = new T[capacity];
    }
    Repository(const Repository<T> & repository) {
        this->elements = new T[repository.capacity];
        dim = repository.dim;
        capacity = repository.capacity;
        for(int i=0;i<capacity;++i)
            elements[i] = repository.elements[i];
    }
    ~Repository() { delete[] elements; }

    Repository& operator=(const Repository& repository)
    {
        this->elements = new T[repository.capacity];
        dim = repository.dim;
        capacity = repository.capacity;
        for(int i=0;i<capacity;++i)
            elements[i] = repository.elements[i];
        return *this;
    }

    // indexator, returnez o referinta la obiect
    // arunc RepoException daca pozitia este invalida
    T& operator[](const int& index){
        try{ return elements[index]; }
        catch(...) { throw RepoException("Indexul "+std::to_string(index)+" este invalid!\n");}
    }

    // returneaza numarul de elemente continute
    int size() const noexcept {return dim; };

    // adaug un element la finalul containerului
    // arunc RepoException daca elementul se afla in container
    void add(const T & element) {
        Repository<T>::const_iterator it = find(element);
        if(it != NULL) throw RepoException("Element duplicat!\n");
        adaug(element);
    }

    // returnez o referinta catre primul element egal cu cel dat
    // sau NULL altfel
    // primul iterator indica pozitia de inceput
    // al doilea indica pozitia de final
    // implicit, cautarea de face pe tot containerul
    iterator find(const T & element, T* begin=NULL, T* end=NULL) {
        if(begin == NULL) begin = this->begin();
        if(end == NULL) end = this->end();
        for(auto it=begin; it != end; ++it)
            if(*it == element)
                return it;
        return NULL;
    }

    // returnez un iterator catre primul element care respecta proprietatea data
    // daca elementul nu este gasit, returnez NULL
    // primul iterator indica pozitia de inceput
    // al doilea indica pozitia de final
    // implicit, cautarea de face pe tot containerul
    template<class UnaryPredicate>
    iterator find(UnaryPredicate fct, T* begin = NULL, T* end = NULL) {
        if(begin == NULL) begin = this->begin();
        if(end == NULL) end = this->end();
        for(auto it=begin; it != end; ++it)
            if(fct(*it))
                return it;
        return NULL;
    }

    void remove(const T& element) {
        T* it = find(element);
        if(it == NULL) throw RepoException("Elementul inexistent!\n");

        delete_poz(it - elements);
    }

    template<class UnaryPredicate>
    T remove(UnaryPredicate fct) {
        T* it = find(fct);
        if(it == NULL) throw RepoException("Elementul inexistent!\n");
        delete_poz(it - elements);
        return *it;
    }

    template<class Compare = std::less<>>
    void sort(Compare compare = Compare{}) {
        std::sort(elements, elements+dim, compare);
    }

    // implementez iteratorii de begin si end pentru a putea intera
    iterator begin() { return elements;}
    const_iterator cbegin() const {return elements; };
    iterator end() {return elements+dim;}
    const_iterator cend() const {return elements+dim;}
};

#endif //LAB6_REPOSITORY_H

// static_assert(std::is_convertible_v<Callable&&, std::function<Signature>>, "Wrong Signature!");
