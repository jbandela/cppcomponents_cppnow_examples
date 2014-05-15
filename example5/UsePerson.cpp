#include <iostream>
#include "Person.h"
#include "Output.h"

struct ImplementOutput:cppcomponents::implement_runtime_class<ImplementOutput,Output_rt>
{
    static void PrintString(std::string s){
        std::cout << s;
    }


};

CPPCOMPONENTS_REGISTER(ImplementOutput)


int main(){
  Person p;
  p.SetName("John");
  p.SayHello();
}
