#ifndef LAB6_DOMAIN_H
#define LAB6_DOMAIN_H

#include <string>
#include <iostream>
#include <vector>
#include <utility>

using std::string;
using std::istream;
using std::ostream;

typedef int TypeApartament;
typedef string TypeNume;
typedef int TypeSuprafata;
typedef string TypeTip;

class Locatar{
private: // campuri
    TypeApartament apartament = 0;
    TypeNume nume_proprietar;
    TypeSuprafata suprafata = 0;
    TypeTip tip;
public:
    // constructori
    // constructor fara parametrii
    Locatar() = default;
    // constructor cu parametrii
    Locatar(const TypeApartament& Apartament, TypeNume  NumeProprietar, const TypeSuprafata& Suprafata, TypeTip  Tip) :
            apartament(Apartament), nume_proprietar(std::move(NumeProprietar)), suprafata(Suprafata), tip(std::move(Tip)) {}
    // constructor de copiere
    Locatar(const Locatar&);

    // operator de atribuire
    Locatar& operator=(const Locatar&);

    // getteri
    TypeApartament getApartament() const;
    TypeNume getNumeProprietar() const;
    TypeSuprafata getSuprafata() const;
    TypeTip getTip() const;

    // setteri
    void setApartament(const TypeApartament&);
    void setNumeProprietar(const TypeNume &);
    void setSuprafata(const TypeSuprafata &);
    void setTip(const TypeTip &);

    // operatori de egalitate
    bool operator==(const Locatar&) const;
    bool operator!=(const Locatar&) const;

    // operatori relationali
    bool operator<(const Locatar&) const;
    bool operator<=(const Locatar&) const;
    bool operator>(const Locatar&) const;
    bool operator>=(const Locatar&) const;
};

#endif //LAB6_DOMAIN_H
