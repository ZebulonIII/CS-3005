GCC := g++ -std=c++11
C := -c
O := -o

all: ppm_menu

ppm_menu: ppm_menu.o image_menu.o PPM.o NumberGrid.o JuliaSet.o
	$(GCC) $^ $(O) ppm_menu

ppm_menu.o: ppm_menu.cpp
	$(GCC) $(C) $<

image_menu.o: image_menu.cpp PPM.h NumberGrid.h
	$(GCC) $(C) $<

PPM.o: PPM.cpp
	$(GCC) $(C) $<

NumberGrid.o: NumberGrid.cpp PPM.h
	$(GCC) $(C) $<

JuliaSet.o: JuliaSet.cpp JuliaSet.h
	$(GCC) $(C) $<

clean:
	rm *.o ppm_menu
