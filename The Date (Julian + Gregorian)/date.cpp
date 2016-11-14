#ifndef DATE_C
#define DATE_C

#include "date.hpp"
#include "kattistime.h"
#include <stdexcept>

using namespace std;

namespace lab2 {
	//
	Date::Date() {
		time_t mytime;
		k_time(&mytime);

		struct tm *t = gmtime(&mytime);
	    _year = t->tm_year + 1900;
	    _month = t->tm_mon + 1;
	    _day = t->tm_mday;
	}

	//
	Date::Date(int year, int month, int day) {
		_year = year;
		_month = month;
		_day = day;
	}

	// Copy-constructor
	Date::Date(Date const & cd) {
		_year = cd._year;
		_month = cd._month;
		_day = cd._day;
	}

	Date::~Date() {}

	Date& Date::operator=(Date const & src) {
		if (&src == this)
			return *this;

		_year = src._year;
		_month = src._month;
		_day = src._day;
		return *this;
	}

	//
	int Date::year() const {
		return _year;
	}

	//
	unsigned int Date::month() const {
		return (unsigned int) _month;
	}

	//
	unsigned int Date::day() const {
		return (unsigned int) _day;
	}

	//
	unsigned int Date::week_day() const {
		return (unsigned int) ((mod_julian_day() - 5) % 7 + 1);
	}

	//
	unsigned int Date::days_per_week() const {
		return 7;
	}

	//
	unsigned int Date::days_this_month() const {
		return (unsigned int) (*this).days_in_month(_month);
	}

	//
	std::string Date::week_day_name() const {
		const std::string weekday_names[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
		return weekday_names[(week_day() - 1) % 7];
	}

	//
	std::string Date::month_name() const {
		const std::string month_names[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
		return month_names[month() - 1];
	}

	//
	void Date::add_year(int yp) {
		_year += yp;

		if (days_in_month(_month, _year) < _day) { // Skottårs hantering
			_day = days_in_month(_month);
		}
	}

	//
	void Date::delete_month(int month) {
		if (month < 0) {
			add_month(-month);
			return;
		}

		_month -= month;
		while (_month < 1) {
			_month += months_per_year();
			_year--;
		}

		if (days_in_month(_month) < _day) {
			_day = days_in_month(_month);
		}
	}

	//
	void Date::add_month(int month) {
		if (month < 0) {
			delete_month(-month);
			return;
		}

		_month += month;
		while (_month > months_per_year()) {
			_month -= months_per_year();
			_year++;
		}

		if (days_in_month(_month) < _day) {
			_day = days_in_month(_month);
		}
	}

	int Date::operator-(const Date& d) const {
		return mod_julian_day() - d.mod_julian_day();
	}

	bool Date::operator==(Date const & d) const {
		return mod_julian_day() == d.mod_julian_day();
	}
	
	bool Date::operator!=(Date const & d) const {
		return mod_julian_day() != d.mod_julian_day();
	}
	
	bool Date::operator<(Date const & d) const {
		return mod_julian_day() < d.mod_julian_day();
	}
	
	bool Date::operator<=(Date const & d) const {
		return mod_julian_day() <= d.mod_julian_day();
	}
	
	bool Date::operator>(Date const & d) const {
		return mod_julian_day() > d.mod_julian_day();
	}
	
	bool Date::operator>=(Date const & d) const {
		return mod_julian_day() >= d.mod_julian_day();
	}

	std::ostream& operator<<(std::ostream & stream, const Date& date) {
		stream << date.year() << "-";
		if (date.month() < 10)
			stream << "0";
		stream << date.month() << "-";
		if (date.day() < 10)
			stream << "0";
		stream << date.day();

	  	return stream;
	}

	unsigned int Date::months_per_year() const {
		return 12;
	}

}

#endif