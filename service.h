//
// Created by Daniel on 26.03.2022.
//

#ifndef LAB6_SERVICE_H
#define LAB6_SERVICE_H

#include <fstream>
#include <regex>
#include <random>
#include <algorithm>
#include <chrono>
#include <set>

#include "domain.h"
#include "repository.h"
#include "validator.h"

using std::vector;

class Service{
    friend class TestService;
private:
    vector<Locatar> repository;
    vector<Locatar> listanotificare;
public:
    // doar constructor fara parametrii
    Service()=default;
    Service(const Service&) = delete;

    // adauga elementul in repository
    // arunca ServiceException daca nu a putut fi creat
    // arunca RepoException daca exista in container
    // arunca ValidatorException daca nu este valid
    void add(const TypeApartament&, const TypeNume&, const TypeSuprafata&, const TypeTip&);

    // sterge elementul din repository
    // arunca RepoException daca elementul nu exista
    // arunca ValidatorException daca nu este valid
    void remove(const TypeApartament&, const TypeNume&, const TypeSuprafata&, const TypeTip&);

    // modific primul elemet cu al doilea
    // arunca RepoException daca elementul nu exista
    // arunca ValidatorException daca unul din locatari nu este valid
    void modify(const TypeApartament&, const TypeApartament&, const TypeNume&, const TypeSuprafata&, const TypeTip&);

    // cauta apartamentul cu numarul dat
    // arunca ServiceException daca nu exista un astfel de apartament
    // arunca InvalidFieldException daca nu este valid
    const Locatar& findApartament(const TypeApartament&);

    // returnez toate elementele care au tipul dat
    // arunca InvalidFieldException daca nu este valid
    vector<Locatar> filterTip(const TypeTip&);

    // returnez toate elementele care au suprafata data?
    // arunca InvalidFieldException daca nu este valid
    vector<Locatar> filterSuprafata(const TypeSuprafata&);

    // sortez repository-ul dupa nume crescator
    void sortNume();

    // sortez repository-ul dupa suprafata crescator
    void sortSuprafata();

    // sortez repository-ul dupa tip, iar la tipuri egale sortez dupa suprafata
    void sortTipSuprafata();

    // adaug apartamentul cu nr dat in lista de notificare
    // arunc ServiceException daca nu exista
    void addNotificare(const int&);

    // sterg lista de notificari
    void clearNotificari();

    // adaug n apartamente alese aleator
    void generateNotificari(const int&);

    // export ca fisier HTML
    void exportNotificariHTML(const string&);

    // export ca fisier CSV
    void exportNotificariCSV(const string&);

    // implementare iteratori de begin si end pentru a putea intera
    vector<Locatar>::iterator begin();
    vector<Locatar>::const_iterator cbegin() const;
    vector<Locatar>::iterator end();
    vector<Locatar>::const_iterator cend() const;
};

#endif //LAB6_SERVICE_H
