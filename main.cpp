// ProductExpirationTracker
// main.cpp
// Created on Feb 03 2026 by Justyn Durnford
// Last modified on Feb 26 2026 by Justyn Durnford

#include "CSVFileReader.h"
#include "CSVFileWriter.h"
#include "Date.h"
#include "DateList.h"
#include "Product.h"
#include "ProductTable.h"

// #include <algorithm>
using std::sort;

#include <compare>
using std::strong_ordering;

// #include <cstdint>
using std::uint8_t;
using std::uint16_t;

// #include <string>
using std::size_t;
using std::string;
using std::to_string;

// #include <tuple>
using std::tuple;
using std::get;

// #include <vector>
using std::vector;

#include <iostream>
using std::cin;
using std::cout;

#if defined(_DEBUG) || !defined(NDEBUG)

void printDateEntry(const tuple<uint8_t, uint8_t, uint16_t>& tup)
{
    cout << int(get<0>(tup)) << '/' << int(get<1>(tup)) << '/' << int(get<2>(tup)) << '\n';
}

void println()
{
    cout << '\n';
}

void println(const string& line)
{
    cout << line << '\n';
}

void print_vec(const vector<string>& vec)
{
    if (vec.size() == 0)
        return;

    if (vec.size() == 1)
    {
        cout << "{ " << vec[0] << " }\n";
        return;
    }

    cout << "{ ";

    for (size_t i = 0; i < vec.size() - 1; ++i)
        cout << vec[i] << ", ";

    cout << vec[vec.size() - 1] << " }\n";
}

void printbool(bool b)
{
    if (b)
        println("true");
    else
        println("false");
}

void print_order(strong_ordering order)
{
    if (order == strong_ordering::less)
        println("less");
    else if (order == std::strong_ordering::greater)
        println("greater");
    else
        println("equal");
}

void printProduct(const Product& product)
{
    cout << product.getName() << ": ";

    for (size_t i = 0; i < product.getKillDates().size(); ++i)
        cout << product.getKillDates()[i].toString() << " ";

    cout << '\n';
}

void printProductTable(const ProductTable& table)
{
    for (auto iter = table.begin(); iter != table.end(); ++iter)
    {
        cout << iter->first << ": ";

        if (iter->second.size() != 0)
        {
            for (auto vec_iter = iter->second.begin(); vec_iter != iter->second.end(); ++vec_iter)
                cout << vec_iter->toString() << " ";
        }

        println();
    }
}

#endif // #if defined(_DEBUG) || !defined(NDEBUG)

int main()
{
    CSVFileReader in_file("data.csv");
    CSVFileWriter out_file("output.csv");
    ProductTable table;
    vector<string> line;
    Date currentDay(Date::getCurrentDate());

    while (in_file.isGood())
    {
        line = in_file.getValuesInLine();

        if (in_file.isGood() || in_file.isEOF())
            table.addProductData(Product(line));
    }

    vector<Product> products(table.getAllProducts());
    table.clear();

    for (Product& product : products)
    {
        size_t pos = product.getName().find('*');

        if (pos != static_cast<size_t>(-1))
            product.setName(product.getName().substr(0, product.getName().size() - 1));

        const vector<Date>& killDates(product.getKillDates());

        for (const Date& date : killDates)
        {
            int distance = currentDay.distanceFrom(date);

            if (distance < 14 && !date.isNullDate())
            {
                cout << product.getName() << " || " << date.toString() << " || " << distance << '\n';
                product.setName(product.getName() + '*');
            }
        }
    }

    for (const Product& product : products)
        out_file.writeValues(product.toCSVLine());

    products.clear();

    cout << '\n';
    cout << "output.csv file updated.\n";
    cout << "Press any key to end program.\n";
    cin.get();

    return 0;
}