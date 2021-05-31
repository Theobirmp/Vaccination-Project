#include <iostream>
#include <string>
#include<fstream>
#include <sstream>
#include <cstring>


#include "Commands.h"
#include "BinarySearchTree.h"
#include "Citizen.h"
#include "Country.h"
#include "Args.h"
#include "helpers.h"
#include "Disease.h"
#include "DataStructures.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 5) {//all arguments need to be passed - nor more nor less
        cout << "not appropriate number of arguments,programme will terminate " << endl; //add more checks for arguments
        exit(0);
    }

    Args args(argc, argv);  //check constructor
    DataStructures dataStructures;//used to create the trees which will store citizens diseases and countries
    Commands commands(args, dataStructures); 
    
    commands.load(args.GetFilename()); //check Commands.cpp
    dataStructures.display(); //displays the content of the trees
    
    while (1) {
        commands.prompt(); //prints a ?
        string user_input = commands.readCommand(); //just a getline
        if (!commands.execute(user_input)) { //check end of main for the explanation
            break;
        }
    }
    return 0;
}


/*
commands.load(args.GetFilename()); ->explanation
opens the file and reads line by line (parsing) (checks if dates exists )
each argument is stored into a variable
calls insertCitizenRecord  (first argument is used to differentiate that we read from the file-check insertCitizenRecord and README for more info)
closes the file
*/