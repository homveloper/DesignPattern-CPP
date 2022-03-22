#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product
{
    string name;
    Color color;
    Size size;
};

/*
    Product를 필터링 하기 위한 클래스이지만,
    필요한 요구 사항들이 점점 늘어나고 복잡해질수록 
    작성해야 되는 코드양이 많아 지고, 내부 구조 또한 복잡해지게 된다.

    예를 들어 지금은 Product가 3개의 멤버 밖에 없어서
    ByColor, BySize 등등의 함수 밖에 나타나지 않을 수 있지만
    Product의 멤버 변수가 점점 늘어나게 되면 
    ProductFilter도 그에 따라 클래스의 크기가 방대해지게 된다.
*/
struct ProductFilter
{
    vector<Product*> ByColor(vector<Product*> items, Color color)
    {
        vector<Product*> result;
        for(auto& i : items)
        {
            if(i->color == color){
                result.emplace_back(i);
            }
        }
        return result;
    }

    vector<Product*> BySize(vector<Product*> items, Size size)
    {
        vector<Product*> result;
        for(auto& i : items)
        {
            if(i->size == size){
                result.emplace_back(i);
            }
        }
        return result;
    }
};

/*
    이러한 문제는 인터페이스를 통해 해결할 수 있다.
    필터링을 위한 인터페이스를 구성하고, 필터에 사용될
    함수 또한 인터페이스로 두는 것이다.
*/

template <typename T> struct AndSpecification;

template <typename T> struct Specification
{
    virtual bool IsSatisfied(T* item) = 0;

    // AndSpecification을 구현이 되있으므로 && 연산자를 통한 추가가 가능합니다.
    AndSpecification<T> operator&&(Specification<T>&& other)
    {
        return AndSpecification<T>(*this, other);
    }
};

template <typename T> struct Filter
{
    virtual vector<T*> Filtered(vector<T*> items, Specification<T>& spec)=0;
};

struct BetterFilter : Filter<Product>
{
    vector<Product*> Filtered(vector<Product*> items, Specification<Product>& spec)
    {
        vector<Product*> result;

        for(auto& item : items)
        {
            if(spec.IsSatisfied(item))
            {
                result.emplace_back(item);
            }
        }
        return result;
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color;
    explicit ColorSpecification(Color color) : color(color){}

    bool IsSatisfied(Product *item) override{
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size;
    explicit SizeSpecification(Size size) : size(size){}

    bool IsSatisfied(Product *item) override{
        return item->size == size;
    }
};

/*
    복수의 조건을 가진 데이터를 필터링 해야 될 때는 어떻게 해야될까?

*/
template <typename T> struct AndSpecification : Specification<T>
{
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T> &first, Specification<T> &second) : first(first), second(second){}

    bool IsSatisfied(T *item) override{
        return first.IsSatisfied(item) && second.IsSatisfied(item);
    }
};


int main()
{
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    vector<Product*> items {&apple, &tree, &house};

    // 좋지 않는 방법
    
    /*
    ProductFilter pf;
    auto green_things = pf.ByColor(items, Color::green);
    for(auto& item : green_things)
    {
        cout<<item->name<<endl;
    }
    */

    // 좋은 방법
    BetterFilter betterFilter;
    ColorSpecification greenSpec(Color::green);
    for(auto& item : betterFilter.Filtered(items, greenSpec))
    {
        cout<<item->name<<endl;
    }

    // 복수의 멤버를 필터링 하는 방법
    SizeSpecification largeSpec(Size::large);
    AndSpecification<Product> largeAndGreenSpec(greenSpec, largeSpec);
    for(auto& item : betterFilter.Filtered(items, largeAndGreenSpec))
    {
        cout<<item->name<<endl;
    }

    auto spec = ColorSpecification(Color::green) && SizeSpecification(Size::large);
    for(auto& item : betterFilter.Filtered(items, spec))
    {
        cout<<item->name<<endl;
    }
}