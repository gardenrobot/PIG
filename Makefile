all:
	cd src; make
	mv src/main .

debug:
	cd src; make debug
	mv src/main .

clean:
	cd src; make clean

realclean: clean
	-/bin/rm -rf main 
