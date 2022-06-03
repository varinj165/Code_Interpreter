all: hw4

hw4: main.cpp arithmetic.o boolexpression.o command.o interpreter.o
	g++ -g -Wall -std=c++11 main.cpp arithmetic.o boolexpression.o command.o interpreter.o -o hw4

arithmetic.o: interpreter/arithmetic.h interpreter/arithmetic.cpp
	g++ -g -Wall -std=c++11 -c interpreter/arithmetic.cpp -o arithmetic.o

boolexpression.o: interpreter/boolexpression.h interpreter/boolexpression.cpp
	g++ -g -Wall -std=c++11 -c interpreter/boolexpression.cpp -o boolexpression.o

command.o: interpreter/command.h interpreter/command.cpp
	g++ -g -Wall -std=c++11 -c interpreter/command.cpp -o command.o

interpreter.o: interpreter/interpreter.h interpreter/interpreter.cpp
	g++ -g -Wall -std=c++11 -c interpreter/interpreter.cpp -o interpreter.o