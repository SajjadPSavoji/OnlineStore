#include "factor.hpp"

using namespace std;
double Factor::goods_price()
{
	double sum=0.0;
	for (int i = 0; i < goods.size(); ++i)
	{
		sum+= goods[i]->get_price()* double(goods[i]->get_count());
	}
	return sum;
}
ostream& operator <<(ostream &out , Factor* factor)
{
	out<< FACTOR_NUMBER << SPACE << factor->number+1<<endl;

	out<< factor->buyer->get_name() << SPACE << factor->buyer->get_surename()
	   << SPACE << factor->buyer->get_user_name() 
	   << SPACE << factor->buyer->get_phone_no()<<endl;

	out<<FACTOR_GOODS_HEADER<<endl;
	out<<factor->goods;
	out<<GOODS_SUM<<SPACE<<factor->goods_price()<<endl;
	out<<TOTAL_SUM<<SPACE<<factor->goods_price()*TAX_COEFFICIENT<<endl;

	return out;
}
bool comp_virtual_goods_by_name_count_price_username(VirtualGood* vir_good1 , VirtualGood* vir_good2)
{
	if(vir_good1->get_name() < vir_good2->get_name()
	   ||vir_good1->get_count() < vir_good2->get_count()
	   ||vir_good1->get_price() < vir_good2->get_price() 
	   ||vir_good1->get_seller_username() < vir_good2->get_seller_username()
	  )
		return	true;
	else
		return false;
}
void Factor::sort_goods()
{
	sort(goods.begin() , goods.end(),comp_virtual_goods_by_name_count_price_username);
}