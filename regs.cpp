#include "regs.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iomanip>

// constructor for Registers class
Registers::Registers() {
    // push back s register titles
    s_regs.push_back("$s0 = ");
    s_regs.push_back("$s1 = ");
    s_regs.push_back("$s2 = ");
    s_regs.push_back("$s3 = ");
    s_regs.push_back("$s4 = ");
    s_regs.push_back("$s5 = ");
    s_regs.push_back("$s6 = ");
    s_regs.push_back("$s7 = ");   

    // push back t register titles
    t_regs.push_back("$s0 = ");
    t_regs.push_back("$s1 = ");
    t_regs.push_back("$s2 = ");
    t_regs.push_back("$s3 = ");
    t_regs.push_back("$s4 = ");
    t_regs.push_back("$s5 = ");
    t_regs.push_back("$s6 = ");
    t_regs.push_back("$s7 = ");
    t_regs.push_back("$s8 = ");
    t_regs.push_back("$s9 = ");

    // initialize all registers to 0
    for (int i = 0; i < 8; i++) {
        sreg_values[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        treg_values[i] = 0;
    }
}

// prints registers and their values in columns of 4
void Registers::print_regs() {
    int mult = 0;
    for (int i = 0; i < 8; i++) {
        std::cout << std::setw(6) << s_regs[i] << std::setw(14) << sreg_values[i];
        mult++;
        if (mult%4 == 0) {
            std::cout << std::endl;
        }
    }

    for (int i = 0; i < 10; i++) {
        std::cout << std::setw(6) << t_regs[i] << std::setw(14) << treg_values[i];
        mult++;
        if (mult%4 == 0) {
            std::cout << std::endl;
        }
    }
}

