**frequencies.cpp** - 
Calculates the frequency of every character in the file

**huffman.cpp** - 
Calculates the encoding for each character and outputs the expected size of the compressed file

**encode.cpp** - 
Compresses the file using a file of character encodings

**decode.cpp** - 
Decompresses the file using a file of character encodings

Usage:

Generate codewords.txt, the file containing the character encodings:

    cat [FILE] | ./frequencies | ./huffman
    832


Encode FILE and write the compressed file to OUTPUT\_FILE:

    cat [FILE] | ./encode codewords.txt > [OUTPUT_FILE]


Decode FILE and write the decoded file to OUTPUT\_FILE:

    cat [FILE] | ./decode codewords.txt > [OUTPUT_FILE]
