#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Document
{

};

struct IMachine
{
    virtual void Print(Document& doc) = 0;
    virtual void Scan(Document& doc) = 0;
    virtual void Fax(Document& doc) = 0;
};

struct MultiFuntionalPrinter : IMachine
{
    void Print(Document& doc) override 
    {

    }
};

struct Scanner : IMachine
{
    void Scan(Document& doc) override
    {

    }
};

struct IPrinter
{
    virtual void Print(Document& doc) = 0;
};

struct IScanner
{
    virtual void Scan(Document& doc) = 0;
};

struct IFax
{
    virtual void Fax(Document& doc) = 0;
};

struct Printer : IPrinter
{

};

struct Sanner : IScanner
{

};


struct IMachine : IPrinter, IScanner
{

};

struct Machine : IMachine
{
    IScanner& scanner;
    IPrinter& printer;

    Machine(IPrinter& printer, IScanner& scanner) : printer(printer), scanner(scanner){}

    void Print(Document& doc) override
    {
        printer.Print(doc);
    }

    void Scan(Document& doc) override
    {
        scanner.Scan(doc);
    }
};

int main()
{

}