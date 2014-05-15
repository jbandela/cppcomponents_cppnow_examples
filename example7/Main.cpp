#include <iostream>
#include "Dynamic.h"
#include <map>
#include <vector>
#include <boost/algorithm/string.hpp>

std::map<std::string,cppcomponents::use<ICBN>> m;

void load_modules(const std::vector<std::string>& v){
  for(auto& s:v){
    try{
      m[s] = CBN::static_interface(s,CBNId()).GetCBN();
    }
    catch(...){
      std::cout << "Unable to load library " << s << "\n";
    }

  }

}

void call_function(const std::string& name){
   try{
   	std::vector<std::string> vec;
	boost::algorithm::split(vec,name,boost::is_any_of("."));
        auto iter = m.find(vec.at(0));
	if(iter == m.end()){
	  std::cout << "Invalid library name\n";
	  return;
	}
	auto ic = iter->second;

	int argc = 0;
	std::vector<std::string> args;
	std::cout << "Enter argument count\n";
	std::cin >> argc;
	std::string line;
	std::getline(std::cin,line);
        for(int i = 0;i < argc; ++i){
	    std::getline(std::cin,line);
	    boost::algorithm::trim(line);
	    args.push_back(line);
	}
	std::cout << "The result is " << ic.Call(vec.at(1),args) << "\n";
        

   }
   catch(...){
      std::cout << "Error calling function " << name << "\n";
   }

}




int main(){
  std::string line;
  std::vector<std::string> modules;
  std::cout << "Enter names of modules on on each line. Enter empty line at end\n";

  std::getline(std::cin,line);
  boost::algorithm::trim(line);
  while(line.empty() ==false){
      modules.push_back(line);
      std::getline(std::cin,line);
      boost::algorithm::trim(line);


  }
  load_modules(modules);

  std::cout << "Enter function to call, blank line to end\n";
  std::getline(std::cin,line);
  boost::algorithm::trim(line);

  while(line.empty() ==false){
     call_function(line);
     std::cout << "Enter function to call, blank line to end\n";
     std::getline(std::cin,line);
     boost::algorithm::trim(line);
  }

}
