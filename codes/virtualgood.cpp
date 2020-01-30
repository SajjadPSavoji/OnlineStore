#include "virtualgood.hpp"

using namespace std;
ostream& operator<<(ostream& out , VirtualGood* vir_good)
{
	out<<vir_good->name << GOOD_DELIMITER << vir_good->count << GOOD_DELIMITER
	   <<vir_good->price << GOOD_DELIMITER << vir_good->seller_username << GOOD_DELIMITER
	   <<vir_good->price*double(vir_good->count);
	return out;
}
ostream& operator<<(ostream& out , vector<VirtualGood*> vir_goods)
{
	for (int i = 0; i < vir_goods.size(); ++i)
	{
		out<<i+1<<DOT<<SPACE<<vir_goods[i]<<endl;
	}
}
string VirtualGood::print_vir_good_request_mode(){
	return name+SPACE+to_string(count)+SPACE+seller_username;
}