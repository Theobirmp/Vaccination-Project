#include "Commands.h"
#include "helpers.h"
#include "Country.h"
#include "Citizen.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "operators.h"
#include "Source.h"
#include "SearchFilterByAge.h"


using namespace std;
//injection was the simplest principle to use so that we have access to the data structures 
Commands::Commands(Args & arguments, DataStructures & structures) : arguments(arguments), structures(structures) {

}

Commands::~Commands() {

}
//just prints a ? for the user to insert a command
void Commands::prompt() {
    cout << "?";
}
//reads the user input-made a function to clean up main
string Commands::readCommand() {
    string user_input;

    getline(cin, user_input);

    return user_input;
}

/*
commands.execute(user_input)->explanation
firstly removes a specific range of characters from the start of the string
this means that you can call a command in many ways
e.g. ./command .command /command and even command
then it reads the name of the command-commands are case sensitive
by knowing which the command is the program calls the aproppriate function
note:the arguments we pass in the functions are in the wrong order!
this happens because we cant know beforehand which argument is missing - thus we dont know which is the correct order of the arguments
we resolve this problem by rearranging the arguments into each function seperately
*/
bool Commands::execute(string user_input) {
    string fun_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8;

    stringstream sso(user_input);
    sso>>fun_name;
    //removes some specific characters from the start of the string so we can call function with ./ / . or even without any of these characters
    fun_name = remove_random_chars(fun_name);

    if (fun_name == "vaccineStatusBloom") {
        sso>>arg1;
        sso>>arg2;
        vaccineStatusBloom(arg1, arg2);
    } else if (fun_name == "vaccineStatus") {
        sso>>arg1;
        sso>>arg2;
        vaccineStatus(arg1, arg2);
    } else if (fun_name == "populationStatus") { //populationStatus(string virusName, string d1="", string d2="",string country="");
        sso>>arg1;
        sso>>arg2;
        sso>>arg3;
        sso>>arg4;
        populationStatus(arg1, arg2, arg3, arg4);
    } else if (fun_name == "popStatusByAge") { //popStatusByAge country virusName date1 date2
        sso>>arg1;
        sso>>arg2;
        sso>>arg3;
        sso>>arg4;
        popStatusByAge(arg1, arg2, arg3, arg4);
    } else if (fun_name == "insertCitizenRecord") {
        sso>>arg1;
        sso>>arg2;
        sso>>arg3;
        sso>>arg4;
        sso>>arg5;
        sso>>arg6;
        sso>>arg7;
        sso>>arg8;
        string msg = insertCitizenRecord(Source::KEYBOARD, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        cout << msg << endl;
    } else if (fun_name == "vaccinateNow") {
        sso>>arg1;
        sso>>arg2;
        sso>>arg3;
        sso>>arg4;
        sso>>arg5;
        sso>>arg6;
        vaccinateNow(Source::KEYBOARD, arg1, arg2, arg3, arg4, arg5, arg6);
    } else if (fun_name == "list-nonVaccinated-Persons" || fun_name == "listNonVaccinatedPersons") {
        sso>>arg1;
        listNonVaccinatedPersons(arg1);
    } else if (fun_name == "exit") {
        return false;
    }

    return true;
}

void Commands::load(string filename) {
    ifstream myfile(filename);

    string id, firstname, lastname, country, age, diseaseName;
    string mystring;
    string yesno;
    string date;
    //opens the file and reads line by line
    //puts the appropriate values into the corresponding variables
    if (myfile.is_open()) {
        while (myfile) {
            getline(myfile, mystring);
            stringstream sso(mystring);
            sso>>id;
            sso>>firstname;
            sso>>lastname;
            sso>>country;
            sso>>age;
            sso>>diseaseName;
            sso>>yesno;
            //checks for date in the input so we know to include the actual date after the YES-NO
            if (yesno == "YES") {
                sso >> date;
            } else {
                date = "";
            }

            string arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8;

            arg1 = id;
            arg2 = firstname;
            arg3 = lastname;
            arg4 = country;
            arg5 = age;
            arg6 = diseaseName;
            arg7 = yesno;
            arg8 = date;

            string msg = insertCitizenRecord(Source::DISK, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
            if (msg != "Command successful") {
                cout << msg << endl;
            }
        }
    } else {
        cout << "this file cannot be opened" << endl;
    }

    myfile.close();
}
//the behaviour of these function is described in the pdf with the explanation of the homework
//however we are going to add some comments 
//in all of these functions there is error checking
//this means that we check that the user input is correct
//this includes diseases and ids existing 
//error checking exists before calling these function and existence of given e.g. disease happens here
void Commands::vaccineStatusBloom(string citizenID, string virusName) {
    cout << "calling vaccineStatusBloom" << citizenID << "," << virusName << endl;

    Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);

    if (activeDisease != NULL) {
        if (activeDisease->filter.contains(citizenID) == true) {
            cout << "Maybe \n";
        } else {
            cout << "No \n";
        }
    } else {
        cout << "Disease not found: " << virusName << endl;
    }
}

void Commands::vaccineStatus(string citizenID, string virusName) {
    if (virusName != "") {
        //we have given a virus name 
        cout << "calling vaccineStatus" << citizenID << "," << virusName << endl;
        //searches into the diseases tree and returns a pointer so that we know if this disease is in it
        Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);
        //if we have found the disease do the same thing for the citizen 
        if (activeDisease != NULL) {
            Citizen * citizen = (Citizen*) structures.bst_citizens->search(citizenID);

            if (citizen != NULL) {
                VaccineData * search_data = new VaccineData();
                search_data->citizen = citizen;

                VaccineData * data = (VaccineData *) activeDisease->vaccinated.search(search_data);

                if (data != NULL) {
                    //if we have found the data we need then the citizen is vacinated
                    cout << "Vaccinated at ";
                    data->date.print();
                    cout << endl;
                } else {
                    cout << "Not vaccinated \n";
                }

                delete search_data;
            } else {
                cout << "Citizen not found \n";
            }
        } else {
            cout << "Disease not found: " << virusName << endl; //these three are(didnt find disease citizen or data)
        }

    } else {
        //we havent given a virus name
        cout << "calling vaccineStatus" << citizenID << endl;

        Citizen * citizen = (Citizen*) structures.bst_citizens->search(citizenID);

        if (citizen != NULL) {
            VaccineData * search_data = new VaccineData();
            search_data->citizen = citizen;
            //inorder_process_data prints all the nodes we need 
            structures.bst_diseases->inorder_process_data(search_data);

            delete search_data;
        } else {
            cout << "Citizen not found: " << virusName << endl;
        }
    }
}
//there are 4 populationStatus ->this one has the _v to show that a virus is given
void Commands::populationStatus_v(string virusName) {

    Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);

    if (activeDisease != NULL) {
        SearchFilter filter("", "", "", activeDisease);

        structures.bst_countries->inorder_process_data(filter);
    } else {
        cout << "Disease not found: " << virusName << endl;
    }
}
//country and virus is given
void Commands::populationStatus_cv(string country, string virusName) {
    Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);

    if (activeDisease != NULL) {
        SearchFilter filter(country, "", "", activeDisease);

        structures.bst_countries->inorder_process_data(filter);
    } else {
        cout << "Disease not found: " << virusName << endl;
    }
}
//virus and dates are given
//note that both dates need to be given
//this is checked before the function is even called
void Commands::populationStatus_vdd(string virusName, string d1, string d2) {
    Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);

    if (activeDisease != NULL) {
        SearchFilter filter("", d1, d2, activeDisease);

        structures.bst_countries->inorder_process_data(filter);
    } else {
        cout << "Disease not found: " << virusName << endl;
    }
}
//country virus and dates are given
//note that both dates need to be given
//if no date is given then another the populationStatuscv will be called
void Commands::populationStatus_cvdd(string country, string virusName, string d1, string d2) {
    Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);

    if (activeDisease != NULL) {
        SearchFilter filter(country, d1, d2, activeDisease);

        structures.bst_countries->inorder_process_data(filter);
    } else {
        cout << "Disease not found: " << virusName << endl;
    }
}
//this populationStatus is used to the call the corresponding one
//here is where the error checking happens
//we check for wrong number of arguments and wrong arguments types
//e.g. user needs to insert two dates if he wants the populationStatus_cvdd
//this means that we cant have only one date and if we have two of them they need to be typed correctly
//e.g. 2-2-2010 2-2- is not a valid input 
//this is where the rearrangement of the variables happens-variables are not given to this functions in the order we want
//e.g. variable date might have country name-this is fixed in each function seperately
//this is not mandatory but it makes life much easier since we expect that a country variable should store a country name
void Commands::populationStatus(string virusName, string d1, string d2, string country) {
    //we have combined the 4 functions in 1. We can know which of the four functions we need to implement based on the number of arguments
    //1 argument->missing date and country
    //2 arguments->missing only date
    //3 arguments->missing only country
    //4 arguments->alla arguments given
    if (d1 == "" && d2 == "" && country == "") {
        if (is_date(virusName)) {
            cout << "why u input a date here???" << endl;
            return;
        }
        cout << "you only gave disease" << virusName << endl;

        //  === v ===
        printf("v \n");
        populationStatus_v(virusName);
    } else if (d2 == "" && country == "") {
        if (is_date(virusName) || is_date(d1)) {
            cout << "why u input a date here???" << endl;
            return;
        } else if (!is_date(d2)) {
            cout << "third argument should be a date" << endl;
        }
        string temp;
        temp = virusName; //we fix the seira of the arguments
        virusName = d1;
        country = temp;
        cout << "you didnt insert date" << endl;
        cout << "this is the virusName: " << virusName << endl;
        cout << "this is the country name: " << country << endl;

        //  === c v ===
        printf("c v \n");
        populationStatus_cv(country, virusName);
    } else if (country == "") {
        if (!is_date(d1) || !is_date(d2)) {
            cout << "pls enter dates correctly" << endl;
            return;
        } else if (is_date(virusName) || is_date(country)) {
            cout << "wrong call of function" << endl;
        }
        cout << "you only inserted date" << endl;
        cout << "this is virusName: " << virusName << endl;
        cout << "this is the date1: " << d1 << endl;
        cout << "this is the date2: " << d2 << endl;

        //  === v d d===
        printf("v d d\n");
        populationStatus_vdd(virusName, d1, d2);
    } else {
        string temp, temp1;
        temp = virusName;
        virusName = d1;
        temp1 = d1;
        d1 = d2;
        d2 = country;
        country = temp;

        if (!is_date(d1) || !is_date(d2) || is_date(virusName) || is_date(country)) {
            cout << "check your input again lad" << endl;
            return;
        }

        cout << "this is virusName: " << virusName << endl;
        cout << "this is the date1: " << d1 << endl;
        cout << "this is the date2: " << d2 << endl;
        cout << "this is the country: " << country << endl;

        //  === c v d d ===
        printf("c v d d \n");
        populationStatus_cvdd(country, virusName, d1, d2);
    }
}
//same concept with popStatusByAge applies here
//there are 4 functions
//the 5th one (the default popStatusbyAge) is used to call the other ones and do the apropriate error checking
void Commands::popStatusByAge_v(string virusName) {
    Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);

    if (activeDisease != NULL) {
        SearchFilterByAge filter("", "", "", activeDisease);

        structures.bst_countries->inorder_process_data(filter);
    } else {
        cout << "Disease not found: " << virusName << endl;
    }
}

void Commands::popStatusByAge_cv(string country, string virusName) {
    Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);

    if (activeDisease != NULL) {
        SearchFilterByAge filter(country, "", "", activeDisease);

        structures.bst_countries->inorder_process_data(filter);
    } else {
        cout << "Disease not found: " << virusName << endl;
    }
}

void Commands::popStatusByAge_vdd(string virusName, string d1, string d2) {
    Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);

    if (activeDisease != NULL) {
        SearchFilterByAge filter("", d1, d2, activeDisease);

        structures.bst_countries->inorder_process_data(filter);
    } else {
        cout << "Disease not found: " << virusName << endl;
    }
}

void Commands::popStatusByAge_cvdd(string country, string virusName, string d1, string d2) {
    Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);

    if (activeDisease != NULL) {
        SearchFilterByAge filter(country, d1, d2, activeDisease);

        structures.bst_countries->inorder_process_data(filter);
    } else {
        cout << "Disease not found: " << virusName << endl;
    }
}

void Commands::popStatusByAge(string virusName, string d1, string d2, string country) {
    //we have combined the 4 functions in 1. We can know which of the four functions we need to implement based on the number of arguments
    //1 argument->missing date and country
    //2 arguments->missing only date
    //3 arguments->missing only country
    //4 arguments->all arguments given
    if (d1 == "" && d2 == "" && country == "") {
        if (is_date(virusName)) {
            cout << "why u input a date here???" << endl;
            return;
        }
        cout << "you only gave disease" << virusName << endl;

        //  === v ===
        printf("v \n");
        popStatusByAge_v(virusName);
    } else if (d2 == "" && country == "") {
        if (is_date(virusName) || is_date(d1)) {
            cout << "why u input a date here???" << endl;
            return;
        } else if (!is_date(d2)) {
            cout << "third argument should be a date" << endl;
        }
        string temp;
        temp = virusName; //we fix the seira of the arguments
        virusName = d1;
        country = temp;
        cout << "you didnt insert date" << endl;
        cout << "this is the virusName: " << virusName << endl;
        cout << "this is the country name: " << country << endl;

        //  === c v ===
        printf("c v \n");
        popStatusByAge_cv(country, virusName);
    } else if (country == "") {
        if (!is_date(d1) || !is_date(d2)) {
            cout << "pls enter dates correctly" << endl;
            return;
        } else if (is_date(virusName) || is_date(country)) {
            cout << "wrong call of function" << endl;
        }
        cout << "you only inserted date" << endl;
        cout << "this is virusName: " << virusName << endl;
        cout << "this is the date1: " << d1 << endl;
        cout << "this is the date2: " << d2 << endl;

        //  === v d d===
        printf("v d d\n");
        popStatusByAge_vdd(virusName, d1, d2);
    } else {
        string temp, temp1;
        temp = virusName;
        virusName = d1;
        temp1 = d1;
        d1 = d2;
        d2 = country;
        country = temp;

        if (!is_date(d1) || !is_date(d2) || is_date(virusName) || is_date(country)) {
            cout << "check your input again lad" << endl;
            return;
        }

        cout << "this is virusName: " << virusName << endl;
        cout << "this is the date1: " << d1 << endl;
        cout << "this is the date2: " << d2 << endl;
        cout << "this is the country: " << country << endl;

        //  === c v d d ===
        printf("c v d d \n");
        popStatusByAge_cvdd(country, virusName, d1, d2);
    }
}
//used to check for conflicts
//the programme will alert for all the conflicts found(e.g. both date and country)
bool conflict(Citizen * citizen, string citizenId, string firstName, string lastName, string countryName, string age) {
    if (citizen->id != atoi(citizenId.c_str())) {
        cout << "Conflict on citizen id" << endl;
        return true;
    }
    if (citizen->firstname != firstName) {
        cout << "Conflict on citizen firstName" << endl;
        return true;
    }
    if (citizen->lastname != lastName) {
        cout << "Conflict on citizen lastName" << endl;
        return true;
    }
    if (citizen->country != countryName) {
        cout << "Conflict on citizen countryName" << endl;
        return true;
    }
    if (citizen->age != age) {
        cout << "Conflict on citizen age" << endl;
        return true;
    }

    return false;
}

string Commands::insertCitizenRecord(Source source, string citizenId, string firstName, string lastName, string countryName, string age, string virusName, string yes_no, string date) {
    //some error checking at the start
    if (yes_no == "NO" && !(date == "")) {
        return "not vacinated but u attempt to input a date at the end???";
    }
    if ((yes_no == "YES" && date == "") || (yes_no == "YES" && !is_date(date))) {
        return "vacinated but no/wrong date???";
    }
    if (yes_no == "NO") { // NO
        cout << "this is the citizenId: " << citizenId << endl;
        cout << "this is the first name: " << firstName << endl;
        cout << "this is the last name: " << lastName << endl;
        cout << "this is the country: " << countryName << endl;
        cout << "this is the age: " << age << endl;
        cout << "this is the virus name: " << virusName << endl;
        cout << "this is the yes-no: " << yes_no << endl;
        //we create a citizen pointer 
        Citizen * pcitizen = (Citizen*) structures.bst_citizens->search(citizenId);

        if (pcitizen == NULL) {
            //we create the citizen (if the pointer is not null this means the citizen already exists-should be nyll on most cases since we want to insert him/her)
            Citizen citizen(atoi(citizenId.c_str()), firstName, lastName, countryName, age);

            Citizen & cref = citizen >> structures.bst_citizens;
            //we insert country name and disease name into the corresponding trees
            //if the already exists they will not get inserted
            Country country(countryName);

            country >> structures.bst_countries;

            Disease disease(virusName, arguments.GetBloom_size(), arguments.GetLevels());

            Disease & dref = disease >> structures.bst_diseases;

            VaccineData * vacdata = new VaccineData(&cref);
            //we insert on not vacinated skip list
            dref.not_vaccinated.insert(vacdata);
        } else {
            if (conflict(pcitizen, citizenId, firstName, lastName, countryName, age)) {
                return "Conflict exists, skipping insert ";
            }

            Citizen & cref = *pcitizen;
            //same concept applies here
            Disease disease(virusName, arguments.GetBloom_size(), arguments.GetLevels());

            Disease & dref = disease >> structures.bst_diseases;

            VaccineData v_data(&cref);

            if (dref.vaccinated.search(&v_data) != NULL) {
                return "already vaccinated";
            } else {
                VaccineData * vacdata = new VaccineData(&cref);

                string s = dref.not_vaccinated.insert(vacdata);
                return s;
            }
        }

        return "Command successful";
    } else if (yes_no == "YES") { // YES
        //same code as above but now we have a date cause the citizen is vacinated
        cout << "this is the citizenId: " << citizenId << endl;
        cout << "this is the first name: " << firstName << endl;
        cout << "this is the last name: " << lastName << endl;
        cout << "this is the country: " << countryName << endl;
        cout << "this is the age: " << age << endl;
        cout << "this is the virus name: " << virusName << endl;
        cout << "this is the yes-no: " << yes_no << endl;
        cout << "this is the date: " << date << endl;

        Citizen * pcitizen = (Citizen*) structures.bst_citizens->search(citizenId);

        if (pcitizen == NULL) {
            Citizen citizen(atoi(citizenId.c_str()), firstName, lastName, countryName, age);
            //same concept as above-not citizen is vacinated
            Citizen & cref = citizen >> structures.bst_citizens;

            Country country(countryName);

            country >> structures.bst_countries;

            Disease disease(virusName, arguments.GetBloom_size(), arguments.GetLevels());

            Disease & dref = disease >> structures.bst_diseases;

            VaccineData * vacdata = new VaccineData(date, &cref);

            dref.filter.insert(citizenId);
            dref.vaccinated.insert(vacdata);
        } else {
            if (conflict(pcitizen, citizenId, firstName, lastName, countryName, age)) {
                return "Conflict exists, skipping insert ";
            }

            Citizen & cref = *pcitizen;

            Disease disease(virusName, arguments.GetBloom_size(), arguments.GetLevels());

            Disease & dref = disease >> structures.bst_diseases;

            VaccineData v_data(&cref);
            //some basic error checking
            if (dref.vaccinated.search(&v_data) != NULL) {
                return "already vaccinated";
            } else {
                if (dref.not_vaccinated.search(&v_data) == NULL) {
                    VaccineData * vacdata = new VaccineData(date, &cref);

                    string s = dref.vaccinated.insert(vacdata);
                    dref.filter.insert(citizenId);
                    return s;
                } else {
                    //there is different behavior depending on wether input is given by the keyboard or we are reding from file
                    //when we try to insert a citizen. if a not vacinated person is getting vacinated from keyboard then we remove him/her
                    //from the non vacinated skip list and insert him/her into the vacinated one
                    //this creates a conflict if the same action happens through the keyboard
                    switch (source) {
                        case DISK:
                        {
                            return "Conflict on vaccination state";
                        }
                        case KEYBOARD:
                        {
                            VaccineData * vacdata = new VaccineData(date, &cref);

                            string s = dref.vaccinated.insert(vacdata);
                            dref.not_vaccinated.remove(vacdata);
                            dref.filter.insert(citizenId);

                            return s;
                        }
                    }

                }
            }
        }

        return "Command successful";
    } else {
        return "pls insert YES or NO";
    }
}

void Commands::vaccinateNow(Source source, string citizenId, string firstName, string lastName, string country, string age, string virusName) {
    cout << "this is the citizenId: " << citizenId << endl;
    cout << "this is the first name: " << firstName << endl;
    cout << "this is the last name: " << lastName << endl;
    cout << "this is the country: " << country << endl;
    cout << "this is the age: " << age << endl;
    cout << "this is the virus name: " << virusName << endl;
    //gets current date from system and converts it from type date to type string
    Date * d = get_current_date();
    string currentDate = date_to_string(*d);
    //inserts the vacinated citizen with current date
    insertCitizenRecord(source, citizenId, firstName, lastName, country, age, virusName, "YES", currentDate);
    delete d;
}

void Commands::listNonVaccinatedPersons(string virusName) {
    cout << "this is the virus name: " << virusName << endl;

    Disease * activeDisease = (Disease *) structures.bst_diseases->search(virusName);

    if (activeDisease != NULL) {
        activeDisease->print(cout, false);
    } else {
        cout << "Disease not found: " << virusName << endl;
    }
}

