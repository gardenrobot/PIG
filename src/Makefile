#
# Created by gmakemake (Ubuntu Sep  7 2011) on Thu Jun 12 14:32:25 2014
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


CPP_FILES =	Battle.cpp Bind.cpp Burn.cpp Choice.cpp Confusion.cpp Effect.cpp EffectFactory.cpp Environment.cpp HumanPlayer.cpp MajorAffliction.cpp MinorAffliction.cpp Move.cpp MoveFactory.cpp Player.cpp Pokemon.cpp PokemonFactory.cpp PokemonSpecies.cpp Round.cpp Stat.cpp StringHelper.cpp Type.cpp main.cpp 
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	Battle.h Category.h Choice.h Debug.h Effect.h EffectFactory.h Environment.h HumanPlayer.h MajorAffliction.h MinorAffliction.h Move.h MoveFactory.h MoveSpecies.h Player.h Pokemon.h PokemonFactory.h PokemonSpecies.h Round.h Stat.h StringHelper.h Type.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	Battle.o Bind.o Burn.o Choice.o Confusion.o Effect.o EffectFactory.o Environment.o HumanPlayer.o MajorAffliction.o MinorAffliction.o Move.o MoveFactory.o Player.o Pokemon.o PokemonFactory.o Round.o Stat.o StringHelper.o Type.o 

#
# Main targets
#

all:	main 

main:	main.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o main main.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

Battle.o:	Battle.h Category.h Debug.h Move.h Pokemon.h Stat.h Type.h
Bind.o:	Battle.h Category.h MinorAffliction.h Move.h Pokemon.h Type.h
Burn.o:	MajorAffliction.h Pokemon.h Type.h
Choice.o:	Choice.h
Confusion.o:	Battle.h Category.h MinorAffliction.h Move.h MoveFactory.h Pokemon.h Type.h
Effect.o:   Effect.h Move.h
EffectFactory.o:    EffectFactory.h Effect.h
Environment.o:	Choice.h Environment.h Player.h Round.h
HumanPlayer.o:	Category.h Choice.h HumanPlayer.h MajorAffliction.h Move.h Player.h Pokemon.h StringHelper.h Type.h
MajorAffliction.o:	MajorAffliction.h
MinorAffliction.o:	MinorAffliction.h Pokemon.h Type.h
Move.o:	Category.h Move.h Type.h
MoveFactory.o:	Category.h Move.h MoveFactory.h MoveSpecies.h Type.h
Player.o:	Choice.h Debug.h MajorAffliction.h MinorAffliction.h Player.h Pokemon.h Type.h
Pokemon.o:	Category.h Debug.h MajorAffliction.h MinorAffliction.h Move.h MoveFactory.h Pokemon.h Stat.h Type.h
PokemonFactory.o:	Pokemon.h PokemonFactory.h Type.h PokemonSpecies.h
Round.o:	Battle.h Choice.h Debug.h Environment.h MinorAffliction.h Player.h Pokemon.h Round.h Stat.h Type.h
Stat.o:	Stat.h
StringHelper.o:	StringHelper.h
Type.o:	Type.h
main.o:	Choice.h Environment.h HumanPlayer.h MajorAffliction.h MinorAffliction.h MoveFactory.h Player.h Pokemon.h PokemonFactory.h Round.h Type.h

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
