
all: ca2.o 
ca2.o :  user.o good.o virtualgood.o factor.o request.o shop.o main.o
	g++ user.o good.o virtualgood.o factor.o request.o shop.o main.o -o ca2.o
main.o : main.cpp 
	g++ -c  main.cpp  
user.o : user.cpp user.hpp 
	g++ -c user.cpp user.hpp 
good.o : good.cpp good.hpp 
	g++ -c good.cpp  good.hpp 
virtualgood.o: virtualgood.cpp virtualgood.hpp 
	g++ -c virtualgood.cpp virtualgood.hpp 
factor.o:factor.cpp factor.hpp
	g++ -c factor.cpp factor.hpp
request.o:request.cpp request.hpp 
	g++ -c request.cpp request.hpp 
shop.o:shop.cpp shop.hpp 
	g++ -c shop.cpp shop.hpp 
clean:
	rm -r *.o
	rm -r *.gch