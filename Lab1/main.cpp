/*
Filip Stenegren
DTATG_HT20
Objektbaserad programmering i c++
LAB1.cpp
2021-05-03
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <iomanip>
#include <cctype>
#include <functional>
#include <limits>


// Mans Hansson     -namn-
// 8510309159       -personnummer / id -
// Bössgränd 90, 373 02  RAMDALA   
// -Gatuadress- -post#-  -Stad-


// SKRIV CHCP 1252 i terminalen fï¿½r att fï¿½ svenska bokstï¿½ver
struct adress {
    std::string street;
    int zip;
    std::string city;
};

struct person {
    std::string name;
    std::string id;
    adress location;  
};

std::ostream& operator<<(std::ostream& os, person p)
{
    os << p.name << ", " << p.id << ", " << p.location.street<< ", "; 
    os << p.location.zip << ", " << p.location.city <<std::endl;
        
    return os;
}

std::istream& operator >>(std::istream& in, person& p)
{
    
    std::string twospace = "  ";
    std::getline(in, p.name);
    std::getline(in, p.id);
    std::getline(in, p.location.street, ',');
    in.ignore(1);
    std::string tempstring1, tempstring2;

    std::getline(in, tempstring1, ' ');
    std::getline(in, tempstring2, ' ');
    tempstring1 = tempstring1 + tempstring2;
    in.ignore(1);

    if (!tempstring1.empty()) {  p.location.zip = std::stoi(tempstring1); }

    std::string Ta_Hela_Raden_Temp;
    std::getline(in, Ta_Hela_Raden_Temp);
    //nu tar vi från första bokstaven på namnet till endl
    //den här börjar på 0 vilket alltid är efter zip-adressen 
   
    size_t CitySize = Ta_Hela_Raden_Temp.find(twospace);
    // size_t blir längden på själva staden
    if (CitySize !=std::string::npos)
    {
        p.location.city = Ta_Hela_Raden_Temp.substr(0, CitySize);
    }
    else
    {
        p.location.city = Ta_Hela_Raden_Temp;
    }

    return in;
}

int toUpper(char C);

std::vector<person> read_file (std::string filename);
int valfunk (int val);



size_t find_in_names(std::vector <person> haystack, std::string name_part);

std::vector <person> find_person_from_city (std::vector <person> haystack ,std::string city );






int main()
{

    std::vector<person> haystack = read_file("names.txt");

    std::string city, name_part; 
    bool done = false;
    while (!done)
    {
        int val;
        std::cout <<std::endl<<"What do you want to do, write the number corresponding to the action."<<std::endl;
        std::cout <<"'1' to search for a person."<<std::endl << "'2' to search for a person IN a city."<<std::endl
        <<"'3' to print out all contacts."<<std::endl
        <<"'4' to shut down the program."<<std::endl<<std::endl;
        std::cout << "Write your input here: ";
        if (!(std::cin >> val) || val > 4)  // kollar att anvï¿½ndaren matade in ett acceptabelt vï¿½rde i variabeln.
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // den hï¿½r gï¿½r att nï¿½r man trycker pï¿½ enter fï¿½r att ange variabeln sï¿½ kommer den inte 
            // att ignorera en rad. dvs utan den kan vissa kommandon komma att skippas eller inte visas.
        }
        std::cout << std::endl;
        switch (val)
        {
            case 1:
            {   
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You're now searching for a person"<<std::endl;
                std::cout <<"input the name of who you are searching for: ";
                getline(std::cin, name_part);
                size_t temp = find_in_names(haystack, name_part);
                
                
                std::cout<<std::endl<<"You found "<<temp<<" matches with that keyword"<<std::endl;
                break;
            }
            case 2:
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //std::cout << "You're now searching for a person in a city"<<std::endl;
                std::cout<<"You're searching for people in a city"<<std::endl;
                std::cout<<"Input the name of the city: ";
                getline(std::cin, city);
                std::cout<<std::endl;

                // std::cout<<"INNAN FUNKTIONEN VAD ÄR cityVAR. "<<city<<std::endl;


                std::vector<person> citytemp = find_person_from_city(haystack, city);

                for (person p : citytemp)
                {
                    std::cout<< p.id<<", "<< p.name<<", "<< p.location.city<<std::endl;
                }
                
                //fråga varför den inte fungerar !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //std::cout<<citytemp[0].id<<std::endl;
                //DENNA PRintar ut första matchningens id de va 
                // därför det vart för mycket utskrift


                if (citytemp.empty())
                {
                    std::cout<<"hittade inga personer i den staden"<<std::endl;
                }
                break;
            }
            case 3:
            {
                for (person p : haystack)
                {
                    std::cout << p;
                } 
                std::cout<<"printar ut allt innehåll ifrån names.txt"<<std::endl;
                break;
            }
            case 4:
            {
                std::cout << "This is going to shut down the program" <<std::endl;
                std::cout << "Goodbye!"<<std::endl;
                
                done = true;
                break;
                return 0;
            }
            default:
            {
                std::cout << "Default case: please only input a number between 1-4"<<std::endl;
                break;
            }
        }
    }
      
    return 0;
}



size_t find_in_names(std::vector <person> haystack, std::string name_part)
{
    size_t temp = 0;
    std::string tempname;
    std::transform(name_part.begin(), name_part.end(), name_part.begin(), ::tolower);
    
    // std::cout<<"Detta är name_part "<<name_part<<std::endl;

    for (std::vector<person>::iterator Piter = haystack.begin(); Piter != haystack.end(); *Piter++)
    {   
        tempname = Piter->name;
        std::transform(tempname.begin(), tempname.end(), tempname.begin(), ::tolower);

        if (tempname.find(name_part) != std::string::npos)
        {
            temp++;
            // std::cout<<"Detta är piter name -> "<<Piter->name<<" det här är name_part "<<name_part<<std::endl;
        }
    }

    return temp;
}


std::vector <person> find_person_from_city (std::vector <person> haystack, std::string city )
{
    std::transform(city.begin(), city.end(), city.begin(), toupper);

    while (city.find("å") != std::string::npos)
    {
        city.replace(city.find("å"), 1,  "Å");
    }
    while (city.find("ä") != std::string::npos)
    {
        city.replace(city.find("ä"), 1,  "Ä");
    }
    while (city.find("ö") != std::string::npos)
    {
        city.replace(city.find("ö"), 1,  "Ö");
    }
    //åäö funkar ej med vanlig to-upper/lower
    //åäö touppergrejen fungerrar men själva sökgrejen funkar inte med åäö
    //annars funkar det som det ska

    // std::cout<<"UTANFÖR funktionen är city variabeln... |"<<city<<"| "<<std::endl;
    std::vector<person> citytemp;
    std::vector<person> cityvector;

    // for (size_t i = 0; i < haystack.size(); i++)    
    // {
    //     if ( haystack[i].location.city == city )
    //     {
    //         citytemp.push_back(haystack[i]);
    //     }
    // }
    
    for (std::vector<person>::iterator SCiter = haystack.begin(); SCiter != haystack.end(); *SCiter++)
    {
        if (SCiter->location.city == city)
        {

            // citytemp.push_back(haystack[*Sciter]);

            citytemp.push_back(*SCiter);
        }
    }    
    return citytemp;
}

// läser in alla namn å skit in i en vector.
std::vector<person> read_file (std::string filename)
{
    std::vector<person> haystack;
    std::ifstream inmatning (filename);
    person p;

    while ( inmatning >> p )
    {
        haystack.push_back(p);
    }
    
    return haystack;    
}