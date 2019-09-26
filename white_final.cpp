#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <map>
#include <exception>
#include <stdexcept>
#include <ctype.h>
#include <string>

using namespace std;

class Date {
public:	
	Date(int y, int m, int d) {
		year = y;
		month = m;
		day = d;
	}

	Date() {
		year = 0;
		month = 0;
		day = 0;
	}

	int Year() const{
		return year;
	}
	int Month() const{
		return month;
	}
	int Day() const{
		return day;
	}

private:
	int year;
	int month;
	int day;
};

bool operator<(const Date& l, const Date& r) {
	return l.Year()*365 + (l.Month()-1)*31 + l.Day() <
		   r.Year()*365 + (r.Month()-1)*31 + r.Day();
}


bool hasCorrectFormat(const string& s) {
	if (s[0] != '-' && !isdigit(s[0]) && s[0] != '+') { 
		return false;
	}
	for (int i = 1; i < s.size(); ++i) {
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}


istream& operator>>(istream& istr, Date& d) {
	int year, month, day, sign = 1;
	string s_year, s_month, s_day;

	string stream_string;
	istr >> stream_string;

	stringstream s(stream_string);

	stream_string = s.str();


	if (stream_string[0] == '-') {
		sign = -1;
		s.ignore(1);
	}

	getline(s, s_year, '-');
	if (!hasCorrectFormat(s_year)) {
		throw invalid_argument("Wrong date format: " + stream_string);
	}
	year = stoi(s_year) * sign;
	

	if (s.peek() == '-') {
		sign = -1;
		s.ignore(1);
	}
	else
		sign = 1;

	getline(s, s_month, '-');
	if (!hasCorrectFormat(s_month)) {
		throw invalid_argument("Wrong date format: " + stream_string);
	}
	month = stoi(s_month) * sign;


	if (s.peek() == '-') {
		sign = -1;
		s.ignore(1);
	}
	else
		sign = 1;

	getline(s, s_day);
	if (!hasCorrectFormat(s_day)) {
		throw invalid_argument("Wrong date format: " + stream_string);
	}
	day = stoi(s_day)*sign;
	
	if (month < 1 || month > 12)
		throw invalid_argument("Month value is invalid: " + to_string(month));
	if (day < 1 || day > 31)
		throw invalid_argument("Day value is invalid: " + to_string(day));
	d = {year, month, day};

	return istr;
}

ostream& operator<<(ostream& s, const Date& d) {
	s << setw(4) << setfill('0') << d.Year() << "-" <<
	setw(2) << setfill('0') << d.Month() << "-" <<
	setw(2) << setfill('0') << d.Day();

	return s;
}

void printMap(const map<Date, set<string>>& m) {
	for (const auto& p : m) 
		for (const auto& ev : p.second)
			cout << p.first << " " << ev << endl;
}

void find(const map<Date, set<string>>& m, Date& d) {
	set<string> s;
	try {
		s = m.at(d);
		for (const auto i : s)
			cout << i << endl;
	}
	catch (exception& e) {
		
	}
}


void go() {
	map<Date, set<string>> events;
	
	try {
		string line;
		while (getline(cin, line)) {
			stringstream stream(line);
			string op, e;
			Date d;
			stream >> op;
			if (op == "Add") {
				stream >> d >> e;
				events[d].insert(e);
			}

			else if (op == "Del") {
				stream >> d;
				stream >> e;

				if (e == "") { //Del date
					cout << "Deleted " << events[d].size() << " events" << endl;
					events.erase(d);
				}
				else { // Del date event
					if (events[d].count(e) != 0) { 
						events[d].erase(e);
						cout << "Deleted successfully" << endl;
					}
					else {
						if (events[d].size() == 0)
							events.erase(d);
						cout << "Event not found" << endl;
					}
				}
			}

			else if (op == "Print") {
				printMap(events);
			}
			else if (op == "Find") {
				stream >> d;
				find(events, d);
			}
			else if (int(op[0]) != 0)
				cout << "Unknown command: " << op << endl;
		}
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
}

int main() {
	go();
	return 0;
}
