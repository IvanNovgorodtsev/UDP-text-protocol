#include<regex>
#include"Packet.h"
#include<iostream>
#include<conio.h>
using namespace std;
Packet::Packet() {}
Packet::Packet(string OP, string PO, string dane, int liczba, string ID_name, int ID, string time_name, string time)
{
	this->OP = OP;
	this->PO = PO;
	this->dane = dane;
	this->liczba = liczba;
	this->ID_name = ID_name;
	this->ID = ID;
	this->time_name = time_name;
	this->time = time;
}

void Packet::packing()
{
	string podmien_liczbe;
	string podmien_ID;
	if (liczba == 0)
	{
		podmien_liczbe = "";
	}
	else
	{
		podmien_liczbe = to_string(liczba);
	}
	if (ID == 0)
	{
		podmien_ID = "";
	}
	else
	{
		podmien_ID = to_string(ID);
	}
	this->message =
		"#" + OP + "#$" +
		"#" + PO + "#" +
		"#" + dane + "#$" +
		"#" + podmien_liczbe + "#" +
		"#" + ID_name + "#$" +
		"#" + podmien_ID + "#" +
		"#" + time_name + "#$" +
		"#" + time + "#";
}
void Packet::unpacking()
{
	string pom;
	bool flick = true;
	for (int i = 0, y = 0; i < message.size(); i++)
	{
		if (flick)
		{
			while (1)
			{
				if (message[i] == '$' && message[i - 1] == '#') break;
				pom = pom + message[i];
				i++;
			}
			flick = false;

		}
		else
		{
			while (1)
			{
				if (i == message.size())break;
				if (message[i] == '#'&&message[i + 1] == '#')break;
				pom = pom + message[i];
				i++;
			}
			flick = true;
		}
		y++;
		switch (y)
		{
		case 1: // OP
		{
			regex reg("[^A-Za-z]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			OP = pom; pom = ""; break;
		}

		case 2: // PO
		{
			regex reg("[^A-Za-z]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			PO = pom; pom = ""; break;
		}
		case 3: // Dane
		{
			regex reg("[^A-Za-z]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			dane = pom; pom = ""; break;
		}
		case 4: // liczba
		{
			if (pom.size())
			{
				regex reg("[^0-9]+");
				pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
				liczba = stoi(pom);
				pom = "";
				break;
			}
			liczba = 0;
			pom = "";
			break;
		}
		case 5: // ID_name
		{
			regex reg("[^A-Za-z]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			ID_name = pom; pom = ""; break;
		}
		case 6: // ID
		{
			if (pom.size())
			{
				regex reg("[^0-9]+");
				pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
				ID = stoi(pom);
				pom = "";
				break;
			}
			ID = 0;
			pom = "";
			break;
		}
		case 7: //time_name
		{
			regex reg("[^A-Za-z]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			time_name = pom; pom = ""; break;
		}
		case 8: //time
		{
			regex reg("[^0-9.:]");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			time = pom; pom = ""; break;
			break;
		}
		}

	}

}


void Packet::setDane(string dane)
{
	this->dane = dane;
}

string Packet::getDane()
{
	return this->dane;
}

void Packet::setID_name(string name)
{
	this->ID_name = name;
}

string Packet::getID_name()
{
	return this->ID_name;
}

void Packet::setTime_name(string time)
{
	this->time_name = time;
}

string Packet::getTime_name()
{
	return this->time_name;
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

void Packet::setPO(string PO)
{
	this->PO = PO;
}
string Packet::getPO()
{
	return this->PO;
}