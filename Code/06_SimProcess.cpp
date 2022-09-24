#include <systemc>
using namespace sc_core;
SC_MODULE(PROCESS) {
  // declares a clock
  sc_clock clk;
  //instantiate a clock with 1sec periodicity
  SC_CTOR(PROCESS) : clk("clk", 1, SC_SEC) {
    //register a method
    SC_METHOD(method);
    // register a thread
    SC_THREAD(thread);
    // register a clocked thread
    SC_CTHREAD(cthread, clk);
  }
  // define the method member function
  void method(void) {
    // no while loop here
    std::cout << "method triggered @ " << sc_time_stamp() << std::endl;
    // trigger after 1 sec
    next_trigger(sc_time(1, SC_SEC));
  }
  // define the thread member function
  void thread() {
    // infinite loop make sure it never exits 
    while (true) {
      std::cout << "thread triggered @ " << sc_time_stamp() << std::endl;
      // wait 1 sec before execute again
      wait(1, SC_SEC);
    }
  }
  // define the cthread member function
  void cthread() {
    // infinite loop
    while (true) {
      std::cout << "cthread triggered @ " << sc_time_stamp() << std::endl;
      // wait for next clk event, which comes after 1 sec
      wait();
    }
  }
};
int sc_main(int, char*[]) {
  // init module
  PROCESS process("process");
  std::cout << "execution phase begins @ " << sc_time_stamp() << std::endl;
  // run simulation for 2 second
  sc_start(2, SC_SEC);
  std::cout << "execution phase ends @ " << sc_time_stamp() << std::endl;
  return 0;
}