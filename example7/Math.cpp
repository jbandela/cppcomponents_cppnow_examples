#include "Dynamic.h"

struct IMath:cppcomponents::define_interface<cppcomponents::uuid<0x8fe6ddb5, 0xd417, 0x4641, 0x8c47, 0x3f6dbc07f076>>
{
    uint32_t Add(uint32_t a, uint32_t b);

    CPPCOMPONENTS_CONSTRUCT(IMath, Add)

};

inline const char* MathId(){return "!Math";}

typedef cppcomponents::runtime_class<MathId,cppcomponents::static_interfaces<IMath>> Math_rt;
typedef cppcomponents::use_runtime_class<Math_rt> Math;



struct ImplementMath:cppcomponents::implement_runtime_class<ImplementMath,Math_rt>
{
   static uint32_t Add(uint32_t a, uint32_t b){
	return a+b;
   }

};

CPPCOMPONENTS_REGISTER(ImplementMath)


struct ImplementCBN:cppcomponents::implement_runtime_class<ImplementCBN,CBN_rt>
{

    static cppcomponents::use<ICBN> GetCBN(){
	return cppcomponents::make_call_by_name<ICBN>(Math::static_interface());
    }

};

CPPCOMPONENTS_REGISTER(ImplementCBN)

CPPCOMPONENTS_DEFINE_FACTORY()


