#include "regs.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iomanip>

// constructor for Registers class
Registers::Registers() {

    std::vector<std::string> s_regs_; // S registers (strings)
    std::vector<int> sreg_values_; // S register values

    std::vector<std::string> t_regs_; // T registers (strings)
    std::vector<int> treg_values_; // T register values

    s_regs = s_regs_;
    sreg_values = sreg_values_;
    t_regs = t_regs_;
    treg_values = treg_values_;

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
    t_regs.push_back("$t0 = ");
    t_regs.push_back("$t1 = ");
    t_regs.push_back("$t2 = ");
    t_regs.push_back("$t3 = ");
    t_regs.push_back("$t4 = ");
    t_regs.push_back("$t5 = ");
    t_regs.push_back("$t6 = ");
    t_regs.push_back("$t7 = ");
    t_regs.push_back("$t8 = ");
    t_regs.push_back("$t9 = ");

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

