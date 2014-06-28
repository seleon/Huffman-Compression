// Sergio Leon <seleon>, Michael Lee <mil039>

#include "BitOutputStream.hpp"

  //  BitOutputStream(ostream& s) : out(s), bufi(0) { }

  /** Write the least significant bit of the argument into
   *  the bit buffer, and increment the bit buffer index.
   *  Flush to the ostream first if the bit buffer is full.
   *  This must be consistent with BitInputStream::readBit().
   */
  void BitOutputStream::writeBit(int bit) {

     //Bit buffer is full
     if(bufi == 8) {
         out << buf;
         out.flush();
         buf = 0;
         bufi = 0;
     }

     //Least significant bit
     buf = buf | (bit << (7 - bufi));
     bufi++;
  }

  /** Write the least significant byte of the argument to the ostream.
   *  This function doesn't touch the bit buffer.
   *  The client has to manage interaction between writing bits
   *  and writing bytes.
   */
  void BitOutputStream::writeByte(int b) {
      out << (char) b;
  }

  /** Write the argument to the ostream.
   *  This function doesn't touch the bit buffer.
   *  The client has to manage interaction between writing bits
   *  and writing ints.
   */
  void BitOutputStream::writeInt(int i) {
      out << i << " ";
  }

  /** If the bit buffer contains any bits, flush the bit buffer to the ostream,
   *  clear the bit buffer, and set the bit buffer index to 0.
   *  Also flush the ostream itself.
   */
  void BitOutputStream::flush() {
      out << buf;
      buf = 0;
      bufi = 0;
      out.flush();
  }

