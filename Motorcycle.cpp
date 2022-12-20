#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include "Motorcycle.h"

namespace sdds {
    bool Motorcycle::invalid(istream& istream) {
        bool status;
        char yn;
        do {
            status = false;
            istream >> yn;
            if (istream.fail()) {
                istream.clear();
                istream.ignore(1000, '\n');
                status = true;
            }
            if (!status && yn != 'Y' && yn != 'y' && yn != 'N' && yn !=
                'n') {
                status = true;
            }
            if (!status && istream.get() != '\n') {
                status = true;
                istream.ignore(1000, '\n');
            }
            if (status) {
                cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
            }
        } while (status);
        return yn == 'Y' || yn == 'y';
    }

    Motorcycle::Motorcycle() : Vehicle() {
        m_HasSidecarflag = false;
    }

    Motorcycle::Motorcycle(const char* Lisenceplate, const char* Makeandmodel)
        : Vehicle(Lisenceplate, Makeandmodel) {
        m_HasSidecarflag = false;
    }

    istream& Motorcycle::read(istream& istream) {
        if (isCsv()) {
            int i;
            Vehicle::read(istream);
            istream >> i;
            m_HasSidecarflag = i;
            istream.ignore(1000, '\n');
        }
        else {
            cout << endl;
            cout << "Motorcycle information entry" << endl;
            Vehicle::read(istream);
            cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
            m_HasSidecarflag = invalid(istream);
        }
        return istream;
    }

    ostream& Motorcycle::write(ostream& ostream) const {
        if (isEmpty()) {
            ostream << "Invalid Motorcycle Object" << endl;
        }
        else {
            if (isCsv()) {
                ostream << "M,";
            }
            else {
                ostream << "Vehicle type: Motorcycle" << endl;
            }
            Vehicle::write(ostream);
            if (isCsv()) {
                ostream << m_HasSidecarflag << endl;
            }
            else {
                if (m_HasSidecarflag) {
                    cout << "With Sidecar";
                    ostream << endl;
                }
            }
        }
        return ostream;
    }

    void Motorcycle::carOfMotor() {
        if (!isEmpty()) {
            cout << "Vehicle type: Motorcycle" << endl;
            cout << "Parking Spot Number: " << m_Parkingspotnumber << endl;
            cout << "License Plate: " << getLicensePlate() << endl;
            cout << "Make and Model: " << getMakeModel() << endl;
            if (m_HasSidecarflag) {
                cout << "With Sidecar" << endl;
            }
        }
        else {
            cout << "Invalid vehicle" << endl;
        }
    }
}
