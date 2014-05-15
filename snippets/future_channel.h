typedef cppcomponents::uuid<0xf2ff083f, 0xa305, 0x4f11, 0x98dc, 0x0b41344d1292> uuid_base_t_IFuture;
template<class T>
struct IFuture : public cppcomponents::define_interface < combine_uuid<uuid_base_t_IFuture, typename uuid_of<T>::uuid_type>>{

  typedef combine_uuid<detail::delegate_uuid, typename uuid_of<void>::uuid_type, uuid_base_t_IFuture, typename uuid_of<T>::uuid_type> u_t;

  typedef cppcomponents::delegate < void(use < IFuture<T >> ), u_t> CompletionHandler;

  T Get();
  bool Ready();
  cppcomponents::error_code ErrorCode();
  void SetCompletionHandlerRaw(use<CompletionHandler>);
  void SetCompletionHandlerAndExecutorRaw(use<IExecutor>, use<CompletionHandler>);
  use<IExecutor> GetExecutor();

  CPPCOMPONENTS_CONSTRUCT_TEMPLATE(IFuture, Get, Ready, ErrorCode, SetCompletionHandlerRaw, SetCompletionHandlerAndExecutorRaw,GetExecutor)

    CPPCOMPONENTS_INTERFACE_EXTRAS(IFuture){
      template<class F>
	void SetCompletionHandler(F f){
	  this->get_interface().SetCompletionHandlerRaw(cppcomponents::make_delegate<CompletionHandler>(f));
	}
      template<class F>
	void SetCompletionHandlerAndExecutor(use<IExecutor> e, F f){
	  this->get_interface().SetCompletionHandlerAndExecutorRaw(e, cppcomponents::make_delegate<CompletionHandler>(f));
	}

      template<class F>
	use < IFuture < typename std::result_of < F(use < IFuture<T >> )>::type >> Then(F f) {
	  typedef typename std::result_of < F(use < IFuture<T >> )>::type R;
	  auto e = this->get_interface().GetExecutor();
	  auto iu = implement_future_promise<R>::create(e);
	  auto p = iu.template QueryInterface<IPromise<R>>();
	  this->get_interface().SetCompletionHandler([p, f](use < IFuture < T >> res)mutable{
	      detail::set_promise_result(p, f, res);
	      });
	  return iu.template QueryInterface<IFuture<R>>();
	}
      template<class F>
	use < IFuture < typename std::result_of < F(use < IFuture<T >> )>::type >> Then(use<IExecutor> e, F f) {
	  typedef typename std::result_of < F(use < IFuture<T >> )>::type R;
	  auto iu = implement_future_promise<R>::create(e);
	  auto p = iu.template QueryInterface<IPromise<R>>();
	  this->get_interface().SetCompletionHandlerAndExecutor(e, [p, f](use < IFuture < T >> res)mutable{
	      detail::set_promise_result(p, f, res);
	      });
	  return iu.template QueryInterface<IFuture<R>>();
	}

      typename detail::unwrap_helper<T>::type Unwrap(){
	return detail::unwrap(this->get_interface());
      }
    };

  typedef cppcomponents::uuid<0xb23a22d4, 0xbafb, 0x4744, 0x8cf1, 0xc85c2d916358> uuid_base_t_IPromise;

  template<class T>
    struct IPromise : public cppcomponents::define_interface <combine_uuid<uuid_base_t_IPromise, typename uuid_of<T>::uuid_type>>{

      void Set(T t);
      void SetError(cppcomponents::error_code);
      typedef IPromise<T> IPromiseT;
      CPPCOMPONENTS_CONSTRUCT_TEMPLATE(IPromise, Set, SetError)

	CPPCOMPONENTS_INTERFACE_EXTRAS(IPromise){

	  template<class F>
	    void SetResultOf(F f){
	      try{
		this->get_interface().Set(f());
	      }
	      catch (std::exception& e){
		auto ec = error_mapper::error_code_from_exception(e);
		this->get_interface().SetError(ec);
	      }
	    }

	};

    };


  typedef cppcomponents::uuid<0x4d327f1c, 0x7515, 0x4dc5, 0xb1e4, 0x4ff5051d2beb> channel_base_uuid_t;
  template<class T>
    struct IChannel : define_interface<combine_uuid<channel_base_uuid_t, typename uuid_of<T>::uuid_type>>{
      typedef delegate<void()> ClosedDelegate;

      use<IFuture<void>> Write(T);
      use<IFuture<void>> WriteError(cppcomponents::error_code);
      use<IFuture<T>> Read();
      void Close();
      void SetOnClosedRaw(use<ClosedDelegate>);
      void Complete();
      bool IsComplete();

      CPPCOMPONENTS_CONSTRUCT_TEMPLATE(IChannel, Write, WriteError, Read, Close,SetOnClosedRaw, Complete, IsComplete)

	CPPCOMPONENTS_INTERFACE_EXTRAS(IChannel){
	  template<class F>
	    void SetOnClosed(F f){
	      this->get_interface().SetOnClosedRaw(make_delegate<ClosedDelegate>(f));
	    }
	};
    };
