#ifndef _CLOG_H_
#define _CLOG_H_

#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

namespace System_LOG
{
	class cLog
	{
	public:
		void Call(std::string &);
		void Call(char*);

	private:
		bool Initialize();
		void loggingInFile(std::string);
		std::string GetLogTime();
		void Shutdown();

		std::ofstream* pLogFile;
	};
}

#endif