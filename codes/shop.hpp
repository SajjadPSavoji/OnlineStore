#ifndef SHOP_HEADER
#define SHOP_HEADER

#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "user.hpp"
#include "good.hpp"
#include "factor.hpp"
#include "request.hpp"
#include "virtualgood.hpp"


#define USER_NOT_FOUND users.size()
#define GOOD_NOT_FOUND goods.size()
#define REQUEST_NOT_FOUND requests.size()
#define ADD "add"
#define REMOVE "remove"
#define BEST_SELLER_THRESHOLD 10.0
#define TAX_COEFFICIENT 1.05
#define BUY_END ';'
#define BUY_DELIMITER ','

#define ADD_USER "add_user"
#define ADD_GOODS "add_goods"
#define SEARCH "search"
#define BUY "buy"
#define SALE "sale"
#define ADD_SPECIAL "add_special"
#define REMOVE_SPECIAL "remove_special"
#define SEARCH_SALE "search_sale"
#define SEARCH_BESTSELLER "search_bestseller"
#define ADD_MONEY "add_money"
#define REQUEST "request"
#define PRINT_REQUESTS "print_request"

#define BUYER "buyer"
#define SELLER "seller"

#define INITIAL_BUDGET 1000000000000000.0
class Shop
{
public:
	void add_user(User* new_user);
	void add_good(Good* new_good);
	int search_username(std::string a_user_name);
	int search_good(std::string seller_username , std::string good_name);
	void search_goods(std::string good_name , int good_count);
	void sale_request(std::string demanding_username , std::string good_name ,
		 std::string seller_username);
	void change_special(std::string seller_username , std::string good_name , 
		int good_count, std::string command);
	void search_sale();
	void search_best_seller();
	void add_budget(double increment){budget+=increment;}
	int get_users_size(){return users.size();}
	void add_money_to_user(std::string user_name , double money);
	bool buy_good_from_user(std::string buyer_username , std::string good_name , 
		int good_count , std::string seller_username , std::vector<VirtualGood*> &virtual_goods);
	bool buy_all(std::vector<std::string> command_splitted);

	int search_request_name(std::string request_name);
	void add_request(std::vector<std::string> &command_splitted);
	void print_request(std::string buyer_username);
	void update_requests();
	bool update_request(Request* request);
private:
	std::vector<User*>    users;
	std::vector<Good*>    goods;
	std::vector<Factor*>  factors;
	std::vector<Request*> requests;
	double budget;
};

void command_failed();
void command_ok();
double str_to_double(std::string double_str);
int str_to_int(std::string int_str);
Role str_to_role(std::string role_str);

#endif