// ProductExpirationTracker
// ProductTable.h
// Created on Feb 14 2026 by Justyn Durnford
// Last modified on Feb 23 2026 by Justyn Durnford
// Header file for the ProductTable class

#pragma once

#include "Product.h"

#include <map>

#include <string>

// 
class ProductTable
{
	std::map<std::string, std::vector<Date>> _productMap;

	public:

	//
	ProductTable() = default;

	// 
	std::map<std::string, std::vector<Date>>::iterator findProductData(const std::string& productName);

	// 
	std::map<std::string, std::vector<Date>>::const_iterator findProductData(const std::string& productName) const;

	// 
	std::map<std::string, std::vector<Date>>::iterator findProductData(const Product& product);

	// 
	std::map<std::string, std::vector<Date>>::const_iterator findProductData(const Product& product) const;

	// 
	std::map<std::string, std::vector<Date>>::iterator findProductKillDate(const std::string& productName, Date killDate);

	// 
	std::map<std::string, std::vector<Date>>::const_iterator findProductKillDate(const std::string& productName, Date killDate) const;

	// 
	std::map<std::string, std::vector<Date>>::iterator findProductKillDate(const Product& product, Date killDate);

	// 
	std::map<std::string, std::vector<Date>>::const_iterator findProductKillDate(const Product& product, Date killDate) const;

	// 
	bool doesProductDataExist(const std::string& productName) const;

	// 
	bool doesProductDataExist(const Product& product) const;

	// 
	bool doesProductHaveKillDate(const std::string& productName, const Date& killDate) const;

	// 
	bool doesProductHaveKillDate(const Product& product, const Date& killDate) const;

	// 
	Product getProductData(const std::string& productName) const;

	// 
	std::vector<Date> getProductKillDates(const std::string& productName) const;

	// 
	Date getProductFirstKillDate(const std::string& productName) const;

	// Adds a Product to the product map constructed with the given values.
	// This function does nothing if a product with the given name already exists.
	std::map<std::string, std::vector<Date>>::iterator addProductData(const std::string& productName, Date killDate = Date());

	// Adds a Product to the product map constructed with the given values.
	// This function does nothing if a product with the given name already exists.
	std::map<std::string, std::vector<Date>>::iterator addProductData(const Product& product);

	// Removes the Product with the given product values from the product map and returns a copy of it.
	// This function does nothing if a product with the given name does not exist.
	Product removeProductData(const std::string& productName);

	// Removes the Product with the given product values from the product map and returns a copy of it.
	// This function does nothing if a product with the given name does not exist.
	Product removeProductData(const Product& product);

	// If a Product with the given name already exists:
	// > Sets the data of the product in the product map to a Product with the given values.
	// 
	// If a Product with the given name does not exist:
	// > Adds a Product to the product map constructed with the given values.
	std::map<std::string, std::vector<Date>>::iterator setProductData(const std::string& productName, Date killDate = Date());

	// If a Product with the given name already exists:
	// > Sets the data of the product in the product map to a Product with the given values.
	// 
	// If a Product with the given name does not exist:
	// > Adds a Product to the product map constructed with the given values.
	std::map<std::string, std::vector<Date>>::iterator setProductData(const Product& product);

	// 
	std::map<std::string, std::vector<Date>>::iterator addProductKillDate(const std::string& productName, Date killDate = Date());

	// 
	std::map<std::string, std::vector<Date>>::iterator addProductKillDates(const std::string& productName, const std::vector<Date>& killDates);

	// 
	Date removeProductKillDate(const std::string& productName, Date killDate);

	// 
	Date removeProductKillDate(const Product& product, Date killDate);

	// 
	std::size_t removeProductKillDates(const std::string& productName);

	// 
	std::size_t removeProductKillDates(const Product& product);

	// 
	// Functionally identical to setProductData(const Product& product) but added for convenience.
	std::map<std::string, std::vector<Date>>::iterator setProductKillDate(const std::string& productName, Date killDate = Date());

	// 
	std::map<std::string, std::vector<Date>>::iterator setProductKillDates(const std::string& productName, const std::vector<Date>& killDates);

	// 
	std::map<std::string, std::vector<Date>>::iterator begin();

	// 
	std::map<std::string, std::vector<Date>>::const_iterator begin() const;

	// 
	std::map<std::string, std::vector<Date>>::iterator end();

	// 
	std::map<std::string, std::vector<Date>>::const_iterator end() const;

	// 
	std::vector<Product> getAllProducts() const;
};