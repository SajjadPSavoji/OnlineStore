#include "shop.hpp"

using namespace std;
Role str_to_role(string role_str)
{
	if(role_str == BUYER)
		return Buyer;
	else if(role_str == SELLER)
		return Seller;
	else 
		return Invalid;
}
int str_to_int(string int_str)
{
	stringstream mystream (int_str);
	int int_out;
	mystream>>int_out;
	return int_out;
}
double str_to_double(string double_str)
{
	stringstream mystream (double_str);
	double double_out;
	mystream>>double_out;
	return double_out;
}
void command_failed()
{
	cout<<"Commmand Failed"<<endl;
}
void command_ok()
{
	cout<<"Command OK"<<endl;
}
int Shop::search_username(std::string a_user_name)
{
	for (int i = 0; i < users.size(); ++i)
	{
		if(users[i]->get_user_name() == a_user_name)
			return i;
	}
	return users.size();
}
void Shop:: add_user(User* new_user)
{
	int user_index=search_username(new_user->get_user_name());
	if(new_user->get_role() == Invalid)
	{
		command_failed();
		delete new_user;
	}
	else if(user_index == USER_NOT_FOUND )
	{
		users.push_back(new_user);
		command_ok();
	}
	else if(users[user_index]->only_role_differ(new_user))
	{
		users[user_index]->change_role();
		command_ok();
	}
	else
	{	
		command_failed();
		delete new_user;
	}
}
void Shop::update_requests()
{
	for (int i = 0; i < requests.size(); ++i)
	{
		if(update_request(requests[i]))
		{
			requests.erase(requests.begin() + i);
			i-=1;
		}
	}
}
bool Shop::update_request(Request* request)
{
	vector<string> req_splitted;
	request->get_splitted(req_splitted);

	/*for (int i = 0; i < req_splitted.size(); ++i)
	{
		cerr<<req_splitted[i]<<" ";
	}
	cerr<<endl;*/

	if(buy_all(req_splitted))
	{
		delete request;
		return true;
	}
	else
		return false;
}
void Shop::add_good(Good* new_good) 
{
	int user_index=search_username(new_good->get_seller_username());
	if ( (user_index== USER_NOT_FOUND) 
		 || (users[user_index]-> get_role() != Seller ))
	{
		delete new_good->get_seller();
		delete new_good;
		command_failed();
	}
	else
	{
		new_good->set_seller(users[user_index]);
		goods.push_back(new_good);
		command_ok();
		update_requests();
	}
}
bool compare_goods_by_name_count_price_owner(Good* first_good , Good* second_good)
{
	return first_good->get_seller_username() < second_good->get_seller_username() 
		||first_good->get_count() < second_good->get_count() ||
		first_good->get_price() < second_good->get_price() ||
		first_good->get_seller_username() < second_good->get_seller_username();	
}
bool compare_goods_by_count_price_owner(Good* first_good , Good* second_good)
{
	return first_good->get_count() < second_good->get_count() ||
		first_good->get_price() < second_good->get_price() ||
		first_good->get_seller_username() < second_good->get_seller_username(); 
}
void sort_goods_by_count_price_owner(vector<Good*> &match_goods)
{
	sort(match_goods.begin(), match_goods.end(),compare_goods_by_count_price_owner);
}
void sort_goods_by_name_count_price_owner(vector<Good*> &match_goods)
{
	sort(match_goods.begin(), match_goods.end(),compare_goods_by_name_count_price_owner);
}
int Shop::search_good(string seller_username , string good_name)
{
	for (int i = 0; i < goods.size(); ++i)
	{
		if(goods[i]-> get_seller_username()== seller_username && 
			goods[i]-> get_name()== good_name)
			return i;
	}
	return goods.size();
}

void Shop::sale_request(string demanding_username , string good_name ,string seller_username)
{
	int req_user_index=search_username(demanding_username);
	int good_index = search_good(seller_username , good_name);

	if(req_user_index == USER_NOT_FOUND ||
		(users[req_user_index]->get_role() == Seller) || good_index == GOOD_NOT_FOUND )
	{
		command_failed();
		return;
	}
	if (goods[good_index]->cross_check_request(users[req_user_index]))
	{
		command_ok();
		return;
	}
	cerr<<"here2"<<endl;
	command_failed();
}
void Shop::change_special(string seller_username , string good_name , int good_count , string command)
{
	int good_index=search_good(seller_username , good_name);
	if(good_index == GOOD_NOT_FOUND)
	{
		command_failed();
		return;
	}
	if(command == ADD)
	{
		if(goods[good_index]->add_special(good_count))
		{
			command_ok();
			return;
		}
		command_failed();
	}
	else if(command == REMOVE)
	{
		if(goods[good_index]->remove_special(good_count))
		{
			command_ok();
			return ;
		}
		command_failed();
	}
}


void Shop::search_goods(std::string good_name , int good_count)
{
	vector<Good*> match_goods;
	for (int i = 0; i < goods.size(); ++i)
	{
		if(goods[i]->get_name() == good_name && goods[i]->get_count() >= good_count)
			match_goods.push_back(goods[i]);
	}
	sort_goods_by_count_price_owner(match_goods);
	print_goods(cout , match_goods ,budget);
}
void Shop::search_sale()
{
	vector<Good*> sale_goods;
	for (int i = 0; i < goods.size(); ++i)
	{
		if(goods[i]->total_sale(budget) > 0)
			sale_goods.push_back(goods[i]);
	}
	sort_goods_by_name_count_price_owner(sale_goods);
	print_goods(cout , sale_goods ,budget);
}
void Shop::search_best_seller()
{
	vector<Good*> best_seller_goods;
	for (int i = 0; i < goods.size(); ++i)
	{
		if(goods[i]->get_trades() > BEST_SELLER_THRESHOLD)
			best_seller_goods.push_back(goods[i]);
	}
	sort_goods_by_name_count_price_owner(best_seller_goods);
	print_goods(cout , best_seller_goods ,budget);
}
void Shop::add_money_to_user(string user_name , double money)
{
	int user_index= search_username(user_name);
	if(user_index == USER_NOT_FOUND)
		command_failed();
	else
	{
		users[user_index]->add_money(money);
	}
}
bool Shop::buy_good_from_user(std::string buyer_username , std::string good_name , 
		int good_count , std::string seller_username , std::vector<VirtualGood*> &virtual_goods)
{
	int buyer_index= search_username(buyer_username);
	int seller_index= search_username(seller_username);
	int good_index = search_good(seller_username , good_name);

	if(buyer_index == USER_NOT_FOUND
		|| good_index == GOOD_NOT_FOUND
		|| goods[good_index]->get_count()< good_count
		|| !users[buyer_index]->can_effort(goods[good_index]->
			total_costumer_cost(good_count , budget)*TAX_COEFFICIENT)
	  )
	{
		return false;
		//command_failed();
	}
	else
	{
		int buyer_loss=goods[good_index]->total_costumer_cost(good_count , budget)*TAX_COEFFICIENT;
		int seller_gain=goods[good_index]->total_seller_gain(good_count);
		int shop_profit=buyer_loss - seller_gain;

		users[buyer_index]->charge(buyer_loss);
		users[seller_index]->add_money(seller_gain);
		add_budget(shop_profit);

		VirtualGood* new_vir_good= new VirtualGood(goods[good_index] , good_count , budget);
		virtual_goods.push_back(new_vir_good);

		goods[good_index]->remove_sold(good_count);
		if(goods[good_index]->get_count() == 0)
		{
			delete goods[good_index];
			goods.erase(goods.begin()+good_index);
		}
		return true;
		//command_ok();
	}
}
bool Shop::buy_all(std::vector<std::string> command_splitted)
{
	string buyer_username = command_splitted[1];
	vector<VirtualGood*> virtual_goods;

	for (int i = 2; i<command_splitted.size(); i+=3)
	{
		buy_good_from_user(buyer_username ,command_splitted[i], 
		 str_to_int(command_splitted[i+1]), command_splitted[i+2], virtual_goods);

	}
	if(virtual_goods.size()>0)
	{
		Factor* new_factor= new Factor(users[search_username(buyer_username)] ,
			virtual_goods ,factors.size());
		new_factor->sort_goods();
		cout<<new_factor;
		factors.push_back(new_factor); 
		return true;
	}
	return false;
}
int Shop::search_request_name(std::string request_name)
{
	for (int i = 0; i < requests.size(); ++i)
	{
		if(requests[i]->get_name() == request_name)
			return i;
	}
	return requests.size();
}
void Shop::add_request(vector<string> &command_splitted)
{
	int buyer_index=search_username(command_splitted[2]);
	if(buyer_index == USER_NOT_FOUND
	   || search_request_name(command_splitted[1]) != REQUEST_NOT_FOUND
	   || users[buyer_index]->get_role() != Buyer
	  )
	{
		command_failed();
	}
	else
	{
		Request* new_request = new Request(command_splitted[1] , users[buyer_index]);

		for (int i = 3; i < command_splitted.size(); i+=3)
		{
			VirtualGood* new_good = new VirtualGood(command_splitted[i],str_to_int(command_splitted[i+1])
				,command_splitted[i+2]);
			new_request->add_good(new_good);
		}
		requests.push_back(new_request);
		command_ok();
		update_requests();
	}
}
void Shop::print_request(std::string buyer_username)
{
	vector<Request*> match_requests;
	for (int i = 0; i < requests.size(); ++i)
	{
		if(requests[i]->get_owner()->get_user_name() == buyer_username)
			match_requests.push_back(requests[i]);
	}
	cout<<match_requests;
}

