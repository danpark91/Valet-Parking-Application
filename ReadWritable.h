#ifndef SDDS_READWRITABLE_H
#define SDDS_READWRITABLE_H
#include <iostream>
#include <fstream>
using namespace std;
namespace sdds {
	class ReadWritable {
		bool m_flag;
	public:
		ReadWritable();
		virtual ~ReadWritable();
		bool isCsv()const;
		void setCsv(bool value);
		virtual istream& read(istream& istr) = 0;
		virtual ostream& write(ostream& ostr) const = 0;
	};
	istream& operator>>(istream& istr, ReadWritable& ReadWritable);
	ostream& operator<<(ostream& ostr, const ReadWritable& ReadWritable);
}
#endif
