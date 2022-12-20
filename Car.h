#ifndef SDDS_CAR_H
#define SDDS_CAR_H
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "Vehicle.h"
using namespace std;
namespace sdds {
	class Car : public Vehicle {
		bool m_Carwashflag;
	protected:
		bool invalid(istream& istream);
	public:
		Car();
		Car(const char* Lisenseplate, const char* Makeandmodel);
		Car& operator=(const Car& car) = delete;
		virtual istream& read(istream& istream);
		virtual ostream& write(ostream& istream) const;

		void carOfMotor() override;
	};
}
#endif