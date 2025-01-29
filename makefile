default: horse.cpp 
	g++ horse.cpp -Iinclude -I..\gendep ..\gendep\libglfw3.a -lgdi32 -o horse
