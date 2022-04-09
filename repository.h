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
    typename vector<T>::iterator getIterator(T* pointer) { return elements.begin() + (pointer - elements.data()); }
public:
    Repository() = default;
    Repository(const Repository<T> & repository) {
        this->elements = repository.elements;
    }

    // operator de atribuire
    // Repository& operator=(const Repository&);

    // indexator, returnez o referinta la obiect
    // arunc RepoException daca pozitia este invalida
    T& operator[](const int& index)
    {
        try{ return elements[index]; }
        catch(...) { throw RepoException("Indexul "+std::to_string(index)+" este invalid!\n");}
    }


    // returneaza numarul de elemente continute
    int size() const {return elements.size(); }

    // adaug un element la finalul containerului
    // arunc RepoException daca elementul se afla in container
    void add(const T & element) {
        const T* it = find(element);
        if(it != NULL) throw RepoException("Element duplicat!\n");
        elements.push_back(element);
    }

    // returnez o referinta catre primul element egal cu cel dat
    // sau NULL altfel
    // primul iterator indica pozitia de inceput
    // al doilea indica pozitia de final
    // implicit, cautarea de face pe tot containerul
    T* find(const T & element, T* begin = NULL, T* end = NULL) {
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
    T* find(UnaryPredicate fct, T* begin = NULL, T* end = NULL) {
        if(begin == NULL) begin = this->begin();
        if(end == NULL) end = this->end();
        for(auto it=begin; it != end; ++it)
            if(fct(*it))
                return it;
        return NULL;
    }

    // sterg prima aparitie a elementului dat din container
    // arunc o exceptie daca nu exista in container
    void remove(const T& element) {
        T* it = find(element);
        if(it == NULL) throw RepoException("Elementul inexistent!\n");

        elements.erase(getIterator(it));
    }

    // sterg primul element care respecta proprietatea
    // returnez elementul sters
    // arunc o exceptie daca nu exista in container
    template<class UnaryPredicate>
    T remove(UnaryPredicate fct) {
        T* it = find(fct);
        if(it == NULL) throw RepoException("Elementul inexistent!\n");
        elements.erase(getIterator(it));
        return *it;
    }

    // sortez repository-ul dupa operatorul < sau dupa functie
    template<class Compare=std::less<T>>
    void sort(Compare compare = Compare{}){
        std::sort(elements.begin(), elements.end(), compare);
    }

    // implementez iteratorii de begin si end pentru a putea intera
    T* begin() { return elements.begin().base();}
    const T* cbegin() const {return elements.cbegin().base(); }
    T* end() {return elements.end().base(); }
    const T* cend() const {return elements.cend().base(); }
};

#endif //LAB6_REPOSITORY_H
