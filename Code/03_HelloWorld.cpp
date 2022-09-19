//include the systemC header file
#include <systemc>
//use namespace
using namespace sc_core;
//a normal c++ function
void hello1() {
  std::cout << "Hello world using approach 1" << std::endl;
}
//define a systemC module
struct HelloWorld : sc_module {
  //constructor function, to be explained later
  SC_CTOR(HelloWorld) {
  //register a member function to the kernel
    SC_METHOD(hello2);
  }
  //a function for systemC simulation kernel, void inside () can be omitted
  void hello2(void) {
    std::cout << "Hello world using approach 2" << std::endl;
  }
};
// entry point
int sc_main(int, char*[]) {
  //approach #1: manually invoke a normal function
  hello1();
  //approach #2, instantiate a systemC module
  HelloWorld helloworld("helloworld");
  //let systemC simulation kernel to invoke helloworld.hello2();
  sc_start();
  return 0;
}