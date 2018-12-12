#ifndef _regs_h_
#define _regs_h_

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <cstring>


class Registers {
public:
    // CONSTRUCTORS:
    Registers();

    // PRINTING:
    void print_regs();

    // ACCESSORS:

    // OTHER METHODS:

private:
    std::vector<std::string> s_regs; // S registers (strings)
    std::vector<int> sreg_values; // S register values

    std::vector<std::string> t_regs; // T registers (strings)
    std::vector<int> treg_values; // T register values

};

#endif