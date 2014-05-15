#define CPPCOMPONENTS_DEFINE_FACTORY() \
	extern "C"{ \
CROSS_CALL_EXPORT_FUNCTION cppcomponents::error_code CROSS_CALL_CALLING_CONVENTION  get_cppcomponents_factory(const char* s, \
		cppcomponents::portable_base** p){ \
	return cppcomponents::get_activation_factory(std::string(s), p); \
}\
CROSS_CALL_EXPORT_FUNCTION cppcomponents::error_code CROSS_CALL_CALLING_CONVENTION  cppcomponents_module_in_use(){ \
	if (cross_compiler_interface::object_counter::get().get_count() == 0) return 0; \
	else return 1; \
}\
CROSS_CALL_EXPORT_FUNCTION cppcomponents::error_code CROSS_CALL_CALLING_CONVENTION  cppcomponents_module_initialize(cppcomponents::portable_base* p){ \
	return cppcomponents::detail::module_intialize(p); \
}\
}
