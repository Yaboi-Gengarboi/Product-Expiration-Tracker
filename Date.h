// ProductExpirationTracker
// Date.h
// Created on Feb 03 2026 by Justyn Durnford
// Last modified on Feb 13 2026 by Justyn Durnford
// Header file for the Date class

#pragma once

#include "DateList.h"

#include <compare>
#include <cstdint>
#include <string>
#include <tuple>

class Date
{
    std::uint8_t _month;
    std::uint8_t _day;
    std::uint16_t _year;

    std::uint16_t _dayIndex;

    // 
    constexpr std::uint16_t _calcDayIndex() const noexcept
    { return MonthStartDayIndexes[_month - 1] + _day - 1; }

    public:

    // Default constructor
    // Date set as 00/00/0000
    Date();

    // Value constructor
    // Sets _day to day
    // Sets _month to month
    // Sets _year to year
    Date(std::uint8_t month, std::uint8_t day, std::uint16_t year);

    // 
    Date(const Date& other) = default;

    // 
    Date(Date&& other) = default;

    // 
    Date(const std::string& str);

    // 
    Date(const std::tuple<std::uint8_t, std::uint8_t, std::uint16_t>& date_tuple);

    // 
    Date& operator = (const Date& other) = default;

    // 
    Date& operator = (Date&& other) = default;

    // 
    Date& operator = (const std::string& str);

    // 
    Date& operator = (const std::tuple<std::uint8_t, std::uint8_t, std::uint16_t>& date_tuple);

    // 
    constexpr std::uint8_t getDay() const noexcept
    { return _day; }

    // 
    constexpr std::uint8_t getMonth() const noexcept
    { return _month; }

    // 
    constexpr std::uint16_t getYear() const noexcept
    { return _year; }

    // 
    constexpr std::uint16_t getDayIndex() const noexcept
    { return _dayIndex; }

    //
    void setDay(std::uint8_t day) noexcept;

    // 
    void setMonth(std::uint8_t month) noexcept;

    // 
    void setYear(std::uint16_t year) noexcept;

    //
    void setValues(std::uint8_t month, std::uint8_t day, std::uint16_t year) noexcept;

    // 
    void copyFrom(const Date& other) noexcept;

    // 
    void copyTo(Date& other) const noexcept;

    // 
    Date nextDate() const noexcept;

    // 
    Date lastDate() const noexcept;

    // 
    int distanceFrom(const Date& other) const noexcept;

    // 
    Date& addDays(std::uint16_t days) noexcept;

    // 
    Date& subtractDays(std::uint16_t days) noexcept;

    // 
    std::string toString() const;

    // 
    void readFromString(const std::string& str);

    // 
    std::tuple<std::uint8_t, std::uint8_t, std::uint16_t> toTuple() const noexcept;

    // 
    void readFromTuple(const std::tuple<std::uint8_t, std::uint8_t, std::uint16_t>& date_tuple) noexcept;

    // 
    bool isNullDate() const;

    // Returns true if all of the following are true:
    // >> A._day == B._day
    // >> A._month == B._month
    // >> A._year == B._year;
    // 
    // Returns false otherwise.
    bool equals(const Date& other) const noexcept;

    // Returns true if any of the following are true:
    // >> A._day != B._day
    // >> A._month != B._month
    // >> A._year != B._year;
    // 
    // Returns false otherwise.
    bool doesNotEqual(const Date& other) const noexcept;

    // Returns true if all of the following are true:
    // >> A._day < B._day
    // >> A._month <= B._month
    // >> A._year <= B._year;
    // 
    // Returns false otherwise.
    bool lessThan(const Date& other) const noexcept;

    // Returns true if all of the following are true:
    // >> A._day <= B._day
    // >> A._month <= B._month
    // >> A._year <= B._year;
    // 
    // Returns false otherwise.
    bool lessThanEqualTo(const Date& other) const noexcept;

    // Returns true if all of the following are true:
    // >> A._day > B._day
    // >> A._month >= B._month
    // >> A._year >= B._year;
    // 
    // Returns false otherwise.
    bool greaterThan(const Date& other) const noexcept;

    // Returns true if all of the following are true:
    // >> A._day >= B._day
    // >> A._month >= B._month
    // >> A._year >= B._year;
    // 
    // Returns false otherwise.
    bool greaterThanEqualTo(const Date& other) const noexcept;

    // Compares the two dates and returns a
    // std::strong_ordering describing their order.
    // 
    // Returns std::strong_ordering::less if A < B
    // Returns std::strong_ordering::greater if A > B
    // Returns std::strong_ordering::equal if A = B
    std::strong_ordering compareWith(const Date& other) const noexcept;

    // 
    static bool isLeapYear(std::uint16_t year) noexcept;

    // 
    static Date getCurrentDate() noexcept;
};

// == Operator
// 
// Returns true if all of the following are true:
// >> A._day == B._day
// >> A._month == B._month
// >> A._year == B._year;
// 
// Returns false otherwise.
bool operator == (const Date& A, const Date& B);

// != Operator
// 
// Returns true if any of the following are true:
// >> A._day != B._day
// >> A._month != B._month
// >> A._year != B._year;
// 
// Returns false otherwise.
bool operator != (const Date& A, const Date& B);

// < Operator
// 
// Returns true if all of the following are true:
// >> A._day < B._day
// >> A._month <= B._month
// >> A._year <= B._year;
// 
// Returns false otherwise.
bool operator < (const Date & A, const Date & B);

// <= Operator
// 
// Returns true if all of the following are true:
// >> A._day <= B._day
// >> A._month <= B._month
// >> A._year <= B._year;
// 
// Returns false otherwise.
bool operator <= (const Date& A, const Date& B);

// > Operator
// 
// Returns true if all of the following are true:
// >> A._day > B._day
// >> A._month >= B._month
// >> A._year >= B._year;
// 
// Returns false otherwise.
bool operator > (const Date& A, const Date& B);

// >= Operator
// 
// Returns true if all of the following are true:
// >> A._day >= B._day
// >> A._month >= B._month
// >> A._year >= B._year;
// 
// Returns false otherwise.
bool operator >= (const Date& A, const Date& B);

// <=> Operator
// 
// Compares the two dates and returns a
// std::strong_ordering describing their order.
// 
// Returns std::strong_ordering::less if A < B
// Returns std::strong_ordering::greater if A > B
// Returns std::strong_ordering::equal if A = B
std::strong_ordering operator <=> (const Date& A, const Date& B);

// ++ Operator
// 
Date& operator ++ (Date& date);

// + Operator
// 
Date operator + (Date& date, std::uint16_t days);

// += Operator
// 
Date& operator += (Date& date, std::uint16_t days);

// -- Operator
// 
Date& operator -- (Date& date);

// - Operator
// 
Date operator - (Date& date, std::uint16_t days);

// -= Operator
// 
Date& operator -= (Date& date, std::uint16_t days);