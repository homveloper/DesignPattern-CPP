#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Journal
{
    string title;
    vector<string> entries;

    Journal(const string&title) : title(title){}

    void AddEntry(const string& entry)
    {
        static int count = 1;
        entries.emplace_back(lexical_cast<string>(count++) + ": " + entry);
    }
};


struct PersistenceManager
{
    // Journal은 데이터를 가진 구조체이므로, 그 자체로 Save 기능을 가져서는 안된다.
    // PersistenceManager를 통해 저장기능을 분리하여 구현하는 것이 좋다.
    static void Save(const Journal& journal, const string& filename)
    {
        ofstream ofs(filename);
        for(auto& e : journal.entries)
            ofs<<e<<endl;
    }
};

int main()
{
    Journal journal{"Dear Diary"};
    journal.AddEntry("I ate a bug");
    journal.AddEntry("I cried today");

    PersistenceManager::Save(journal, "SOLID/diary.txt");

    return 0;
}