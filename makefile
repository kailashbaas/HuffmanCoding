CXX=g++

CXXFLAGS= -Wall -g

BINARIES=frequencies huffman encode decode

all: ${BINARIES}

frequencies: frequencies.cpp
	${CXX} -o $@ $^ ${CXXFLAGS}

huffman: huffman.cpp
	${CXX} -o $@ $^ ${CXXFLAGS}

encode: encode.cpp
	${CXX} -o $@ $^ ${CXXFLAGS}

decode: decode.cpp
	${CXX} -o $@ $^ ${CXXFLAGS}

clean:
	/bin/rm -f ${BINARIES} codewords.txt encoded decoded
