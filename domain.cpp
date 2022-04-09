//
// Created by Daniel on 25.03.2022.
//

#include "domain.h"

Locatar::Locatar(const Locatar & obj) {
    apartament = obj.apartament;
    nume_proprietar = obj.nume_proprietar;
    suprafata = obj.suprafata;
    tip = obj.tip;
    //std::cout<<"Obiectul "<<obj<<"\n a fost copiat!\n";
}

Locatar& Locatar::operator=(const Locatar & obj) = default;

TypeApartament Locatar::getApartament() const { return apartament; }
TypeNume Locatar::getNumeProprietar() const { return nume_proprietar; }
TypeSuprafata Locatar::getSuprafata() const { return suprafata; }
TypeTip Locatar::getTip() const { return tip; }

void Locatar::setApartament(const TypeApartament& value) { apartament = value; }
void Locatar::setNumeProprietar(const TypeNume& value) { nume_proprietar = value; }
void Locatar::setSuprafata(const TypeSuprafata& value) { suprafata = value; }
void Locatar::setTip(const TypeTip& value) { tip = value; }

bool Locatar::operator==(const Locatar & obj) const {
    return  apartament == obj.apartament &&
            nume_proprietar == obj.nume_proprietar &&
            suprafata == obj.suprafata &&
            tip == obj.tip;
}
bool Locatar::operator!=(const Locatar & obj) const { return !(*this == obj); }

bool Locatar::operator<(const Locatar & obj) const { return this->apartament < obj.apartament; }
bool Locatar::operator>(const Locatar & obj) const { return !(*this<obj) && !(*this == obj);}
bool Locatar::operator<=(const Locatar & obj) const { return !(*this > obj); }
bool Locatar::operator>=(const Locatar &obj) const { return !(*this < obj); }