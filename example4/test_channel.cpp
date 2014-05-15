#include <iostream>
#include <cppcomponents_concurrency/await.hpp>
#include <cppcomponents/channel.hpp>
#include <cppcomponents/loop_executor.hpp>
#include <functional>

void printer(cppcomponents::Channel<std::int32_t> chan){
  for(;;){
    auto f = cppcomponents::await_as_future(chan.Read());
    if(f.ErrorCode() < 0 ){
      return;
    }
    std::cout << f.Get() << "\n";
  }
}


void generator(cppcomponents::Channel<std::int32_t> chan){
  for(int i = 0; i < 10; ++i){
    cppcomponents::await(chan.Write(i));
  }
  chan.Complete();
}


int main(){
  cppcomponents::LoopExecutor exec;
  auto chan = cppcomponents::make_channel<int>();
  auto f1 = cppcomponents::co_async(exec,std::bind(printer,chan));
  auto f2 = cppcomponents::co_async(exec,std::bind(generator,chan));
  cppcomponents::when_all(f1,f2).
  Then([exec](cppcomponents::Future<void> f){
      exec.MakeLoopExit();
      });
  exec.Loop();
  f1.Get();
  f2.Get();

}
