#include <iostream>
#include <iomanip>
#include <fstream>
#include "regs.h"
#include "commands.h"
#include <string>
#include <vector>

// void controlHazardCheck(Commands cmmd, ) {
	
// }

void nopInsert() {

}

int nopCheck(std::vector<Commands> &commandLines, int row, int cycle){//checks two behind for data nop insert
	int two = row-1;
	int nops = 0;
	while(two != (row-2) && row <=0){
		if (commandLines[two].getRegs().size() >= 3) //if its a command with registers
		{
			if (commandLines[row].getRegs()[0] == commandLines[two].getRegs()[1] && commandLines[row].getRegs()[0] == commandLines[two].getRegs()[2])
			{
				nops = 3 - (two - row);//might have to check this again later.......................
				break;
			}
		}
		two++;
	}
	return nops;
}

void cycleIncrement(std::vector<Commands> &commandLines,bool forwarding , int row , int cycle){
	int intstore = 0;
	if (row <= cycle) 
	{
		//std::cout << "this is instore before: " << intstore << std::endl; //test print
		intstore = commandLines[row].getCycle_line()[cycle];
		if (cycle == 0 ) //if its the first index increment
		{
			intstore++;
		}
		else if (commandLines[row].getDelay() > 0) //if the line has delays set the cycle equal to the one prevouse
		{
			intstore = commandLines[row].getCycle_line()[cycle-1]; 
			commandLines[row].setDelay((commandLines[row].getDelay() -1)); 
		}
		else if (commandLines[row].getCycle_line()[cycle-1] < 6) //else grab the one prev and increment it as one 
		{
			intstore = 1 + commandLines[row].getCycle_line()[cycle-1];
		}
		else{ // this doesnt need to be here but watev
			intstore = 6;
		}

		commandLines[row].setCycle_line(cycle,intstore); //assign 
		//std::cout << "this is instore after: " << intstore << std::endl; //test print
	}		
}

int main(int argc, char const *argv[])
{
	//variable_declarations------------------------------------------------------------
	std::vector<Commands> commandLines; //holds command objects for as many lines
	bool forwarding = (*argv[1] == 'F'); //bool determinig forwording
	std::string linebuff; 
	int id = 0;
	unsigned int finished_cmmds = 0;
	unsigned int i = 0,j = 0;
	Registers regs;
	int nops = 0;

	//ERROR CHECKING----------------------------------------------------------------------
	if (argc > 3){
		std::cerr << "Invalid Arguments PAT!" << std::endl;
	}
	std::ifstream mipscode(argv[2]);
	if (!mipscode.good())
	{
		std::cerr << "Cannot Read FILE PAT!" << std::endl;
	}

	//FILE READING-------------------------------------------------------------------------
	while(getline(mipscode,linebuff)) {

		Commands commandline;
		commandline.setWholeCommand(linebuff); // store whole command line for easy printing

		std::string delimiter = " ";
		size_t pos = 0;
		std::string token;
		pos = linebuff.find(delimiter);
		token = linebuff.substr(0, pos); 		//grab the command portion from read file
		// std::cout << token << std::endl;		//assign here
		linebuff.erase(0, pos + delimiter.length());
		commandline.setCommand(token); 			//set command portion

		delimiter = ",";
		if (token != "loop:") { //if command has registers add them to this register vector
			while ((pos = linebuff.find(delimiter)) != std::string::npos) {
		    	token = linebuff.substr(0, pos);
		    	// std::cout << token << std::endl;	//assign here
		    	linebuff.erase(0, pos + delimiter.length());
		    	commandline.addRegs(token);			//add to commandlineobj reg storage
			}
			commandline.addRegs(linebuff);
			// std::cout << linebuff << std::endl;
		}

		commandline.setID(id);
		commandLines.push_back(commandline); //add to overall commandlines vector
		id++;
	}


	//TEST PRINT---------------------------------------------------------------------------
	// std::cout << "here are all the commands given and their attributes" <<std::endl;
	// for (i = 0; i < commandLines.size(); ++i) {
	// 	std::cout << "commmand: " << commandLines[i].getCommand() << " ~registers ";
	// 	for (j = 0; j < commandLines[j].getRegs().size(); ++j) {
	// 		std::cout << commandLines[i].getRegs()[j] << " ";
	// 	}
	// 	std::cout << " Id: " << commandLines[i].getID() << std::endl;
	// }

	// for (i = 0; i < commandLines.size(); ++i) {
	// 	std::cout << commandLines[i].getWholeCommand() << std::endl;
	// }

	//ASSIGN DEPENDENCIES -------------------------------------------------------------------
	//TO DO: read through vector of commands, assign dependencies
	//TO DO: test print of dependencies "CMMD ID # is dependent on CMMD ID #"

	//PROGRAM RUN --------------------------------------------------------------------------
	std::cout << "START OF SIMULATION";
	if (forwarding) {
		std::cout << " (forwarding)" << std::endl;
	}
	else {
		std::cout << " (no forwarding)" << std::endl;
	}
	
	//incrementation
	for (i = 0; i < 16; ++i) { //for the 16 cycles
		if (finished_cmmds == commandLines.size()) {
			break;
		}
		std::cout << "----------------------------------------------------------------------------------" << std::endl;
		std::cout << "CPU Cycles ===>     1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16" << std::endl;
		for (j = 0; j < commandLines.size(); ++j) { //for each row

			//nops check------------------------------------------------------------------------------------------------------------
			if (i != 0 && commandLines[j].getCycle_line()[i-1] == 1)//check stage of prev for ID
			{
				if (forwarding) //check forwarding
				{
					if (commandLines[j].getCommand() != "add" && commandLines[j].getCommand() != "and" && commandLines[j].getCommand() != "or" && commandLines[j].getCommand() != "sit") //excluse these commands
					{
						nops = nopCheck(commandLines,j,i);
					}
				}
				else{//normal checkall
					nops = nopCheck(commandLines,j,i);// check and set nops
				}
			}
			//nops insert-----------------------------------------------------------------------------------------------------------

			//incroment----------------------------------------------------------------------------------------------------------

			if (commandLines[j].getCommand() != "loop:") {
				cycleIncrement(commandLines,forwarding,j,i); //increment cycle by column
			}
			//printf command and cycle line
			if (commandLines[j].getCycle_line()[i] != 0 && commandLines[j].getCommand() != "loop:") {
				commandLines[j].print_line();	
			}
			// if command is an immediate, store digit in register
			if (commandLines[j].getCycle_line()[i] == 5 && isdigit(commandLines[j].getRegs()[2][0])) {
				regs.setRegValue(commandLines[j].getRegs()[0], std::stoi(commandLines[j].getRegs()[2]));

			}
			//if command is finished, add to number of finished commands
			if (commandLines[j].getCycle_line()[i] == 5) {
				finished_cmmds++;	
			}
			if (commandLines[j].getCycle_line()[i] == 4 && (commandLines[j].getCommand() == "bne" || commandLines[j].getCommand() == "beq")) {
				std::cout << "LOOP AT MEM STAGE" << std::endl;
			}
			// std::cout << "val check: " << commandLines[j].getCycle_line()[i] << std::endl;
		}

		//prints register contents-------------------------------------------------------------------------------
		regs.print_regs();
	}
	std::cout << "----------------------------------------------------------------------------------" << std::endl;
	std::cout << "END OF SIMULATION" << std::endl;
	std::cout << std::endl;

	return 0;
}