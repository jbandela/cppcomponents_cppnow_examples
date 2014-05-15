#include "Dynamic.h"
#include <boost/algorithm/string.hpp>

struct IString:cppcomponents::define_interface<cppcomponents::uuid<0x081cc95c, 0xf624, 0x4392, 0xb0f3, 0x629d52c33bcd>>
{
    std::string Concat(std::string a, std::string b);
    std::string ToUpper(std::string s);

    CPPCOMPONENTS_CONSTRUCT(IString, Concat, ToUpper)

};

inline const char* StringId(){return "!String";}

typedef cppcomponents::runtime_class<StringId,cppcomponents::static_interfaces<IString>> String_rt;
typedef cppcomponents::use_runtime_class<String_rt> String;



struct ImplementString:cppcomponents::implement_runtime_class<ImplementString,String_rt>
{
   static std::string Concat(std::string a, std::string b){
       return a+b;
   }
   static std::string ToUpper(std::string s){
       boost::algorithm::to_upper(s);
       return s;
   }

};

CPPCOMPONENTS_REGISTER(ImplementString)


struct ImplementCBN:cppcomponents::implement_runtime_class<ImplementCBN,CBN_rt>
{

    static cppcomponents::use<ICBN> GetCBN(){
	return cppcomponents::make_call_by_name<ICBN>(String::static_interface());
    }

};

CPPCOMPONENTS_REGISTER(ImplementCBN)

CPPCOMPONENTS_DEFINE_FACTORY()


