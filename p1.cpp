#include <iostream>
#include <fstream>
#include "regs.h"
#include "commands.h"

static int id;


int main(int argc, char const *argv[])
{
	// var dicks-------------------------------------------------------------
	std::vector<Commands> commanLines; //holds command objects for as many lines
	bool forwarding = (*argv[1] == 'F'); //bool determinig forwording
	if (argc > 3){
		std::cerr << "Invalid Arguments PAT!" << std::endl;
	}
	std::ifstream mipscode(argv[2]);
	if (!mipscode.good())
	{
		std::cerr << "Cannot Read FILE PAT!" << std::endl;
	}

	
	



	return 0;
}