/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
ExprTreeNode::ExprTreeNode(){
    type="";
    val=nullptr;
    evaluated_value=nullptr;
    id="";
    left=nullptr;
    right=nullptr;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    type=t;
    val=new UnlimitedRational(v,new UnlimitedInt("1"));
    evaluated_value=nullptr;
    id="";
    left=nullptr;
    right=nullptr;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    type=t;
    val=v;
    evaluated_value=nullptr;
    id="";
    left=nullptr;
    right=nullptr;    
}
ExprTreeNode::~ExprTreeNode(){
    if(type=="VAL"){
    delete val;//evaluated value same as val don't delete it again
    }
    else if(type=="ADD" or type=="SUB" or type=="MUL" or type=="DIV"){
        delete evaluated_value;
        delete left;
        delete right;
    }
    else if(type=="EQL"){
        delete right;
    }
}