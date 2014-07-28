all:
	cd src; make
	mv src/main .

mingw:
	cd src; make mingw
	mv src/main.exe .

debug:
	cd src; make debug
	mv src/main .

clean:
	cd src; make clean

realclean: clean
	-/bin/rm -rf main 
