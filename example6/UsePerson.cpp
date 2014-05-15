#include <iostream>
#include "Person.h"

int main(){
  auto p1 = Person::dynamic_creator("Bandela",PersonId())();

  auto p2 = Person::dynamic_creator("Smith",PersonId())();
  p1.SetName("John");
  std::cout << p1.GetName() << "\n";
  p2.SetName("John");
  std::cout << p2.GetName() << "\n";
}
