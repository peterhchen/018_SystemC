#include <systemc>
using namespace sc_core;
// module without simulation processes doesn't need SC_CTOR or SC_HAS_PROCESS
SC_MODULE(MODULE_A) {
  // c++ style constructor, the base class is implicitly instantiated with module name.
  MODULE_A(sc_module_name name) {
    std::cout << this->name() << ", no SC_CTOR or SC_HAS_PROCESS" << std::endl;
  }
};
//constructor with module name as the only input argument
SC_MODULE(MODULE_B1) {
  //implicitly declares a constructor of MODULE_B1(sc_module_name)
  SC_CTOR(MODULE_B1) {
    // register member function to simulation kernel
    SC_METHOD(func_b);
  }
  //define function
  void func_b() {
    std::cout << name() << ", SC_CTOR" << std::endl;
  }
};
// constructor with module name as the only input argument
SC_MODULE(MODULE_B2) {
  // no implicit constructor declarition
  SC_HAS_PROCESS(MODULE_B2);
  // explicit constructor declaration, also instantiate base class by default via sc_module(name)
  MODULE_B2(sc_module_name name) {
     // register member function
    SC_METHOD(func_b);
  }
  // define function
  void func_b() {
    std::cout << name() << ", SC_HAS_PROCESS" << std::endl;
  }
};
//pass additional input argument(s)
SC_MODULE(MODULE_C) {
  const int i;
  // OK to use SC_CTOR, which will also define an un-used constructor: MODULE_A(sc_module_name);
  SC_HAS_PROCESS(MODULE_C);
  //define the constructor function
  MODULE_C(sc_module_name name, int i) : i(i) {
    //register member function
    SC_METHOD(func_c);
  }
  // define function
  void func_c() {
   std::cout << name() << ", additional input argument" << std::endl;
  }
};
// SC_CTOR inside header, constructor defined outside header
SC_MODULE(MODULE_D1) {
  SC_CTOR(MODULE_D1);
  void func_d() {
    std::cout << this->name() << ", SC_CTOR inside header, constructor defined outside header" << std::endl;
  }
};
// defines constructor. Fine with/without "sc_module(name)"
MODULE_D1::MODULE_D1(sc_module_name name) : sc_module(name) {
  SC_METHOD(func_d);
}
// SC_HAS_PROCESS inside header, constructor defined outside header
SC_MODULE(MODULE_D2) {
  SC_HAS_PROCESS(MODULE_D2);
  // declares constructor
  MODULE_D2(sc_module_name);
  void func_d() {
    std::cout << this->name() << ", SC_CTOR inside header, constructor defined outside header" << std::endl;
  }
};
// defines constructor. Fine with/without "sc_module(name)"
MODULE_D2::MODULE_D2(sc_module_name name) : sc_module(name) {
  SC_METHOD(func_d);
}
// SC_CURRENT_USER_MODULE and constructor defined outside header
SC_MODULE(MODULE_E) {
  // c++ style constructor declaration
  MODULE_E(sc_module_name name);
  void func_e() {
    std::cout << this->name() << ", SC_HAS_PROCESS outside header, CANNOT use SC_CTOR" << std::endl;
  }
};
// constructor definition
MODULE_E::MODULE_E(sc_module_name name) {
  // NOT OK to use SC_CTOR
  SC_HAS_PROCESS(MODULE_E);
  SC_METHOD(func_e);
}
int sc_main(int, char*[]) {
  MODULE_A module_a("module_a");
  MODULE_B1 module_b1("module_b1");
  MODULE_B2 module_b2("module_b2");
  MODULE_C module_c("module_c", 1);
  MODULE_D1 module_d1("module_d1");
  MODULE_D2 module_d2("module_d2");
  MODULE_E module_e("module_e");
  sc_start();
  return 0;
}