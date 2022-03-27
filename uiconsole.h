//
// Created by Daniel on 26.03.2022.
//

#ifndef LAB6_UICONSOLE_H
#define LAB6_UICONSOLE_H

#include "service.h"
#include <windows.h>
#include <iostream>

using std::cin;
using std::cout;

class ConsoleUI
{
private:
    Service service;

    // afisarea meniului
    void printMenu(ostream&);

    // citeste datele unui locatar
    // le atribui parametrilor de tip out
    void readLocatar(istream&, ostream&, TypeApartament&, TypeNume&, TypeSuprafata&, TypeTip&);

    // afisez locatarul
    void writeLocatar(ostream&, const Locatar&);

    // adauga
    void adauga(istream&, ostream&);

    // sterge
    void sterge(istream&, ostream&);

    // modifica
    void modifica(istream&, ostream&);

    // listare
    void afisare(ostream&);

    // cauta apartament
    void cautaApartament(istream&, ostream&);

    // filtrare
    void filtrare(istream&, ostream&);

    // sortare
    void sortare(istream&, ostream&);

public:
    ConsoleUI()=default;
    // rulez meniul
    void run(istream& = cin, ostream& = cout);
};

#endif //LAB6_UICONSOLE_H
