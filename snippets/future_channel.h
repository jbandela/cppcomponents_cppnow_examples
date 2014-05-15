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


