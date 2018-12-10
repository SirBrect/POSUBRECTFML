#include "regs.h"

// constructor for register class
Registers::Registers() {
    // push back s register titles
    s_regs.push_back("$s0");
    s_regs.push_back("$s1");
    s_regs.push_back("$s2");
    s_regs.push_back("$s3");
    s_regs.push_back("$s4");
    s_regs.push_back("$s5");
    s_regs.push_back("$s6");
    s_regs.push_back("$s7");   

    // push back t register titles
    t_regs.push_back("$s0");
    t_regs.push_back("$s1");
    t_regs.push_back("$s2");
    t_regs.push_back("$s3");
    t_regs.push_back("$s4");
    t_regs.push_back("$s5");
    t_regs.push_back("$s6");
    t_regs.push_back("$s7");
    t_regs.push_back("$s8");
    t_regs.push_back("$s9");

    // initialize all registers to 0
    for (int i = 0; i < 8; i++) {
        s_regs[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        t_regs[i] = 0;
    }
}

void Registers::print_regs();

