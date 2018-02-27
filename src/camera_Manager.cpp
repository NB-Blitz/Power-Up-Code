#include <WPILib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Auto_Manager.hpp"
#include "camera_Manager.hpp"


FRC::camera_Manager::camera_Manager()
{

}

void FRC::camera_Manager::camSetup()
{
	tilt = new Servo(1);
	pan = new Servo(0);

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr("10.51.48.36");

	serverLen = sizeof(server);

	udpSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	camPanPos = pan->Get() * 180;
	camTiltPos = tilt->Get() * 180;
}

void FRC::camera_Manager::grabData()
{
	char xBuffer[256];

	const char* msg = "x";
	sendto(udpSock, msg,sizeof(msg),0,(struct sockaddr *)&server,serverLen);
	recv(udpSock,xBuffer,256,0);
	//SmartDashboard::PutString("recieved buffer", xBuffer);
	std::string xPosStr(xBuffer);

	xPos = atoi(xPosStr.c_str());


	char yBuffer[256];

	msg = "y";
	sendto(udpSock, msg,sizeof(msg),0,(struct sockaddr *)&server,serverLen);
	recv(udpSock,yBuffer,256,0);
	SmartDashboard::PutString("recieved buffer", yBuffer);
	std::string yPosStr(yBuffer);

	yPos = atoi(yPosStr.c_str());

//	char distBuffer[2];

//	msg = "d";
//	SmartDashboard::PutNumber("step: ", 1);
//	sendto(udpSock, msg,sizeof(msg),0,(struct sockaddr *)&server,serverLen);
//	recv(udpSock,distBuffer,256,0);
//	//std::string distStr(buffer);
//	SmartDashboard::PutString("dist: ", distBuffer);
//
//	dist = atoi(distBuffer);
}

void FRC::camera_Manager::closeNet()
{
	close(udpSock);
}

void FRC::camera_Manager::sendData(std::string data)
{
	const char* msg = data.c_str();
	sendto(udpSock, msg,sizeof(msg),0,(struct sockaddr *)&server,serverLen);
}

void FRC::camera_Manager::trackColor(std::string color)
{
	sendData(color.substr(0,1));
}

void FRC::camera_Manager::camScan(int autoGoal)
{
	if(xPos > 90 || xPos < -90)
	{
		if(camPanPos >= MAX_PAN)
		{
			panDir = -1;
			camPanPos = MAX_PAN;
		}
		else if(camPanPos <= MIN_PAN)
		{
			panDir = 1;
			camPanPos = MIN_PAN;
		}

		angle = 0;
		dist = -1;

		camPanPos += panDir;
	}
	else
	{
		camPanPos += xPos * .01;

		angle = camPanPos;

//		if(yPos > 1 && camTiltPos < MIN_TILT)
//		{
//			camTiltPos -= 1;
//		}
//		else if(yPos < -1 && camTiltPos < MAX_TILT)
//		{
//			camTiltPos += 1;
//		}
//
//		dist = tan(camTiltPos) * (M_PI/180) * CAM_HEIGHT;

		if(camPanPos >= MAX_PAN)
		{
			camPanPos = MAX_PAN;
		}
		else if(camPanPos <= MIN_PAN)
		{
			camPanPos = MIN_PAN;
		}
	}

	setPanPos(camPanPos);

}


void FRC::camera_Manager::setPanPos(double pos)
{
	pan->Set(pos/180);
}

void FRC::camera_Manager::setTiltPos(double pos)
{
	tilt->Set(pos/180);
}
