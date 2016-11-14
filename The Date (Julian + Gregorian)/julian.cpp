#ifndef JULIAN_C
#define JULIAN_C

#include "julian.hpp"
#include "kattistime.h"

#define DAYS_PER_WEEK 7

namespace lab2 {
	using namespace std;

	//
	Julian::Julian() {
		Gregorian * g = new Gregorian();
		*this = *g;
		delete g;
	}

	//
	Julian::Julian(int year, int month, int day) : Date(year, month, day) {
		if (month > 12 || month < 1) {
			throw std::invalid_argument("Invalid month.");
		} 
		if (day > days_in_month(month, year) || day < 1) {
			throw std::invalid_argument("Invalid day.");
		} 
	}

	// Copy-constructor
	Julian::Julian(Date const * cd) {
		_year = (*cd).year();
		_month = (*cd).month();
		_day = (*cd).day();
	}

	// Copy-constructor
	Julian::Julian(Date const & cd) {
		_year = cd.year();
		_month = cd.month();
		_day = cd.day();
		(*this) -= mod_julian_day() - cd.mod_julian_day();
	}

	Julian& Julian::operator=(Date const & cd) {
		_year = cd.year();
		_month = cd.month();
		_day = cd.day();
		(*this) -= mod_julian_day() - cd.mod_julian_day();
		return *this;
	}

	Julian::~Julian() {}

	Date& Julian::operator++() {
		*this += 1;
		return *this;
	}

	Julian Julian::operator++(int) {
		Julian date_copy(*this);
		++(*this);
		return date_copy;
	}

	Date& Julian::operator--() {
		*this -= 1;
		return *this;
	}

	Julian Julian::operator--(int) {
		Julian date_copy(*this);
		--(*this);
		return date_copy;
	}

	Date& Julian::operator+=(int add) {
		if (add < 0) {
			*this -= -add;
			return *this;
		}

		// TODO Fix for negative values
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

	Date& Julian::operator-=(int del) {
		if (del < 0) {
			*this += -del;
			return *this;
		}
		
		// TODO Fix for negative values
		_year -= del / 365;
		_day -= del % 365;

		// Now, the date could be like 2017-11-223
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

	//2015-01-09 -17
	//2015-01-(-8)

	int Julian::days_in_month(int month, int year) const {
		if (year == -1)
			year = _year;
		if (month == -1)
			month = _month;

		if (month == 2 && _year % 4 == 0)
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
	int Julian::mod_julian_day() const {
		int a = (14 - _month) / 12;
		int ye = _year + 4800 - a;
		int mo = _month + 12 * a - 3;
		return _day + (153 * mo + 2) / 5 + 365 * ye + ye / 4 - 32083 - 2400001; // 2400001 kommer från att 5/11 1858 har det värdet
	}
}

#endif