#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

// A.   고수준 모듈은 저수준 모듈을 의존해서는 안된다.
//      둘다 추상적으로 의존해야 한다.

// B.   추상화는 세부 사항에 의존해서는 안 됩니다.
//      세부사항은 추상화에 의존해야 한다.

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    string name;
};

struct RelationshipBrowser
{
    virtual vector<Person> FindAllChildrenOf(const string& name) = 0;
};

struct RelationShips : RelationshipBrowser    // Low-Level module
{
    vector<tuple<Person,Relationship,Person>> relations;

    void AddParentAndChild(const Person& parent, const Person& child)
    {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    vector<Person> FindAllChildrenOf(const string& name) override
    {
        vector<Person> result;
        for(auto&& [first, relation, second] : relations)
        {
            if(first.name == name && relation == Relationship::parent)
            {
                result.emplace_back(second);
            }
        }

        return result;
    }
};

struct Research     // High-Level
{
    Research(RelationshipBrowser& browser)
    {
        for(auto & child : browser.FindAllChildrenOf("John"))
        {
            cout<<"John has child called "<<child.name<<endl;
        }
    }
};

int main()
{
    Person parent{"John"};
    Person child1{"chris"}, child2{"Matt"};

    RelationShips relationships;
    relationships.AddParentAndChild(parent, child1);
    relationships.AddParentAndChild(parent, child2);

    Research _(relationships);

}
