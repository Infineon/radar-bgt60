CPPFLAGS = -DBGT60_FRAMEWORK=BGT60_FRMWK_RPI

lib:
	mkdir -p ../../../build
	g++ -c $(CPPFLAGS) -o ../../../build/bgt60.o ../../corelib/bgt60.cpp
	g++ -c $(CPPFLAGS) -o ../../../build/bgt60-pal-gpio-rpi.o pal/bgt60-pal-gpio-rpi.cpp

clean:
	rm -f ../../../build/*