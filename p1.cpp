#include <iostream>
#include <fstream>
#include "regs.h"
#include "commands.h"
#include <string.h>
#include <vector>





int main(int argc, char const *argv[])
{
	// var_dicks-------------------------------------------------------------
	std::vector<Commands> commandLines; //holds command objects for as many lines
	bool forwarding = (*argv[1] == 'F'); //bool determinig forwording
	std::string linebuff; 
	int id = 0,i = 0;

	//argument_checking-----------------------------------------------------
	if (argc > 3){
		std::cerr << "Invalid Arguments PAT!" << std::endl;
	}
	std::ifstream mipscode(argv[2]);
	if (!mipscode.good())
	{
		std::cerr << "Cannot Read FILE PAT!" << std::endl;
	}

	//file_reading--------------------------------------------------------------------
	while(getline(mipscode,linebuff)){

		std::string delimiter = " ";
		size_t pos = 0;
		std::string token;
		pos = linebuff.find(delimiter);
		token = linebuff.substr(0, pos); //grap the command portion from read file
		std::cout << token << std::endl;//assing here
		linebuff.erase(0, pos + delimiter.length());
		Commands commandline;
		commandline.setCommand(token); //set command portion

		delimiter = ",";
		if (token != "loop:") //if command has registers add them to tis register vector
		{
			while ((pos = linebuff.find(delimiter)) != std::string::npos) {
		    	token = linebuff.substr(0, pos);
		    	std::cout << token << std::endl;//assing here
		    	linebuff.erase(0, pos + delimiter.length());
		    	commandline.addRegs(token); // add to commandlineobj reg storage
			}
		}
		commandline.setID(id);
		commandLines.push_back(commandline); //add to overall commandlines vector
		id++;
	}

	//test print-------------------------------------------
	std::cout << "here are all the commands given and their atributes" <<std::endl;
	for (i = 0; i < commandLines.size(); ++i)
	{
		std::cout << "commmand: " << commandLines[i].getCommand() << " ~registers ";
		for (int j = 0; j < commandLines[j].getRegs().size(); ++j)
		{
			std::cout << commandLines[i].getRegs()[j] << " ";
		}
		std::cout << " Id: " << commandLines[i].getID() << std::endl;
	}



	



	return 0;
}