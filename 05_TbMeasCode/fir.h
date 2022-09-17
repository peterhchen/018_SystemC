#include <system.h>
// SystemC (4) Handshake: (7:36/18:25)
SC_MODULE (fir) {
    sc_in< bool >           clk;
    sc_in< bool >           rst;
    sc_in< sc_int<16> >     inp;
    sc_int < bool >         inp_vld;
    sc_out < bool >         inp_rdy;
    sc_out < sc_int<16> >   outp;
    sc_out < bool >         outp_vld;
    sc_in < bool >          outp_rdy;

    void fir_main();

    SC_CTOR (fir) {
        SC_CTHREAD (fir_main, clk.pos() );
        reset_signal_is (rst, true);S
    }
}