#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Route {
private:
	float price;
	vector<string> stops;
	string username;
public:
	Route(string username);
	void addStops(string stop);
};