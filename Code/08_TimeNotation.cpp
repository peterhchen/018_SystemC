#include <systemc>
using namespace sc_core;

int sc_main(int, char*[]) {
  sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated", sc_core::SC_DO_NOTHING );
  //suppress warning due to set_time_resolution                          
  //deprecated function but still useful, default is 1 PS
  sc_set_time_resolution(1, SC_FS);
  //change time unit to 1 second
  sc_set_default_time_unit(1, SC_SEC);
  std::cout << "1 SEC =     " << sc_time(1, SC_SEC).to_default_time_units() << " SEC"<< std::endl;
  std::cout << "1  MS = " << sc_time(1, SC_MS).to_default_time_units()  << " SEC"<< std::endl;
  std::cout << "1  US = " << sc_time(1, SC_US).to_default_time_units()  << " SEC"<< std::endl;
  std::cout << "1  NS = " << sc_time(1, SC_NS).to_default_time_units()  << " SEC"<< std::endl;
  std::cout << "1  PS = " << sc_time(1, SC_PS).to_default_time_units()  << " SEC"<< std::endl;
  std::cout << "1  FS = " << sc_time(1, SC_FS).to_default_time_units()  << " SEC"<< std::endl;
  // run simulation for 7261 second
  sc_start(7261, SC_SEC);
  // get time in second
  double t = sc_time_stamp().to_seconds();
  std::cout << int(t) / 3600 << " hours, " << (int(t) % 3600) / 60 << " minutes, " << (int(t) % 60) << "seconds" << std::endl;
  return 0;
}
//Result:
// 1 SEC =     1 SEC
// 1  MS = 0.001 SEC
// 1  US = 1e-06 SEC
// 1  NS = 1e-09 SEC
// 1  PS = 1e-12 SEC
// 1  FS = 1e-15 SEC
// 7261 seconds
// 2 hours, 1 minutes, 1seconds
