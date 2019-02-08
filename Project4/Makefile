GCC := g++ -std=c++11
C := -c
O := -o

all: ppm_menu

ppm_menu: ppm_menu.o image_menu.o PPM.o
	$(GCC) $^ $(O) ppm_image

ppm_menu.o: ppm_menu.cpp
	$(GCC) $(C) $<

image_menu.o: image_menu.cpp
	$(GCC) $(C) $<

PPM.o: PPM.cpp
	$(GCC) $(C) $<

clean:
	rm *.o ppm_menu
