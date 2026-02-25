// ProductExpirationTracker
// Product.h
// Created on Feb 13 2026 by Justyn Durnford
// Last modified on Feb 19 2026 by Justyn Durnford
// Header file for the Product class

#pragma once

#include "Date.h"

class Product
{
	std::string _name;
	std::vector<Date> _killDates;

	public:

	// 
	Product() = default;

	// 
	Product(const std::string& name, Date killDate);

	// 
	Product(const std::string& name, const std::vector<Date>& killDates);

	// 
	Product(const std::vector<std::string>& csvLine);

	// 
	const std::string& getName() const;

	// 
	const std::vector<Date>& getKillDates() const;

	// 
	Date getKillDate(std::size_t index) const;

	// 
	void setName(const std::string& name);

	// 
	std::vector<Date>::iterator addKillDate(Date killDate);

	// 
	std::vector<Date>::iterator setKillDate(std::size_t index, Date killDate);

	// 
	std::string toString() const;

	// 
	bool readFromCSVLine(const std::vector<std::string>& csvLine);

	// 
	std::vector<std::string> toCSVLine() const;
};