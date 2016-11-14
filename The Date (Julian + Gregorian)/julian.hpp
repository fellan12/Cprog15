#ifndef JULIAN_H
#define JULIAN_H

#include <string>
#include <iostream>
#include <stdexcept> 

#include "date.hpp"
#include "gregorian.hpp"

namespace lab2 {
	class Julian : public Date {
	public:
		Julian();
		Julian(int, int, int);
		Julian(Date const *);
		Julian(Date const &);
		~Julian();
		Julian& operator=(Date const & cd);
		virtual int days_in_month(int = -1, int = -1) const override;
		virtual int mod_julian_day() const override;

		virtual Date& operator++() override;
		virtual Date& operator--() override;
		virtual Date& operator+=(int) override;
		virtual Date& operator-=(int) override;
		Julian operator++(int);
		Julian operator--(int);
	};
}

#endif