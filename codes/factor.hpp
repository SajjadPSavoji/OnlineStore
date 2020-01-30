#ifndef FACTOR_H
#define FACTOR_H
#include <iostream>
#include <vector>
#include <algorithm>

#include "user.hpp"
#include "virtualgood.hpp"

#define TAX_COEFFICIENT 1.05
#define GOODS_SUM "Goods Sum" 
#define TOTAL_SUM "Total Sum"
#define SPACE " "
#define DOT "."
#define FACTOR_NUMBER "Factor numbe"
#define FACTOR_GOODS_HEADER "#. Goods Name  | Goods Count | Goods Price | Seller Username | Sum (count * price "

class Factor
{
public:
	Factor(User* a_user , std::vector<VirtualGood*> & some_goods ,int a_number): buyer(a_user) ,
		goods(some_goods) ,number(a_number){}
	double goods_price();
	void sort_goods();
	friend std::ostream& operator<<(std::ostream &out ,  Factor* factor);
private:
	User* buyer;
	std::vector<VirtualGood*> goods;
	int number;
};

std::ostream& operator<<(std::ostream &out ,Factor* factor);
bool comp_virtual_goods_by_name_count_price_username(VirtualGood* vir_good1 , VirtualGood* vir_good2);
#endif