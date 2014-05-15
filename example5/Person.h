#include <cppcomponents/cppcomponents.hpp>


struct IPerson:cppcomponents::define_interface<cppcomponents::uuid<0x6c365014,0x1bf9,0x4af8,0x863b,0x07a4bdf69c46 >>
{
	std::string GetName();
	void SetName(std::string);
	void SayHello();

	CPPCOMPONENTS_CONSTRUCT(IPerson,GetName,SetName,SayHello)


};

inline const char* PersonId(){return "Person!Person";}
typedef cppcomponents::runtime_class<PersonId,cppcomponents::object_interfaces<IPerson>> Person_rt;
typedef cppcomponents::use_runtime_class<Person_rt> Person;


