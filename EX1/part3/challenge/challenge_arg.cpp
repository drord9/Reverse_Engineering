// challenge.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Write a program that counts the resources needed to buy or build the given goals. Each line in the input contains a single goal from {road, settlement, city, development}.

The program outputs 2 digit costs, space separated, with a new line at the end.
For example, given the input: [road, road, city, development]
the returned value would be the following: 02 02 01 03 04 [WOOD, BRICK, WOLL, GRAIN, ORE]
*/

enum resources { WOOD, BRICK, WOLL, GRAIN, ORE, NUM_OF_RESOURCES };

typedef int(*strCmpPtr)(const char*, const char*);
typedef int(*printPtr)(const char*, ...);

void* GetFuncAdd(char*);

void GetCosts(char* goal, int* resources)
{
    char _strcmp[]      = "strcmp";
    char road[]         = "road";
    char settlement[]   = "settlement";
    char city[]         = "city";
    char development[]  = "development";

    strCmpPtr strcmp = (strCmpPtr)GetFuncAdd(_strcmp);

	if (!strcmp(goal, road))
	{
		resources[WOOD]++;
		resources[BRICK]++;
	}
	else if (!strcmp(goal, settlement))
	{
		resources[WOOD]++;
		resources[BRICK]++;
		resources[WOLL]++;
		resources[GRAIN]++;
	}
	else if (!strcmp(goal, city))
	{
		resources[GRAIN] += 2;
		resources[ORE] += 3;
	}
	else if (!strcmp(goal, development))
	{
		resources[WOLL]++;
		resources[GRAIN]++;
		resources[ORE] ++;
	} 
}


int main(int argc, char* argv[])
{
    int resources[NUM_OF_RESOURCES] = { 0 };
    char print_str[]    = "%02d ";
    char _printf[]      = "printf";
    char endl[]         = "\n";
	
	printPtr print = (printPtr)GetFuncAdd(_printf);

    for (int i = 1; i < argc; ++i)
    {
        GetCosts(argv[i], resources);
    }

	//print resources
	for (int i = 0; i < NUM_OF_RESOURCES; ++i)
	{
    	print(print_str, resources[i]);
	}

    print(endl);
    return 0;
}

