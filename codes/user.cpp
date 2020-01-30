#include "user.hpp"

using namespace std;

void User::change_role()
{
	if(role == Buyer)
		role = Seller;
	else	
		role = Buyer;
}
bool User::only_role_differ(User* user) const
{
	if(user->get_user_name() == user_name && user->get_surename() == surename && 
		user->get_phone_no() == phone && user->get_money() == money && 
		user->get_role()!= role && user->get_name() == name)
		return true;
	return false;

}
bool User::add_money(double increment)
{
	money+=increment;
}

