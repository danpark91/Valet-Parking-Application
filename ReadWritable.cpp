#include <iostream>
#include <fstream>
#include "ReadWritable.h"
namespace sdds {
	ReadWritable::ReadWritable() {
		m_flag = false;
	}
	ReadWritable::~ReadWritable() {
	}
	bool ReadWritable::isCsv() const {
		return m_flag;
	}
	void ReadWritable::setCsv(bool value) {
		m_flag = value;
	}
	istream& operator>>(istream& istr, ReadWritable& ReadWritable) {
		return ReadWritable.read(istr);
	}
	ostream& operator<<(ostream& ostr, const ReadWritable& ReadWritable) {
		return ReadWritable.write(ostr);
	}
}
