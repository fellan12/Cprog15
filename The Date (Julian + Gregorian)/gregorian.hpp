#ifndef GREGORIAN_H
#define GREGORIAN_H

#include <string>
#include <iostream>
#include <stdexcept> 

#include "date.hpp"
#include "julian.hpp"

namespace lab2 {
	class Gregorian : public Date {
	public:
		Gregorian();
		Gregorian(int, int, int);
		Gregorian(Gregorian const &);
		Gregorian(Date const &);
		~Gregorian();
		Gregorian& operator=(Date const & cd);
		virtual int days_in_month(int = -1, int = -1) const override;
		virtual int mod_julian_day() const override;

		virtual Date& operator++() override;
		virtual Date& operator--() override;
		virtual Date& operator+=(int) override;
		virtual Date& operator-=(int) override;
		Gregorian operator++(int);
		Gregorian operator--(int);
	};
}

#endif