GCC := g++ -std=c++11 -g

all: ppm_image

ppm_image: ppm_menu.o image_menu.o PPM.o
	$(GCC) ppm_menu.o image_menu.o PPM.o -o ppm_image

ppm_menu.o: ppm_menu.cpp
	$(GCC) -c ppm_menu.cpp

image_menu.o: image_menu.cpp
	$(GCC) -c image_menu.cpp

PPM.o: PPM.cpp
	$(GCC) -c PPM.cpp

clean:
	rm ppm_menu.o image_menu.o PPM.o
