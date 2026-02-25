// ProductExpirationTracker
// DateList.h
// Created on Feb 06 2026 by Justyn Durnford
// Last modified on Feb 08 2026 by Justyn Durnford
// Header file for the DateList

#include <cstdint>
#include <tuple>
#include <vector>

extern std::vector<std::tuple<std::uint8_t, std::uint8_t, std::uint16_t>> DateList;
extern std::vector<std::uint16_t> MonthStartDayIndexes;