#include <systemc>
using namespace sc_core;
SC_MODULE(SENSITIVITY) {
  // events for inter-process triggering
  sc_event e1, e2;
  SC_CTOR(SENSITIVITY) {
    // register processes
    SC_THREAD(trigger_1);
    SC_THREAD(trigger_2);
    SC_THREAD(catch_1or2_dyn);
    SC_THREAD(catch_1or2_static);
    // static sensitivity for the preceeding process, can only "OR" the triggers
    sensitive << e1 << e2;
  }
  void trigger_1() {
    // delay trigger by a delta cycle, make sure catcher is ready
    wait(SC_ZERO_TIME);
    while (true) {
      // trigger e1
      e1.notify();
      // dynamic sensitivity, re-trigger after 2 s
      wait(2, SC_SEC);
    }
  }
  // delay trigger by a delta cycle
  void trigger_2() {
    wait(SC_ZERO_TIME);
    while (true) {
      // trigger e2
      e2.notify();
      // dynamic sensitivity, re-trigger after 3 s
      wait(3, SC_SEC);
    }
  }
  void catch_1or2_dyn() {
    while (true) {
      // dynamic sensitivity
      wait(e1 | e2);
      std::cout << "Dynamic sensitivty: e1 or e2 @ " << sc_time_stamp() << std::endl;
    }
  }
  void catch_1or2_static(void) {
    while (true) {
      // static sensitivity
      wait();
      std::cout << "Static sensitivity: e1 or e2 @ " << sc_time_stamp() << std::endl;
    }
  }
};
int sc_main(int, char*[]) {
  SENSITIVITY sensitivity("sensitivity");
  sc_start(7, SC_SEC);
  return 0;
}