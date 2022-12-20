#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include "Parking.h"

namespace sdds {
    int Parking::assignedVehicle(Vehicle *vehicle) {
        if (vehicle == nullptr || numOfPV >= numOfSpots) {
            return 0;
        }

        // Check if vehicle has parking spot already
        if (vehicle->getParkingSpot() != 0) {
            parkingSpots[vehicle->getParkingSpot() - 1] = vehicle;
            invalidNumOfPV(numOfPV + 1);
            return vehicle->getParkingSpot();
        } else {
            for (int i = 0; i < numOfSpots; i++) {
                if (parkingSpots[i] == nullptr) {
                    parkingSpots[i] = vehicle;
                    vehicle->setParkingSpot(i + 1);
                    invalidNumOfPV(numOfPV + 1);
                    return i + 1;
                }
            }
        }

        return 0;
    }

    void Parking::clear() {
        m_filename = nullptr;
    }

    bool Parking::isEmpty() {
        return m_filename == nullptr;
    }

    void Parking::parkingStatus() {
        cout << "****** Valet Parking ******" << endl;
        cout << "*****  Available spots: " << numOfSpots - numOfPV << "    *****" << endl;
    }

    void Parking::parkVehicle() {
        if (numOfPV >= numOfSpots) {
            cout << "Parking is full" << endl;
            return;
        }
        int menu = m_vehicleMenu.run();
        Vehicle *vehicle;
        switch (menu) {
            case 1: {
                vehicle = new Car();
                vehicle->setCsv(false);
                vehicle->read(cin);
                if (assignedVehicle(vehicle) == 0) {
                    cout << "Parking is Full" << endl;
                } else {
                    cout << "Parking Ticket" << endl;
                    vehicle->carOfMotor();
                    cout << endl << "Press <ENTER> to continue...." << endl;
                }
                break;
            }
            case 2: {
                vehicle = new Motorcycle();
                vehicle->setCsv(false);
                vehicle->read(cin);
                if (assignedVehicle(vehicle) == 0) {
                    cout << "Parking is Full" << endl;
                } else {
                    cout << endl << "Parking Ticket" << endl;
                    vehicle->carOfMotor();
                    cout << endl << "Press <ENTER> to continue...." << endl;
                }
                break;
            }
            default: {
                cout << "Cancelled parking";
            }
                cout << endl;
        }
    }

    void Parking::returnVehicle() {
        cout << "Return Vehicle" << endl;
        char LPN[100];
        cout << "Enter License Plate Number: ";
        cin >> LPN;
        cout << endl;
        while (strlen(LPN) > 8 || strlen(LPN) < 1) {
            cout << "Invalid License Plate, try again: ";
            cin >> LPN;
        };
        for (int i = 0; i < numOfSpots; i++) {
            if (parkingSpots[i] != nullptr && (*parkingSpots[i]) == LPN) {
                cout << "Returning:" << endl;
                parkingSpots[i]->carOfMotor();
                delete parkingSpots[i];
                parkingSpots[i] = nullptr;
                invalidNumOfPV(numOfPV - 1);
                cout << endl << "Press <ENTER> to continue...." << endl;
                return;
            }
        }
        for (unsigned int i = 0; i < 100; i++) {
            if (LPN[i] == 0)
                break;
            LPN[i] = toupper(LPN[i]);
        }
        cout << "License plate " << LPN << " Not found" << endl;
        cout << endl << "Press <ENTER> to continue...." << endl;
    }

    void Parking::listParkedVehicles() {
        cout << "*** List of parked vehicles ***" << endl;
        for (int i = 0; i < returnNumOfSpots(); i++) {
            if (parkingSpots[i] != nullptr) {
                parkingSpots[i]->carOfMotor();
                cout << "-------------------------------" << endl;
            }
        }
        cout << "Press <ENTER> to continue...." << endl;
    }

    bool Parking::closeParking() {
        if (numOfPV == 0) {
            return true;
        }
        cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
        cout << "Are you sure? (Y)es/(N)o: ";
        bool status;
        char yn;
        do {
            status = false;
            cin >> yn;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2000, '\n');
                status = true;
            }
            if (!status && yn != 'y' && yn != 'Y' && yn != 'n' && yn !=
                                                                  'N') {
                status = true;
            }
            if (!status && cin.get() != '\n') {
                status = true;
                cin.ignore(2000, '\n');
            }
            if (status) {
                cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
            }
        } while (status);
        if (yn == 'N' || yn == 'n') {
            return false;
        }
        if (yn == 'Y' || yn == 'y') {
            cout << "Closing Parking" << endl;
            for (int i = 0; i < numOfSpots; i++) {
                if (parkingSpots[i] != nullptr) {
                    cout << endl << "Towing request" << endl;
                    cout << "*********************" << endl;
                    parkingSpots[i]->carOfMotor();
                    delete parkingSpots[i];
                    parkingSpots[i] = nullptr;
                    invalidNumOfPV(numOfPV - 1);
                }
            }
            return true;
        }
        return true;
    }

    bool Parking::exitParkingApp() {
        cout << "This will terminate the program!" << endl;
        cout << "Are you sure? (Y)es/(N)o: ";
        char yn;
        do {
            cin >> yn;
            if (cin.get() != '\n') {
                cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
                cin.ignore(2000, '\n');
                yn = '\0';
            }
        } while (yn != 'y' && yn != 'Y' && yn != 'n' && yn != 'N');
        return yn == 'y' || yn == 'Y';
    }

    bool Parking::loadData() {
        bool success = false;
        if (!isEmpty()) {
            char getFile{};
            ifstream file(m_filename);
            Vehicle *vehicle;
            while (file.get(getFile)) {
                file.ignore();
                switch (tolower(getFile)) {
                    case 'c':
                    case 'C':
                        vehicle = new Car();
                        vehicle->setCsv(true);
                        vehicle->read(file);
                        vehicle->setVehicleType(0);
                        if (assignedVehicle(vehicle) == 0)
                            cout << "Parking is Full" << endl;
                        break;
                    case 'm':
                    case 'M':
                        vehicle = new Motorcycle();
                        vehicle->setCsv(true);
                        vehicle->read(file);
                        vehicle->setVehicleType(1);
                        if (assignedVehicle(vehicle) == 0)
                            cout << "Parking is Full" << endl;
                        break;
                    default:
                        file.ignore(2000, '\n');
                        break;
                }
            }
            file.close();
            success = true;
        }
        return success;
    }

    void Parking::saveData() {
        if (!isEmpty()) {
            ofstream file(m_filename);
            for (int i = 0; i < numOfSpots; i++) {
                if (parkingSpots[i] != nullptr) {
                    int typeValue = parkingSpots[i]->returnVehicleType();
                    if (typeValue == 0) {
                        parkingSpots[i]->setCsv(true);
                        parkingSpots[i]->write(file);
                    }
                    if (typeValue == 1) {
                        parkingSpots[i]->setCsv(true);
                        parkingSpots[i]->write(file);
                    }
                }
            }
            file.close();
        }
    }

    void Parking::mainMenu() {
        m_parkingMenu << "Park Vehicle" << "Return Vehicle" << "List Parked Vehicles" << "Find Vehicle"
                      << "Close Parking (End of day)" << "Exit Program";
        m_vehicleMenu << "Car" << "Motorcycle" << "Cancel";
    }

    Parking::Parking(const char *filename) : m_parkingMenu("Parking Menu, select an action : "),
                                             m_vehicleMenu("Select type of the vehicle:", 1) {
        if (filename != nullptr && filename[0] != '\0') {
            m_filename = new char[strlen(filename) + 1];
            strcpy(m_filename, filename);
            invalidNumOfSpots(MAX_NUM_OF_PARKING_SPOTS);
            for (int i = 0; i < MAX_NUM_OF_PARKING_SPOTS; i++) {
                parkingSpots[i] = nullptr;
            }
            if (loadData()) {
                mainMenu();
            } else {
                cout << "Error in data file" << endl;
                clear();
            }
        } else {
            cout << "Error in data file" << endl;
            clear();
        }
    }

    Parking::~Parking() {
        saveData();
        delete[] m_filename;
        for (int i = 0; i < numOfSpots; ++i) {
            delete parkingSpots[i];
        }
    }

    Parking::Parking(const char *datafile, int noOfSpots) :
            m_parkingMenu("Parking Menu, select an action:"), m_vehicleMenu("Select type of the vehicle:", 1) {
        if (datafile != nullptr && datafile[0] != '\0') {
            m_filename = new char[strlen(datafile) + 1];
            strcpy(m_filename, datafile);
            if (noOfSpots < 10 || noOfSpots > MAX_NUM_OF_PARKING_SPOTS) {
                cout << "Invalid number of parking slots." << endl;
                clear();
            } else {
                invalidNumOfSpots(noOfSpots);
                for (int i = 0; i < noOfSpots; i++) {
                    parkingSpots[i] = nullptr;
                }
                invalidNumOfPV(0);
                if (loadData()) {
                    mainMenu();
                } else {
                    cout << "Error in data file" << endl;
                    clear();
                }
            }
        } else {
            cout << "Error in data file" << endl;
            clear();
        }
    }

    int Parking::run() {
        int ret = 0;
        if (!isEmpty()) {
            bool endProgram;
            do {
                endProgram = false;
                parkingStatus();
                int menu = m_parkingMenu.run();
                switch (menu) {
                    case 1: {
                        parkVehicle();
                        break;
                    }
                    case 2: {
                        returnVehicle();
                        break;
                    }
                    case 3: {
                        listParkedVehicles();
                        break;
                    }
                    case 4: {
                        findVehicle();
                        break;
                    }
                    case 5: {
                        if (closeParking()) {
                            endProgram = true;
                        }
                        break;
                    }
                    case 6: {
                        if (exitParkingApp()) {
                            endProgram = true;
                            cout << "Exiting program!" << endl;
                        }
                        break;
                    }
                }
            } while (!endProgram);
            ret = 1;
        }
        return ret;
    }

    int Parking::returnNumOfSpots() {
        return numOfSpots;
    }

    int Parking::invalidNumOfSpots(int setNOS) {
        numOfSpots = -1;
        if (setNOS < 10 || setNOS > MAX_NUM_OF_PARKING_SPOTS) {
            cout << "Invalid number of spots" << endl;
        } else {
            numOfSpots = setNOS;
        }
        return numOfSpots;
    }

    int Parking::returnNumOfPV() {
        return numOfPV;
    }

    int Parking::invalidNumOfPV(int setPV) {
        numOfPV = setPV;
        return numOfPV;
    }

    void Parking::findVehicle() {
        string licenceplate;
        cout << "Vehicle Search" << endl;
        cout << "Enter License Plate Number: ";
        cin >> licenceplate;
        cout << endl;
        for (unsigned int i = 0; i < licenceplate.length(); i++) {
            licenceplate[i] = toupper(licenceplate[i]);
        }

        Vehicle *found = nullptr;
        for (int i = 0; i < numOfSpots; i++) {
            if (parkingSpots[i] == nullptr)
                continue;
            if (string(parkingSpots[i]->getLicensePlate()) == licenceplate) {
                found = parkingSpots[i];
                break;
            }
        }

        if (found != nullptr) {
            cout << "Vechicle found: " << endl;
            found->carOfMotor();
        } else {
            cout << "License plate " << licenceplate << " Not found" << endl;
        }
        cout << endl << "Press <ENTER> to continue...." << endl;
    }
}