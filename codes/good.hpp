#ifndef GOOD_HEADER
#define GOOD_HEADER  

#define SPACE " "
#define DOT "."
#define MANDETORY_OFFER_LIMIT 30
#define MANDETORY_OFFER_DEFAULT 0
#define SALE_REQUEST_THRESHOLD 10
#define SALE_REQUEST_DEFAULT 0
#define FINANCIAL_LOSS_COEFFICIENT +0.1 - (0.9)*(0.05) 


#include <iostream>
#include <vector>

#include "user.hpp"

class Good
{
public:
	Good(User* a_seller, std::string a_name , double a_price , int a_count) : 
		seller(a_seller) , name(a_name) , price(a_price) , count(a_count){}

	std::string get_seller_username() const {return seller->get_user_name();}
	std::string get_name() const {return name;}
	double get_price() const {return price;}
	int get_count() const {return count;} 
	void set_seller(User* user);
	User* get_seller() const {return seller;}
	int get_trades()const {return trades;}

	double customer_cost(double shop_budget) const;  
	double sale_cost()const{return price*0.9;}
	double total_costumer_cost(int good_count , double shop_budget) const 
		{return double(good_count)*customer_cost(shop_budget);}
	double total_seller_gain(int good_count) const;
	void remove_sold(int good_count);

	bool cross_check_request(User* demanding_user);

	bool add_special(int increment);
	bool remove_special(int decrement);

	int mandetory_offer_count(double shop_budget) const;
	int requested_offer_count(double shop_budget ) const;
	double financial_loss_of_mandetory_offer_per_good() const;
	int total_sale(double shop_budget) const;
private:
	std::string name;
	int  count;
	double price;
	User* seller;
	std::vector<User*> sale_requested_users;
	int special_count=0;
	int trades=0;
};
void print_good(std::ostream& out , const Good& good , int shop_budget);
void print_goods(std::ostream& out , const std::vector<Good*> goods , int shop_budget);

#endif