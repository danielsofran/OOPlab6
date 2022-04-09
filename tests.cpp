//
// Created by Daniel on 25.03.2022.
//

#include "tests.h"

class TestDomain : public ITest
{
protected:
    void ctors() override{
        Locatar l1;
        Locatar l2(10, "Ion", 200, "apartament");
        Locatar l3(l2);
    }

    void getters() override{
        Locatar l2(10, "Ion", 200, "apartament");
        assert(l2.getTip() == "apartament");
        assert(l2.getApartament() == 10);
        assert(l2.getNumeProprietar() == "Ion");
        assert(l2.getSuprafata() == 200);
    }

    void setters() override{
        Locatar l1;
        assert(l1 == Locatar());
        l1.setTip("apartament");
        l1.setApartament(10);
        l1.setNumeProprietar("Ion");
        l1.setSuprafata(200);
        assert(l1 == Locatar(10, "Ion", 200, "apartament"));
    }

    void operators() override{
        Locatar l1;
        assert(l1 == Locatar());
        Locatar l2(10, "Ion", 200, "apartament");
        Locatar l3(l2);
        assert( l3 != l1);
        l1.setApartament(5);
        assert(l1 < l2);
        assert(l1 <= l2);
        assert(l2 > l1);
        assert(l2 >= l1);
        std::strstream sout;
        sout<<l2;
        sout>>l2;
        assert(l3 == l2);
    }
};

class TestRepository : public ITest{
protected:
    void ctors() override {
        Repository<int> repository;
        assert(repository.size()==0);
        repository.elements[0] = 2;
        repository.dim = 1;
        Repository<int> r2(repository);
        assert(r2.capacity == repository.capacity);
        assert(r2.size() == 1);
    }
    void add() override{
        Repository<int> repository;
        repository.add(1);
        assert(repository.size() == 1);
        repository.add(2);
        assert(repository.size() == 2);
        try{ repository.add(1); assert(false); }
        catch(RepoException& re) {}
    }
    void find() override{
        Repository<int> repository;
        repository.add(1);
        repository.add(2);
        auto it = repository.find(2);
        assert(*it == 2);
        assert( repository.find(2, it+1) == NULL);
        it = repository.find(3);
        assert(it == nullptr);
        it = repository.find([](const int& a){return !(a&1);});
        assert(*it == 2);
        assert(repository.find([](const int& a){return !(a&1);}, nullptr, it) == nullptr);
        it = repository.find([](const int& a){return a>10;});
        assert(it == nullptr);
    }
    void remove() override{
        Repository<int> repository;
        repository.add(1);
        repository.add(2);
        repository.remove(2);
        assert(repository.size() == 1);
        assert(repository[0] == 1);
        try {repository.remove(2); assert(false); }
        catch(RepoException& re) {}
        int elem = repository.remove([](const int& x){return x < 2;});
        assert(elem == 1);
        assert(repository.size() == 0);
    }
    void methods() override{
        Repository<int> repository;
        repository.add(2);
        repository.add(1);
        repository.sort();
        assert(repository[0]==1);
        assert(repository[1]==2);
        repository.sort([](const int& a, const int& b){return a > b;});
        assert(repository[0]==2);
        assert(repository[1]==1);
    }
    void getters() override{
        Repository<int> repository;
        int a=1, b=2;
        repository.add(a);
        repository.add(b);
        for(int x : repository){}
        for(int& x : repository){}
        for(const int x: repository){}
        for(const int& x: repository){}
        for(auto x : repository){}
        for(auto& x : repository){}
        for(const auto x: repository){}
        for(const auto& x: repository){}
    }
};

class TestService : public ITest{
private:
    static int lg(const Service& s) { return (int)(s.cend() - s.cbegin()); }
    static void init(Service& s, Locatar& l1, Locatar& l2, Locatar& l3)
    {
        l1 = Locatar {32, "Andi", 200, "apartament"};
        l2 = Locatar {13, "Ioana", 130, "apartament"};
        l3 = Locatar {13, "Ioana", 7, "apartament"};
        s.add(32, "Andi", 200, "apartament");
        s.add(13, "Ioana", 130, "apartament");
        s.add(13, "Ioana", 7, "apartament");
    }
    static bool equals(const Service& s, const Locatar& l1, const Locatar& l2, const Locatar& l3)
    {
        return  *(s.cbegin()) == l1 &&
                *(s.cbegin()+1) == l2 &&
                *(s.cbegin()+2) == l3;
    }
protected:
    void add() override{
        Service s;
        assert(lg(s) == 0);
        s.add(32, "Andi", 200, "apartament");
        assert(lg(s) == 1);
        s.add(13, "Ioana", 130, "apartament");
        assert(lg(s) == 2);
        try{ s.add(32, "Andi", 200, "apartament"); assert(false);}
        catch(RepoException& re) {}
    }
    void remove() override{
        Service s;
        s.add(32, "Andi", 200, "apartament");
        s.add(13, "Ioana", 130, "apartament");
        s.remove(32, "Andi", 200, "apartament");
        assert(lg(s) == 1);
        try{s.remove(32, "Andi", 200, "apartament"); assert(false); }
        catch(RepoException& re){}
        try{s.remove(12, "Ioana", 130, "apartament"); assert(false); }
        catch(RepoException& re){}
        s.remove(13, "Ioana", 130, "apartament");
        assert(lg(s) == 0);
        try{s.remove(32, "Andi", 200, "apartament"); assert(false); }
        catch(RepoException& re){}
    }
    void methods() override{
        Service s;
        s.add(32, "Andi", 200, "apartament");
        s.add(13, "Ioana", 130, "apartament");
        s.modify(13, "Ioana", 130, "apartament", 13, "Ioana Pir", 130, "apartament");
        assert(*(s.begin()+1) == Locatar(13, "Ioana Pir", 130, "apartament"));
        try{s.modify(1, "Ioana", 130, "apartament", 13, "Ioana Pir", 130, "apartament"); assert(false);}
        catch(RepoException&){}
        try{s.modify(-1, "Ioana", 130, "apartament", 13, "Ioana Pir", 130, "apartament"); assert(false);}
        catch(ValidatorException&){}
        try{s.modify(1, "Ioana", 130, "apartament", 13, "Ioana Pir", -130, "apartament"); assert(false);}
        catch(ValidatorException&){}
    }
    void find() override{
        Service s;
        Locatar l1, l2, l3;
        init(s, l1, l2, l3);
        Locatar l = s.findApartament(32);
        assert(l == Locatar(32, "Andi", 200, "apartament"));
        try{ s.findApartament(23); assert(false);}
        catch (ServiceException& se) {}
        l = s.findApartament(13);
        assert(l == Locatar(13, "Ioana", 130, "apartament"));
        s.remove(13, "Ioana", 130, "apartament");
        l = s.findApartament(13);
        assert(l == Locatar(13, "Ioana", 7, "apartament"));
    }
    void filter() override{
        Service s;
        Locatar l1, l2, l3;
        init(s, l1, l2, l3);
        Repository<Locatar> filtrutip{s.filterTip("apartament")};
        assert(filtrutip.size() == 3);
        Repository<Locatar> filtrusupr{s.filterSuprafata(130)};
        assert(filtrusupr[0] == l2);
        Repository<Locatar> filtrutip2{s.filterTip("garsoniera1")};
        assert(filtrutip2.size() == 0);
    }
    void sort() override{
        Service s;
        Locatar l1, l2, l3;
        init(s, l1, l2, l3);
        s.sortNume();
        assert(equals(s, l1, l2, l3));
        s.sortSuprafata();
        assert(equals(s, l3, l2, l1));
        s.sortTipSuprafata();
        assert(equals(s, l3, l2, l1));
    }
    void getters() override{
        Service s;
        Locatar l1, l2, l3;
        init(s, l1, l2, l3);
        for(Locatar x : s){}
        for(Locatar& x : s){}
        for(const Locatar x: s){}
        for(const Locatar& x: s){}
        for(auto x : s){}
        for(auto& x : s){}
        for(const auto x: s){}
        for(const auto& x: s){}
    }
};

class TestExceptions : public ITest{
protected:
    void ctors() override{
        try {throw MyException("12");}
        catch(MyException& ex){ assert(strcmp(ex.what(), "12")==0);}
        try {throw RepoException("12");}
        catch(RepoException& ex){ assert(strcmp(ex.what(), "12")==0);}
        try {throw ServiceException("12");}
        catch(ServiceException& ex){ assert(strcmp(ex.what(), "12")==0);}
        try {throw InvalidFieldException("12");}
        catch(InvalidFieldException& ex){ assert(strcmp(ex.what(), "12")==0);}

        ValidatorException ve;
        InvalidFieldException ie("ex");
        vector<InvalidFieldException> vct{ie};
        ValidatorException ve2(vct);
        ValidatorException ve3(ve2);
        MyException me(ve); // testez pofimorfism
        assert(strcmp(me.what(), ve.what()) == 0);
        assert(strcmp(ve3.what(), ve2.what()) == 0);
    }
    void operators() override{
        ValidatorException ve, data;
        InvalidFieldException ie("ex");
        vector<InvalidFieldException> vct{ie};
        ValidatorException ve2(vct); // 1
        ValidatorException ve3(ve2); // 1
        assert((int)data == 0);
        data = ve2 + ve3;
        assert((int)data == 2);
        data = ve2 + ie;
        assert((int)data == 2);
        data = ve2 + "Eroare la afisare!";
        assert((int)data == 2);
        ve2 += ve3;
        ve2 += ie;
        ve2 += "Eroare la afisare!";
        std::ostrstream out;
        out<<ve2 + "rip";
    }
};

class TestValidator : public ITest{
protected:
    void methods() override{
        Locatar l(12, "Andrei Mirun", 25, "apartament");
        ValidatorLocatar::validLocatar(l);
        try {ValidatorLocatar::validApartament(-12);assert(false);}
        catch(InvalidFieldException&){}
        try {ValidatorLocatar::validSuprafata(-23);assert(false);}
        catch(InvalidFieldException&){}
        try {ValidatorLocatar::validNume("Dac @"); assert(false);}
        catch(InvalidFieldException&){}
        try {ValidatorLocatar::validTip("tip2#");assert(false);}
        catch(InvalidFieldException&){}
        Locatar l2(-12, "324324v3 #$#@$", -5, "2783682737sf%R%^");
        try{ValidatorLocatar::validLocatar(l2);assert(false);}
        catch(ValidatorException& ve) { assert((int)ve == 4); }
    }
};

void test()
{
    TestDomain().run();
    TestRepository().run();
    TestService().run();
    TestExceptions().run();
    TestValidator().run();
    std::cout<<"Tests done!\n";
}