#include "cLog.h"

//*********************************************************************************************
void System_LOG::cLog::Call(std::string &message)
{
	if(Initialize())
	{
		loggingInFile(message);
		Shutdown();
	}
	else
		std::cout << "Error open log-file!\n";
}
//*********************************************************************************************
void System_LOG::cLog::Call(char* message)
{
	if(Initialize())
	{
		std::string convertedMessage = message;
		loggingInFile(convertedMessage);
		Shutdown();
	}
	else
		std::cout << "Error open log-file!\n";
}
//*********************************************************************************************
bool System_LOG::cLog::Initialize()
{
	pLogFile = new std::ofstream("logfile.txt", std::ios::app | std::ofstream::out);
	if(pLogFile->is_open())
		return true;
	else
		return false;
}
//*********************************************************************************************
void System_LOG::cLog::loggingInFile(std::string message)
{
	message = GetLogTime() + message + "\n";
	pLogFile->write(message.c_str(), message.size());
}
//*********************************************************************************************
std::string System_LOG::cLog::GetLogTime()
{
	char buffer[100];
	std::string currentTimeAndDate;
	time_t seconds = time(NULL);
	tm* timeInfo = localtime(&seconds);
	char* format = "[%d-%m-%Y][%H:%M:%S]-> ";
	strftime(buffer, 100, format, timeInfo);
	currentTimeAndDate = buffer;
	return currentTimeAndDate;
}
//*********************************************************************************************
void System_LOG::cLog::Shutdown()
{
	pLogFile->close();
	delete pLogFile;
	pLogFile = nullptr;
}