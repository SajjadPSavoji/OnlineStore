#ifndef VIRGOOD_H
#define VIRGOOD_H

#include <iostream>
#include <string>

#include "good.hpp"
#define GOOD_DELIMITER " | "
class VirtualGood
{
public:
	VirtualGood(std::string a_seller_username , std::string a_name , double a_price, int a_count) : 
		seller_username(a_seller_username) , name(a_name) , price(a_price) , count(a_count) {}

	VirtualGood(std::string a_name , int a_count,std::string a_seller_username): 
		seller_username(a_seller_username) , name(a_name) , count(a_count) {}

	VirtualGood(Good* good , int good_count , double shop_budget):seller_username(good->get_seller_username()),name(good->get_name()),
		 price(good->customer_cost(shop_budget)), count(good_count){} 
	std::string get_seller_username(){return seller_username;}
	std::string get_name(){return name;}
	int get_price(){return price;}
	int get_count(){return count;} 
	std::string print_vir_good_request_mode();
	friend std::ostream& operator<<(std::ostream& out , VirtualGood* vir_good);
	friend std::ostream& operator<<(std::ostream& out , std::vector<VirtualGood*> vir_goods);
private:
	std::string seller_username, name;
	int count;
	double price;	

};
std::ostream& operator<< (std::ostream& out , VirtualGood* vir_good);
std::ostream& operator<< (std::ostream& out , std::vector<VirtualGood*> vir_goods);
#endif