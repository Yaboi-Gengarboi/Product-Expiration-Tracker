// ProductExpirationTracker
// CSVFileWriter.h
// Created on Feb 23 2026 by Justyn Durnford
// Last modified on Feb 23 2026 by Justyn Durnford
// Header file for the CSVFileWriter class

#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

// 
class CSVFileWriter
{
	std::ofstream _fout;
	bool _isGood;

	// 
	bool _tryOpenFile(const std::filesystem::path& filepath);

	public:

    //
    CSVFileWriter(const std::filesystem::path& filepath);

    // 
    constexpr bool isGood() const noexcept
    { return _isGood; }

    // 
    bool openFile(const std::filesystem::path& filepath);

    //
    bool writeValue(const std::string& str);

    // 
    bool writeValues(const std::vector<std::string>& values);
};