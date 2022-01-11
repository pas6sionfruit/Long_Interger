#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

class bigInt
{
	bool _non;
	bool _sign;
	std::vector<unsigned short> _interger;


	//explicit bigInt(const bool non); // Mysterous magic Hogwarts when implementing this constructor the one for const string& doesen't work

	bool IsGreater(const std::vector<unsigned short>& l, const std::vector<unsigned short>& r) const;
	std::vector<unsigned short>Sum(const std::vector<unsigned short>& l, const std::vector<unsigned short>& r) const;
	void SumReserve(const std::vector<unsigned short>& val, std::vector<unsigned short>& dest, int step) const;
	std::vector<unsigned short>Dif(const std::vector<unsigned short>& l, const std::vector<unsigned short>& r) const;
	void DifReserve(const std::vector<unsigned short>& val, std::vector<unsigned short>& dest, int step) const;



public:

	
	bigInt();
	bigInt(bool sign, std::vector<unsigned short>& val);
	bigInt(std::vector<unsigned short>& val);
	bigInt(bool sign, const std::string& val);
	bigInt(const std::string& val);
	bigInt(bool sign, std::string&& val);
	bigInt(std::string&& val);
	bigInt(const bigInt& val);
	bigInt(bigInt&& val) noexcept;
	bigInt& operator=(const bigInt& val);
	bigInt& operator=(bigInt&& val) noexcept;
	bigInt operator+(const bigInt& val) const;
	bigInt operator-(const bigInt& val) const;
	bool operator==(const bigInt& val) const;
	bool operator!=(const bigInt& val) const;
	bool operator>(const bigInt& val) const;
	bool operator<(const bigInt& val) const;
	bool operator>=(const bigInt& val) const;
	bool operator<=(const bigInt& val) const;
	void SetSign(bool sign);
	void SetValue(std::vector<unsigned short>& val);
	[[nodiscard]] bool GetSign()const;
	[[nodiscard]] std::vector<unsigned short> GetValue()const;
	friend std::ostream& operator<<(std::ostream& os, const bigInt& val);


};

