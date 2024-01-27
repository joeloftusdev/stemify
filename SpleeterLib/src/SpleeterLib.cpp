#include "pch.h"
#include "framework.h"
#include "SpleeterLib.h"
#include "SpleeterService.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdio>
#include <system_error>
#include <ctime>
#include <filesystem>




namespace fs = std::filesystem;

SPLEETERLIB_API int nSpleeterLib=0;

int WAV_LIB_ERROR = -1;

SPLEETERLIB_API int fnSpleeterLib(void)
{
    return 0;
}

CSpleeterLib::CSpleeterLib()
{
    return;
}

extern "C" SPLEETERLIB_API int fnSpleeterLibGenerateStems(const char* sourceFile, const char* targetDir, const int numOfStems,  CallbackFunction callbackFunction)
{
   
    std::string sourceFileStr = std::string(sourceFile);
    std::string targetDirStr = std::string(targetDir);
    
  
    int returnValue = GenerateStems(sourceFile,  targetDirStr, numOfStems, callbackFunction);
    return returnValue;
}

std::string getCurrentDateTime(const std::string& s) {
    time_t now = time(0);
    struct tm tstruct;

#if defined(_WIN32)
    localtime_s(&tstruct, &now);
#else
    localtime_r(&now, &tstruct);
#endif

    char buf[80];
    if (s == "now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if (s == "date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    else {
        std::cerr << "Invalid format specified. Please use 'now' or 'date'.\n";
        return "";
    }

    return std::string(buf);
};

void Logger(std::string logMsg, std::string verbosity) {

    fs::path tempDir = fs::temp_directory_path();
    fs::path logFileName = "output.log";
    fs::path logFilePath = tempDir / logFileName;

    std::string now = getCurrentDateTime("now");
    std::ofstream ofs(logFilePath.c_str(), std::ios_base::out | std::ios_base::app);

    ofs << now << '[' << verbosity << ']' << '\t' << logMsg << '\n'; 
    ofs.close();
}



int GenerateStems(const std::string& sourceFile, const std::string& targetDir, const int numOfStems, CallbackFunction callbackFunction)
{  
    callbackFunction("Initializing Spleeter");
    Logger("Initializing spleeter", "INFO");
    wave::File file;
    file.Open(sourceFile, wave::kIn);

    std::error_code err;
    std::vector<float> data;
    file.Read(&data);

    auto source = Eigen::Map<spleeter::Waveform>(data.data(), 2, data.size() / 2);

    fs::path currentPath = fs::current_path();

    fs::path modelsPath = currentPath / "models";

    std::string modelsPathString = modelsPath.string();

    spleeter::Initialize(
        std::string(modelsPathString), 
        { spleeter::TwoStems, spleeter::FourStems, spleeter::FiveStems }, err);

    callbackFunction("Generating stems");
    Logger("Generating stems", "INFO");
    if (numOfStems == 2) {
        spleeter::Waveform vocals, accompaniment;
       callbackFunction("Splitting track");
       Logger("Splitting track", "INFO");
        spleeter::Split(source, &vocals, &accompaniment, err);
        if (err) {
            return 1;
        }
       callbackFunction("Writing stems");
       Logger("Writing stems", "INFO");
       try {
           Write(vocals, "vocals-2stems", targetDir);
           Write(accompaniment, "accompaniment-2stems", targetDir);
       }
       catch (...) {
           return 1;
       }
       
    }
    else if (numOfStems == 4) {
        spleeter::Waveform vocals, drums, bass, other;
        callbackFunction("Splitting track");
        Logger("Splitting track", "INFO");
        spleeter::Split(source, &vocals, &drums, &bass, &other, err);
        if (err) {
            return 1;
        }
        callbackFunction("Writing stems");
        Logger("Writing stems", "INFO");
        try {
            Write(vocals, "vocals-4stems", targetDir);
            Write(drums, "drums-4stems", targetDir);
            Write(bass, "bass-4stems", targetDir);
            Write(other, "other-4stems", targetDir);
        }
        catch (...) {
            return 1;
        }

    }
    else {
        spleeter::Waveform vocals, drums, bass, piano, other;
        callbackFunction("Splitting track");
        Logger("Splitting track", "INFO");
        spleeter::Split(source, &vocals, &drums, &bass, &piano, &other, err);
        if (err) {
            return 1;
        }
        callbackFunction("Writing stems");
        Logger("Writing stems", "INFO");
        try {
            Write(vocals, "vocals-5stems", targetDir);
            Write(drums, "drums-5stems", targetDir);
            Write(bass, "bass-5stems", targetDir);
            Write(piano, "piano-5stems", targetDir);
            Write(other, "other-5stems", targetDir);
        }
        catch (...) {
            return 1;
        }
    }
    callbackFunction("Stems Generated");
    Logger("Stems Generated", "INFO");
    return 0;
}

int Write(const spleeter::Waveform& data, const std::string& name, const std::string& targetDir) {
    try {

        std::string outputFilenamestr = targetDir + "/" + name + ".wav";

        std::vector<float> vec_data(data.size());
        std::copy(data.data(), data.data() + data.size(), vec_data.data());
        wave::File file;
        wave::Error err;
        err = file.Open(targetDir + "/" + name + ".wav", wave::kOut);
        if (err) {
            throw(err);
        }
        file.set_sample_rate(44100);
        file.set_channel_number(2);
        err = file.Write(vec_data);
        if (err) {
            throw(err);
        }
    }
    catch (...) {
        Logger("Error Writing stems", "ERROR");
        throw(WAV_LIB_ERROR);

    }

    return 0;
}

