#include "request.hpp"

#define RQ_HEADER "Request"
#define BUY_IN_REQ "buy"

using namespace std;
ostream& operator<< (ostream& out , Request* request)
{
	out<<request->name<<SPACE<<request->owner->get_user_name()<<endl;
	for (int i = 0; i < request->goods.size(); ++i)
	{
		out<<i+1<<DOT<<SPACE<<request->goods[i]->print_vir_good_request_mode()<<endl;
	}
	return out;
}
ostream& operator<< (ostream& out , vector<Request*> requests)
{
	for (int i = 0; i < requests.size(); ++i)
	{
		out<<RQ_HEADER<<SPACE<<i+1<<SPACE;
		out<<requests[i];
	}
	return out;
}
void Request::get_splitted(vector<string> &req_splitted)
{
		req_splitted.push_back(BUY_IN_REQ);
		req_splitted.push_back(owner->get_user_name());
		for (int i = 0; i < goods.size(); ++i)
		{
			req_splitted.push_back(goods[i]->get_name());
			req_splitted.push_back(to_string(goods[i]->get_count()));
			req_splitted.push_back(goods[i]->get_seller_username());
		}
}