#ifndef GREGORIAN_C
#define GREGORIAN_C

#include "gregorian.hpp"
#include "kattistime.h"

using namespace std;

namespace lab2 {
	//
	Gregorian::Gregorian() : Date() {}

	//
	Gregorian::Gregorian(int year, int month, int day) : Date(year, month, day) {
		if (month > 12 || month < 1) {
			throw std::invalid_argument("Invalid month.");
		} 
		if (day > days_in_month(month, year) || day < 1) {
			throw std::invalid_argument("Invalid day.");
		} 
	}

	// Copy-constructor
	Gregorian::Gregorian(Gregorian const & cd) {
		_year = cd._year;
		_month = cd._month;
		_day = cd._day;
	}

	// Copy-constructor
	Gregorian::Gregorian(Date const & cd) {
		_year = cd.year();
		_month = cd.month();
		_day = cd.day();
		(*this) -= mod_julian_day() - cd.mod_julian_day();
	}

	Gregorian::~Gregorian() {}

	Gregorian& Gregorian::operator=(Date const & cd) {
		_year = cd.year();
		_month = cd.month();
		_day = cd.day();
		(*this) -= mod_julian_day() - cd.mod_julian_day();
		return *this;
	}

	Date& Gregorian::operator++() {
		*this += 1;
		return *this;
	}

	Gregorian Gregorian::operator++(int) {
		Gregorian date_copy(*this);
		++(*this);
		return date_copy;
	}

	Date& Gregorian::operator--() {
		*this -= 1;
		return *this;
	}

	Gregorian Gregorian::operator--(int) {
		Gregorian date_copy(*this);
		--(*this);
		return date_copy;
	}

	Date& Gregorian::operator+=(int add) {
		if (add < 0) {
			*this -= -add;
			return *this;
		}

		_year += add / 365;
		_day += add % 365;

		// Now, the date could be like 2017-11-223
		while (_day > days_in_month(_month)) {
			_day -= days_in_month(_month);
			++_month;
			if (_month > 12) {
				++_year;
				_month = 1;
			}
		}

		return *this;
	}

	Date& Gregorian::operator-=(int del) {
		if (del < 0) {
			*this += -del;
			return *this;
		}
		
		_year -= del / 365;
		_day -= del % 365;

		// Now, the date could be like 2017-11--223
		while (_day < 1) {
			_day += days_in_month((_month - 2 + 12) % 12 + 1);
			--_month;
			if (_month < 1) {
				--_year;
				_month = 12;
			}
		}

		return *this;
	}

	int Gregorian::days_in_month(int month, int year) const {
		if (year == -1)
			year = _year;
		if (month == -1)
			month = _month;

		if (month == 2 && _year % 4 == 0 && (_year % 100 != 0 || _year % 400 == 0))
			return 29;
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			return 31;
		} else if (month == 4 || month == 6 || month == 9 || month == 11) {
			return 30;
		} else if (month == 2) {
			return 28;
		}
		return 0;
	}

	//
	int Gregorian::mod_julian_day() const {
		int a = (14 - _month) / 12;
		int ye = _year + 4800 - a;
		int mo = _month + 12*a - 3;
		return _day + (153*mo+2) / 5 + 365 * ye + ye / 4 - ye / 100 + ye / 400 - 32045 - 2400001;
	}

	
}

#endif