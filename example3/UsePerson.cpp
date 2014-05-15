#include <iostream>
#include "Person.h"

int main(){
  Person p{"John"};
  std::cout << p.GetName() << "\n";
   
  Person p2{"John2"}; 
  std::cout << p2.GetName() << "\n";

  std::cout << "Population: " << Person::GetPopulation() << "\n";
}
