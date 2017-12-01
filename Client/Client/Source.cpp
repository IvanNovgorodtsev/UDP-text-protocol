#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Client.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <regex>
using namespace std;
int main()
{
	Client client;
	/*
	string message="## $ ## $ #0# $ #0# $ #0# $ #19:44:40#$";
	string pole1, pole2, pole6;
	int pole3, pole4, pole5;
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
			pole1 = pom; pom = "";
			break;
		}
		case 2:
		{
			pole2 = pom; pom = ""; break;
		}
		case 3:
		{
			regex reg("[^0-9]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			pole3 = stoi(pom);
			pom = "";
			break;
		}
		case 4:
		{
			regex reg("[^0-9]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			pole4 = stoi(pom);
			pom = "";
			break;
		}
		case 5:
		{
			regex reg("[^0-9]+");
			pom = regex_replace(pom, reg, ""); // czyszczenie # oraz $  // -_-
			pole5 = stoi(pom);
			pom = "";
			break;
		}
		case 6:
		{
			if (pom.size()>0)pole6 = pom; pom = ""; break;
			break;
		}
		}
	}

	cout << pole1;// << pole2 << pole3 << pole4 << pole5 << pole6;
	*/
}
