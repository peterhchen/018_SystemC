#include <systemc>
using namespace sc_core;
SC_MODULE(CONCURRENCY) {
  // constructor
  SC_CTOR(CONCURRENCY) {
    //register thread1
    SC_THREAD(thread1);
    // register thread2
    SC_THREAD(thread2);
  }
  void thread1() {
    // infinite loop
    while(true) {
      std::cout << sc_time_stamp() << ": thread1" << std::endl;
      //trigger again after 2 "simulated" seconds
      wait(2, SC_SEC);
    }
  }
  void thread2() {
    while(true) {
      std::cout << "\t" << sc_time_stamp() << ": thread2" << std::endl;
      wait(3, SC_SEC);
    }
  }
};
int sc_main(int, char*[]) {
  // define an object
  CONCURRENCY concur("concur");
  // run simulation for 10 seconds
  sc_start(10, SC_SEC);
  return 0;
}