// This handles all vtable entries
template<int N,class ... Parms>
struct vtable_entry{

  template<class C, class MF, MF mf, class R>
    static error_code CROSS_CALL_CALLING_CONVENTION func(const portable_base* v,typename cross_conversion<Parms>::converted_type... p, typename cross_conversion_return<R>::converted_type* r){
      try{
        const vtable_n_base* vt = static_cast<const vtable_n_base*>(v);

        C* f = static_cast<C*>(vt->pdata[n]);
        cross_conversion_return<R::do_return((f->*mf)(cross_conversion<Parms>::to_original_type(p)...),*r);
        return 0;
      } catch(std::exception& e){
        return error_mapper<Iface>::mapper::error_code_from_exception(e);
      }
    }
};
