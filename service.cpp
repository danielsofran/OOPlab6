//
// Created by Daniel on 26.03.2022.
//

#include "service.h"

void Service::add(const TypeApartament & apartament, const TypeNume & numeproprietar, const TypeSuprafata & suprafata, const TypeTip & tip) {
    Locatar locatar{apartament, numeproprietar, suprafata, tip};
    ValidatorLocatar::validLocatar(locatar);
    repository.add(locatar);
}

void Service::remove(const TypeApartament & apartament, const TypeNume & numeproprietar, const TypeSuprafata & suprafata, const TypeTip & tip) {
    Locatar locatar{apartament, numeproprietar, suprafata, tip};
    ValidatorLocatar::validLocatar(locatar);
    repository.remove(locatar);
}

void Service::modify(const TypeApartament & apartament1, const TypeNume & nume1, const TypeSuprafata & suprafata1, const TypeTip & tip1,
                     const TypeApartament & apartament2, const TypeNume & nume2, const TypeSuprafata & suprafata2, const TypeTip & tip2) {
    Locatar locatar1{apartament1, nume1, suprafata1, tip1};
    Locatar locatar2{apartament2, nume2, suprafata2, tip2};
    ValidatorLocatar::validLocatar(locatar1);
    ValidatorLocatar::validLocatar(locatar2);
    auto it = repository.find(locatar1);
    if(it == NULL) throw RepoException("Elementul nu a fost gasit!\n");
    *it = locatar2;
}

Locatar Service::findApartament(const TypeApartament & apartament) {
    ValidatorLocatar::validApartament(apartament);
    auto it = repository.find([&apartament](const Locatar& l){return l.getApartament() == apartament; });
    if(it == nullptr) throw ServiceException("Apartamentul dat nu exista!\n");
    return *it;
}

Repository<Locatar> Service::filterTip(const TypeTip & tip) {
    ValidatorLocatar::validTip(tip);
    Repository<Locatar> rez;
    auto pred = [&tip](const Locatar &l)
            { return l.getTip() == tip; };
    auto it = repository.find(pred);
    while(it != nullptr)
    {
        rez.add(*it);
        it = repository.find(pred, it+1);
    }
    return rez;
}

Repository<Locatar> Service::filterSuprafata(const TypeSuprafata & suprafata) {
    ValidatorLocatar::validSuprafata(suprafata);
    Repository<Locatar> rez;
    auto pred = [&suprafata](const Locatar &l)
            { return l.getSuprafata() == suprafata; };
    auto it = repository.find(pred);
    while(it != nullptr)
    {
        rez.add(*it);
        it = repository.find(pred, it+1);
    }
    return rez;
}

void Service::sortNume() {
    auto cmp = [](const Locatar& l1, const Locatar& l2)
    {
        return l1.getNumeProprietar() < l2.getNumeProprietar();
    };
    repository.sort(cmp);
}

void Service::sortSuprafata() {
    auto cmp = [](const Locatar& l1, const Locatar& l2)
    {
        return l1.getSuprafata() < l2.getSuprafata();
    };
    repository.sort(cmp);
}

void Service::sortTipSuprafata() {
    auto cmp = [](const Locatar& l1, const Locatar& l2)
    {
        return  l1.getTip() < l2.getTip() ||
            l1.getTip() == l2.getTip() && l1.getSuprafata() < l2.getSuprafata();
    };
    repository.sort(cmp);
}

Locatar* Service::begin() { return repository.begin(); }
Locatar* Service::end() { return repository.end(); }
const Locatar* Service::cbegin() const { return repository.cbegin(); }
const Locatar* Service::cend() const { return repository.cend(); }
