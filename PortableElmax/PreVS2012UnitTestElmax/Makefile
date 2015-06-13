# Project: UnitTestXML

#CPP      = clang++ -stdlib=libstdc++ -lstdc++ -std=c++11
CPP      = g++
CC       = gcc
OBJ      = Assert.o PreVS2012UnitTestElmax.o UnitTestAttribute.o UnitTestCommentAndCData.o UnitTestMisc.o UnitTestSaveAndRead.o UnitTestSetterGetter.o UnitTestVoidGetter.o $(RES)
LINKOBJ  = Assert.o PreVS2012UnitTestElmax.o UnitTestAttribute.o UnitTestCommentAndCData.o UnitTestMisc.o UnitTestSaveAndRead.o UnitTestSetterGetter.o UnitTestVoidGetter.o $(RES)
LIBS     = -static-libgcc ../PortableElmax/PortableElmax.a  -g 
CXXINCS  = -I ~/Downloads/boost_1_55_0
BIN      = UnitTestXML.exe
CXXFLAGS = -Wall -g -O1 $(CXXINCS)
CFLAGS   = -Wall -g -O1  
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before UnitTestXML.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "UnitTestXML.exe" $(LIBS)

Assert.o: Assert.cpp
	$(CPP) -c Assert.cpp -o Assert.o $(CXXFLAGS)

PreVS2012UnitTestElmax.o: PreVS2012UnitTestElmax.cpp
	$(CPP) -c PreVS2012UnitTestElmax.cpp -o PreVS2012UnitTestElmax.o $(CXXFLAGS)

UnitTestAttribute.o: UnitTestAttribute.cpp
	$(CPP) -c UnitTestAttribute.cpp -o UnitTestAttribute.o $(CXXFLAGS)

UnitTestCommentAndCData.o: UnitTestCommentAndCData.cpp
	$(CPP) -c UnitTestCommentAndCData.cpp -o UnitTestCommentAndCData.o $(CXXFLAGS)

UnitTestMisc.o: UnitTestMisc.cpp
	$(CPP) -c UnitTestMisc.cpp -o UnitTestMisc.o $(CXXFLAGS)

UnitTestSaveAndRead.o: UnitTestSaveAndRead.cpp
	$(CPP) -c UnitTestSaveAndRead.cpp -o UnitTestSaveAndRead.o $(CXXFLAGS)

UnitTestSetterGetter.o: UnitTestSetterGetter.cpp
	$(CPP) -c UnitTestSetterGetter.cpp -o UnitTestSetterGetter.o $(CXXFLAGS)

UnitTestVoidGetter.o: UnitTestVoidGetter.cpp
	$(CPP) -c UnitTestVoidGetter.cpp -o UnitTestVoidGetter.o $(CXXFLAGS)
