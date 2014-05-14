#include <iostream>
#include "Person.h"

int main(){
  Person p;
  p.SetName("John");
  std::cout << p.GetName();

}
