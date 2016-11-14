#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

namespace lab2 {
	class Date {
	public:
		Date();
		Date(int, int, int);
		Date(Date const &);
		virtual ~Date();

		int year() const;
		unsigned int month() const;
		unsigned int day() const;
		unsigned int week_day() const;
		unsigned int days_per_week() const;
		unsigned int months_per_year() const;
		unsigned int days_this_month() const;
		std::string week_day_name() const;
		std::string month_name() const;
		void add_year(int = 1);
		void add_month(int = 1);
		void delete_month(int = 1);
		int operator-(const Date&) const;
		bool operator==(Date const &) const;
		bool operator!=(Date const &) const;
		bool operator<(Date const &) const;
		bool operator<=(Date const &) const;
		bool operator>(Date const &) const;
		bool operator>=(Date const &) const;
		virtual Date& operator+=(int) = 0;
		virtual Date& operator-=(int) = 0;
		virtual Date& operator++() = 0;
		virtual Date& operator--() = 0;
		virtual Date& operator=(Date const &);
		virtual int mod_julian_day() const = 0;
		virtual int days_in_month(int = -1, int = -1) const = 0;

	protected:
		int _year;
		int _month;
		int _day;
	};
	std::ostream& operator<<(std::ostream & o, const Date& date);
}

#endif