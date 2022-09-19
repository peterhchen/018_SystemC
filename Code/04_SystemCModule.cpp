#include <systemc>
using namespace sc_core;
// approach #1, use systemC provided SC_MODULE macro
SC_MODULE(MODULE_A) {
  // default constructor
  SC_CTOR(MODULE_A) {
    // name() returns the object name, which is provided during instantization
    std::cout << name() << " constructor" << std::endl;
  }
};
//approach #2, this uses c++ syntax and is more readiable
struct MODULE_B : public sc_module {
  SC_CTOR(MODULE_B) {
    std::cout << name() << " constructor" << std::endl;
  }
};
// approach #3, use class instead of struct
class MODULE_C : public sc_module {
  // have to explicitly declare constructor function as public 
public:
  SC_CTOR(MODULE_C) {
    std::cout << name() << " constructor" << std::endl;
  }
};
// systemC entry point
int sc_main(int, char*[]) {
  //declare and instantiate module_a, it's common practice to assign module name == object name
  MODULE_A module_a("module_a");
  //declare and instantiate module_b, module name != object name
  MODULE_B module_b("modb");
  // declare and instantiate module_c
  MODULE_C module_c("module_c");
  //this can be skipped in this example because module instantiation happens during elaboration phase which is before sc_start
  sc_start();
  return 0;
}