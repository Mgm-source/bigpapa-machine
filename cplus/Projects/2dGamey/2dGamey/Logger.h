#pragma once
#include <fstream>

enum class Severity
{
	INFO,
	WARNING,
	CRITICAL
};

class Logger
{
	std::wofstream m_log;
public:
	Logger();
	Logger(std::wstring filename);

	void log(std::wstring message, Severity level);
	std::wstring getDate();
};

