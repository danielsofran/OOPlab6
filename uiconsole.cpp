//
// Created by Daniel on 26.03.2022.
//

#include "uiconsole.h"

void ConsoleUI::printMenu(ostream & out) {
    out<<"\tMeniu\n"
         "1. Adaugare\n"
         "2. Stergere\n"
         "3. Modificare\n"
         "4. Afisare\n"
         "5. Cauta apartament\n"
         "6. Filtrare\n"
         "7. Sortare\n"
         "8. Iesire\n";
}

void ConsoleUI::readLocatar(istream & in, ostream& out, TypeApartament& apartament, TypeNume& nume, TypeSuprafata& suprafata, TypeTip& tip) {
    string strap, strsup;

    out<<"Introduceti apartamentul: ";
    in>>strap;
    try{ apartament = std::stoi(strap); }
    catch(...) { out<<"Apartament invalid!\n";  apartament=0;}

    out<<"Introduceti numele proprietarului: ";
    std::getline(in>>std::ws, nume); //in>>std::noskipws;

    out<<"Introduceti suprafata: ";
    in>>strsup;
    try{ suprafata = std::stoi(strsup); }
    catch(...) { out<<"Suprafata invalida!\n";  suprafata=0;}
    out<<"Introduceti tipul: "; in>>tip;
}

void ConsoleUI::writeLocatar(ostream & out, const Locatar& locatar) {
    out<<"Apartament: "<<locatar.getApartament()<<'\n';
    out<<"Nume Proprietar: "<<locatar.getNumeProprietar()<<'\n';
    out<<"Suprafata: "<<locatar.getSuprafata()<<'\n';
    out<<"Tip: "<<locatar.getTip()<<'\n';
}

void ConsoleUI::adauga(istream & in, ostream & out) {
    TypeApartament apartament;
    TypeNume nume;
    TypeTip tip;
    TypeSuprafata suprafata;
    readLocatar(in, out, apartament, nume, suprafata, tip);
    try{service.add(apartament, nume, suprafata, tip);}
    catch(MyException& me) { out<<me; return;}
    out<<"Operatie efectuata cu succes!\n";
}

void ConsoleUI::sterge(istream &in, ostream &out) {
    TypeApartament apartament;
    TypeNume nume;
    TypeTip tip;
    TypeSuprafata suprafata;
    readLocatar(in, out, apartament, nume, suprafata, tip);
    try{service.remove(apartament, nume, suprafata, tip);}
    catch(MyException& me) { out<<me; return;}
    out<<"Operatie efectuata cu succes!\n";
}

void ConsoleUI::modifica(istream & in, ostream & out) {
    TypeApartament apartament1, apartament2;
    TypeNume nume1, nume2;
    TypeTip tip1, tip2;
    TypeSuprafata suprafata1, suprafata2;
    readLocatar(in, out, apartament1, nume1, suprafata1, tip1);
    readLocatar(in, out, apartament2, nume2, suprafata2, tip2);
    try{ service.modify(apartament1, nume1, suprafata1, tip1,
                        apartament2, nume2, suprafata2, tip2);}
    catch(MyException& me) { out<<me; return;}
    out<<"Operatie efectuata cu succes!\n";
}

void ConsoleUI::afisare(ostream & out) {
    if(service.end() - service.begin() == 0) out<<"Nu exista astfel de elemente!\n";
    for(const auto& elem : service)
        writeLocatar(out, elem);
}

void ConsoleUI::cautaApartament(istream & in, ostream & out) {
    TypeApartament apartament;
    out<<"Introduceti numarul apartamentului: ";
    in >> apartament;
    Locatar locatar;
    try{ locatar = service.findApartament(apartament);}
    catch(MyException& me) { out<<me; return;}
    writeLocatar(out, locatar);
}

void ConsoleUI::filtrare(istream & in, ostream & out) {
    out<<"Introduceti filtrul(tip/suprafata): ";
    string cmd;
    in>>cmd;
    if(cmd == "tip"){
        TypeTip tip;
        out<<"Introduceti tipul: "; in >> tip;
        Repository<Locatar> rez;
        try{rez = service.filterTip(tip); }
        catch(MyException& me) { out<<me; return;}
        if(rez.size() == 0) out<<"Nu exista astfel de elenmente!\n";
        for(const auto& elem : rez)
            writeLocatar(out, elem);
    }
    else if(cmd == "suprafata"){
        TypeSuprafata suprafata;
        out<<"Introduceti suprafata: "; in >>suprafata;
        Repository<Locatar> rez;
        try{rez = service.filterSuprafata(suprafata); }
        catch(MyException& me) { out<<me; return;}
        if(rez.size() == 0) out<<"Nu exista astfel de elenmente!\n";
        for(const auto& elem : rez)
            writeLocatar(out, elem);
    }
    else out<<"Filtru invalid!\n";
}

void ConsoleUI::sortare(istream & in, ostream & out) {
    out<<"\tSortati dupa:\n"
         "1. Nume proprietar\n"
         "2. Suprafata\n"
         "3. Tip apartament si suprafata\n";
    string cmd; in>>cmd;
    if(cmd=="1") {
        service.sortNume();
    }
    else if(cmd == "2"){
        service.sortSuprafata();
    }
    else if(cmd == "3"){
        service.sortTipSuprafata();
    }
    else {
        out<<"Optiune invalida!\n";
        return;
    }
    afisare(out);
}

void ConsoleUI::run(istream & in, ostream & out) {
    while (true){
        system("cls");
        printMenu(out);
        out<<"\nIntroduceti comanda: ";
        string cmd;
        in>>cmd;
        if(cmd=="1") adauga(in, out);
        else if(cmd=="2") sterge(in, out);
        else if(cmd=="3") modifica(in, out);
        else if(cmd=="4") afisare(out);
        else if(cmd=="5") cautaApartament(in, out);
        else if(cmd=="6") filtrare(in, out);
        else if(cmd=="7") sortare(in, out);
        else if(cmd=="8") break;
        else out<<"Comanda invalida!\n";
        system("pause");
    }
}



