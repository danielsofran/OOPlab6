#ifndef LAB6_DOMAIN_H
#define LAB6_DOMAIN_H

#include <string>
#include <iostream>

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
    Locatar(const TypeApartament& Apartament, const TypeNume& NumeProprietar, const TypeSuprafata& Suprafata, const TypeTip& Tip) :
            apartament(Apartament), nume_proprietar(NumeProprietar), suprafata(Suprafata), tip(Tip) {}
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


    // operatori de intrare/iesire
    friend istream& operator>>(istream&, Locatar&);
    friend ostream& operator<<(ostream&, const Locatar&);
};

#endif //LAB6_DOMAIN_H
