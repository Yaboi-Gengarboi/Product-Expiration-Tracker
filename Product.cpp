// ProductExpirationTracker
// Product.h
// Created on Feb 13 2026 by Justyn Durnford
// Last modified on Feb 24 2026 by Justyn Durnford
// Implementation file for the Product class

#include "Product.h"

#include <algorithm>
using std::find;
using std::sort;

// <string>
using std::size_t;
using std::string;

// <vector>
using std::vector;

Product::Product(const string& name, Date killDate)
{
	_name = name;
	_killDates.push_back(killDate);
}

Product::Product(const string& name, const vector<Date>& killDates)
{
	_name = name;
	_killDates = killDates;
	sort(_killDates.begin(), _killDates.end());
}

Product::Product(const vector<string>& csvLine)
{
	readFromCSVLine(csvLine);
}

const string& Product::getName() const
{
	return _name;
}

const vector<Date>& Product::getKillDates() const
{
	return _killDates;
}

Date Product::getKillDate(size_t index) const
{
	return _killDates[index];
}

void Product::setName(const string& name)
{
	_name = name;
}

vector<Date>::iterator Product::addKillDate(Date killDate)
{
	if (find(_killDates.begin(), _killDates.end(), killDate) != _killDates.end())
	{
		_killDates.push_back(killDate);
		sort(_killDates.begin(), _killDates.end());
		return find(_killDates.begin(), _killDates.end(), killDate);
	}

	return _killDates.end();
}

vector<Date>::iterator Product::setKillDate(size_t index, Date killDate)
{
	if (index < _killDates.size())
	{
		_killDates[index] = killDate;
		sort(_killDates.begin(), _killDates.end());
		return find(_killDates.begin(), _killDates.end(), killDate);
	}

	return _killDates.end();
}

string Product::toString() const
{
	string str(_name);
	str += ": ";

	if (_killDates.empty())
		str += "NA";
	else if (_killDates[0].isNullDate())
		str += "NA";
	else
	{
		for (size_t i = 0; i < _killDates.size(); ++i)
		{
			if (!_killDates[i].isNullDate())
				str += _killDates[i].toString();
			else
				return str;

			if (i < _killDates.size() - 1 && !_killDates[i + 1].isNullDate())
				str += ", ";
		}
	}

	return str;
}

bool Product::readFromCSVLine(const vector<string>& csvLine)
{
	try
	{
		if (csvLine.size() >= 4)
		{
			string name(csvLine[0]);
			string dateStr;

			if (!name.empty())
			{
				_name = name;

				for (size_t i = 3; i < csvLine.size(); ++i)
				{
					dateStr = csvLine[i];

					if (dateStr != "" && dateStr != "NA")
						_killDates.push_back(dateStr);
				}

				return true; 
			}
			else
				return false;
		}
		else
			return false;
	}
	catch (...)
	{

	}

	return false;
}

vector<string> Product::toCSVLine() const
{
	vector<string> csvLine;

	csvLine.push_back(_name);
	csvLine.push_back("");
	csvLine.push_back("");

	if (_killDates.empty())
		csvLine.push_back("NA");
	else
	{
		for (size_t i = 0; i < _killDates.size(); ++i)
			csvLine.push_back(_killDates[i].toString());
	}

	return csvLine;
}
