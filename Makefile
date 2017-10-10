all: hw4

hw4: ArithmeticExpression.o BooleanExpression.o Command.o hw4.cpp
	g++ -g -Wall -std=c++11 ArithmeticExpression.cpp \
	BooleanExpression.cpp Command.cpp hw4.cpp -o hw4

ArithmeticExpression.o: ArithmeticExpression.h ArithmeticExpression.cpp
	g++ -g -Wall -std=c++11 -c ArithmeticExpression.cpp -o \
	 ArithmeticExpression.o

BooleanExpression.o: BooleanExpression.h BooleanExpression.cpp
	g++ -g -Wall -std=c++11 -c BooleanExpression.cpp -o \
	BooleanExpression.o

Command.o: Command.h Command.cpp
	g++ -g -Wall -std=c++11 -c Command.cpp -o Command.o

clean:
	rm ArithmeticExpression.o BooleanExpression.o Command.o hw4