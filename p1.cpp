#include <iostream>
#include <iomanip>
#include <fstream>
#include "regs.h"
#include "commands.h"
#include <string>
#include <vector>

void branchAndDiscard(std::vector<Commands> &commandLines, int j, int i, int loopIndex, bool &controlHazard, int &id) {
	// discard commands started (up to 3)
	int discardCount = 0;
	// i = cycleline

	// std::cout << "I: " << i << " J: " << j << std::endl;
	// increment next 3 commands to 7 (discard them)
	for (unsigned int k = j+1; k < commandLines.size(); k++) {
		if (discardCount == 3) {					// if discarded 3 commands, stop discarding
			break;
		}
		commandLines[k].setCycle_line(i, 7);		//set cycleline to 7 (*)
		commandLines[k].setDelay(discardCount + 2);
		discardCount++;
	}

	controlHazard = false;

	unsigned int ogSize = commandLines.size();

	for (unsigned int m = loopIndex; m < ogSize; m++) {
		Commands tempcmmd;
		// if (commandLines[m].getCommand() == "nop") {
		// 	ogSize++;
		// 	continue;
		// }
		tempcmmd.setWholeCommand(commandLines[m].getWholeCommand()); 
		tempcmmd.setCommand(commandLines[m].getCommand()); 	
		tempcmmd.setRegs(commandLines[m].getRegs()); 			
		tempcmmd.setID(id);
		commandLines.push_back(tempcmmd); 
		id++;
	}
}

void nopInsert(std::vector<Commands> &commandLines, int row, int cycle,int nops){
	Commands nopline;
	nopline.setCommand("nop");
	nopline.setWholeCommand("nop");
	nopline.setDelay(3);
	nopline.setCycle_line((cycle -2),1);
	nopline.setCycle_line((cycle-1),2);
	std::vector<Commands>::iterator it = commandLines.begin();
	it = it + row;
	it =  commandLines.insert(it,nopline);
}

int nopCheck(std::vector<Commands> commandLines, int row, int cycle){//checks two behind for data nop insert
	int two = row-1;
	int nops = 0;
	//std::cout << "two :" << two << " row: " << row << std::endl;
	while(two >= (row-2) && row >= 0 && two >= 0){
		//std::cout << commandLines[two].getRegs().size();
		if (commandLines[two].getRegs().size() >= 3) //if its a command with registers
		{
			
			if ((commandLines[row].getRegs()[1] == commandLines[two].getRegs()[0] || commandLines[row].getRegs()[2] == commandLines[two].getRegs()[0])) // && commandLines[two].getCycle_line()[cycle] < 5
			{	
				//std::cout << "cycle stage " << commandLines[two].getCycle_line()[cycle] << std::endl;
				//std::cout << "done?: " << !commandLines[row].getDone() << std::endl;
				//std::cout << "comparing: " << commandLines[row].getRegs()[1] << " vs " << commandLines[two].getRegs()[0] << " and " << commandLines[row].getRegs()[2] << " vs " <<commandLines[two].getRegs()[0] << std::endl;
				nops = 3 - (row - two);//might have to check this again later.......................
				//std::cout << "TRUEEEEEEEEEEEEEEEEE" << std::endl;
				break;
			}
		}
		two--;
	}
	return nops;
}

void cycleIncrement(std::vector<Commands> &commandLines, bool forwarding, int row, int cycle){
	int intstore = 0;
	if (row <= cycle) {
		//std::cout << "this is instore before: " << intstore << std::endl; //test print
		intstore = commandLines[row].getCycle_line()[cycle];
		if (cycle == 0 ) //if its the first index increment
		{
			intstore++;
		}
		else if (commandLines[row].getDelay() > 0) //if the line has delays set the cycle equal to the one prevouse
		{
			if (commandLines[row].getCycle_line()[cycle] == 7 || commandLines[row].getCommand() == "nop") {
				intstore = 7; 
			}
			else {
				intstore = commandLines[row].getCycle_line()[cycle-1]; 
			}
			commandLines[row].setDelay((commandLines[row].getDelay() -1)); 
		}
		else if (commandLines[row].getCycle_line()[cycle-1] < 6) //else grab the one prev and increment it as one 
		{
			intstore = 1 + commandLines[row].getCycle_line()[cycle-1];
		}
		// else if (commandLines[row].getCycle_line()[cycle-1] == 7) {
		// 	std::cout << "ASTERIKS!!!" << std::endl;
		// }
		else{ // this doesnt need to be here but watev
			intstore = 6;
			commandLines[row].setDone(true);
		}

		if (intstore == 5)
		{
			commandLines[row].setDone(true);
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
	int id = 0, loopIndex;
	unsigned int finished_cmmds = 0;
	unsigned int i = 0,j = 0;
	Registers regs;
	int nops = 0;
	bool controlHazard = false;
	unsigned int icopy, jcopy;

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
		if (linebuff != "loop:") {
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
			commandLines.push_back(commandline); //add to overall commandLines vector
			id++;
		}
		else if (linebuff == "loop:") {
			loopIndex = id;
		}

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
		if (commandLines[commandLines.size()-1].getDone()) {
			for (unsigned int k = 0; k < commandLines.size(); ++k)
			{
				// std::cout << "command: " << commandLines[k].getCommand() << " done?: " << commandLines[k].getDone() << std::endl;
			}
			break;
		}
		std::cout << "----------------------------------------------------------------------------------" << std::endl;
		std::cout << "CPU Cycles ===>     1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16" << std::endl;
		for (j = 0; j < commandLines.size(); ++j) { //for each row
			nops = 0;

			//nops check------------------------------------------------------------------------------------------------------------
			if (i >= 1 && j >= 1 && commandLines[j].getCycle_line()[i-1] == 2)//check stage of prev for ID
			{
				//std::cout << "nop checking in row " << i << std::endl;
				if (forwarding) //check forwarding
				{
					if (commandLines[j].getCommand() != "add" && commandLines[j].getCommand() != "and" && commandLines[j].getCommand() != "or" && commandLines[j].getCommand() != "sit") //excluse these commands
					{
						//nops = nopCheck(commandLines,j,i);
					}
				}
				else{//normal checkall
					nops = nopCheck(commandLines,j,i);// check and set nops
				}
			}
			//nops insert----------------------------------------------------------------------------------------------------------
			if (nops > 0)
			{
				//std::cout << "nop inserting in row " << i << " nops: " << nops <<  std::endl;
				commandLines[j].setDelay(nops);
				nopInsert(commandLines,j,i,nops);
			}
			//increment----------------------------------------------------------------------------------------------------------

			if (commandLines[j].getCommand() != "loop:") {
				cycleIncrement(commandLines,forwarding,j,i); //increment cycle by column
			}

			//printf command and cycle line
			if (commandLines[j].getCycle_line()[i] != 0 && commandLines[j].getCommand() != "loop:") {
				commandLines[j].print_line();	
			}

			// if command is an immediate, store digit in register
			if (commandLines[j].getCycle_line()[i] == 5 && isdigit(commandLines[j].getRegs()[2][0])) {
				regs.setRegValue(commandLines[j].getCommand(), commandLines[j].getRegs()[0], commandLines[j].getRegs()[1], std::stoi(commandLines[j].getRegs()[2]));
			}

			//if command is finished, add to number of finished commands
			if (commandLines[j].getCycle_line()[i] == 5) {
				finished_cmmds++;	
			}

			//CHECK FOR CONTROL HAZARD
			//check if branch command at MEM stage, calculate if branch should be taken
			if (commandLines[j].getCycle_line()[i] == 4 && (commandLines[j].getCommand() == "bne" || commandLines[j].getCommand() == "beq")) {
				//get values of first two registers & compare
				//if equal and beq command
				if (regs.getRegValue(commandLines[j].getRegs()[0]) == regs.getRegValue(commandLines[j].getRegs()[1]) && commandLines[j].getCommand() == "beq") {
					controlHazard = true;
					icopy = i; 
					jcopy = j;

				}
				//if not equal and bne command
				else if (regs.getRegValue(commandLines[j].getRegs()[0]) != regs.getRegValue(commandLines[j].getRegs()[1]) && commandLines[j].getCommand() == "bne") {
					controlHazard = true;
					icopy = i; 
					jcopy = j;
				}
			}
			// std::cout << "val check: " << commandLines[j].getCycle_line()[i] << std::endl;
		}
		// BRANCH SHOULD BE HERE
		if (controlHazard) {
			branchAndDiscard(commandLines, jcopy, icopy+1, loopIndex, controlHazard, id);
			// std::cout << "OUTSIDE: " << commandLines[jcopy+1].getCycle_line()[icopy+1] << std::endl;
		}
		//prints register contents-------------------------------------------------------------------------------
		regs.print_regs();
	}
	std::cout << "----------------------------------------------------------------------------------" << std::endl;
	std::cout << "END OF SIMULATION" << std::endl;

	return 0;
}