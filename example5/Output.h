#include <cppcomponents/cppcomponents.hpp>

struct IOutput: cppcomponents::define_interface<cppcomponents::uuid<0xed5d3f5c, 0x1957, 0x4b8c, 0xb66c, 0x6ed9f0b5687e>>
{
    void PrintString(std::string s);

    CPPCOMPONENTS_CONSTRUCT(IOutput,PrintString)
};

inline const char* OutputId(){return "Output";}

typedef cppcomponents::runtime_class<OutputId,cppcomponents::static_interfaces<IOutput>> Output_rt;

typedef cppcomponents::use_runtime_class<Output_rt> Output;


