template<class charT>
struct cross_string{
  const charT* begin;
  const charT* end;
}CROSS_COMPILER_INTERFACE_PACK;


template<class charT, class Allocator>
struct cross_conversion<std::basic_string<charT, Allocator>>{
  typedef std::basic_string<charT, Allocator> original_type;
  typedef cross_string<charT> converted_type;
  static converted_type to_converted_type(const original_type& s){
    cross_string<charT> ret;
    ret.begin = s.data();
    ret.end = s.data() + s.size();
    return ret;
  }
  static  original_type to_original_type(const converted_type& c){
    return original_type(c.begin, c.end);
  }
};


struct converted_type_return{
  typedef cross_conversion<T> cc;
  error_code(CROSS_CALL_CALLING_CONVENTION* transfer_)(void* dest, const typename cc::converted_type& c);
  void* dest_;

};
// General return
template<class T, bool trivial>	struct cross_conversion_return_imp;

template<class T>
struct cross_conversion_return_imp<T, false>{
  typedef cross_conversion<T> cc;
  typedef typename cc::original_type return_type;
  typedef converted_type_return<T> converted_type;


  static error_code CROSS_CALL_CALLING_CONVENTION do_transfer(void* pdest, const typename cc::converted_type& c){
    try{
      auto& dest = *static_cast<return_type*>(pdest);
      dest = cc::to_original_type(c);
      return 0;
    }
    catch (std::exception& e){
      return general_error_mapper::error_code_from_exception(e);
    }

  }

  static void initialize_return(return_type& r, converted_type& c){
    c.transfer_ = do_transfer;
    c.dest_ = &r;

  }

  static void do_return(const return_type& r, const converted_type& c){
    auto rc = cc::to_converted_type(r);
    auto ec = c.transfer_(c.dest_, rc);
    if (ec < 0){
      general_error_mapper::exception_from_error_code(ec);
    }

  }
  static void finalize_return(return_type&, converted_type&){
    // do nothing
  }

};

// Trivial return
template<class T>
struct cross_conversion_return_imp<T, true>{
  typedef cross_conversion<T> cc;
  typedef typename cc::original_type return_type;
  typedef typename cc::converted_type converted_type;

  static void initialize_return(return_type&, converted_type&){
    // do nothing
  }

  static void do_return(const return_type& r, converted_type& c){
    typedef cross_conversion<T> cc;
    c = cc::to_converted_type(r);
  }
  static void finalize_return(return_type& r, converted_type& c){
    r = cc::to_original_type(c);
  }

};
}

template<class T>
struct cross_conversion_return : public detail::cross_conversion_return_imp<T, is_trivial_cross_conversion<T>::value >{};

