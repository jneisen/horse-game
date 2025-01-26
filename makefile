default: horse.cpp 
	g++ horse.cpp -Iinclude -I ..\gendep\ft2\include\freetype2 -I ..\gendep ..\gendep\libglfw3.a -L ..\gendep\ft2\lib -lfreetype -lgdi32 -o horse
