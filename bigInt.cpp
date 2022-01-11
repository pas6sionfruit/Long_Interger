#include "bigInt.h"

bool bigInt::IsGreater(const std::vector<unsigned short>& l, const std::vector<unsigned short>& r) const {

	bool b = false;

	if (l.size() == r.size()) {

		for (int i = 0; i < l.size(); i++) {

			if (l[i] > r[i]) {

				b = true;
			}
		}
	}
	else b = l.size() > r.size();

	return b;
}

void bigInt::SumReserve(const std::vector<unsigned short>& val, std::vector<unsigned short>& dest, int step) const {

	size_t size = val.size() + step + 1;
	dest.reserve(size);

	for (int i = 0; i < size; i++) {

		i <= step ? dest.push_back(0) : dest.push_back(val[i - step - 1]);
	}

}

void bigInt::DifReserve(const std::vector<unsigned short>& val, std::vector<unsigned short>& dest, int step) const {

	size_t size = val.size() + step;
	dest.reserve(size);

	for (int i = 0; i < size; i++) {

		i < step ? dest.push_back(0) : dest.push_back(val[i - step]);
	}
}

//bigInt::bigInt(const bool non) {
//
//	_sign = false;
//	_non = true;
//}

std::vector<unsigned short> bigInt::Sum(const std::vector<unsigned short>& l, const std::vector<unsigned short>& r) const {

	std::vector<unsigned short> res;
	int step, sum, carry = 0;
	bool b;

	if (l.size() > r.size()) {  // Seeking a value with a grater size to provide an appropriate initialization and size reservation for the resulting vector.

		b = true;
		step = l.size() - r.size();
		SumReserve(r, res, step);
	}

	else {

		b = false;
		step = r.size() - l.size();
		SumReserve(l, res, step);
	}

	for (int i = res.size() - 1; i > 0; i--) {

		b ? sum = l[i - 1] + res[i] + carry : sum = r[i - 1] + res[i] + carry;

		if (sum > 9) {

			carry = sum / 10;
			sum %= 10;
		}
		else carry = 0;

		res[i] = sum;
	}

	if (carry) res[0] = carry;

	else res.erase(res.begin());
	
	return res;
}

std::vector<unsigned short> bigInt::Dif(const std::vector<unsigned short>& l, const std::vector<unsigned short>& r) const {

	std::vector<unsigned short> res;
	int sum, step;
	bool carry = false, b;

	if (IsGreater(l,r)) {

		b = true;
		step = l.size() - r.size();
		DifReserve(r, res, step);
	}

	else {

		b = false;
		step = r.size() - l.size();
		DifReserve(l, res, step);
	}

	for (int i = res.size() - 1; i >= 0; i--) {

		b ? sum = l[i] - res[i] : sum = r[i] - res[i];

		if (carry) sum -= 1;

		if (sum < 0) {

			carry = true;
			sum += 10;
		}

		else carry = false;

		res[i] = sum;
	}

	return res;
}

bigInt::bigInt() {

	_sign = false;
	_non = false;
}

bigInt::bigInt(bool sign, std::vector<unsigned short>& val) {

	_non = val.empty();
	_sign = sign;
	_interger = val;
}

bigInt::bigInt(std::vector<unsigned short>& val) {

	_non = val.empty();
	_sign = false;
	_interger = val;

}

bigInt::bigInt(bool sign, const std::string& val) {

	_non = !(std::all_of(val.begin(), val.end(), std::isdigit));
	_sign = sign;

	for (auto i : val) {

		_interger.push_back(i - '0');
	}		
}

bigInt::bigInt(const std::string& val) {

	_non = !(std::all_of(val.begin(), val.end(), std::isdigit));
	_sign = false;

	for (auto i : val) {

		_interger.push_back(i - '0');
	}
}

bigInt::bigInt(bool sign, std::string&& val) {

	_non = !(std::all_of(val.begin(), val.end(), std::isdigit));
	_sign = sign;

	for (auto i : val) {

		_interger.push_back(i - '0');
	}

}

bigInt::bigInt(std::string&& val) {

	_non = !(std::all_of(val.begin(), val.end(), std::isdigit));
	_sign = false;

	for (auto i : val) {

		_interger.push_back(i - '0');
	}

}

bigInt::bigInt(const bigInt& val) {

	_non = val._non;
	_sign = val._sign;
	_interger = val._interger;
}

bigInt::bigInt(bigInt&& val) noexcept {

	_non = val._non;
	_sign = val._sign;
	_interger = std::move(val._interger);

}

bigInt& bigInt::operator=(const bigInt& val) {

	if (this == &val)
		return *this;

	_non = val._non;
	_sign = val._sign;
	_interger = val._interger;

	return *this;
}

bigInt& bigInt::operator=(bigInt&& val) noexcept {

	if (this == &val)
		return *this;

	_non = val._non;
	_sign = val._sign;
	_interger = std::move(val._interger);

	return *this;
}

bigInt bigInt::operator+(const bigInt& val) const {


	if (_non || val._non) return *this;  // Operator implementation for "non" as an operand(s) returns non.

	if (_sign && !val._sign && _interger == val._interger

		|| !_sign && val._sign && _interger == val._interger) {  // If values are equal but signs aren't.

		return bigInt("0");
	}

	std::vector<unsigned short> res_val;


	if (!_sign && val._sign || _sign && !val._sign) {

		res_val = Dif(this->_interger, val._interger);

		bigInt res(res_val);

		!_sign && val._sign ? res._sign = !IsGreater(_interger, val._interger) : res._sign = IsGreater(_interger, val._interger);

		return res;
	}

	res_val = Sum(_interger, val._interger);

	bigInt res(res_val);

	_sign&& val._sign ? res._sign = true : res._sign = false;

	return res;

}

bigInt bigInt::operator-(const bigInt& val) const { 

	if (_non || val._non) return *this;   // Operator implementation for "non" as an operand(s) returns non.

	if (!_sign && !val._sign && _interger == val._interger) {  // Both positive with values equal.

		return bigInt("0");
	}

	std::vector<unsigned short> res_val;


	if (!_sign && val._sign || _sign && !val._sign) {

		res_val = Sum(this->_interger, val._interger);

		bigInt res(res_val);

		!_sign && val._sign ? res._sign = false : res._sign = true;

		return res;

	}

	res_val = Dif(_interger, val._interger);

	bigInt res(res_val);

	if (_sign && val._sign) {

		res._sign = IsGreater(_interger, val._interger);
	}
	
	if (!_sign && !val._sign) {

		res._sign = !IsGreater(_interger, val._interger);
	}

	

	return res;

}

bool bigInt::operator==(const bigInt& val) const {

	return _non == val._non 
		&& _sign == val._sign 
		&& _interger == val._interger;
}

bool bigInt::operator!=(const bigInt& val) const {

	return !(*this == val);
}

bool bigInt::operator>(const bigInt& val) const {

	if (_non || val._non) return false;

	if (*this == val) return false;

	if (_sign != val._sign) {

		return _sign < val._sign;
	}

	if (_sign && val._sign) {

		return !IsGreater(_interger, val._interger);
	}
	return IsGreater(_interger,val._interger);
}

bool bigInt::operator<(const bigInt& val) const {

	if (_non || val._non) return false;

	if (*this == val) return false;

	if (_sign != val._sign) {

		return _sign > val._sign;
	}

	if (_sign && val._sign) {

		return IsGreater(_interger, val._interger);
	}

	return !IsGreater(_interger, val._interger);
}

bool bigInt::operator>=(const bigInt& val) const {

	return (*this > val || *this == val);
}

bool bigInt::operator<=(const bigInt& val) const {
	
	return (*this < val || *this == val);
}

void bigInt::SetSign(bool sign) {

	_sign = sign;
}

void bigInt::SetValue(std::vector<unsigned short>& val) {

	_interger = val;
}

bool bigInt::GetSign() const {

	return _sign;
}

std::vector<unsigned short> bigInt::GetValue() const {
	return _interger;
}

std::ostream& operator<<(std::ostream& os, const bigInt& val) {

	if (val._non)
		os << "non";

	else {

		if (val._sign) os << "-";

		for (auto i : val._interger) {
			os << i;
		}
	}

	return os;
}
