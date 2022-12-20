#ifndef SDDS_VEHICLE_H
#define SDDS_VEHICLE_H
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "ReadWritable.h"
using namespace std;
namespace sdds {
	class Vehicle :
		public ReadWritable {
		char m_Licenseplate[9]{};
		char* m_Makeandmodel{};
		void upper(char* upper) const;
	protected:
		void setEmpty();
		bool isEmpty() const;
		const char* getMakeModel() const;
		void setMakeModel(const char* value);
		int vehicleType{};
		int m_Parkingspotnumber{};
	public:
		int getParkingSpot();
		void setParkingSpot(const int value);
		bool operator==(const char* value)const;
		bool operator==(const Vehicle& rhs)const;
		virtual istream& read(istream& istr);
		virtual ostream& write(ostream& ostr) const;
		Vehicle(const char* Licenseplate, const char* Makeandmodel);
		Vehicle(const Vehicle& vehicle);
		Vehicle& operator=(const Vehicle& vehicle);
		Vehicle();
		~Vehicle();
		virtual void carOfMotor();
		int returnVehicleType();

		void setVehicleType(int vehicleType);
		const char* getLicensePlate() const;
	};
}
#endif