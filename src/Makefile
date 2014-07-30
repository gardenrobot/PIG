#
# Created by gmakemake (Ubuntu Sep  7 2011) on Wed Jul 16 14:15:18 2014
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
CLIBFLAGS =	-lm -ljsoncpp -lboost_system -lboost_filesystem
CCLIBFLAGS =	-ljsoncpp -lboost_system -lboost_filesystem
MAINFILE = main
########## End of default flags

# Cross-compiling Linux-to-Mingw 
MINGWCXX = i586-mingw32msvc-g++
MINGMAINFILE = main.exe
MINGWINCLUDEFLAGS = -I/usr/local/win32/include
MINGWLIBFLAGS = -L/usr/local/win32/lib -ljson_mingw_libmt -lboost_filesystem-mt-s -lboost_system-mt-s


CPP_FILES =	Battle.cpp Burn.cpp Confusion.cpp Effect.cpp EffectFactory.cpp Environment.cpp Flinch.cpp Gender.cpp HumanPlayer.cpp Infatuation.cpp MajorAffliction.cpp MinorAffliction.cpp Move.cpp MoveFactory.cpp PartialTrap.cpp Player.cpp Pokemon.cpp PokemonFactory.cpp Round.cpp Seeding.cpp Stat.cpp StringHelper.cpp Type.cpp main.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	Battle.h Category.h Choice.h Debug.h Effect.h EffectFactory.h EffectId.h Environment.h Gender.h HumanPlayer.h MajorAffliction.h MinorAffliction.h Move.h MoveFactory.h MoveSpecies.h Player.h Pokemon.h PokemonFactory.h PokemonSpecies.h Round.h Stat.h StringHelper.h Type.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	Battle.o Burn.o Confusion.o Effect.o EffectFactory.o Environment.o Flinch.o Gender.o HumanPlayer.o Infatuation.o MajorAffliction.o MinorAffliction.o Move.o MoveFactory.o PartialTrap.o Player.o Pokemon.o PokemonFactory.o Round.o Seeding.o Stat.o StringHelper.o Type.o 

#
# Main targets
#

all:	main 

main:	main.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $(MAINFILE) main.o $(OBJFILES) $(CCLIBFLAGS)

debug:
	make CXXFLAGS="$(CXXFLAGS) -DDEBUG_MODE"

mingw:
	make CXX="$(MINGWCXX)" CCLIBFLAGS="$(MINGWLIBFLAGS)" CXXFLAGS="$(MINGWINCLUDEFLAGS)" MAINFILE="$(MINGMAINFILE)"

#
# Dependencies
#

Battle.o:	Battle.h Category.h Debug.h Gender.h Move.h Pokemon.h Stat.h Type.h
Burn.o:	Gender.h MajorAffliction.h Pokemon.h Type.h
Confusion.o:	Battle.h Category.h Gender.h MinorAffliction.h Move.h MoveFactory.h Pokemon.h Type.h
Effect.o:	Category.h Debug.h Effect.h Gender.h MajorAffliction.h Move.h Pokemon.h Stat.h Type.h
EffectFactory.o:	Debug.h Effect.h EffectFactory.h EffectId.h
Environment.o:	Choice.h Environment.h Player.h Round.h
Flinch.o:	Battle.h Category.h Gender.h MinorAffliction.h Move.h Pokemon.h Type.h
Gender.o:	Gender.h
HumanPlayer.o:	Category.h Choice.h Gender.h HumanPlayer.h MajorAffliction.h Move.h Player.h Pokemon.h StringHelper.h Type.h
Infatuation.o:	Battle.h Category.h Gender.h MinorAffliction.h Move.h Pokemon.h Type.h
MajorAffliction.o:	MajorAffliction.h
MinorAffliction.o:	Gender.h MinorAffliction.h Pokemon.h Type.h
Move.o:	Category.h Effect.h Move.h Type.h
MoveFactory.o:	Category.h Debug.h Effect.h EffectFactory.h EffectId.h Move.h MoveFactory.h MoveSpecies.h Type.h
PartialTrap.o:	Battle.h Category.h Gender.h MinorAffliction.h Move.h Pokemon.h Type.h
Player.o:	Choice.h Debug.h Gender.h MajorAffliction.h MinorAffliction.h Player.h Pokemon.h Type.h
Pokemon.o:	Category.h Debug.h Gender.h MajorAffliction.h MinorAffliction.h Move.h MoveFactory.h Pokemon.h Stat.h Type.h
PokemonFactory.o:	Debug.h Gender.h MoveFactory.h Pokemon.h PokemonFactory.h PokemonSpecies.h Type.h
Round.o:	Battle.h Choice.h Debug.h Environment.h Gender.h MinorAffliction.h Player.h Pokemon.h Round.h Stat.h Type.h
Seeding.o:	Battle.h Category.h Gender.h MinorAffliction.h Move.h Pokemon.h Type.h
Stat.o:	Stat.h
StringHelper.o:	StringHelper.h
Type.o:	Type.h
main.o:	Choice.h EffectFactory.h EffectId.h Environment.h Gender.h HumanPlayer.h MajorAffliction.h MinorAffliction.h MoveFactory.h Player.h Pokemon.h PokemonFactory.h PokemonSpecies.h Round.h StringHelper.h Type.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) main.o core 2> /dev/null
	-/bin/rm -rf main 
	-/bin/rm -rf main.exe 
