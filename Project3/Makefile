GCC := g++ -std=c++11

all: ppm_image

ppm_image: ppm_menu.o image_menu.o PPM.o
	$(GCC) $^ -o ppm_image

ppm_menu.o: ppm_menu.cpp
	$(GCC) -c $<

image_menu.o: image_menu.cpp
	$(GCC) -c $<

PPM.o: PPM.cpp
	$(GCC) -c $<

clean:
	rm ppm_menu.o image_menu.o PPM.o
