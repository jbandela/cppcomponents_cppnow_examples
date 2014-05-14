#include <iostream>
#include "Person.h"

int main(){
  Person p{"John"};
  std::cout << p.GetName() << "\n";
  p.SetName("John2"); 
  std::cout << p.GetName() << "\n";

}
