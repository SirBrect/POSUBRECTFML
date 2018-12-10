#ifndef _commands_h_
#define _commands_h_

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>



class Commands {
public:
    // CONSTRUCTORS:
    Commands(std::string command_, std::vector<std::string> regs_, char type_, int id_);
	// ~Commands();
	
	// PRINTING:
	// prints out command and cycleline
    void print_line();	
    void cycleline_decoder(int num);

    // ACCESSORS:
    // OTHER METHODS:
	

private:
    std::string command; // stores the MIPS command line
    std::vector<int> cycle_line; // stores the cycle instructions for all cycles
    int dependency; // ID of command that this command is dependent on
    std::vector<std::string> regs; // registers that this command uses
    char type; // stores instructions type (R/I)
    int id // ID tag for command line
    


	
};

#endif
