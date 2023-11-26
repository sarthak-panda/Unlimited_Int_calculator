/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
SymEntry::SymEntry(){
    key="";
    val=nullptr;
    left=nullptr;
    right=nullptr;
}
SymEntry::SymEntry(string k, UnlimitedRational* v){
    key=k;
    val=v;
    left=nullptr;
    right=nullptr;
}
SymEntry::~SymEntry(){
//no need to delete symtable as it contains same unlimited ration as expression tree
// delete val;
// if(left!=nullptr) delete left;
// if(right!=nullptr) delete right;
}