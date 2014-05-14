#include "Person.h"

struct ImplementPerson:cppcomponents::implement_runtime_class<ImplementPerson,Person_rt>
{

    std::string name_;
    std::string GetName(){return name_;}
    void SetName(std::string s){name_ = s;}

};

CPPCOMPONENTS_REGISTER(ImplementPerson)

CPPCOMPONENTS_DEFINE_FACTORY()


