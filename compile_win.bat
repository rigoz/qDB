@echo off
set INCLUDE_DIRS=-I utils/ -I entities/Match/ -I entities/FootballMatch/ -I entities/BasketballMatch/ -I entities/VolleyballMatch/ -I entities/TennisMatch/ -I db/
set OBJECT_DIR=../build/obj/
cd ./src

:: Compile entities
start "" /W /B g++ -c %INCLUDE_DIRS% entities/Match/Match.cpp -o %OBJECT_DIR%Match.o
start "" /W /B g++ -c %INCLUDE_DIRS% entities/BasketballMatch/BasketballMatch.cpp -o %OBJECT_DIR%BasketballMatch.o
start "" /W /B g++ -c %INCLUDE_DIRS% entities/FootballMatch/FootballMatch.cpp -o %OBJECT_DIR%FootballMatch.o
start "" /W /B g++ -c %INCLUDE_DIRS% entities/VolleyballMatch/VolleyballMatch.cpp -o %OBJECT_DIR%VolleyballMatch.o
start "" /W /B g++ -c %INCLUDE_DIRS% entities/TennisMatch/TennisMatch.cpp -o %OBJECT_DIR%TennisMatch.o
start "" /W /B g++ -c %INCLUDE_DIRS% main.cpp -o %OBJECT_DIR%main.o

cd %OBJECT_DIR%

:: Link everything
start "" /WAIT /B g++ main.o Match.o BasketballMatch.o FootballMatch.o VolleyballMatch.o TennisMatch.o -o ../qDB.exe

cd ../..

pause