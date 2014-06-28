// Sergio Leon <seleon>, Michael Lee <mil039>

#include <iostream>
#include <fstream>
#include "HCTree.hpp"

using namespace std;

int main(int argc, char* argv[]) { 
    ifstream infile(argv[1], ios::binary); //Input file
    ofstream outfile(argv[2], ios::binary); //Output file
    string str; //String to input file
    vector<int> freqs(256, 0); //Empty vector
    HCTree tree; //Huffman code tree
    int count = 0; //Amount to encode
    BitInputStream bitIS(infile); //Input stream

    //Exit if insufficent arguments
    if(!infile || !outfile) {
        cerr << "Insufficient arguments.\n" << endl;
        return -1;
    }

    //Exit if invalid files
    if(!infile.good() || !outfile.good()) return -1;

    cout << "Reading from file \"" << argv[1] << "\"..."; 

    //Send file to string 
    infile.seekg(0, ios::end);
    str.reserve(infile.tellg());
    infile.seekg(0, ios::beg);

    str.assign((istreambuf_iterator<char>(infile)), 
                istreambuf_iterator<char>());

    //Count frequency of each symbol
    for(int i = 0; i < str.size(); i++) {
        byte sym = str[i];
        freqs[sym]++;
    }

    BitOutputStream bitOS(outfile); //Output stream

    //Write header
    for(int i = 0; i < freqs.size(); i++) {
        bitOS.writeInt(freqs[i]);

        if(freqs[i] > 0) 
            count++;
    }

    cout << "Building Huffman code tree... ";

    //Build Huffman code tree
    tree.build(freqs); 

    cout << "done.\nWriting to file \"" << argv[2] << "\"... ";

    cout << "done.\nFound " << count << " unique symbols in input file of size " 
         << infile.tellg() << " bytes.\n";

    //Encode symbols to output file
    for(int i = 0; i < str.size(); i++) {

        //Exit loop if invalid files
        if(!infile.good() || !outfile.good()) 
            break;

        tree.encode(str[i], bitOS); 
    }

    outfile.seekp(0, ios_base::end);
    cout << "Output file has size " << outfile.tellp() << " bytes.\n" 
         << "Compression ratio: " << (double) outfile.tellp()/infile.tellg() << endl;

    //Flush remaining bits in output stream
    bitOS.flush();

    //Close files
    outfile.close();
    infile.close();
}
     

    
    
