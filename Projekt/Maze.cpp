#include "Maze.h"
/*
Filip Stenegren (fist2000)
2021-10-18
Siktar på ett starkt godkänt :)!
*/


Maze::Maze()
{
	std::vector< std::vector <node>> Row;
	//etablerar en Row för varje instans av en maze har en Row
	Generate();
}

void Maze::DFS()
{
	for (std::vector<node> vect1D : Row)
	{
		for (node &a : vect1D)  // sätter alla boolvärden till false för
		{						// möjligheten till loopar med att göra nya mazes
			int y = a.y;
			int x = a.x;		// flytta till konstruktorn

			Row[y][x].visited = false;
			Row[y][x].Up = false;
			Row[y][x].Down = false;
			Row[y][x].Right = false;
			Row[y][x].Left = false;
		}
	}

	//(y,x) y = ^v , x = <-> 
	//				   y  x   
	node N = this->Row[0][0];
	N.visited = true;

	this->Row[N.y][N.x].visited = true;
	std::stack<node> S;
	S.push(N);
	int B = 0;
	while (!S.empty())
	{

		N = S.top();
		S.pop();
		if (NeighCheck(N))
		{
			S.push(N);
			node G = RandNeigh(N);
			this->Row[G.y][G.x].visited = true;												
			Gates(G, N);				
			G.visited = true;
			S.push(G);
		}

		B++;
	}
	//std::cout << B << std::endl; var ba en check för å se ifall den visitat alla för 49 är nå golden number typ 
	
}

void Maze::Generate() 
{
	for (int row = 0; row < 5; row++)
	{
		std::vector<node> ColumnVector; 

		for (int col = 0; col < 5; col++)
		{
			node rownode = node(row, col);
			ColumnVector.push_back(rownode);
		}
		Row.push_back(ColumnVector); //här pushbackar vi en vector in i en Row, så Row blir 2D
	}
}

/*  moving/checking in my 2D vector:
	Left	[y][x-1]
	Right	[y][x+1]
	Down	[y+1][x]
	Up		[y-1][x]

		  0  1  2   X
		⬛⬛⬛⬛⬛⬛⬛
	0   ⬛⬜⬛⬜⬛⬜⬛
	1   ⬛⬜⬛⬜⬛⬜⬛
	2   ⬛⬜⬛⬜⬛⬜⬛
	Y	⬛⬛⬛⬛⬛⬛⬛

*/


//ska ge tillbaka en random neighNod
Maze::node Maze::RandNeigh(node nod)
{
	std::vector<node> Neighs; //här måste vi ju spara våra grannar som inte är visited 
	int x = nod.x;			  //jämfört med bool neigh checken
	int y = nod.y;			  //sparar alla grannar som inte är visisted och randomizar här

	if (x > 0 )
	{
		if (this->Row[y][x - 1].visited == false)
		{
			Neighs.push_back(this->Row[y][x - 1]);
		}
	}
	if (x < 4)
	{
		if (this->Row[y][x + 1].visited == false)
		{
			Neighs.push_back(this->Row[y][x + 1]);
		}
	}
	if (y > 0)
	{
		if (this->Row[y - 1][x].visited == false)
		{
			Neighs.push_back(this->Row[y - 1][x]);
		}
	}
	if (y < 4)
	{
		if (this->Row[y + 1][x].visited == false)
		{
			Neighs.push_back(this->Row[y + 1][x]);
		}
	}

	size_t Check = Neighs.size();

	int stop = Check;
	int slump = rand() % stop;

	switch (slump)
	{
	case 0:

		return Neighs[0];
		break;

	case 1:
		return Neighs[1];
		break;

	case 2:
		return Neighs[2];
		break;

	default:
		break;
	}
}

bool Maze::NeighCheck(node n) 
{
	int x = n.x;
	int y = n.y;

	if (y > 0) //kolla neighbors Uppåt // den behöver bara hitta en i den här funktionen
	{
		if (Row[y - 1][x].visited == false)
		{
			return true;
		}
	}
	if (y < 4 ) // kolla neighbors Neråt // har den en granne så ska vi fortsätta ba liksom
	{
		if (Row[y + 1][x].visited == false)
		{
			return true;
		}
	}
	if (x > 0) //kolla neighbors Vänster
	{
		if (Row[y][x - 1].visited == false)
		{
			return true;
		}
	}
	if (x < 4) // kolla neighbors Höger
	{
		if (Row[y][x + 1].visited == false)
		{
			return true;
		}
	}
	return false;
}


/*  moving in my 2D vector:
	Left	[y][x-1]
	Right	[y][x+1]
	Down	[y+1][x]
	Up		[y-1][x]

		  0  1  2   X
		⬛⬛⬛⬛⬛⬛⬛
	0   ⬛⬜⬛⬜⬛⬜⬛
	1   ⬛⬜⬛⬜⬛⬜⬛
	2   ⬛⬜⬛⬜⬛⬜⬛
	Y	⬛⬛⬛⬛⬛⬛⬛

*/

void Maze::Gates(node G, node N)
{
	int NuX = this->Row[N.y][N.x].x; //Nuvarande nodens X värde.. NuX
	int NuY = this->Row[N.y][N.x].y; //...
	int GrX = this->Row[G.y][G.x].x; //noden Grannens X värde .. GrX
	int GrY = this->Row[G.y][G.x].y; //...

	if (GrX == NuX) // om x är lika rör vi oss upp / ner
	{
		if (GrY > NuY && this->Row[G.y][G.x].Up == false)
		{
			this->Row[G.y][G.x].Up = true;
			this->Row[N.y][N.x].Down= true;
		}
		if (GrY < NuY && this->Row[G.y][G.x].Down == false)
		{
			this->Row[G.y][G.x].Down = true;
			this->Row[N.y][N.x].Up = true;
		}
	}
	if (GrY == NuY) // om y är lika rör vi oss åt sidan
	{
		if (GrX > NuX && this->Row[G.y][G.x].Left == false)
		{
			this->Row[G.y][G.x].Left = true;
			this->Row[N.y][N.x].Right = true;
		}
		if (GrX < NuX && this->Row[G.y][G.x].Right == false)
		{
			this->Row[G.y][G.x].Right = true;
			this->Row[N.y][N.x].Left = true;
		}
	}
}


Maze::node::node(int y, int x)
{
	this->y = y;
	this->x = x;

	Up = false;
	Down = false;
	Left = false;
	Right = false;
	visited = false;
}


void Maze::PrintMaze() const
{
	std::cout << "OOOOOOOOOeO" << std::endl; //hårdkodad topprad

	std::vector<std::string> NradV; //NodRadenVectorn
	std::vector<std::string> UradV; //UnderRadVectorn
	//Urad += O;

	for (std::vector<node> vect1D : Row) //
	{
		std::string Nrad;
		std::string Urad; 
		Nrad += 'O';			//vänster vägg
		Urad += 'O';	
		for (node &a : vect1D)	//för varje nod som undersöks gör vi en space alltid
		{						//för den ska vara besökt / öppen på något sätt
			Nrad += ' ';
			int y = a.y;
			int x = a.x;
			if (Row[y][x].Right)
			{
				Nrad += ' '; //manöppnar väggen bara för nästa nod öppnas automatiskt
			}
			else
			{
				Nrad += 'O'; //annars gör man en vägg till höger om noden
			}

			if (Row[y][x].Down )
			{	
				Urad += ' '; //öpnnar väggen neråt mod den undre noden
			}
			else
			{
				Urad += 'O'; //annars gör man en vägg neråt
			}
			Urad += 'O';	//vad som en händer i Urad måste man lägga till en extra vägg för clariy
							//den här hamnar / eller \ riktningarna 
			
		}
		NradV.push_back(Nrad);
		UradV.push_back(Urad);
		
	}
	std::cout << NradV[0] << std::endl;
	std::cout << UradV[0] << std::endl;

	std::cout << NradV[1] << std::endl;
	std::cout << UradV[1] << std::endl;

	std::cout << NradV[2] << std::endl;
	std::cout << UradV[2] << std::endl;
	
	std::cout << NradV[3] << std::endl;
	std::cout << UradV[3] << std::endl;

	std::cout << NradV[4] << std::endl; 

	std::cout << "OsOOOOOOOOO" << std::endl<<std::endl;

	//vill inte printa ut sista UradV för då blir det en vägg för mycket
	//kan säkert lösa det bättre med att iterera igenom nån av doms size -1 
	//å sen printa ut nradV.back() eller nå liknande
				  
}

/*  moving in my 2D vector:
	Left	[y][x-1]
	Right	[y][x+1]
	Down	[y+1][x]
	Up		[y-1][x]

		  0  1  2  3  4 X
		⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛
	0   ⬛⬜⬛⬜⬛⬜⬛⬜⬛⬜⬛
		⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛
	1   ⬛⬜⬛⬜⬛⬜⬛⬜⬛⬜⬛
		⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛
	2   ⬛⬜⬛⬜⬛⬜⬛⬜⬛⬜⬛
		⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛
	3	⬛⬜⬛⬜⬛⬜⬛⬜⬛⬜⬛
		⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛
	4   ⬛⬜⬛⬜⬛⬜⬛⬜⬛⬜⬛
	Y	⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛

*/