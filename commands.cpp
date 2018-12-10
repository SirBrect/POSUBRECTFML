#include "commands.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

Commands::Commands(std::string command_, std::vector<std::string> regs_, char type_, int id_) {
    command = command_;
    regs = regs_;
    type = type_;
    id = id_;
}

Commands::print_line() {
    std::cout << command;
}

Commands::cycleline_decoder(int num) {
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
        std::cout << "." << std::endl;
    }
    else if (num == 1) {
        std::cout << "ID" << std::endl;
    }
    else if (num == 2) {
        std::cout << "IF" << std::endl;
    }
    else if (num == 3) {
        std::coutn << "EX" << std::endl;
    }
    else if (num == 4) {
        std::cout << "MEM" << std::endl;
    }
    else if (num == 5) {
        std::cout << "WB" << std::endl;
    }
    else if (num == 7) {
        std::cout << "*" << std::endl;
    }

}