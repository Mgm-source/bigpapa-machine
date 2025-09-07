#pragma once
#include <fstream>

enum class Severity
{
	DEBUG,
	INFO,
	WARNING,
	CRITICAL
};

class Logger
{
	std::wofstream m_log;
public: 
	Logger() : m_log(L"logs/log.txt", std::ofstream::app )
	{
	}

	Logger(std::wstring filename)  : m_log(filename, std::ofstream::app)
	{
	}

	std::wstring getSeverity(Severity level)
	{
		switch (level)
		{
		case Severity::DEBUG:
			return L"Debug";

		case Severity::INFO:
			return L"Information";
			
		case Severity::CRITICAL:
			return L"Critical";

		case Severity::WARNING:
			return L"Warning";

		default:
				return L"Unknown";
		}
	};


	void log(std::wstring message, Severity level)
	{

		m_log << L"Time:" << getDate() << L" Type:" << getSeverity(level) << L" Log:" << message << std::endl;
	}
		
	std::wstring getDate()
	{
		time_t rawtime;
		struct tm timeinfo{};
		wchar_t buffer[20];

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		wcsftime(buffer, 20, L"%Y-%m-%d %H:%M:%S", &timeinfo);

		return std::wstring(buffer);
	}
};

