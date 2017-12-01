#include<regex>
#include"Packet.h"
#include<iostream>
#include<conio.h>
using namespace std;
Packet::Packet() {}
Packet::Packet(string OP, string PO, int liczba, int ID, int State,string time)
{
	this->OP = OP;
	this->PO = PO;
	this->liczba = liczba;
	this->ID = ID;
	this->State = State;
	this->time = time;
}

void Packet::packing()
{
	this->message = "#"+OP+"#$"+ 
					"#"+PO +"#$"+ 
					"#"+to_string(liczba)+"#$"+
					"#"+to_string(ID)+"#$"+
					"#"+to_string(State)+"#$"+
					"#"+time+"#$";
}
void Packet::unpacking()
{
	string pom;
	for (int i = 0, y = 0; i < message.size(); i++)
	{
		while (1)
		{
			if (message[i] == '$')break;
			pom = pom + message[i];
			i++;
		}
		y++;
		switch (y)
		{
		case 1:
		{
			OP = pom; pom = "";
			break;
		}
		case 2:
		{
			PO = pom; pom = ""; break;
		}
		case 3:
		{
			regex reg("[^0-9]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			liczba = stoi(pom);
			pom = "";
			break;
		}
		case 4:
		{
			regex reg("[^0-9]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			ID = stoi(pom);
			pom = "";
			break;
		}
		case 5:
		{
			regex reg("[^0-9]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			State = stoi(pom);
			pom = "";
			break;
		}
		case 6:
		{
			if (pom.size()>0)time = pom; pom = ""; break;
			break;
		}
		}
	}
}

void Packet::setMessage(string m)
{
	this->message = m;
}

string Packet::getMessage()
{
	return this->message;
}

void Packet::setTime(string time)
{
	this->time = time;
}

string Packet::getTime()
{
	return this->time;
}

void Packet::setState(int s)
{
	this->State = s;
}
int Packet::getState()
{
	return this->State;
}

void Packet::setID(int id)
{
	this->ID = id;
}
int Packet::getID()
{
	return ID;
}

void Packet::setLiczba(int number)
{
	this->liczba = number;
}

int Packet::getLiczba()
{
	return this->liczba;
}

void Packet::setOP(string OP)
{
	this->OP = OP;
}

string Packet::getOP()
{
	return this->OP;
}
