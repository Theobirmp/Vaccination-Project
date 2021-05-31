OBJS	= Args.o BinarySearchTree.o BloomFilter.o Citizen.o Commands.o compare_dates.o Country.o Data.o DataStructures.o Date.o Disease.o helpers.o main.o operators.o SkipList.o VaccineData.o
SOURCE	= Args.cpp BinarySearchTree.cpp BloomFilter.cpp Citizen.cpp Commands.cpp compare_dates.cpp Country.cpp Data.cpp DataStructures.cpp Date.cpp Disease.cpp helpers.cpp main.cpp operators.cpp SkipList.cpp VaccineData.cpp
HEADER	= 
OUT	= vaccineMonitor
CC	 = g++
FLAGS	 = -g -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Args.o: Args.cpp
	$(CC) $(FLAGS) Args.cpp 

BinarySearchTree.o: BinarySearchTree.cpp
	$(CC) $(FLAGS) BinarySearchTree.cpp 

BloomFilter.o: BloomFilter.cpp
	$(CC) $(FLAGS) BloomFilter.cpp 

Citizen.o: Citizen.cpp
	$(CC) $(FLAGS) Citizen.cpp 

Commands.o: Commands.cpp
	$(CC) $(FLAGS) Commands.cpp 

compare_dates.o: compare_dates.cpp
	$(CC) $(FLAGS) compare_dates.cpp 

Country.o: Country.cpp
	$(CC) $(FLAGS) Country.cpp 

Data.o: Data.cpp
	$(CC) $(FLAGS) Data.cpp 

DataStructures.o: DataStructures.cpp
	$(CC) $(FLAGS) DataStructures.cpp 

Date.o: Date.cpp
	$(CC) $(FLAGS) Date.cpp 

Disease.o: Disease.cpp
	$(CC) $(FLAGS) Disease.cpp 

helpers.o: helpers.cpp
	$(CC) $(FLAGS) helpers.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

operators.o: operators.cpp
	$(CC) $(FLAGS) operators.cpp 

SkipList.o: SkipList.cpp
	$(CC) $(FLAGS) SkipList.cpp 

VaccineData.o: VaccineData.cpp
	$(CC) $(FLAGS) VaccineData.cpp 


clean:
	rm -f $(OBJS) $(OUT)
