#ifndef SDDS_MOTORCYCLE_H
#define SDDS_MOTORCYCLE_H
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "Vehicle.h"
using namespace std;
namespace sdds {
	class Motorcycle :
		public Vehicle {
		bool m_HasSidecarflag{};
	protected:
		bool invalid(istream& istream);
	public:
		Motorcycle();
		Motorcycle(const char* Lisenseplate, const char* Makeandmodel);
		Motorcycle& operator=(const Motorcycle& motorcycle) = delete;
		virtual istream& read(istream& istream);
		virtual ostream& write(ostream& ostream) const;

		void carOfMotor() override;
	};
}
#endif
