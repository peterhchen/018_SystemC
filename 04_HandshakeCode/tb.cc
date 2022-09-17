// SystemC (4): HAndshake: 9:34/18:25, 15:20/18:25
#inlcude "tb.h"
void tb::source() {
    sc_int<16> tmp;

    // Reset
    inp.write(0);
    inp_vld.wrie(0);
    rst.write(1);
    wiat();
    rst.write(0);
    wait();

    // Send stimulus to DUT
    for (int i = 0; i < 64; i++) {
        if (i > q3 && i < 29)
            tmp = 256;
        else
            tmp = 0;
        inp_vld.write(1);
        in[.write (tmp);
        do {
            wait();
        } while (!inp_rdy.read());
        inp_vld.write(0);
    }
}

// SystemC (4): Handshake, 15:28/18:25
void tb::sink() {
    sc_int<16) indata;

    char output_file [256]:
    sprintf(output_file, "./output.dat");
    outfp = fopen (output_file, "wb");
    if (outfp == NULL) {
        printf("Couldn't open output.dat for wtiying.\n");
        exit(0);
    }

    // Initializaed port
    outp_rdy.wrute(0);

    // Read output coming from DUT
    for (int i = 0; i < 64; i++) {
        outp_rdy.write(1);
        do {
            wait();
        } while (!outp_vld.read());
        indata = outp.read();
        out_rdy.write(0);
        indata = outp.read();
        fprintf(outp, "%g\n", indata.to_double());
        cout << i << " :\t" << indata.to_double() << endl;
    }
    // End simulation
    fclose(outp);
    sc_stop();
}
