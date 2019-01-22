all: ppm_image

ppm_image: ppm_menu.o
	g++ -std=c++11 *.cpp -o ppm_image

ppm_menu.o: ppm_menu.cpp image_menu.o
	g++ -std=c++11 -c ppm_menu.cpp

image_menu.o: image_menu.cpp PPM.o
	g++ -std=c++11 -c image_menu.cpp

PPM.o: PPM.cpp
	g++ -std=c++11 -c PPM.cpp

clean:
	rm ppm_image ppm_menu.o image_menu.o PPM.o