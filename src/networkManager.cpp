#include <WPILib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "networkManager.hpp"

FRC::networkManager::networkManager()
{

}

int FRC::networkManager::netSetup()
{

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr("10.51.48.36");

	serverLen = sizeof(server);

	udpSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	return 0;
}

int FRC::networkManager::grabData()
{
	char xBuffer[256];

	const char* msg = "x";
	sendto(udpSock, msg,sizeof(msg),0,(struct sockaddr *)&server,serverLen);
	recv(udpSock,xBuffer,256,0);
	SmartDashboard::PutString("recieved buffer", xBuffer);
	std::string xPosStr(xBuffer);

	xPos = atoi(xPosStr.c_str());

	char yBuffer[256];

	msg = "y";
	sendto(udpSock, msg,sizeof(msg),0,(struct sockaddr *)&server,serverLen);
	recv(udpSock,yBuffer,256,0);
	SmartDashboard::PutString("recieved buffer", yBuffer);
	std::string yPosStr(yBuffer);

	yPos = atoi(yPosStr.c_str());


	char distBuffer[2];

	msg = "d";
	SmartDashboard::PutNumber("step: ", 1);
	sendto(udpSock, msg,sizeof(msg),0,(struct sockaddr *)&server,serverLen);
	recv(udpSock,distBuffer,256,0);
	//std::string distStr(buffer);
	SmartDashboard::PutString("dist: ", distBuffer);

	dist = atoi(distBuffer);

	return 0;
}

void FRC::networkManager::sendData(char * data)
{
	sendto(udpSock, data,sizeof(data),0,(struct sockaddr *)&server,serverLen);
}

 int FRC::networkManager::closeNet()
 {
	close(udpSock);
	return 0;
 }

