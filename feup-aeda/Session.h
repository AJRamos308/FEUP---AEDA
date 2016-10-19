#include "User.h"
#include "Vehicle.h"
#include "Route.h"

class Session {
private:
	vector<User> users;
	vector<string> districts;
public:
	Session();
	void importUsers();
	void importDistricts();
};

