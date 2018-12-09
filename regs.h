#ifndef _regs_h_
#define _regs_h_

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

class Registers {
public:
    // CONSTRUCTORS:
    Registers();

    // PRINTING:
    // prints all the registers with their values
    void print_regs();

    // ACCESSORS:
    // OTHER METHODS:

private:
    std::vector<string> s_regs; // S registers (strings)
    std::vector<int> sreg_values // S register values

    std::vector<string> t_regs; // T registers (strings)
    std::vector<int> treg_values // T register values

};

#endif