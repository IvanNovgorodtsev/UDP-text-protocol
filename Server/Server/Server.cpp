#define _CRT_SECURE_NO_WARNINGS
#include "Server.h"

int generateLvalue()
{
	srand(time(NULL));
	int out;
	out = (rand() % 10) + 1;
	return out;
}

int generateRvalue()
{
	srand(time(NULL));
	int out;
	out = (rand() % 50) + 10;
	return out;
}

int generateRandomInt()
{
	srand(time(NULL));
	int out;
	out = (rand() % generateRvalue()) + generateLvalue();
	return out;
}
int Lvalue = generateLvalue();
int Rvalue = generateRvalue();
int RANDOM_NUMBER = generateRandomInt();
int CLIENT_ID = 1;
string nadawanie_czasu()
{
	std::string output;
	std::time_t rawtime;
	std::tm* timeinfo;
	char buffer[80];

	std::time(&rawtime);
	timeinfo = std::localtime(&rawtime);

	std::strftime(buffer, 80, "%H:%M:%S", timeinfo);
	output = buffer;
	return output;
}

Server::Server()
{
		try
		{
			WSAData data;//contains information about the Windows Sockets implementation
			int ReturnCheck = WSAStartup(MAKEWORD(2, 2), &data);//initiates use of the Winsock DLL by a process
			if (ReturnCheck==SOCKET_ERROR)//Tell the user that we could not find a usable Winsock DLL.
				throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");
			
			UDPSocket Socket;
			Packet packet;

			bool sendLR = false;
			char buffer[100];
			Socket.Bind(1111);
			sockaddr_in add;
			cout << "Liczba wygenerowana przez serwer: " << RANDOM_NUMBER << endl;
			while(1)
			{	
				add = Socket.RecvFrom(buffer, sizeof(buffer));
				packet.message = string(buffer);	// podstawienie wiadomosci
				packet.unpacking();			// odpakowanie
				cout << "[" << packet.getTime() << "]" << " Packed received: " << packet.message << endl;

				// ustawienie Statusu
				if(packet.getOP()=="O"&&packet.getPO()=="PrzydzielID")
				{
					packet.setOP("o");
					packet.setPO("OdbierzID");
					packet.setTime(nadawanie_czasu());
					packet.setID(CLIENT_ID); CLIENT_ID++;
					packet.packing();
					Socket.SendTo(add, packet.message.c_str(), packet.message.size());
					sendLR = true;
				}
				else if(packet.getOP() == "O"&&packet.getPO() == "LosujZakres")
				{
					if (sendLR)
					{
						packet.setOP("o");
						packet.setPO("OdbierzZakres");
						packet.setLiczba(Lvalue);
						packet.packing();
						sendLR = false;
						Socket.SendTo(add, packet.message.c_str(), packet.message.size());
					}
					else
					{
						packet.setOP("o");
						packet.setPO("OdbierzZakres");
						packet.setLiczba(Rvalue);
						packet.packing();
						Socket.SendTo(add, packet.message.c_str(), packet.message.size());
					}
				}
				else if(packet.getOP()=="O"&&packet.getPO()=="Request")
				{
					packet.setOP("o");
					packet.setPO("Pick");
					packet.setTime(nadawanie_czasu());
					packet.packing();
					Socket.SendTo(add, packet.message.c_str(), packet.message.size());
				}
				else if (packet.getOP() == "O" && packet.getPO() == "Sprawdz")
				{
					if (packet.getLiczba() == RANDOM_NUMBER)
					{
						packet.setOP("o");
						packet.setPO("End");
						packet.setTime(nadawanie_czasu());
						packet.packing();
					}
					else
					{
						packet.setOP("o");
						packet.setPO("Pick");
						packet.setTime(nadawanie_czasu());
						packet.packing();
					}
					Socket.SendTo(add, packet.message.c_str(), packet.message.size());			
				}
				}
			}
		
		catch (std::system_error& e)
		{
			std::cout << e.what();
		}
}