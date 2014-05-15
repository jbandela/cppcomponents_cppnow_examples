
struct ITestTemplatedConstructorFactory : cppcomponents::define_interface < cppcomponents::uuid<0x9adbd21b, 0x5ef7, 0x4a3c, 0x8c0c, 0xb07d78428939>>
{
  typedef cppcomponents::delegate < int()> IntDelegate;
  cppcomponents::use<cppcomponents::InterfaceUnknown> Create(cppcomponents::use<IntDelegate>);

  CPPCOMPONENTS_CONSTRUCT(ITestTemplatedConstructorFactory, Create)

  CPPCOMPONENTS_INTERFACE_EXTRAS(ITestTemplatedConstructorFactory){
      template<class F>
      cppcomponents::use<cppcomponents::InterfaceUnknown> TemplatedConstructor(F f){
	  return this->get_interface().Create(cppcomponents::make_delegate<IntDelegate>(f));
	}

    };

};

struct StaticInterface3 : public cppcomponents::define_interface < cppcomponents::uuid<0xF2CE950A, 0xB826, 0x4354, 0xA07C, 0xD17431323C26>> {


  std::string GetStaticString();
  std::string GetStaticString2(cppcomponents::string_ref s);


  cppcomponents::use<ComponentInterface> GetTestComponent();


  CPPCOMPONENTS_CONSTRUCT(StaticInterface3,GetStaticString,GetTestComponent,GetStaticString2)


    CPPCOMPONENTS_STATIC_INTERFACE_EXTRAS(StaticInterface3){
      static std::string OtherGetStaticString(){
	return Class::GetStaticString();
      }
    };
};
