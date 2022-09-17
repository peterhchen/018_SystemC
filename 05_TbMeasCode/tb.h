#inlcude <systemc.h>
// Handshake: 7:31/18:25
SC_MODULE(tb) {
    sc_in<bool>             clk;
    sc_out<bool>            rst;
    sc_out< mc_int<16> >    inp;
    sc_out< bool >          inp_vld;
    sc_in< bool >           inp_rdy;

    sc_in< sc_int<16> >     outp;
    sc_in<bool>             outp_vld;
    sc_out< bool >          outp_rdy;

    void source();
    void sink();

    SC_CTOR(tb) {
        
    }
}