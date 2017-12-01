#pragma once
#include<string>
using namespace std;
class Packet
{
public:
	string message;
	int message_size = message.size();
	Packet();
	Packet(string OP, string PO, int liczba, int ID, int State, string time);

	void setMessage(string m);
	string getMessage();

	void setTime(string time);
	string getTime();

	void setState(int s);
	int getState();

	void setID(int id);
	int getID();

	void setLiczba(int number);
	int getLiczba();

	void setOP(string OP);
	string getOP();
	
	void packing();
	void unpacking();
	


private:
	string OP;		// pole operacji 
	string PO;		// pole odpowiedzi 
	int liczba;  // liczba przeslana przez klienta 
	int ID;		// pole ID     
	int State;	// pole status 
	string time;    // pole czasu 

};