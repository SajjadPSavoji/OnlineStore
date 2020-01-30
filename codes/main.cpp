
#include "shop.hpp"

using namespace std;


void command_split(string command_line , vector<string> &command_splited)
{
	string delimiter=" ";
	size_t pos = 0;
	string token;

	while ((pos = command_line.find(delimiter)) != std::string::npos) {
	    token = command_line.substr(0, pos);
	    command_splited.push_back(token);
	    command_line.erase(0, pos + delimiter.length());
	}
	command_splited.push_back(command_line);
}
void get_alike_commands(vector<string> &command_splited)
{
	string command_line;
	while((command_splited.back()).back() != BUY_END )
	{
		(command_splited.back()).erase((command_splited.back()).end()-1);
		getline(cin ,command_line);
		command_split(command_line , command_splited);
	}
	(command_splited.back()).erase((command_splited.back()).end()-1);
}
bool is_command_valid(const vector<string> &command_splited)
{
	if( command_splited[0] == ADD_USER 
		|| command_splited[0] == ADD_GOODS 
		|| command_splited[0] == SEARCH 
		|| command_splited[0] == BUY 
		|| command_splited[0] == SALE 
		|| command_splited[0] == ADD_SPECIAL 
		|| command_splited[0] == REMOVE_SPECIAL 
		|| command_splited[0] == SEARCH_SALE 
		|| command_splited[0] == SEARCH_BESTSELLER 
		|| command_splited[0] == ADD_MONEY 
		|| command_splited[0] == REQUEST 
		|| command_splited[0] == PRINT_REQUESTS 
	)
		return true;
	return false;
}
User* make_new_user(const vector<string> &command_splited)
{
	User* new_user = new User(command_splited[1], command_splited[2], command_splited[3]
		, command_splited[4] ,str_to_double(command_splited[5]), str_to_role(command_splited[6]));
	return new_user;
}
Good* make_new_good(const vector<string> &command_splited)
{
	User* new_user = new User(command_splited[1]);
	Good* new_good = new Good(new_user , command_splited[2], 
		str_to_double(command_splited[3]), str_to_int(command_splited[4]));
	return new_good;
}
void execute_command(vector<string> &command_splited , Shop &shop)
{
	if(command_splited[0] == ADD_USER)
	{
		
		User* new_user = make_new_user(command_splited);
		shop.add_user(new_user);
	}
	else if(command_splited[0] == ADD_GOODS )
	{
		Good* new_good = make_new_good(command_splited);
		shop.add_good(new_good);
	}
	else if(command_splited[0] == SEARCH )
	{
		shop.search_goods(command_splited[1], str_to_int(command_splited[2]));
	}
	else if(command_splited[0] == BUY )
	{
		get_alike_commands(command_splited);
		if(shop.buy_all(command_splited))
		{
			command_ok();
		}
		else
			command_failed();
	}
	else if(command_splited[0] == SALE )
	{
		shop.sale_request( command_splited[1] , command_splited[2] ,command_splited[3]);
	}
	else if(command_splited[0] == ADD_SPECIAL )
	{
		shop.change_special(command_splited[1], command_splited[2],
			str_to_int(command_splited[3]), ADD);
	}
	else if(command_splited[0] == REMOVE_SPECIAL )
	{
		shop.change_special(command_splited[1], command_splited[2],
			str_to_int(command_splited[3]), REMOVE);
	}
	else if(command_splited[0] == SEARCH_SALE )
	{
		shop.search_sale();
	}
	else if(command_splited[0] == SEARCH_BESTSELLER )
	{
		shop.search_best_seller();
	}
	else if(command_splited[0] == ADD_MONEY )
	{
		 shop.add_money_to_user(command_splited[1] , str_to_double(command_splited[2]));
	}
	else if(command_splited[0] == REQUEST )
	{
		get_alike_commands(command_splited);
		shop.add_request(command_splited);
	}
	else if(command_splited[0] == PRINT_REQUESTS )
	{
		shop.print_request(command_splited[1]);
	}
}
int main(int argc, char const *argv[])
{
	Shop shop;
	shop.add_budget(INITIAL_BUDGET);
	string command_line;
	vector<string> command_splited;
	while(getline(cin, command_line))
	{
		command_splited.clear();
		command_split(command_line , command_splited);
		if(is_command_valid(command_splited))
		{
			execute_command(command_splited , shop);
		}
		else
		{
			command_failed();
		}
	}
	return 0;
}