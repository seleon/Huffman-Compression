// Sergio Leon <seleon>, Michael Lee <mil039>

#include <iostream>
#include <fstream>
#include <sstream>
#include "HCTree.hpp"
#include <stdlib.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) { 
    ifstream infile(argv[1], ios::binary); //Open input file
    ofstream outfile(argv[2], ios::binary); //Open output file
    vector<int> freqs(256, 0); //Empty array of size 256
    HCTree tree; //Huffman coding tree
    int count = 0; //Count of characters
    string str;

    //Display error message if not enough arguments
    if(!infile || !outfile) {
        cerr << "Insufficient arguments.\n";
        return -1;
    }

    if(!infile.good() || !outfile.good()) return -1;

    //Input contents of file to array
    for(int i = 0; i < freqs.size(); i++) {
    
        //Exit loop if invalid file
        if(!infile.good() || !outfile.good()) break;

        //Get symbols 
        getline(infile, str, ' ');
        istringstream val(str);
        val >> freqs[i];

        //Increment decode count
        count += freqs[i];
    }

    //Build Huffman code tree
    tree.build(freqs); 

    BitInputStream bitIS(infile);

    //Decode count number of times, send to output file
    for(int i = 0; i < count; i++) {
	if(!infile.good() || !outfile.good()) break;
        
        outfile << (unsigned char) tree.decode(bitIS);
    } 

    //Close files
    outfile.close();
    infile.close();
}
