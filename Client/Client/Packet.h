#pragma once
#include<string>
using namespace std;
class Packet
{
public:
	string message;
	int message_size = message.size();
	Packet();
	Packet(string OP, string PO, string dane, int liczba, string ID_name, int ID, string time_name, string time);

	void setMessage(string m);
	string getMessage();

	void setTime(string time);
	string getTime();

	void setID(int id);
	int getID();

	void setLiczba(int number);
	int getLiczba();

	void setOP(string OP);
	string getOP();

	void setPO(string PO);
	string getPO();

	void packing();
	void unpacking();

	void setDane(string dane);
	string getDane();

	void setID_name(string name);
	string getID_name();

	void setTime_name(string time);
	string getTime_name();

private:
	string OP;		// pole operacji 
	string PO;		// pole odpowiedzi 
	string dane; // pole nazwy dla liczby
	int liczba;  // liczba przeslana przez klienta 
	string ID_name; // pole nazwy ID
	int ID;		// pole ID     
	string time_name; // pole nazwy czasu
	string time;    // pole czasu 

};