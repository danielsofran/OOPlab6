//
// Created by Daniel on 26.03.2022.
//

#include "service.h"

void Service::add(const TypeApartament & apartament, const TypeNume & numeproprietar, const TypeSuprafata & suprafata, const TypeTip & tip) {
    Locatar locatar{apartament, numeproprietar, suprafata, tip};
    ValidatorLocatar::validLocatar(locatar);
    auto it = std::find(repository.begin(), repository.end(), locatar);
    if(it != end()) throw RepoException("Element duplicat!\n");
    repository.push_back(locatar);
}

void Service::remove(const TypeApartament & apartament, const TypeNume & numeproprietar, const TypeSuprafata & suprafata, const TypeTip & tip) {
    Locatar locatar{apartament, numeproprietar, suprafata, tip};
    ValidatorLocatar::validLocatar(locatar);
    auto it = std::find(repository.begin(), repository.end(), locatar);
    if(it == end()) throw RepoException("Elementul nu exista!\n");
    repository.erase(it);
}

void Service::modify(const TypeApartament & apartament1,
                     const TypeApartament & apartament2, const TypeNume & nume2, const TypeSuprafata & suprafata2, const TypeTip & tip2) {
    Locatar locatar{apartament2, nume2, suprafata2, tip2};
    ValidatorLocatar::validLocatar(locatar);
    ValidatorLocatar::validApartament(apartament1);
    auto it = std::find_if(begin(), end(), [&apartament1](const Locatar& l) {return l.getApartament() == apartament1;});
    if(it == end()) throw RepoException("Elementul nu a fost gasit!\n");
    *it = locatar;
}

const Locatar& Service::findApartament(const TypeApartament & apartament) {
    ValidatorLocatar::validApartament(apartament);
    const auto& it = std::find_if(begin(), end(), [&apartament](const Locatar& l){return l.getApartament() == apartament; });
    if(it == cend()) throw ServiceException("Apartamentul dat nu exista!\n");
    return *it;
}

vector<Locatar> Service::filterTip(const TypeTip & tip) {
    ValidatorLocatar::validTip(tip);
    vector<Locatar> rez;
    auto pred = [&tip](const Locatar &l)
            { return l.getTip() == tip; };
    auto it = std::find_if(begin(), end(), pred);
    while(it != end())
    {
        rez.push_back(*it);
        it = std::find_if(it+1, end(), pred);
    }
    return rez;
}

vector<Locatar> Service::filterSuprafata(const TypeSuprafata & suprafata) {
    ValidatorLocatar::validSuprafata(suprafata);
    vector<Locatar> rez;
    auto pred = [&suprafata](const Locatar &l)
            { return l.getSuprafata() == suprafata; };
    auto it = std::find_if(begin(), end(), pred);
    while(it != end())
    {
        rez.push_back(*it);
        it = std::find_if(it+1, end(), pred);
    }
    return rez;
}

void Service::sortNume() {
    auto cmp = [](const Locatar& l1, const Locatar& l2)
    {
        return l1.getNumeProprietar() < l2.getNumeProprietar();
    };
    std::sort(begin(), end(), cmp);
}

void Service::sortSuprafata() {
    auto cmp = [](const Locatar& l1, const Locatar& l2)
    {
        return l1.getSuprafata() < l2.getSuprafata();
    };
    std::sort(begin(), end(), cmp);
}

void Service::sortTipSuprafata() {
    auto cmp = [](const Locatar& l1, const Locatar& l2)
    {
        return  l1.getTip() < l2.getTip() ||
            (l1.getTip() == l2.getTip() && l1.getSuprafata() < l2.getSuprafata());
    };
    std::sort(begin(), end(), cmp);
}

vector<Locatar>::iterator Service::begin() {return repository.begin();}
vector<Locatar>::const_iterator Service::cbegin() const {return repository.cbegin();}
vector<Locatar>::iterator Service::end() {return repository.end();}
vector<Locatar>::const_iterator Service::cend() const {return repository.cend();}

void Service::addNotificare(const int & nrap) {
    auto it = std::find_if(repository.begin(), repository.end(), [&nrap](const Locatar& l){return l.getApartament() == nrap; });
    if(it == end()) throw ServiceException("Apartament inexistent!\n");
    listanotificare.push_back(*it);
}

void Service::clearNotificari() {
    listanotificare.clear();
}

void Service::generateNotificari(const int & nr) {
    if(nr<0) throw ServiceException("Imposibil de generat un numar negativ de apartamente!\n");
    listanotificare.clear();
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, (int)repository.size()-1);
    std::set<int> used;
    //int rndNr = dist(mt);// numar aleator intre [0,size-1]
    listanotificare = vector<Locatar>(nr);
    for(int ind=0;ind<nr;++ind) {
        int i;
        while(used.find((i=dist(mt))) != used.end());
        listanotificare[ind] = repository[i];
        used.insert(i);
        if(used.size() == repository.size())
            used.clear();
    }
}

void Service::exportNotificariHTML(const string& filename) {
    std::ifstream fin("OwnFiles/LocatariTemplate.html");
    string text, line;
    while(fin){
        getline(fin, line);
        text += line + "\n";
    }
//    std::ostringstream out;
//    string line;
//    while(getline(fin>>std::noskipws, line))
//        out<<line<<'\n';
    string htmlcontent;
    for(const auto& locatar : listanotificare)
    {
        std::ostringstream out2;
        out2<<"<Locatar nrap={"<<locatar.getApartament()
            <<"} nume=\""<<locatar.getNumeProprietar()
            <<"\" suprafata={"<<locatar.getSuprafata()
            <<"} tip=\""<<locatar.getTip()<<"\"/>\n";
        htmlcontent += out2.str();
    }
    text = std::regex_replace(text, std::regex("!REPLACE_LOCATARI!"), htmlcontent);
    std::ofstream fout("OwnFiles/"+filename+".html");
    fout<<std::noskipws<<text;
    fout.close();
    fin.close();
}

void Service::exportNotificariCSV(const string& filename) {
    std::ofstream fout("OwnFiles/"+filename+".csv");
    char sep=';';
    for(const auto& locatar : listanotificare)
        fout<<locatar.getApartament()<<sep
            <<locatar.getNumeProprietar()<<sep
            <<locatar.getSuprafata()<<sep
            <<locatar.getTip()<<"\n";
    fout.close();
}


