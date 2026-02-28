// ProductExpirationTracker
// CSVFileReader.h
// Created on Feb 10 2026 by Justyn Durnford
// Last modified on Feb 25 2026 by Justyn Durnford
// Header file for the CSVFileReader class

#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

// 
class CSVFileReader
{
    std::ifstream _fin;
    bool _isGood;

    bool _tryOpenFile(const std::filesystem::path& filepath);

    public:

    //
    CSVFileReader(const std::filesystem::path& filepath);

    // 
    constexpr bool isGood() const noexcept
    { return _isGood; }

    // 
    constexpr bool isEOF() const noexcept
    { return _fin.eofbit; }

    // 
    bool openFile(const std::filesystem::path& filepath);

    //
    std::string readValue();

    // 
    std::string readLine();

    // 
    std::vector<std::string> getValuesInLine();
};
