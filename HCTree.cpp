// Sergio Leon <seleon>, Michael Lee <mil039>

#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCTree.hpp"

    //Helper method for destructor
    void HCTree::DeleteNode(HCNode* node) {
  
        //Traverse through nodes to delete all
        if(node != nullptr)
            if(node->c0 != nullptr)
                DeleteNode(node->c0);
            if(node->c1 != nullptr)
                DeleteNode(node->c1);

            delete node;
    }

    //Destructor
    HCTree::~HCTree() {

        //Run DeleteNode starting at root
        if(root != nullptr)
            DeleteNode(root);
    }

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void HCTree::build(const vector<int>& freqs) {
        priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
        int count = 0;

        //Creates a forest of nodes
        for(int i = 0; i < freqs.size(); i++) {
              if(freqs[i] > 0) {
               HCNode* temp = new HCNode(freqs[i], i, nullptr, nullptr);
               leaves[i] = temp;
               pq.push(temp);
           }

           //Increment count if frequency at index is 0 
           if(freqs[i] == 0) count++;
        }

        //Pop until size 1 in order to set root at end
        while(pq.size() > 1) {
            HCNode* parent = new HCNode(0, 0, nullptr, nullptr); //Empty parent node
            int sum; //Sum of smallest nodes

            //Link to two smallest value nodes 
            parent->c0 = pq.top();
            pq.pop();

            parent->c1 = pq.top();
            pq.pop();

            //Parent value is sum of children value 
            sum = parent->c1->count + parent->c0->count;
            parent->count = sum;

            parent->c1->p = parent;
            parent->c0->p = parent;
            pq.push(parent);
        }

        //Set root to highest node if not reading from empty file
        if(count != 256) {
            root = pq.top();
            pq.pop();
        }

   }

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void HCTree::encode(byte symbol, BitOutputStream& out) const {
        HCNode* node = leaves[(int) symbol]; //Access node at symbol index
        stack<int> st; //Used to output in correct order

        //Push 0 onto stack if left child, 1 if right
        while(node != nullptr && node->p != nullptr) {
            if(node->p->c0 == node)
                st.push(0);
            else if(node->p->c1 == node)
                st.push(1);

            node = node->p;
        }

        //Output stack contents to file 
        while(!st.empty()) {
            out.writeBit(st.top());
            st.pop();
       }
    }

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int HCTree::decode(BitInputStream& in) const {
        HCNode* node = root; //Start at root node
        int n = 0; //Individual bit

        //Go from root to leaf node
        while(node->c0 != nullptr || node->c1 != nullptr) {
            n = in.readBit();

            if(n)
                node = node->c1;
            else
                node = node->c0;
        }

        //Return leaf symbol
        return node->symbol;
     }

