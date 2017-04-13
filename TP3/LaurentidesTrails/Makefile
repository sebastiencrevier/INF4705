PROGRAM=tp3
SOURCES=main.cpp Point.cpp Edge.cpp Solution.cpp Graph.cpp
DEPS=stdc++.h Utilities.h Point.h Edge.h Solution.h Graph.h

GCC=g++
CPPFLAGS=-std=c++11 -g -O0 -Wall -Werror -pthread

${PROGRAM} : ${SOURCES} ${DEPS}
	${GCC} ${CPPFLAGS} -o ${PROGRAM} ${SOURCES}

clean:
	rm -rf *.o *.txt *.exe ${PROGRAM}