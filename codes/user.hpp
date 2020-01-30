#ifndef USER_HEADER
#define USER_HEADER
#include <iostream>

enum Role
{
	Buyer,
	Seller,
	Invalid
};

class User
{
public:
	User (std::string a_name , std::string a_surename , std::string a_username ,std::string a_phone_number ,
		double a_money ,Role a_role): name(a_name) , surename(a_surename), user_name(a_username) , 
		phone(a_phone_number) ,money(a_money) , role(a_role){}

	User(std::string a_username):user_name(a_username){}

	std::string get_name() const {return name;}
	std::string get_surename() const {return surename;}
	std::string get_phone_no() const {return phone;}
	double get_money() const {return money;}
	Role get_role() const {return role;}
	std::string get_user_name() const {return user_name;}

	void change_role();
	bool only_role_differ (User* user) const ;
	bool add_money(double increment);
	bool can_effort(double charge){return money >= charge;}
	void charge(double charge){ money -= charge;}

private:
	std::string name , surename, user_name,
			phone;
	double money;
	Role role;
	
	
};

#endif