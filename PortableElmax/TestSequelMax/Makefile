# Project: TestSequelMax

#CPP      = clang++ -stdlib=libstdc++ -lstdc++ -std=c++11
CPP      = g++ -lstdc++ -std=c++11
CC       = gcc
OBJ      = TestSequelMax.o TestStream.o $(RES)
LINKOBJ  = TestSequelMax.o TestStream.o $(RES)
LIBS     = -static-libgcc ../SequelMax/SequelMax.a  -g 
CXXINCS  = -I ~/Downloads/boost_1_55_0
BIN      = TestSequelMax.exe
CXXFLAGS = -Wall -g -O1 $(CXXINCS)
CFLAGS   = -Wall -g -O1  
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before TestSequelMax.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "TestSequelMax.exe" $(LIBS)

TestSequelMax.o: TestSequelMax.cpp
	$(CPP) -c TestSequelMax.cpp -o TestSequelMax.o $(CXXFLAGS)

TestStream.o: TestStream.cpp
	$(CPP) -c TestStream.cpp -o TestStream.o $(CXXFLAGS)
