
gamemake: main.cpp
	g++ -c main.cpp src/*
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	./sfml-app
clean:
	rm *.o src/*.gch sfml-app

