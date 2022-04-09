#include <fstream>
#include "tests.h"
#include "uiconsole.h"

int main() {
    test();
    ConsoleUI console;
    //console.run();
    Service s;
    for(int i=1;i<=50;++i)
    {
        s.add(i, "Nume"+std::to_string(i), i*100, (i%4==0)?("apartament"):("garsoniera"));
    }
    std::ofstream fout("add50.txt");
    for(const auto& elem : s)
    {
        fout<<elem<<'\n';
    }
    fout.close();
    return 0;
}
