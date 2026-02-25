// ProductExpirationTracker
// Date.cpp
// Created on Feb 06 2026 by Justyn Durnford
// Last modified on Feb 23 2026 by Justyn Durnford
// Implementation file for the Date class

#include "Date.h"

#include <ctime>
using std::time_t;
using std::tm;
using std::time;

#include <iostream>
using std::cout;

// <compare>
using std::strong_ordering;

// <cstdint>
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;

// <string>
using std::size_t;
using std::string;
using std::stoi;
using std::to_string;

// <tuple>
using std::tuple;
using std::get;
using std::make_tuple;

Date::Date()
{
	_day = 0;
	_month = 0;
	_year = 0;

	_dayIndex = -1;
}

Date::Date(uint8_t month, uint8_t day, uint16_t year)
{
	setValues(month, day, year);
}

Date::Date(const string& str)
{
	readFromString(str);
}

Date::Date(const std::tuple<std::uint8_t, std::uint8_t, std::uint16_t>& date_tuple)
{
	readFromTuple(date_tuple);
}

Date& Date::operator = (const string& str)
{
	readFromString(str);
	return *this;
}

Date& Date::operator = (const tuple<uint8_t, uint8_t, uint16_t>& date_tuple)
{
	readFromTuple(date_tuple);
	return *this;
}

void Date::setDay(std::uint8_t day) noexcept
{
	_day = day; 
	_dayIndex = _calcDayIndex();
}

void Date::setMonth(std::uint8_t month) noexcept
{
	_month = month;
	_dayIndex = _calcDayIndex();
}

void Date::setYear(std::uint16_t year) noexcept
{
	_year = year;
}

void Date::setValues(std::uint8_t month, std::uint8_t day, std::uint16_t year) noexcept
{
	_day = day;
	_month = month;
	_year = year;

	_dayIndex = _calcDayIndex();
}

void Date::copyFrom(const Date& other) noexcept
{
	_day = other._day;
	_month = other._month;
	_year = other._year;
	_dayIndex = other._dayIndex;
}

void Date::copyTo(Date& other) const noexcept
{
	other._day = _day;
	other._month = _month;
	other._year = _year;
	other._dayIndex = _dayIndex;
}

Date Date::nextDate() const noexcept
{
	if (!isLeapYear(_year))
	{
		if (_month == 2 && _day == 28)
			return Date(3, 1, _year);
	}

	if (_dayIndex == 365)
	{
		Date date(*this);
		date.setYear(_year + 1);
		return date;
	}

	Date date(DateList[_dayIndex + 1]);
	date.setYear(_year);

	return date;
}

Date Date::lastDate() const noexcept
{
	// Check for leap year
	if (!isLeapYear(_year))
	{
		if (_month == 3 && _day == 1)
			return Date(2, 28, _year);
	}

	if (_dayIndex == 0)
	{
		Date date(*this);
		date.setYear(_year - 1);
		return date;
	}

	Date date(DateList[_dayIndex - 1]);
	date.setYear(_year);

	return date;
}

int Date::distanceFrom(const Date& other) const noexcept
{
	int year_dist = int{ other._year } - int{ _year };
	int day_dist = int{ other._dayIndex } - int{ _dayIndex };

	return day_dist + (year_dist * 366);
}

Date& Date::addDays(uint16_t days) noexcept
{
	if (_dayIndex + days > 365)
	{
		uint16_t year = _year + 1;
		*this = DateList[days - (365 - _dayIndex)];
		_year = year;
		return *this;
	}

	uint16_t year = _year;
	*this = DateList[_dayIndex + days];
	_year = year;

	return *this;
}

Date& Date::subtractDays(uint16_t days) noexcept
{
	if (_dayIndex < days)
	{
		uint16_t year = _year - 1;
		*this = DateList[365 - (days - _dayIndex)];
		_year = year;
		return *this;
	}

	uint16_t year = _year;
	*this = DateList[_dayIndex - days];
	_year = year;

	return *this;
}

string Date::toString() const
{
	if (_dayIndex == -1)
		return "NA";

	string str;
	str.reserve(10);

	if (_month < 10)
		str += '0';
	str += to_string(_month);
	str += '/';

	if (_day < 10)
		str += '0';
	str += to_string(_day);
	str += '/';

	str += to_string(_year);

	return str;
}

void Date::readFromString(const string& str)
{
	_day = 0;
	_month = 0;
	_year = 0;
	_dayIndex = -1;

	try
	{
		size_t month_ind = 0;
		size_t day_ind = str.find('/');
		size_t year_ind = str.find('/', day_ind + 1);

		string month_str(str.substr(month_ind, day_ind - month_ind));
		string day_str(str.substr(day_ind + 1, year_ind - day_ind - 1));
		string year_str(str.substr(year_ind + 1));

		_day = stoi(day_str);
		_month = stoi(month_str);
		_year = stoi(year_str);

		_dayIndex = _calcDayIndex();
	}
	catch (...)
	{

	}
}

tuple<uint8_t, uint8_t, uint16_t> Date::toTuple() const noexcept
{
	return make_tuple(_month, _day, _year);
}

void Date::readFromTuple(const tuple<uint8_t, uint8_t, uint16_t>& date_tuple) noexcept
{
	_month = get<0>(date_tuple);
	_day = get<1>(date_tuple);
	_year = get<2>(date_tuple);

	_dayIndex = _calcDayIndex();
}

bool Date::isNullDate() const
{
	return _day == 0 && _month == 0 && _year == 0;
}

bool Date::equals(const Date& other) const noexcept
{
	if (_dayIndex == other._dayIndex && _year == other._year)
		return true;

	return false;
}

bool Date::doesNotEqual(const Date& other) const noexcept
{
	if (_dayIndex != other._dayIndex || _year != other._year)
		return true;

	return false;
}

bool Date::lessThan(const Date& other) const noexcept
{
	if (_year != other._year)
		return _year < other._year;
	if (_month != other._month)
		return _month < other._month;
	return _day < other._day;
}

bool Date::lessThanEqualTo(const Date& other) const noexcept
{
	if (_year < other._year) 
		return true;
	if (_year > other._year) 
		return false;

	// _year == other._year
	if (_month < other._month) 
		return true;
	if (_month > other._month) 
		return false;

	// _year == other._year
	// _month == other._month
	return _day <= other._day;
}

bool Date::greaterThan(const Date& other) const noexcept
{
	if (_year != other._year)
		return _year > other._year;
	if (_month != other._month)
		return _month > other._month;
	return _day > other._day;
}

bool Date::greaterThanEqualTo(const Date& other) const noexcept
{
	if (_year > other._year)
		return true;
	if (_year < other._year)
		return false;

	// _year == other._year
	if (_month > other._month)
		return true;
	if (_month < other._month)
		return false;

	// _year == other._year
	// _month == other._month
	return _day >= other._day;
}

strong_ordering Date::compareWith(const Date& other) const noexcept
{
	if (_year < other._year)
		return strong_ordering::less;
	if (_year > other._year)
		return strong_ordering::greater;

	// _year == other._year
	if (_month < other._month)
		return strong_ordering::less;
	if (_month > other._month)
		return strong_ordering::greater;

	// _year == other._year
	// _month == other._month
	if (_day < other._day)
		return strong_ordering::less;
	if (_day > other._day)
		return strong_ordering::greater;

	return strong_ordering::equal;
}

bool Date::isLeapYear(uint16_t year) noexcept
{
	return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
}

Date Date::getCurrentDate() noexcept
{
	const time_t now = time(nullptr);
	tm cal_time;
	localtime_s(&cal_time, &now);

	return Date(cal_time.tm_mon + 1, cal_time.tm_mday, cal_time.tm_year + 1900);
}

bool operator == (const Date& A, const Date& B)
{
	return A.equals(B);
}

bool operator != (const Date& A, const Date& B)
{
	return A.doesNotEqual(B);
}

bool operator < (const Date& A, const Date& B)
{
	return A.lessThan(B);
}

bool operator <= (const Date& A, const Date& B)
{
	return A.lessThanEqualTo(B);
}

bool operator > (const Date& A, const Date& B)
{
	return A.greaterThan(B);
}

bool operator >= (const Date& A, const Date& B)
{
	return A.greaterThanEqualTo(B);
}

strong_ordering operator <=> (const Date& A, const Date& B)
{
	return A.compareWith(B);
}

Date& operator ++ (Date& date)
{
	date = date.nextDate();
	return date;
}

Date operator + (Date& date, uint16_t days)
{
	Date newDate(date);
	newDate.addDays(days);
	return newDate;
}

Date& operator += (Date& date, uint16_t days)
{
	date.addDays(days);
	return date;
}

Date& operator -- (Date& date)
{
	date = date.lastDate();
	return date;
}

Date operator - (Date& date, uint16_t days)
{
	Date newDate(date);
	newDate.subtractDays(days);
	return newDate;
}

Date& operator -= (Date& date, uint16_t days)
{
	date.subtractDays(days);
	return date;
}
