#include <systemc>
using namespace sc_core;
SC_MODULE(EVENT) {
  // declare an event
  sc_event e;
  SC_CTOR(EVENT) {
    // register a trigger process
    SC_THREAD(trigger);
    // register a catcher process
    SC_THREAD(catcher);
  }
  void trigger() {
    // infinite loop
    while (true) {
      // trigger after 1 second
      e.notify(1, SC_SEC);
      if (sc_time_stamp() == sc_time(4, SC_SEC)) {
        //cancel the event triggered at time = 4 s
        e.cancel();
      }
      // wait for 2 seconds before triggering again
      wait(2, SC_SEC);
    }
  }
  void catcher() {
    // loop forever
    while (true) {
      // wait for event
      wait(e);
      // print to console
      std::cout << "Event cateched at " << sc_time_stamp() << std::endl;
    }
  }
};
int sc_main(int, char*[]) {
  //define object
  EVENT event("event");
  //run simulation for 8 seconds
  sc_start(8, SC_SEC);
  return 0;
}