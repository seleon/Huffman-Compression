// Sergio Leon <seleon>, Michael Lee <mil039>

#include "BitInputStream.hpp"


  /** Read the next bit from the bit buffer.
  *  If the bit buffer is currently empty,
  *  fill the bit buffer by reading a char from the istream first.
  *  Return the bit read as the least signficant bit of an int.
  *  Return -1 on EOF.
  *  This must be consistent with BitOutputStream::writeBit(), in terms
  *  of ordering of bits in the stream.
  */
  int BitInputStream::readBit() {
       unsigned int temp; //Represents bit

       //Bit buffer is empty
       if(bufi == 8) {
           buf = in.get();

           //Exit if invalid file
           if(!in.good())
               return -1;

           bufi = 0;
       }

       //Least significant bit of int
       temp = buf& (1 << (7 - bufi));

       //Increment index
       bufi++;

       return temp;
    }

    /** Read a byte from the ostream.
     *  Return -1 on EOF.
     *  This function doesn't touch the bit buffer.
     *  The client has to manage interaction between reading bits
     *  and reading bytes.
     */
    int BitInputStream::readByte() {
        if(in.eof())
            return -1;

        return in.get();
    }

    /** Read a non-negative int from the ostream.
     *  Return -1 on EOF.
     *  This function doesn't touch the bit buffer.
     *  The client has to manage interaction between reading bits
     *  and reading ints.
     */
    int BitInputStream::readInt() {
        int temp; //int from ostream

        if(in.eof())
            return -1;

        //Get int if input file is valid 
        if(in.good())
            in >> temp;

        return temp;
    }

