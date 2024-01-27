#pragma once
#include "wave/file.h"
#include "spleeter/spleeter.h"

int Write(const spleeter::Waveform& data, const std::string& name, const std::string& targetDir);

int GenerateStems(const std::string& sourceFile, const std::string& targetDir, const int numOfStems, CallbackFunction callbackFunction);

void Logger(std::string logMsg, std::string verbosity);