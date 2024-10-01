.PHONY: all clean

pis-oledui:
	make GCFK
	make oled
	make main
	make test

clean:
	rm -rf build/{bin,obj,lib}/*

GCFK:
	mkdir -p build/{obj,lib}
	gcc -c src/pis-oledui/GCFK.c -o build/obj/GCFK.o
	ar rcs build/lib/libGCFK.a build/obj/GCFK.o

oled:
	mkdir -p build/{obj,lib}
	gcc -c src/pis-oledui/oled.c -o build/obj/oled.o
	ar rcs build/lib/liboled.a build/obj/oled.o

main:
	mkdir -p build/bin
	g++ src/pis-oledui/main.cpp -lwiringPi -I include/pis-oledui -L build/lib -lGCFK -loled -o build/bin/main

test:
	mkdir -p build/bin
	g++ samples/test.cpp src/polonium/Page.cpp src/polonium/Element.cpp src/polonium/Elements/TextElements.cpp -o build/bin/test -loled -lGCFK -lwiringPi -L build/lib