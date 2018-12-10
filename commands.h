#ifndef _commands_h_
#define _commands_h_

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>;



class Commands {
public:
    // CONSTRUCTORS:
    Commands();
    Commands(std::string command_, std::vector<std::string> regs_, char type_, int id_);
	// ~Commands();
	
	// PRINTING:
    void print_line();	
    void decoder(int num);

    // ACCESSORS:

    // OTHER METHODS:
	

private:
    std::string command; // stores the MIPS command line
    std::vector<int> cycle_line; // stores the cycle instructions for all cycles
    int dependency; // ID of command that this command is dependent on
    std::vector<std::string> regs; // registers that this command uses
    char type; // stores instructions type (R/I)
    int id; // ID tag for command line
    


	
};

#endif
