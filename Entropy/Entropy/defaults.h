#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "typedefs.h"

namespace entropy
{
    static const String APP_NAME = "Entropy";
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
namespace entropy
{
    static const String SLASH="\\";
    static const String APP_EXTENSION = ".exe";
}
#else
namespace entropy
{
    static const String SLASH="/";
    static const String APP_EXTENSION = "";
}
#endif

namespace entropy
{
    inline String inputFileName()
    {
        return "input.csv";
    }
    inline String scalesFileName()
    {
        return "scales.txt";
    }
    inline String configFileName()
    {
        return "config.txt";
    }
    inline String defaultDirectory()
    {
        return "."+SLASH;
    }
    inline String inputFilePath()
    {
        return defaultDirectory()+inputFileName();
    }
    inline String scalesFilePath()
    {
        return defaultDirectory()+scalesFileName();
    }
    inline String configFilePath()
    {
        return defaultDirectory()+configFileName();
    }
    inline String appName()
    {
        return APP_NAME+APP_EXTENSION;
    }
    inline String errorMessageImproperMain()
    {
        std::stringstream m;
        m << "Incorrect usage of " << appName() << "." << std::endl;
        m << "Three input files are required (see documentation for specifications):" << std::endl;
        m << '\t' << "input.csv - data set to drive the composition" << std::endl;
        m << '\t' << "config.txt - configuration such as length of composition" << std::endl;
        m << '\t' << "scales.txt - twelve scales to be used in the composition" << std::endl;
        m << std::endl;
        m << "If you do not provide any arguments when calling " << appName() << "," << std::endl;
        m << "then you must have these three files in the same directory as the binary." << std::endl;
        m << "Otherwise, you must specify the complete filepaths (including filenames) to" << std::endl;
        m << "these files when running " << appName() << ", in the order 1) input, 2) config, 3) scales." << std::endl;
        m << std::endl;
        m << "For example..." << std::endl;
        m << std::endl;
        m << "Entropy \"./Dir1/SomeInput.xyz\" \"./DirX/somefile.config\" \"./Dir1/MyScales.txt\"" << std::endl;
        m << std::endl;
        m << "Or..." << std::endl;
        m << std::endl;
        m << "Entropy.exe \"C:\\Dir1\\SomeInput.xyz\" \"C:\\DirX\\somefile.config\" \"C:\\Dir1\\MyScales.txt\"" << std::endl;
        return m.str();
    }
}