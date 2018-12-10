#include "commands.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

Commands::Commands(std::string command_, int regs_, char type_, int id_) {
    command = command_;
    regs = regs_;
    type = type_;
    id = id_;
}