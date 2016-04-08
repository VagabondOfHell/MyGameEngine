#pragma once
#include <ostream>

#ifdef MYGAMEENGINE_EXPORTS
  #define MYGAMEENGINE_EXPORT __declspec(dllexport)
#else
  #define MYGAMEENGINE_EXPORT __declspec(dllimport)
#endif

enum LogPriority{None, Trace, Info, Warning, Error};

class MYGAMEENGINE_EXPORT Logger
{
public:
	
	~Logger(void);

	//Log the message with the set log priority
	void LogMessage(std::string message, LogPriority severity = LogPriority::Error)const;

	//Gets the singleton instance
	static Logger& GetInstance();

	//Set the filepath to be able to change the name and file
	void SetFilePath(const std::string newFilePath);

	//Set the lowest severity level that should be allowed in the Log File
	void SetLogSeverity(LogPriority);

	//Destroy the singleton instance
	void DestroySingleton();

private :
	LogPriority currentSeverity;
	
	Logger(void);
};

