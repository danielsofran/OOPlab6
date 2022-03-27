//
// Created by Daniel on 25.03.2022.
//
#pragma once
#include "repository.h"

template<typename T>
typename vector<T>::iterator Repository<T>::getIterator(T* pointer){ return elements.begin() + (pointer - elements.data()); }

template<typename T>
Repository<T>::Repository(const Repository<T> & repository) {
    this->elements = repository.elements;
}

template<typename T>
Repository<T>::Repository(const std::initializer_list<T>& list)
{
    for(const auto& elem : list)
        elements.push_back(elem);
}

template<typename T>
int Repository<T>::size() const {
    return elements.size();
}

template<typename T>
T& Repository<T>::operator[](const int& index)
{
    try{ return elements[index]; }
    catch(...) { throw RepoException("Indexul "+std::to_string(index)+" este invalid!\n");}
}

template<typename T>
void Repository<T>::add(const T & element) {
    const T* it = find(element);
    if(it != NULL) throw RepoException("Element duplicat!\n");
    try{elements.push_back(element);}
    catch(...){ throw RepoException("Eroare la stocarea elementului!\n");}
}

template<typename T>
T* Repository<T>::find(const T & element, T* begin, T* end) {
    if(begin == NULL) begin = this->begin();
    if(end == NULL) end = this->end();
    for(auto it=begin; it != end; ++it)
        if(*it == element)
            return it;
    return NULL;
}

template<typename T> template<class UnaryPredicate>
T* Repository<T>::find(UnaryPredicate fct, T* begin, T* end) {
    if(begin == NULL) begin = this->begin();
    if(end == NULL) end = this->end();
    for(auto it=begin; it != end; ++it)
        if(fct(*it))
            return it;
    return NULL;
}

template<typename T>
void Repository<T>::remove(const T& element) {
    T* it = find(element);
    if(it == NULL) throw RepoException("Elementul inexistent!\n");

    elements.erase(getIterator(it));
}

template<typename T> template<class UnaryPredicate>
T Repository<T>::remove(UnaryPredicate fct) {
    T* it = find(fct);
    if(it == NULL) throw RepoException("Elementul inexistent!\n");
    elements.erase(getIterator(it));
    return *it;
}

template<typename T>
T* Repository<T>::begin() { return elements.begin().base();}

template<typename T>
T* Repository<T>::end() {return elements.end().base(); }

template<typename T>
const T* Repository<T>::cbegin() const {return elements.cbegin().base();}

template<typename T>
const T* Repository<T>::cend() const { return elements.cend().base();}


template<typename T> template<class Compare>
void Repository<T>::sort(Compare compare) {
    std::sort(elements.begin(), elements.end(), compare);
}