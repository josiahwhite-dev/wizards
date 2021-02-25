output: main.o player.o enemy.o shop.o
	g++ main.o player.o enemy.o shop.o -o output

main.o: main.cpp
	g++ -c main.cpp

player.o: player.cpp player.h
	g++ -c player.cpp

enemy.o: enemy.cpp enemy.h
	g++ -c enemy.cpp

shop.o: shop.cpp shop.h
	g++ -c shop.cpp

clean: 
	rm *.o output 