#include "commands.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iomanip>

//default constructer
Commands::Commands(){
	std::string command_ = "null";
	std::vector<int> cycle_line_;
	int dependency_ = 0;
	std::vector<std::string> regs_;
	char type_ = 'x';
	int id_ = 0;
	int delay_ = 0;
	bool done_ = false;


	command = command_;
	cycle_line = cycle_line_;
	dependency = dependency_;
	regs = regs_;
	type = type_;
	id = id_;
	delay = delay_; 
	done = done_;

	for (int i = 0; i < 16; ++i)
	{
		cycle_line.push_back(0);
	}
}

// constructor for Command class
Commands::Commands(std::string command_, std::vector<std::string> regs_, char type_, int id_) {
    command = command_;
    regs = regs_;
    type = type_;
    id = id_;
}

// prints out command and cycleline
void Commands::print_line() {
    std::cout << std::left << std::setw(20) << wholeCommand << std::flush;
    for (unsigned int i = 0; i < cycle_line.size(); i++) {
        decoder(cycle_line[i]);
        // if (i != cycle_line.size()-1) {
        //     std::cout << " ";
        // }
    }
    std::cout << std::endl;
}

// decodes cycle_line into proper instructions
void Commands::decoder(int num) {
    // KEY:
    // 0 = .
    // 1 = ID
    // 2 = IF
    // 3 = EX
    // 4 = MEM
    // 5 = WB
    // 6 = .
    // 7 = *

    if (num == 0 || num == 6) {
        std::cout << std::left << std::setw(4) << ".";
    }
    else if (num == 1) {
        std::cout << std::left << std::setw(4) << "IF";
    }
    else if (num == 2) {
        std::cout << std::left << std::setw(4) << "ID";
    }
    else if (num == 3) {
        std::cout << std::left << std::setw(4) << "EX";
    }
    else if (num == 4) {
        std::cout << std::left << std::setw(4) << "MEM";
    }
    else if (num == 5) {
        std::cout << std::left << std::setw(4) << "WB";
    }
    else if (num == 7) {
        std::cout << std::left << std::setw(4) << "*";
    }

}

//setters----------------------------------------------
void Commands::setCommand(std::string command_){
	command = command_;
}
void Commands::setDependency(int dependency_){
	dependency = dependency_;
}
void Commands::setType(char type_){
	type = type_;
}

void Commands::setID(int id_){
	id = id_;
}

void Commands::addRegs(std::string reg){
	regs.push_back(reg);
}

void Commands::setDelay(int delay_){
	delay = delay_;
}

void Commands::setCycle_line(int index, int val){
	cycle_line[index] =  val;
}

void Commands::setWholeCommand(std::string wholeCommand_){
	wholeCommand = wholeCommand_;
}

void Commands::setDone(bool done_){
	done = done_;
}