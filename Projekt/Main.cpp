#include "Maze.h"
/*
Filip Stenegren (fist2000)
2021-10-18
Siktar på ett starkt godkänt :)!
*/

void Menu();

int main()
{
	srand(time(NULL));
	
	Menu();
	int action;
	Maze M1;	//nodgeneringen sker här eftersom det inte spelar någon roll för att kunna göra nya mazes

	bool loop = true;
	while (loop)
	{
		action = 0;
		std::cin >> action;
		std::cout << std::endl << std::endl;

		if (!std::cin>> action) //rensar action ifall det vart fel input annars loopar den förevigt
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		} 

		switch (action)
		{
			case 1:

				std::cout << "creating a new maze with DFS..." << std::endl << std::endl;
				M1.DFS();
				Menu();
				break;
			
			case 2:

				std::cout << "Printing the Maze: " << std::endl << std::endl;
				M1.PrintMaze();
				Menu();			
				break;

			case 3:

				std::cout << "Shutting down the program... " << std::endl;
				loop = false;
				break;

			default:
				std::cout << "Wrong input please only input a number between 1-4: " << std::endl << std::endl;
				Menu();
				break;
		}
	}
	return 0;
}

void Menu()
{
	std::cout << "1 to create a unique maze with DFS: " << std::endl;
	std::cout << "2 to Print the Maze: " << std::endl;
	std::cout << "3 to shut down the program: " << std::endl;
	std::cout << "Write input here: ";
}


