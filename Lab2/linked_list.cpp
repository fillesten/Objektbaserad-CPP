#pragma once
#include "linked_list.h"
#include <stdlib.h>
#include <iostream>

linked_list::linked_list()
{
	head = nullptr;
	tail = nullptr;
}

//skapa b utifr�n en existerande grej d�r b �r TOM 
//linket_list a;
//linked_list b(a);			this = b | src = (a)

//kopieringskonstruktorn
linked_list::linked_list(const linked_list& src)
{
	//g�r this head & tail till nullptrs f�r annars �r de ej definierad i den globala print funken 
	head = nullptr;
	tail = nullptr;
	*this = src;

}

linked_list::~linked_list() {

	while (!is_empty())
	{
		pop_front();
	}
	//f�rst�r listan med en popfunk
} 


// linked list c;
// linked list d;
// c = d; 
// this = c 
// rhs = d
// 
//tilldelningsoperatorn
linked_list& linked_list::operator =(const linked_list &rhs)
{
	
		
	if (this != &rhs)  //ifall man k�r en c = c kommer man t�mma listan ifall denna check inte finns
	{
		while (!this->is_empty()) //�r tom = true... orkar inte t�nka igenom funktionen varje g�ng
		{
			this->pop_back(); //this ska t�mmas varje g�ng 
		}
		if (!rhs.is_empty())
		{
			node* alloPtr = rhs.head;

			this->push_back(alloPtr->value);
			//l�gger till ett element som ett base case s� �r if size = 1 redan l�st
			//f�r rhs �r INTE tom s� det finns noder att l�gga till
			//s� vi b�rjar sen iterera f�rst efter
			while (alloPtr->next != nullptr )
			{
				alloPtr = alloPtr->next;
				this->push_back(alloPtr->value);
				//ordning viktig h�r m�ste ja byta VALUE innan jag pushbacka pekarens.value 
			}
		}
	}

	return *this;
}


linked_list& linked_list::operator +=(const linked_list& rhs)
{
	const size_t rhs_storlek = rhs.size(); //g�r en egen variabel annars blir det en o�ndlig loop eftersom rhs.size kommer �kas i for loopen annars.
	node* rhsPtr = rhs.head;

	for (size_t rhsCtr = 0; rhsCtr != rhs_storlek; rhsCtr++)
	{
		this->push_back(rhsPtr->value);
		rhsPtr = rhsPtr->next;
	}
	
	return *this;
}

// --- INSERT METHODS ----

void linked_list::insert(double value, size_t pos)
{
	node* Insert_node = new node(value);

	if (is_empty())
	{
		push_front(value);
	}
	else if (pos == 0)
	{
		push_front(value);
	}
	else if (size() == 1) 
	{
		if (pos >= 1)
		{
			push_back(value);
		}
		else
		{
			push_front(value);
		}
	}
	else if (pos >= size())
	{
		push_back(value);
	}
	else
	{
		size_t plussEttCheck = pos;
		plussEttCheck++;

		if (plussEttCheck == size())
		{
			push_back(value);
		}
		else
		{
			size_t insertCtr = 0;
			node* insertPtr = head;

			while (insertCtr != pos)
			{
				insertPtr = insertPtr->next;
				insertCtr++;
			}
			node* tempprev = insertPtr->prev;

			Insert_node->next = insertPtr;
			Insert_node->prev = tempprev;

			tempprev->next = Insert_node;
			insertPtr->prev = Insert_node;

		}
	}
}

void linked_list::push_front(double value)
{
	node* PF_node = new node(value);
	
	if (is_empty())
	{
		tail = PF_node;
		head = PF_node;
	}
	else if (size() == 1 )	
	{
		head = PF_node;
		PF_node->next = tail;
		tail->prev = PF_node;
	}
	else
	{
		node* Else_temp = head;
		head = PF_node;
		PF_node->next= Else_temp;
		Else_temp->prev = PF_node;
	}

}

void linked_list::push_back(double value)
{
	node* PB_node = new node(value);

	if (is_empty())
	{
		tail = PB_node;
		head = PB_node;
	}
	else if (size() == 1)
	{
		PB_node->prev = head; 
		head->next = PB_node;
		tail = PB_node;
	}
	else
	{
		//viktigt med ordningen... visualisera i excel hur det blir ifall tail = pb inte kommer sist.
		tail->next = PB_node;
		PB_node->prev = tail;
		tail = PB_node;
	}
}


// --- accessiNG ELEMENTS ---

double linked_list::front() const 
{
	if (is_empty())
	{
		//std::cout << "Front() The list has no nodes containing any value, returning NULL ";
		return NULL;
	}
	return head->value;
}

double linked_list::back() const
{
	if (is_empty())
	{
		//std::cout << "Back() The list has no nodes containing any value, returning NULL ";
		return NULL;
	}
	
	return tail->value;
}

//at ANV�NDER 0 BASERAT

double linked_list::at(size_t pos) const  
{
	if (is_empty())
	{
		//std::cout << "at() The list has no nodes containing any value, returning NULL ";
		return NULL;
	}
	else if (pos >= size())
	{
		//std::cout << "at(>=)The given positkion in the list exceeds the amount of elements, returning NULL ";
		return NULL;
	}
	else
	{
		double temp = 0;
		node* atPtr = head;
		while (temp != pos)
		{
			atPtr = atPtr->next;
			temp++;
		}
		return atPtr->value;
	}
}

// --- REMOVING ELEMENTS --- 

void linked_list::remove(size_t pos)
{
	if (is_empty()) { NULL; }
	else if (pos >= size()) 
	{ 
		NULL;
		//exit;
	}
	else if (pos == 0)
	{
		pop_front();
	}
	else if (size() == 1) 
	{ 
		pop_back(); 
		//or pop_front();
	}
	else //den kommer bara hit ifall pos �r 1 mindre eller �nnu mindre �n size()!!!
	{
		size_t plussEttCheck = pos;
		plussEttCheck++;

		if (plussEttCheck == size())
		{
			pop_back();
		}
		else
		{
			unsigned int atCtr = 0;
			node* findPtr = head;

			while (atCtr != pos)
			{
				findPtr = findPtr->next;
				atCtr++;
			}

			node* tempprev = findPtr->prev;
			node* tempnext = findPtr->next;

			tempnext->prev = tempprev;
			tempprev->next = tempnext;
			findPtr->next = nullptr;
			findPtr->prev = nullptr;
			delete findPtr;
			findPtr = nullptr;

		}
	}
}

double linked_list::pop_front()
{
	if (is_empty())
	{
		//std::cout << "in p_front the list has no nodes containing any value, returning null ";
		return NULL;
	}
	else if (size() == 1)
	{
		node* pftemp = head;
		head = nullptr;
		tail = nullptr;
		double returdouble = pftemp->value;
		delete pftemp; 
		pftemp = nullptr;
		return returdouble;
	}
	else //n�r den har 2+ element 
	{
		node* pftemp = head;
		head = head->next;
		head->prev = nullptr;
		pftemp->next = nullptr;
		double returdouble = pftemp->value;
		delete pftemp;
		pftemp = nullptr;
		return returdouble;
	}
}

double linked_list::pop_back()
{
	
	if (is_empty())
	{
		return NULL;
	}
	else if (size() == 1)
	{
		node* pbtemp = head;
		head = nullptr;
		tail = nullptr;
		double returdouble = pbtemp->value;
		delete pbtemp;
		pbtemp = nullptr;
		return returdouble;
	}
	else //n�r den har 3+ element funkar det men vet ej ifall endast 2 funkar
	{
		node* pbtemp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		pbtemp->prev = nullptr;
		double returdouble = pbtemp->value;
		delete pbtemp;
		pbtemp = nullptr;
		return returdouble;
	}
	return 0;
}

//								--- STATUS ---									

//size ANV�NDER EJ 0 BASERAT / DEN GER EN EN OUTPUT P� 50 
//MEDANS AT FUNKTIONEN ENDAST KAN TA EMOT UP EMOT 49

size_t linked_list:: size() const
{	 
	if (is_empty()) 
	{ 
		return NULL; 
	} 
	else
	{
		node* sizeptr = this->head;
		size_t storlek;
		for (storlek = 0; sizeptr != nullptr; storlek++, sizeptr = sizeptr->next) {  }
		return storlek;
	}
}

bool linked_list::is_empty() const 
{
	if (head == nullptr && tail == nullptr) { return true; }
	else { return false; }
	//testar b�de head och tail f�r att l�ttare kunna debugga / se ifall 
	//jag gl�mt att g�ra head/tail->prev/next till nullptr
}


// --- OUTPUT --- 																			 ---------DONE-------------

void linked_list::print() const // denna funkar so far
{
	if (!is_empty())
	{
		std::cout << "| ";
		for (node* printptr = head; printptr != nullptr; printptr = printptr->next)
		{
			std::cout << printptr->value << " | ";
		}
		std::cout << std::endl << std::endl;
	}
}

void linked_list::print_reverse() const //denna funkar so far
{
	if (!is_empty())
	{
		std::cout << "| ";
		for (node* printreverse = tail; printreverse != nullptr; printreverse = printreverse->prev)
		{
			std::cout << printreverse->value << " | ";
		}
		std::cout << std::endl;
	}
}

//konstruktor f�r noden! h�r skulle n�nting fixas.
linked_list::node::node(double value)
{
	this->value = value;
	next = nullptr;
	prev = nullptr;
}


////exempel p� utstr�msoperator
////det kommer kaosa ifall ja inte g�r denna till en friend som f�r tillg�ng till privata medlemmar i klassen
//std::ostream& operator<<(std::ostream& os, const linked_list& listnr)
//{
//	std::cout << "skriv n�nting om va head � tail �r � kanske n�n size_t" << std::endl;
//	//node* osPtr = listnr.head 
//	return os;
//}
//
//std::istream& operator>>(std::istream& in, linked_list& listnr)
//{
//	//kanske inte beh�ver men �r till f�r att mata in ett specifikt value in i en funktion med cin / user input
//	return in;
//}




