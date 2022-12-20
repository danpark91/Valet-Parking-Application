#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include <iostream>
#include "Menu.h"
namespace sdds {
	void Menu::clear() {
		delete[] m_title;
		if (m_number != 0) {
			for (int i = 0; i < m_number; i++) {
				delete m_menuItems[i];
			}
		}
	}
	void Menu::emptyState() {
		m_title = nullptr;
		m_number = 0;
		m_indentation = 0;
	}
	MenuItem::MenuItem(const char* content) {
		if (content != nullptr && content[0] != '\0') {
			m_content = new char[strlen(content) + 1];
			strcpy(m_content, content);
		}
		else {
			m_content = nullptr;
		}
	}
	MenuItem::~MenuItem() {
		delete[] m_content;
	}
	MenuItem::operator bool() const {
		return m_content != nullptr;
	}
	Menu::Menu(const char* title, int indentation) {
		emptyState();
		if (title != nullptr && title[0] != '\0') {
			m_title = new char[strlen(title) + 1];
			strcpy(m_title, title);
			m_indentation = indentation;
		}
	}
	Menu::Menu(const Menu& menu) {
		emptyState();
		*this = menu;
	}
	Menu::~Menu() {
		delete[] m_title;
		for (int i = 0; i < m_number; i++) {
			delete m_menuItems[i];
		}
	}
	Menu::operator bool() const {
		return m_title != nullptr;
	}
	bool Menu::isEmpty() const {
		return !*this;
	}
	void Menu::display() const {
		if (isEmpty()) {
			cout << "Invalid Menu!" << endl;
		}
		else {
			int size = m_indentation * 4;
			cout << setw(size) << "" << m_title << endl;
			if (m_number == 0) {
				cout << "No Items to display!" << endl;
			}
			else {
				for (int i = 0; i < m_number; i++) {
					cout << setw(size) << "" << i + 1 << "- " << *m_menuItems[i];
				}
				cout << setw(size) << "" << "> ";
			}
		}
	}
	void Menu::add(const char* content) {
		if (content == nullptr || content[0] == '\0') {
			clear();
			emptyState();
		}
		if (!isEmpty()) {
			if (m_number < MAX_NO_OF_ITEMS) {
				m_menuItems[m_number] = new MenuItem(content);
				m_number++;
			}
		}
	}
	int Menu::run() const {
		int selection;
		bool option = false;
		display();
		if (m_number != 0) {
			do {
				cin >> selection;
				if (!cin.good()) {
					cin.clear();
					cin.ignore(2000, '\n');
					cout << "Invalid Integer, try again: ";
				}
				else if (selection < 1 || selection > m_number) {
					cout << "Invalid selection, try again: ";
				}
				else {
					option = true;
					cin.ignore();
				}
			} while (!option);
		}
		else {
			selection = 0;
		}
		return selection;
	}
	Menu::operator int() const {
		return run();
	}
	Menu& Menu::operator=(const Menu& menu) {
		if (this != &menu) {
			if (menu) {
				delete[] m_title;
				m_title = new char[strlen(menu.m_title) + 1];
				strcpy(m_title, menu.m_title);
				m_indentation = menu.m_indentation;
				for (int i = 0; i < m_number; i++) {
					delete m_menuItems[i];
				}
				m_number = menu.m_number;
				for (int i = 0; i < m_number; i++) {
					m_menuItems[i] = new MenuItem(menu.m_menuItems[i]->m_content);
				}
			}
			else {
				clear();
				emptyState();
			}
		}
		return *this;
	}
	Menu& Menu::operator=(const char* title) {
		delete[] m_title;
		m_title = new char[strlen(title) + 1];
		strcpy(m_title, title);
		return *this;
	}
	Menu& Menu::operator<<(const char* content) {
		add(content);
		return *this;
	}
	ostream& operator<<(ostream& ost, const MenuItem& menuItem) {
		ost << menuItem.m_content << endl;
		return ost;
	}
}
