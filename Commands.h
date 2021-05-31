#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

#include "DataStructures.h"
#include "Args.h"
#include "Source.h"

using namespace std;

class Commands {
public:
//dependency injection used
    Commands(Args & arguments, DataStructures & structures);
    virtual ~Commands();

    void prompt();
    string readCommand();
    bool execute(string command);
    
    void load(string filename);
    
    // TODO: change all void to string
    void vaccineStatusBloom(string citizenID, string virusName);
    void vaccineStatus(string citizenID, string virusName = "");

    //void populationStatus(string virusName, string citizenID ="", string d1 = "", string d2 = "");
    void populationStatus(string virusName, string d1 = "", string d2 = "", string country = ""); //if the function is called with default args in d1 or d2 its an error
    void popStatusByAge(string virusName, string d1 = "", string d2 = "", string country = "");
    string insertCitizenRecord(Source source, string citizenId, string firstName, string lastName, string country, string age, string virusName, string yes_no, string date = "");
    void vaccinateNow(Source source, string citizenId, string firstName, string lastName, string country, string age, string virusName);
    void listNonVaccinatedPersons(string virusName);
private:
    DataStructures & structures;
    Args & arguments;
    
    void populationStatus_v(string virusName);
    void populationStatus_cv(string country, string virusName);
    void populationStatus_vdd(string virusName, string d1, string d2);
    void populationStatus_cvdd(string country, string virusName, string d1, string d2);
    
    void popStatusByAge_v(string virusName);
    void popStatusByAge_cv(string country, string virusName);
    void popStatusByAge_vdd(string virusName, string d1, string d2);
    void popStatusByAge_cvdd(string country, string virusName, string d1, string d2);
};

#endif /* COMMANDS_H */

