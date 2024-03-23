#include "pch.h"
#include "Logger.h"
#include <chrono>
#include <iomanip>

Logger::Logger() : m_log(L"log.txt", std::ofstream::app )
{

}

Logger::Logger(std::wstring filename) : m_log(filename, std::ofstream::app)
{

}

void Logger::log(std::wstring message, Severity level)
{

	std::wstring logInformation;

	switch (level)
	{
	case Severity::INFO:
		logInformation = L"Information";
		break;
	case Severity::WARNING:
		logInformation = L"Warning";
		break;
	case Severity::CRITICAL:
		logInformation = L"Critical";
		break;
	}

	m_log << L"Time:" << getDate() << L" Type:" << logInformation << L" Log:" << message << std::endl;
}

std::wstring Logger::getDate()
{
	time_t rawtime;
	struct tm timeinfo;
	wchar_t buffer[20];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	auto now = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(now);

	wcsftime(buffer, 20, L"%Y-%m-%d %H:%M:%S", &timeinfo);

	return std::wstring(buffer);
}