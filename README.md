frequencies.cpp calculates the frequency of every character in the file
huffman.cpp calculates the encoding for each character and outputs the expected
size of the compressed file
encode.cpp compresses the file using a file of character encodings
decode.cpp decompresses the file using a file of character encodings

Usage:

 $~] cat [FILE] | ./frequencies | ./huffman
    832
    (And also generates the file 'codewords.txt')

 $~] cat [FILE] | ./encode codewords.txt > [OUTPUT\_FILE]

    Encodes the file and writes the compressed file to OUTPUT_FILE

 $~] cat encoded | ./decode codewords.txt > [OUTPUT\_FILE]

    Decodes the file and writes the decoded file to OUTPUT_FILE
