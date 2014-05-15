template<class R,class... Parms>
struct vtable_caller{
	static R call_vtable_func(const detail::ptr_fun_void_t pFun,const portable_base* v,Parms... p){
		typename cross_conversion_return<R>::return_type r;
		typename cross_conversion_return<R>::converted_type cret;
		cross_conversion_return<R>::initialize_return(r,cret);
		auto ret =  detail::call<error_code,const portable_base*, typename cross_conversion<Parms>::converted_type..., cret_t*>(pFun,
				v,cross_conversion<Parms>::to_converted_type<Parms>(p)...,&cret);
		if(ret < 0){
			error_mapper<Iface>::mapper::exception_from_error_code(ret);
		}
		ccr::finalize_return(r,cret);
		return r;
	}

};

namespace detail{

	// Helper functions to cast a vtable function to the correct type and call it
	template<class R, class... Parms>
		R call(const ptr_fun_void_t pFun,Parms... p){
			typedef R( CROSS_CALL_CALLING_CONVENTION *fun_t)(Parms...);
			auto f = reinterpret_cast<fun_t>(pFun);
			return f(p...);
		}
