#include <cppcomponents/cppcomponents.hpp>
#include <cppcomponents/call_by_name.hpp>
#include <boost/lexical_cast.hpp>


typedef cppcomponents::uuid<0x61a960a1, 0x9a68, 0x45b9, 0x941a, 0x6ab2a20d1995> MyUuid;

namespace cppcomponents{
	template<class AnyType, class U>
	struct call_by_name_conversion<MyUuid,AnyType,U>{
		static U convert_from_any(const AnyType& t){
			return boost::lexical_cast<U>(t);
		}
		static AnyType convert_to_any(const U& u){
			return boost::lexical_cast<AnyType>(u);
		}
	};


}

typedef cppcomponents::ICallInterfaceByName<MyUuid, std::string> ICBN;

struct IGetCBN:cppcomponents::define_interface<cppcomponents::uuid<0x6c365014,0x1bf9,0x4af8,0x863b,0x07a4bdf69c46 >>
{
	cppcomponents::use<ICBN> GetCBN();

	CPPCOMPONENTS_CONSTRUCT(IGetCBN,GetCBN)


};

inline const char* CBNId(){return "CBN";}
typedef cppcomponents::runtime_class<CBNId,cppcomponents::static_interfaces<IGetCBN>> CBN_rt;
typedef cppcomponents::use_runtime_class<CBN_rt> CBN;


