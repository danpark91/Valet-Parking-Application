#ifndef SDDS_PARKING_H
#define SDDS_PARKING_H
#include <cstring>
#include <iomanip>
#include <iostream>
#include <ctype.h>
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Menu.h"
using namespace std;
namespace sdds {
	const int MAX_NUM_OF_PARKING_SPOTS = 100;
	class Parking {
		char* m_filename{};
		Menu m_parkingMenu;
		Menu m_vehicleMenu;
		int numOfSpots{};
		Vehicle* parkingSpots[MAX_NUM_OF_PARKING_SPOTS]{};
		int numOfPV{};
		int assignedVehicle(Vehicle* vehicle);
		void clear();
		bool isEmpty();
		void parkingStatus();
		void parkVehicle();
		void findVehicle();
		void returnVehicle();
		void listParkedVehicles();
		bool closeParking();
		bool exitParkingApp();
		bool loadData();
		void saveData();
		void mainMenu();
	public:
		Parking(const char* filename);
		~Parking();
		Parking(const char* datafile, int noOfSpots);
		int run();
		int returnNumOfSpots();
		int invalidNumOfSpots(int setNOS);
		int returnNumOfPV();
		int invalidNumOfPV(int setPV);
	};
}
#endif
