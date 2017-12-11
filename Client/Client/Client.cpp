#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <ctime>
#include "UDPSocket.h"
#include "Client.h"
#include "Packet.h"
using namespace std;

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

Client::Client()
{

	try
	{
		WSAData data;//contains information about the Windows Sockets implementation
		int ReturnCheck = WSAStartup(MAKEWORD(2, 2), &data);//initiates use of the Winsock DLL by a process
		if (ReturnCheck == SOCKET_ERROR)//Tell the user that we could not find a usable Winsock DLL.
			throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");

		UDPSocket Socket;
		Packet packet("O", "PrzydzielID", "Dane", 0, "ID", 0, "Czas", nadawanie_czasu());
		packet.packing();
		int client_number;
		int L1 = 0, L2 = 0;
		char buffer[100];
		bool inicjalizacja = true;
		bool getLR = false;

		while (1)
		{
			Socket.SendTo("127.0.0.1", 1111, packet.message.c_str(), packet.message.size()); // pierwszy pusty
			Socket.RecvFrom(buffer, 100); // odebrany pierwszy ze state i ID
			packet.message = string(buffer);
			packet.unpacking();
			/// nowe fory
			if (packet.getOP() == "o" && packet.getPO() == "OdbierzID")
			{
				packet.setOP("O");
				packet.setPO("LosujZakres");
				packet.setTime(nadawanie_czasu());
				packet.packing();
				getLR = true;
			}
			else if (packet.getOP() == "o"&&packet.getPO() == "OdbierzZakres")
			{
				//Socket.RecvFrom(buffer, 100); // odbieramy Lvalue
				if (getLR)
				{
					packet.message = string(buffer);
					packet.unpacking();
					L1 = packet.getLiczba();

					/// Zamiast setState
					/// cin>>string;
					/// packet.setOP("Losuj_zakresR");
					packet.setOP("O");
					packet.setPO("LosujZakres");
					getLR = false;
					packet.packing();
				}
				else
				{
					packet.message = string(buffer);
					L2 = packet.getLiczba();
					/// Prosba o rozpoczecie zgadywania
					packet.setOP("O");
					packet.setPO("Request");
					packet.packing();
				}
			}
			else if (packet.getOP() == "o"&&packet.getPO() == "Pick")
			{
				if (inicjalizacja)
				{
					cout << "Client[" << packet.getID() << "] " << "Liczba znajduje sie w przedziale: " << L1 << " - " << L2 << endl;
					inicjalizacja = false;
				}
				// status wysylania liczby
				inicjalizacja = false;
				cout << "Twoja liczba: ";
				cin >> client_number;
				packet.setLiczba(client_number);
				/// Wyslij liczbe
				/// set State
				packet.setOP("O");
				packet.setPO("Sprawdz");
				packet.setTime(nadawanie_czasu());
				packet.packing();
			}
			else if (packet.getOP() == "o"&&packet.getPO() == "End")
			{
				// Klient odgadnal liczbe!
				cout << "Liczba zostala znaleziona. Gratulacje!" << endl;
			}
		}
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what();
	}
}