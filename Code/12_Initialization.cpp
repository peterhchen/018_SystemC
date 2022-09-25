#include <systemc>
using namespace sc_core;
SC_MODULE(INITIALIZATION) {
  // event for inter-process trigger
  sc_event e;
  SC_CTOR(INITIALIZATION) {
    // no static sensitivity
    SC_THREAD(trigger);
    // no static sensitivity
    SC_THREAD(catcher_1);
    // no static sensitivity
    SC_THREAD(catcher_2);
    SC_THREAD(catcher_3);
    // statically sensitive to e
    sensitive << e;
    // don't initialize
    dont_initialize();
  }
  void trigger() {
    // e triggered at 1, 3, 5, 7 ...
    while (true) {
      // notify after 1 s
      e.notify(1, SC_SEC);
      // trigger every 2 s
      wait(2, SC_SEC);
    }
  }
  void catcher_1() {
    while (true) {
      std::cout << sc_time_stamp() << ": catcher_1 triggered" << std::endl;
      // dynamic sensitivity
      wait(e);
    }
  }
  void catcher_2() {
    // avoid initialization --- mimic systemC 1.0 behavior
    wait(e);
    while (true) {
      std::cout << sc_time_stamp() << ": catcher_2 triggered" << std::endl;
      // dynamic sensitivity
      wait(e);
    }
  }
  // relies on dont_initialize() to avoid initialization
  void catcher_3() {
    while (true) {
      std::cout << sc_time_stamp() << ": catcher_3 triggered" << std::endl;
      // dynamic sensitivity
      wait(e);
    }
  }
};
int sc_main(int, char*[]) {
  INITIALIZATION init("init");
  sc_start(4, SC_SEC);
  return 0;
}