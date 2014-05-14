#include "Person.h"

struct ImplementPerson:cppcomponents::implement_runtime_class<ImplementPerson,Person_rt>
{
    static std::int32_t count_;
    std::string name_;

    ImplementPerson(){++count_;}
    ImplementPerson(std::string name):name_(std::move(name)){++count_;}
    ~ImplementPerson(){--count_;}

    std::string GetName(){return name_;}
    void SetName(std::string s){name_ = s;}

    static std::int32_t GetPopulation(){return count_;}

};

std::int32_t ImplementPerson::count_ = 0;

CPPCOMPONENTS_REGISTER(ImplementPerson)

CPPCOMPONENTS_DEFINE_FACTORY()


