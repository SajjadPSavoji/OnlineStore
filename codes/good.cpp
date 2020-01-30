#include "good.hpp"

using namespace std;

void print_good(ostream& out , const Good& good , int shop_budget)
{
	if(good.total_sale(shop_budget) > 0)
		out<<good.get_name()<<SPACE<<good.total_sale(shop_budget)<<SPACE<<good.sale_cost()
	   		<<SPACE<<good.get_seller_username();
	else
		out<<good.get_name()<<SPACE<<good.get_count()<<SPACE<<good.get_price()
	   		<<SPACE<<good.get_seller_username();
}
void print_goods(ostream& out , const vector<Good*> goods , int shop_budget)
{
	for (int i = 0; i < goods.size(); ++i)
	{
		cout<<i+1<<DOT<<SPACE;
		print_good(out, *(goods[i]), shop_budget);
		out<<endl;
	}
}
void Good::set_seller(User* user)
{
	delete seller;
	seller = user;
}
bool Good::cross_check_request(User* demanding_user)
{
	for (int i = 0; i < sale_requested_users.size(); ++i)
	{
		if(demanding_user->get_user_name() == sale_requested_users[i]->get_user_name())
			return false;
	}
	sale_requested_users.push_back(demanding_user);
	return true;
}
bool Good::add_special(int increment)
{
	if(special_count + increment <= count)
	{
		special_count+=increment;
		return true;
	}
	return false;

}
bool Good::remove_special(int decrement)
{
	if(special_count - decrement >=0)
	{
		special_count-=decrement;
		return true;
	}
	return false;
}
double Good::financial_loss_of_mandetory_offer_per_good() const
{
	double(price)* FINANCIAL_LOSS_COEFFICIENT;
}
int Good::mandetory_offer_count(double shop_budget) const
{
	if(count > MANDETORY_OFFER_LIMIT && 
		count*financial_loss_of_mandetory_offer_per_good() < shop_budget)
		return count - MANDETORY_OFFER_LIMIT;
	return MANDETORY_OFFER_DEFAULT;
}
int Good::requested_offer_count(double budget )const
{
	if(sale_requested_users.size() > SALE_REQUEST_THRESHOLD &&
		count*financial_loss_of_mandetory_offer_per_good() < budget )
		return count;
	return SALE_REQUEST_DEFAULT;
}
int Good::total_sale(double shop_budget) const
{
	if ((special_count+ mandetory_offer_count(shop_budget) +requested_offer_count(shop_budget)) > count)
		return count;
	return (special_count+ mandetory_offer_count(shop_budget) +requested_offer_count(shop_budget)) ;
}
double Good::customer_cost(double shop_budget) const
{
	if(total_sale(shop_budget)>0)
		return sale_cost();
	return price;
}  
double Good::total_seller_gain(int good_count) const
{
	if(special_count != 0)
	{
		if(special_count >= good_count)
			return good_count*sale_cost();
		else
		{
			return special_count*sale_cost() +(good_count - special_count)*price;
		}
	}
	else
		return good_count * price;
}
void Good::remove_sold(int good_count)
{
	count -= good_count;
	if(special_count>0)
	{
		special_count -=good_count;
		if(special_count < 0)
			special_count=0;
	}
}

