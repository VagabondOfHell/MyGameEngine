#include "Logger.h"
#include <fstream>

static Logger* instance;
static const std::string DEFAULT_FILENAME = "DefaultLogFile.log";

std::ofstream outFile;

Logger::Logger(void)
{
	outFile = std::ofstream(DEFAULT_FILENAME);
	currentSeverity = LogPriority::None;
}


Logger::~Logger(void)
{
	outFile.flush();
	outFile.close();
}

void Logger::LogMessage(std::string message, LogPriority severity)const
{
	if(severity >= currentSeverity)
	{
		std::string severityToString;

		switch (severity)
		{
		case None:
			severityToString = "None: ";
			break;
		case Trace:
			severityToString = "TRACE: ";
			break;
		case Info:
			severityToString = "INFO: ";
			break;
		case Warning:
			severityToString = "WARNING: ";
			break;
		case Error:
			severityToString = "ERROR: ";
			break;
		default:
			break;
		}

		outFile << severityToString.c_str() << message.c_str() << '\n';
		outFile.flush();
	}
}

Logger& Logger::GetInstance()
{
	if(!instance)
		instance = new Logger();

	return (*instance);
}

void Logger::DestroySingleton()
{
	if(instance)
		delete instance;
}

void Logger::SetFilePath(const std::string newFilePath)
{
	outFile.flush();
	outFile.close();
	outFile.open(newFilePath);
}

void Logger::SetLogSeverity(LogPriority severity)
{
	currentSeverity = severity;
}