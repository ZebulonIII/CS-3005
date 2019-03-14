GCC := g++ -std=c++11
C := -c
O := -o

all: ppm_menu

ppm_menu: ppm_menu.o image_menu.o PPM.o NumberGrid.o ComplexFractal.o JuliaSet.o MandelbrotSet.o Color.o ColorTable.o
	$(GCC) $^ $(O) ppm_menu

ppm_menu.o: ppm_menu.cpp
	$(GCC) $(C) $<

image_menu.o: image_menu.cpp PPM.h NumberGrid.h JuliaSet.h MandelbrotSet.h ColorTable.h Color.h
	$(GCC) $(C) $<

PPM.o: PPM.cpp
	$(GCC) $(C) $<

NumberGrid.o: NumberGrid.cpp PPM.h
	$(GCC) $(C) $<

ComplexFractal.o: ComplexFractal.cpp NumberGrid.h
	$(GCC) $(C) $<

JuliaSet.o: JuliaSet.cpp ComplexFractal.h
	$(GCC) $(C) $<

MandelbrotSet.o: MandelbrotSet.cpp ComplexFractal.h
	$(GCC) $(C) $<

Color.o: Color.cpp
	$(GCC) $(C) $<

ColorTable.o: ColorTable.cpp
	$(GCC) $(C) $<

clean:
	rm *.o ppm_menu
