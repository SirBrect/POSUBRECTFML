#include <iostream>
#include <fstream>
//#include "regs.h"
//#include "commands.h"
#include <string.h>
#include <vector>
#include <cstring>

static int id;


int main(int argc, char const *argv[])
{
	// var_dicks-------------------------------------------------------------
	std::vector<int> commanLines; //holds command objects for as many lines
	bool forwarding = (*argv[1] == 'F'); //bool determinig forwording
	std::string linebuff; 

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
		//implement parsing here

		std::string delimiter = " ";
		size_t pos = 0;
		std::string token;
		pos = linebuff.find(delimiter);
		token = linebuff.substr(0, pos);
		std::cout << token << std::endl;//assing here
		linebuff.erase(0, pos + delimiter.length());
		delimiter = ",";
		while ((pos = linebuff.find(delimiter)) != std::string::npos) {
		    token = linebuff.substr(0, pos);
		    std::cout << token << std::endl;//assing here
		    linebuff.erase(0, pos + delimiter.length());
		}

		linebuff;
		std::cout << linebuff << std::endl;
		//Command Commands(std::string command_, int regs_, char type_, int id_)

	}



	



	return 0;
}