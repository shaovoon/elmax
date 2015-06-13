# Project: SequelMax

#CPP      = clang++ -stdlib=libstdc++ -lstdc++ -std=c++11
CPP      = g++ -lstdc++ -std=c++11
CC       = gcc
OBJ      = ../FileIO/Common/Common.o ../FileIO/Common/Enumeration.o ../FileIO/Common/RAII_Array.o ../FileIO/Linux/LinuxOperation.o ../FileIO/Text/Reader/AsciiReader.o ../FileIO/Text/Reader/AsciiReaderA.o ../FileIO/Text/Reader/BaseTextReader.o ../FileIO/Text/Reader/BaseTextReaderA.o ../FileIO/Text/Reader/BEUnicodeReader.o ../FileIO/Text/Reader/UnicodeReader.o ../FileIO/Text/Reader/UTF8Reader.o ../FileIO/Text/Reader/UTF8ReaderA.o ../FileIO/Text/Reader/xTextReader.o ../FileIO/Text/Reader/xTextReaderA.o ../FileIO/Text/Utils/StrUtil.o ../FileIO/Text/Utils/StrUtilA.o ../FileIO/Text/Writer/AsciiWriter.o ../FileIO/Text/Writer/AsciiWriterA.o ../FileIO/Text/Writer/BaseTextWriter.o ../FileIO/Text/Writer/BaseTextWriterA.o ../FileIO/Text/Writer/BEUnicodeWriter.o ../FileIO/Text/Writer/UnicodeWriter.o ../FileIO/Text/Writer/UTF8Writer.o ../FileIO/Text/Writer/UTF8WriterA.o ../FileIO/Text/Writer/xTextWriter.o ../FileIO/Text/Writer/xTextWriterA.o ../FileIO/UTF16Utils/utf16.o Elmax/Attribute.o Elmax/Date.o Elmax/DateAndTime.o Elmax/Element.o Map/DictMap.o Map/HashMap.o Map/SListMap.o Map/VectorMap.o RawElement/RawAttribute.o RawElement/RawElement.o RawElement/RawTreeNode.o Utils/BoolHexUtil.o Utils/StrConv.o Elmax/StringStack.o Elmax/Document.o Elmax/XMLWriter.o Elmax/istream.o Elmax/ostream.o $(RES)
LINKOBJ  = ../FileIO/Common/Common.o ../FileIO/Common/Enumeration.o ../FileIO/Common/RAII_Array.o ../FileIO/Linux/LinuxOperation.o ../FileIO/Text/Reader/AsciiReader.o ../FileIO/Text/Reader/AsciiReaderA.o ../FileIO/Text/Reader/BaseTextReader.o ../FileIO/Text/Reader/BaseTextReaderA.o ../FileIO/Text/Reader/BEUnicodeReader.o ../FileIO/Text/Reader/UnicodeReader.o ../FileIO/Text/Reader/UTF8Reader.o ../FileIO/Text/Reader/UTF8ReaderA.o ../FileIO/Text/Reader/xTextReader.o ../FileIO/Text/Reader/xTextReaderA.o ../FileIO/Text/Utils/StrUtil.o ../FileIO/Text/Utils/StrUtilA.o ../FileIO/Text/Writer/AsciiWriter.o ../FileIO/Text/Writer/AsciiWriterA.o ../FileIO/Text/Writer/BaseTextWriter.o ../FileIO/Text/Writer/BaseTextWriterA.o ../FileIO/Text/Writer/BEUnicodeWriter.o ../FileIO/Text/Writer/UnicodeWriter.o ../FileIO/Text/Writer/UTF8Writer.o ../FileIO/Text/Writer/UTF8WriterA.o ../FileIO/Text/Writer/xTextWriter.o ../FileIO/Text/Writer/xTextWriterA.o ../FileIO/UTF16Utils/utf16.o Elmax/Attribute.o Elmax/Date.o Elmax/DateAndTime.o Elmax/Element.o Map/DictMap.o Map/HashMap.o Map/SListMap.o Map/VectorMap.o RawElement/RawAttribute.o RawElement/RawElement.o RawElement/RawTreeNode.o Utils/BoolHexUtil.o Utils/StrConv.o Elmax/StringStack.o Elmax/Document.o Elmax/XMLWriter.o Elmax/istream.o Elmax/ostream.o $(RES)
CXXINCS  = -I ~/Downloads/boost_1_55_0
BIN      = SequelMax.a
CXXFLAGS = -Wall -g -O1 $(CXXINCS)
CFLAGS   = -Wall -g -O1  
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before SequelMax.a all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	ar r $(BIN) $(LINKOBJ)
	ranlib $(BIN)

../FileIO/Common/Common.o: ../FileIO/Common/Common.cpp
	$(CPP) -c ../FileIO/Common/Common.cpp -o ../FileIO/Common/Common.o $(CXXFLAGS)

../FileIO/Common/Enumeration.o: ../FileIO/Common/Enumeration.cpp
	$(CPP) -c ../FileIO/Common/Enumeration.cpp -o ../FileIO/Common/Enumeration.o $(CXXFLAGS)

../FileIO/Common/RAII_Array.o: ../FileIO/Common/RAII_Array.cpp
	$(CPP) -c ../FileIO/Common/RAII_Array.cpp -o ../FileIO/Common/RAII_Array.o $(CXXFLAGS)

../FileIO/Linux/LinuxOperation.o: ../FileIO/Linux/LinuxOperation.cpp
	$(CPP) -c ../FileIO/Linux/LinuxOperation.cpp -o ../FileIO/Linux/LinuxOperation.o $(CXXFLAGS)

../FileIO/Text/Reader/AsciiReader.o: ../FileIO/Text/Reader/AsciiReader.cpp
	$(CPP) -c ../FileIO/Text/Reader/AsciiReader.cpp -o ../FileIO/Text/Reader/AsciiReader.o $(CXXFLAGS)

../FileIO/Text/Reader/AsciiReaderA.o: ../FileIO/Text/Reader/AsciiReaderA.cpp
	$(CPP) -c ../FileIO/Text/Reader/AsciiReaderA.cpp -o ../FileIO/Text/Reader/AsciiReaderA.o $(CXXFLAGS)

../FileIO/Text/Reader/BaseTextReader.o: ../FileIO/Text/Reader/BaseTextReader.cpp
	$(CPP) -c ../FileIO/Text/Reader/BaseTextReader.cpp -o ../FileIO/Text/Reader/BaseTextReader.o $(CXXFLAGS)

../FileIO/Text/Reader/BaseTextReaderA.o: ../FileIO/Text/Reader/BaseTextReaderA.cpp
	$(CPP) -c ../FileIO/Text/Reader/BaseTextReaderA.cpp -o ../FileIO/Text/Reader/BaseTextReaderA.o $(CXXFLAGS)

../FileIO/Text/Reader/BEUnicodeReader.o: ../FileIO/Text/Reader/BEUnicodeReader.cpp
	$(CPP) -c ../FileIO/Text/Reader/BEUnicodeReader.cpp -o ../FileIO/Text/Reader/BEUnicodeReader.o $(CXXFLAGS)

../FileIO/Text/Reader/UnicodeReader.o: ../FileIO/Text/Reader/UnicodeReader.cpp
	$(CPP) -c ../FileIO/Text/Reader/UnicodeReader.cpp -o ../FileIO/Text/Reader/UnicodeReader.o $(CXXFLAGS)

../FileIO/Text/Reader/UTF8Reader.o: ../FileIO/Text/Reader/UTF8Reader.cpp
	$(CPP) -c ../FileIO/Text/Reader/UTF8Reader.cpp -o ../FileIO/Text/Reader/UTF8Reader.o $(CXXFLAGS)

../FileIO/Text/Reader/UTF8ReaderA.o: ../FileIO/Text/Reader/UTF8ReaderA.cpp
	$(CPP) -c ../FileIO/Text/Reader/UTF8ReaderA.cpp -o ../FileIO/Text/Reader/UTF8ReaderA.o $(CXXFLAGS)

../FileIO/Text/Reader/xTextReader.o: ../FileIO/Text/Reader/xTextReader.cpp
	$(CPP) -c ../FileIO/Text/Reader/xTextReader.cpp -o ../FileIO/Text/Reader/xTextReader.o $(CXXFLAGS)

../FileIO/Text/Reader/xTextReaderA.o: ../FileIO/Text/Reader/xTextReaderA.cpp
	$(CPP) -c ../FileIO/Text/Reader/xTextReaderA.cpp -o ../FileIO/Text/Reader/xTextReaderA.o $(CXXFLAGS)

../FileIO/Text/Utils/StrUtil.o: ../FileIO/Text/Utils/StrUtil.cpp
	$(CPP) -c ../FileIO/Text/Utils/StrUtil.cpp -o ../FileIO/Text/Utils/StrUtil.o $(CXXFLAGS)

../FileIO/Text/Utils/StrUtilA.o: ../FileIO/Text/Utils/StrUtilA.cpp
	$(CPP) -c ../FileIO/Text/Utils/StrUtilA.cpp -o ../FileIO/Text/Utils/StrUtilA.o $(CXXFLAGS)

../FileIO/Text/Writer/AsciiWriter.o: ../FileIO/Text/Writer/AsciiWriter.cpp
	$(CPP) -c ../FileIO/Text/Writer/AsciiWriter.cpp -o ../FileIO/Text/Writer/AsciiWriter.o $(CXXFLAGS)

../FileIO/Text/Writer/AsciiWriterA.o: ../FileIO/Text/Writer/AsciiWriterA.cpp
	$(CPP) -c ../FileIO/Text/Writer/AsciiWriterA.cpp -o ../FileIO/Text/Writer/AsciiWriterA.o $(CXXFLAGS)

../FileIO/Text/Writer/BaseTextWriter.o: ../FileIO/Text/Writer/BaseTextWriter.cpp
	$(CPP) -c ../FileIO/Text/Writer/BaseTextWriter.cpp -o ../FileIO/Text/Writer/BaseTextWriter.o $(CXXFLAGS)

../FileIO/Text/Writer/BaseTextWriterA.o: ../FileIO/Text/Writer/BaseTextWriterA.cpp
	$(CPP) -c ../FileIO/Text/Writer/BaseTextWriterA.cpp -o ../FileIO/Text/Writer/BaseTextWriterA.o $(CXXFLAGS)

../FileIO/Text/Writer/BEUnicodeWriter.o: ../FileIO/Text/Writer/BEUnicodeWriter.cpp
	$(CPP) -c ../FileIO/Text/Writer/BEUnicodeWriter.cpp -o ../FileIO/Text/Writer/BEUnicodeWriter.o $(CXXFLAGS)

../FileIO/Text/Writer/UnicodeWriter.o: ../FileIO/Text/Writer/UnicodeWriter.cpp
	$(CPP) -c ../FileIO/Text/Writer/UnicodeWriter.cpp -o ../FileIO/Text/Writer/UnicodeWriter.o $(CXXFLAGS)

../FileIO/Text/Writer/UTF8Writer.o: ../FileIO/Text/Writer/UTF8Writer.cpp
	$(CPP) -c ../FileIO/Text/Writer/UTF8Writer.cpp -o ../FileIO/Text/Writer/UTF8Writer.o $(CXXFLAGS)

../FileIO/Text/Writer/UTF8WriterA.o: ../FileIO/Text/Writer/UTF8WriterA.cpp
	$(CPP) -c ../FileIO/Text/Writer/UTF8WriterA.cpp -o ../FileIO/Text/Writer/UTF8WriterA.o $(CXXFLAGS)

../FileIO/Text/Writer/xTextWriter.o: ../FileIO/Text/Writer/xTextWriter.cpp
	$(CPP) -c ../FileIO/Text/Writer/xTextWriter.cpp -o ../FileIO/Text/Writer/xTextWriter.o $(CXXFLAGS)

../FileIO/Text/Writer/xTextWriterA.o: ../FileIO/Text/Writer/xTextWriterA.cpp
	$(CPP) -c ../FileIO/Text/Writer/xTextWriterA.cpp -o ../FileIO/Text/Writer/xTextWriterA.o $(CXXFLAGS)

../FileIO/UTF16Utils/utf16.o: ../FileIO/UTF16Utils/utf16.cpp
	$(CPP) -c ../FileIO/UTF16Utils/utf16.cpp -o ../FileIO/UTF16Utils/utf16.o $(CXXFLAGS)

Elmax/Attribute.o: Elmax/Attribute.cpp
	$(CPP) -c Elmax/Attribute.cpp -o Elmax/Attribute.o $(CXXFLAGS)

Elmax/Date.o: Elmax/Date.cpp
	$(CPP) -c Elmax/Date.cpp -o Elmax/Date.o $(CXXFLAGS)

Elmax/DateAndTime.o: Elmax/DateAndTime.cpp
	$(CPP) -c Elmax/DateAndTime.cpp -o Elmax/DateAndTime.o $(CXXFLAGS)

Elmax/Element.o: Elmax/Element.cpp
	$(CPP) -c Elmax/Element.cpp -o Elmax/Element.o $(CXXFLAGS)

Map/DictMap.o: Map/DictMap.cpp
	$(CPP) -c Map/DictMap.cpp -o Map/DictMap.o $(CXXFLAGS)

Map/HashMap.o: Map/HashMap.cpp
	$(CPP) -c Map/HashMap.cpp -o Map/HashMap.o $(CXXFLAGS)

Map/SListMap.o: Map/SListMap.cpp
	$(CPP) -c Map/SListMap.cpp -o Map/SListMap.o $(CXXFLAGS)

Map/VectorMap.o: Map/VectorMap.cpp
	$(CPP) -c Map/VectorMap.cpp -o Map/VectorMap.o $(CXXFLAGS)

RawElement/RawAttribute.o: RawElement/RawAttribute.cpp
	$(CPP) -c RawElement/RawAttribute.cpp -o RawElement/RawAttribute.o $(CXXFLAGS)

RawElement/RawElement.o: RawElement/RawElement.cpp
	$(CPP) -c RawElement/RawElement.cpp -o RawElement/RawElement.o $(CXXFLAGS)

RawElement/RawTreeNode.o: RawElement/RawTreeNode.cpp
	$(CPP) -c RawElement/RawTreeNode.cpp -o RawElement/RawTreeNode.o $(CXXFLAGS)

Utils/BoolHexUtil.o: Utils/BoolHexUtil.cpp
	$(CPP) -c Utils/BoolHexUtil.cpp -o Utils/BoolHexUtil.o $(CXXFLAGS)

Utils/StrConv.o: Utils/StrConv.cpp
	$(CPP) -c Utils/StrConv.cpp -o Utils/StrConv.o $(CXXFLAGS)

Elmax/StringStack.o: Elmax/StringStack.cpp
	$(CPP) -c Elmax/StringStack.cpp -o Elmax/StringStack.o $(CXXFLAGS)

Elmax/Document.o: Elmax/Document.cpp
	$(CPP) -c Elmax/Document.cpp -o Elmax/Document.o $(CXXFLAGS)
	
Elmax/XMLWriter.o: Elmax/XMLWriter.cpp
	$(CPP) -c Elmax/XMLWriter.cpp -o Elmax/XMLWriter.o $(CXXFLAGS)

Elmax/istream.o: Elmax/istream.cpp
	$(CPP) -c Elmax/istream.cpp -o Elmax/istream.o $(CXXFLAGS)

Elmax/ostream.o: Elmax/ostream.cpp
	$(CPP) -c Elmax/ostream.cpp -o Elmax/ostream.o $(CXXFLAGS)
