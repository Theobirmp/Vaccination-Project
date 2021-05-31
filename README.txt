Μπιρμπίλης Θεοφάνης 1115201600110

compilation command-make (check makefile)
run command->./vaccineMonitor -c citizenRecordsFile –b bloomSize

When running the programme you need to specify all arguments and give them in this order.

when the programme begins it reads the file.txt we have specified in the arguments. It creates the data structures needed to run the application. This includes three trees(citizen,country,disease)
the skip lists and the bloom filters. The user is faced with a prompt (?) and can call each of the given functions to e.g. check on the status of the citizens or vacinate someone.
Note that the commands need to be typed EXCACTLY the way they are written in the homework description and not any other way. The arguments should be given in the correct order and the correct
number so that the commands are executed. If not, the programme continues with not problem and nothing happens. Note that u can call a command
even without the ./
This means that you can call a fucntion in multiple ways
e.g. function ./function .function /function etc.
There is a function that removes a set of random characters from the start of the command. This is easy to be altered in case we want to call each function with more or less ways.
Error checking happens before we call a function. This means that e.g. the user must insert a date type into the date argument. if some info of the date is missing then the date is invalid and the command cant be executed. The same concept applies for the rest of the arguments.
Programme is terminated by typing exit. This way all the data structures are deleted and no leaks happen. Pls dont terminate the programme with ctrl c cause the destructors will never get
called and there will be memory leaks. If terminated correctly the programme has no memory leaks.


Note:whenever we are refering to a tree we mean a binary one.

General notes:
There is one tree implementation that is used to house all the trees needed. In this project we need three trees. This means that we have to include  a data type in the tree (a superclass) 
for the data to be stored. This is solved easily through C++ cause we can make the Classes Citizen Country and Disease inherit from the their mother class Data. This way we can achieve 
one implementation of the tree but have an infinite amount of different types of trees.
Note that this causes a lot of problems. E.g. we have to overload a lot of operators so that we can e.g. compare different types of values
Some operator overloading is mandatory.
E.g. we overload the < > and == operators to be able to work with strings.
Some others are not, but are overloaded for better cohision of the code
E.g. >> is used to insert to a tree
Note that these operators need to be overloaded more than once sometimes cause we work with different arguments each time.

Commands contructor has a reference to arguments and datastructures classes. This is the easiest and most readable way to give access these types to commands class. This is called
injection.

populationStatus and popStatusByAge are two functions that each split into four. The names of them include the letters c v d d to show which arguments are being given,cause there is slightly different implementation based on that.

Note that whenever we need to pass arguments to a function we need to alter them. This happens cause we cant know beforehand how many they are. We just need to swap some values.
This is not mandatory but helps the readability of the code cause it is logical that a variable called country holds a country name.

All the functions calculate results based on the latest updates on piazza. 

Source.h has an enum used for one very specific case. In case we want to vacinate a citizen from the keyboard we should remove him from the non vacinated skip list and insert him/her into the vacinated one. The same concept does not apply to when we read from a file. This record should be thrown away. This enum serves this and only this purpose.



