#include <iostream>
#include "linked_list.h"
#include <time.h>
#include <cstdlib>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void ShowMenu();

void print_list(linked_list l)
{
	l.print();
}

linked_list merge(linked_list& a, linked_list& b);

bool is_sorted(linked_list l) ;



int main()
{
	srand(time(NULL));

	linked_list a;
	linked_list b;
	linked_list c;
	linked_list d;


	int menyint;		
	do
	{
		ShowMenu();
		//std::cout << "Enter value here: ";
		std::cin >> menyint;
		std::cout << std::endl << std::endl;
		switch (menyint)
		{
			case 1:
			{
				std::cout << std::endl;
				double pbvalue1 = 1.0 + rand() % 4;
				for (int i = 0; i != 50; i++)
				{
					//pushbackar valuet som skapades innan
					a.push_back(pbvalue1);
					int slump_incre1 = rand() % 5;
					pbvalue1 += slump_incre1;
				}
				print_list(a);

				std::cout << "------ ^  A  ^ ------" << std::endl <<
							 "------ v  B  v ------" << std::endl << std::endl;

				double pbvalue2 = 1.0 + rand() % 4;
				for (int i = 0; i != 50; i++)
				{
					b.push_back(pbvalue2);
					int slump_incre2 = rand() % 5;
					pbvalue2 += slump_incre2;
				}
				print_list(b);
				break;
			}
			case 2:
			{

				std::cout << std::endl << std::endl;
				std::cout << "a.at 24: " << a.at(24) << " | b.at 24: " << b.at(24) << std::endl << std::endl;

				//ta bort 25:e elementet:: då måste remove vara på 24 
				//eftersom at och remove börjar RÄKNA på 0  
				//medans size ger 0 ifall den e tom å 1 om en node osv.
				if (b.at(24) > a.at(24))
				{
					b.remove(24);
				}
				else if (a.at(24) >= b.at(24))
				{
					a.remove(24);
				}
				std::cout << "size of list A: " << a.size() << std::endl << std::endl;
				std::cout << "size of list B: " << b.size() << std::endl << std::endl;
				break;
			}
			case 3:
			{
				std::cout << std::endl;

				if (b.size() == 50)
				{
					c = a;
					std::cout << "C = A " << std::endl;
				}
				else
				{
					c = b;
					std::cout << "C = B " << std::endl;
				}
				std::cout << "size of list C: " << c.size() << " |  C printed in reverse V" << std::endl << std::endl;
				c.print_reverse();
				std::cout << std::endl << std::endl;
				break;
				
			}
			case 4:
			{
				std::cout << std::endl;

				if (b.size() == 50)
				{
					std::cout << "B Before: " << std::endl;
					print_list(b);
					std::cout << std::endl;

					for (int i = 0; i != 25; i++)
					{
						b.pop_back();
						b.push_front(b.pop_back());
					}
					
				}
				else
				{
					std::cout << "A Before: " << std::endl;
					print_list(a);
					std::cout << std::endl;
					for (int i = 0; i != 25; i++)
					{
						a.pop_back();
						a.push_front(a.pop_back());
					}
				

				}
				break;
			}
			case 5:
			{
				std::cout << std::endl;

				if (b.size() == 25)
				{
					std::cout << "B After: " << "size of list B: " << b.size() << std::endl << std::endl;
					print_list(b);
				}
				else
				{
					std::cout << "A After: " << "size of list A: " << a.size() << std::endl << std::endl;

					print_list(a);
				}
				break;
			}
			case 6:
			{
				std::cout << std::endl;


				d = merge(a, b);

				std::cout << "D After: " << "size of list D: " << d.size() << std::endl << std::endl;
				print_list(d);
				break;
			}
			case 7:
			{
				std::cout << std::endl;
				if (is_sorted(d))
				{
					std::cout << "The list is sorted!" << std::endl << std::endl;
				}
				else
				{
					std::cout << "The list is NOT sorted!" << std::endl << std::endl;
				}
				break;
			}
			case 0:
			{
				break; 
			}
			default:
			{
				std::cout << "Only enter a value between 0-7 " << std::endl;
				
			}
		}
	}
	while (menyint != 0);

	return 0;
}


linked_list merge(linked_list& a, linked_list& b)
{
	linked_list c;
		
	while (!a.is_empty() && !b.is_empty()) //har en dubbelcheck här eftersom ifall ena är tom kan jag använda += på resterande lista.
	{
		if (a.front() < b.front()) //checkar listornas value på front å pbar sen den mindre till c å tar sen bort den noden
		{
			c.push_back(a.front());
			a.pop_front();
		}
		else if (b.front() < a.front())
		{
			c.push_back(b.front());
			b.pop_front();
		}
		else  
		{
			c.push_back(a.front());
			a.pop_front();
		}
	}
	if (a.is_empty())
	{

		c += b;
		while (!b.is_empty())
		{
			b.pop_front();
		}
	}
	else if (b.is_empty())
	{
		c += a;
		while (!a.is_empty())
		{
			a.pop_front();
		}
	}
	return c;
}

void ShowMenu()
{
	std::cout << "Menu for the lab. Select an interger between 0-7 " << std::endl;
	std::cout << "1 for Push_back			(pushbacks 50 doubles into two separate lists)"
		<< std::endl << "2 for At and Remove		(tar bort det större 25e objektet i listorna)"
		<< std::endl << "3 for operator=			(creates a third list and inserts the smaller of the two into it and prints it reversed)" 
		<< std::endl << "4 for Pop_back and Push_front	(clears every other element in the list still containing 50 elements)"
		<< std::endl << "5 for Print_list		(calls the global print function)"
		<< std::endl << "6 for Merge			(merges the lists creating a list with 49+25= 74 elements)"
		<< std::endl << "7 for Sort check		(calls the is sorted function)" 
		<< std::endl << "0 to Exit			(shuts down the program)	"  
		<< std::endl << std::endl
		<< "Enter value here: ";

}

bool is_sorted(linked_list l)
{
	size_t at = 0;
	size_t at2 = 1;

	//skapar size_t:s för at.functionen å itererar tills slutet.
	
	if (!l.is_empty())
	{
		if (l.size() == 1)
		{
			return true;
		}

		while (at2 != l.size())
		{

			if (l.at(at) > l.at(at2))
			{
				return false;
			}
			at++;
			at2++;
		}
		return true;
	}
}