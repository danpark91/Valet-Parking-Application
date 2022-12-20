#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;
namespace sdds {
	const int MAX_NO_OF_ITEMS = 10;
	class MenuItem {
		char* m_content{};
		MenuItem(const char* content);
		MenuItem(const MenuItem& menuItem) = delete;
		MenuItem& operator=(const MenuItem& menuItem) = delete;
		~MenuItem();
		explicit operator bool() const;
		friend ostream& operator<<(ostream& ost, const MenuItem& menuItem);
		friend class Menu;
	};
	class Menu {
		void clear();
		void emptyState();
		char* m_title{};
		int m_number{};
		int m_indentation{};
		MenuItem* m_menuItems[MAX_NO_OF_ITEMS]{};
	public:
		explicit Menu(const char* title, int indentation = 0);
		Menu(const Menu& menu);
		~Menu();
		explicit operator bool() const;
		bool isEmpty() const;
		void display() const;
		void add(const char* content);
		int run() const;
		operator int() const;
		Menu& operator=(const Menu& menu);
		Menu& operator=(const char* title);
		Menu& operator<<(const char* content);
	};
	ostream& operator<<(ostream& ost, const MenuItem& menuItem);
}
#endif