#ifndef REQ_HEADER
#define REQ_HEADER

#include <iostream>
#include <vector>

#include "user.hpp"
#include "virtualgood.hpp" 

class Request
{
public:
	Request(std::string request_name,User* a_user , std::vector<VirtualGood*> & some_goods): 
		owner(a_user) , goods(some_goods),name(request_name){}

	Request(std::string request_name,User* a_user ): owner(a_user) ,name(request_name){}
	void add_good(VirtualGood* new_good){goods.push_back(new_good);}
	User* get_owner(){return owner;}
	std::string get_name() const {return name;}
	void get_splitted(std::vector<std::string> &req_splitted);
	friend std::ostream& operator<< (std::ostream& out , Request* request);
	friend std::ostream& operator<< (std::ostream& out , std::vector<Request*> requests);
private:
	std::string name;
	User* owner;
	std::vector<VirtualGood*> goods;
};
std::ostream& operator<< (std::ostream& out , Request* request);
std::ostream& operator<< (std::ostream& out , std::vector<Request*> requests);
#endif