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

				// ustawienie Statusu
				switch (packet.getState())
				{
				case 0:
				{
					cout <<"["<<packet.getTime()<<"]"<< " Packed received: "<< packet.message << endl;
						
					packet.setID(CLIENT_ID); CLIENT_ID++;
					packet.setState(1);
					packet.setTime(nadawanie_czasu());
					packet.packing();
					Socket.SendTo(add, packet.message.c_str(), packet.message.size());
					sendLR = true;
					break;
				}
				case 2:
				{
					if (sendLR)
					{
						packet.setState(3);
						packet.setLiczba(Lvalue);
						packet.packing();
						sendLR = false;
						Socket.SendTo(add, packet.message.c_str(), packet.message.size());
					}
					else
					{
						packet.setState(3);
						packet.setLiczba(Rvalue);
						packet.packing();
						Socket.SendTo(add, packet.message.c_str(), packet.message.size());
					}
					break;
				}
				case 4:
				{
					packet.setState(5);
					packet.setTime(nadawanie_czasu());
					packet.packing();
					Socket.SendTo(add, packet.message.c_str(), packet.message.size());
					break;
				}
				case 6:
				{
					cout << "[" << packet.getTime() << "]" << " Packed received: " << packet.message << endl;
					if (packet.getLiczba() == RANDOM_NUMBER)
					{
						packet.setState(7);
						packet.setTime(nadawanie_czasu());
						packet.packing();
					}
					else
					{
						packet.setState(5);
						packet.setTime(nadawanie_czasu());
						packet.packing();
					}
					Socket.SendTo(add, packet.message.c_str(), packet.message.size());
					break;
					
				}
				}
			}
		}
		catch (std::system_error& e)
		{
			std::cout << e.what();
		}
}