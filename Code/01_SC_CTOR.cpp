#include <systemc>
using namespace sc_core;
//constructor: taking only module name
SC_MODULE(MODULE_A) {
  // register member function to systemC
  // simulation kernel, to be explained later
  SC_CTOR(MODULE_A) {
    SC_METHOD(func_a);
  }
  // a member function with no input, no output
  void func_a() {
    std::cout << name() << std::endl;
  }
};

// constructor
SC_MODULE(MODULE_B) {
  // register member function
  SC_CTOR(MODULE_B) {

    SC_METHOD(func_b);
  }
  // declare function
  void func_b();
};

// define function outside class definition
void MODULE_B::func_b() {
  std::cout << this->name() << std::endl;
}
// constructor taking more arguments
SC_MODULE(MODULE_C) {
  const int i;
  // SC_HAS_PROCESS is recommended, see next example for details
  SC_CTOR(MODULE_C);
  // explicit constructor
  MODULE_C(sc_module_name name, int i) : sc_module(name), i(i) {
    SC_METHOD(func_c);
  }
  void func_c() {
    std::cout << name() << ", i = " << i << std::endl;
  }
};
int sc_main(int, char*[]) {
  MODULE_A module_a("module_a");
  MODULE_B module_b("module_b");
  MODULE_C module_c("module_c",1);
  sc_start();
  return 0;
}