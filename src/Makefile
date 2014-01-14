#
# Created by gmakemake (Ubuntu Sep  7 2011) on Thu Mar 14 01:17:27 2013
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =	-ggdb
CFLAGS =	-ggdb
CLIBFLAGS =	-lm
CCLIBFLAGS =	
########## End of default flags


CPP_FILES =	Battle.cpp Burn.cpp Choice.cpp Confusion.cpp Environment.cpp HumanPlayer.cpp main.cpp MajorAffliction.cpp MinorAffliction.cpp Move.cpp Player.cpp Pokemon.cpp Round.cpp Stat.cpp StringHelper.cpp Type.cpp Bind.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	Battle.h Category.h Choice.h Debug.h Environment.h HumanPlayer.h MajorAffliction.h MinorAffliction.h Move.h Player.h Pokemon.h Round.h Stat.h StringHelper.h Type.h PokemonFactory.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	Battle.o Burn.o Choice.o Confusion.o Environment.o HumanPlayer.o main.o MajorAffliction.o MinorAffliction.o Move.o Player.o Pokemon.o Round.o Stat.o StringHelper.o Type.o Bind.o PokemonFactory.o

#
# Main targets
#

all:	main 

main:	$(OBJFILES)
	$(CXX) $(CXXFLAGS) -o main $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

Battle.o:	Battle.h Category.h Debug.h Move.h Pokemon.h Stat.h Type.h
Bind.o:     Move.h
Burn.o:		Move.h
Choice.o:	Choice.h
Confusion.o:	MinorAffliction.h Pokemon.h Type.h
Environment.o:	Choice.h Environment.h Player.h Round.h
HumanPlayer.o:	Choice.h HumanPlayer.h Player.h StringHelper.h
MajorAffliction.o:	MajorAffliction.h
MinorAffliction.o:	MinorAffliction.h Pokemon.h Type.h
Move.o:	Category.h Move.h Type.h
Player.o:	Choice.h Player.h Pokemon.h Type.h
Poison.o:	MajorAffliction.h Pokemon.h Type.h
Pokemon.o:	Category.h MajorAffliction.h MinorAffliction.h Move.h Pokemon.h Stat.h Type.h
Round.o:	Battle.h Choice.h Debug.h Environment.h Player.h Pokemon.h Round.h Stat.h Type.h
Stat.o:	Stat.h
StringHelper.o:	StringHelper.h
Type.o:	Type.h
PokemonFactory.o: PokemonFactory.h
main.o:	Choice.h Debug.h Environment.h HumanPlayer.h Move.h Player.h Pokemon.h Round.h Type.h PokemonFactory.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) main.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf main 

debug:
	make CXXFLAGS=-DDEBUG_MODE
