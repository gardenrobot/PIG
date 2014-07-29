#PIG - Pokemon Imitating Game

##Description
This is a text-based game that mimics the game mechanics of Pokemon battles from the Pokemon game series, Generation 2. Supports Linux and Windows.

##Dependencies
* Jsoncpp 0.5.0
* Boost C++ 1.55.0

##Building
* For Linux
  * Install all dependencies.
  * Download and unzip archive.
  * Run "make".
* For Windows
  * Though this project can be run on Windows, it must be built in Linux.
  * Install mingw32 with its g++ compiler.
  * Install all dependencies with mingw32. This probably means downloading and building them manually with mingw32.
  * Download and unzip archive.
  * The Makefile assumes the dependencies are installed to /usr/local/win32/. If they are not, edit src/Makefile to point to the correct directory.
  * Run "make mingw".

##Running
Ensure main(.exe) and data/ are in the same directory. Run main(.exe).
