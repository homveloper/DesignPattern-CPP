#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
리스코프 치환 원칙

리스코프 치환 원칙의 목표는 하위 타입이 기본 타입을 즉시 대체할 수 있어야 한다는 것이다. 

즉, 다형성 개념을 소개하고 있다.

*/

class Rectangle
{
protected:
    int width, height;
public:
    Rectangle(int width, int height) : width(width), height(height){}

    int GetWidth() const {return width;}
    virtual void SetWidth(int width) {Rectangle::width = width;}

    int GetHeight() const {return height;}
    virtual void SetHeight(int height) {Rectangle::height = height;}

    int Area() const {return width * height;}
};

class Square : public Rectangle
{
public:
    Square(int size) : Rectangle(size, size){}

    void SetWidth(int width) override{
        this->width = this->height = width;        
    }

    void SetHeight(int height) override{
        this->height = this->width = height;        
    }
};

void process(Rectangle& r)
{
    int w = r.GetWidth();
    r.SetHeight(10);

    cout<<"expected area ="<<(w*10)
        <<", got "<<r.Area()
        <<endl;
}

struct RectangleFactory
{
    static Rectangle CreateRectangle(int width, int height);
    static Rectangle CreateSquare(int size);
};

int main()
{
    Rectangle r{3,4};
    process(r);

    // 정사각형은 width, height가 동일해야 하기에
    // 예상한 결과와 다른 결과가 나오게 된다.
    Square sq{5};
    process(sq);
}