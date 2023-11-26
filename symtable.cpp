/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
SymbolTable::SymbolTable(){
    size=0;
    root=nullptr;
}
SymbolTable::~SymbolTable(){
//if(root!=nullptr)delete root;
}
void SymbolTable::insert(string k, UnlimitedRational* v){
    SymEntry* n=new SymEntry(k,v);
    if(size==0){
        root=n;
    }
    else{
        SymEntry* temp=root,*temppar=root;
        while(temp!=nullptr){
            if(k>temp->key){
                temppar=temp;
                temp=temp->right;
            }
            else{
                temppar=temp;
                temp=temp->left;
            }
        }
        if(k>temppar->key){
            temppar->right=n;
        }
        else{
            temppar->left=n;
        }
    }
    size++;

}
void SymbolTable::remove(string k){//here we neglected the cases root is null or key not found cases were  not handelled.
    SymEntry* temp=root,*temppar=root;
    while(temp->key!=k){
        if(k>temp->key){
            temppar=temp;
            temp=temp->right;
        }
        else{
            temppar=temp;
            temp=temp->left;
        }
    }
    size--;
    //case1 the key is leaf node
    if(temp->left==nullptr and temp->right==nullptr){
        if(temppar->left==temp){
            temppar->left=nullptr;
        }
        else{
            temppar->right=nullptr;
        }
        delete temp;
    }   
    //case 2 one child only 
    else if((temp->left==nullptr and temp->right!=nullptr) or (temp->left!=nullptr and temp->right==nullptr)){
        if(temp==root){
            if(temp->left!=nullptr){
                root=temp->left;
            }
            else{
                root=temp->right;
            }
        }
        else{
            if(temppar->right==temp){
                if(temp->left!=nullptr){
                    temppar->right=temp->left;
                }
                else{
                    temppar->right=temp->right;
                }
            }
            else{
                if(temp->left!=nullptr){
                    temppar->left=temp->left;
                }
                else{
                    temppar->left=temp->right;
                }              
            }
        }
        delete temp;
    }
    //case 3 both the child are present
    else{
        SymEntry* s,*spar;
        spar=temp;
        s=temp->right;
        while(s->left!=nullptr){
            spar=s;
            s=s->left;
        }
        temp->key=s->key;
        temp->val=s->val;
        if(spar==temp){
            spar->right=s->right;
        }
        else{
        if(s->right==nullptr){
            spar->left=nullptr;
        }
        else{
            spar->left=s->right;
        }
        }
        delete s;
    }
}
UnlimitedRational* SymbolTable::search(string k){
    SymEntry* temp=root;
    while(temp->key!=k){
        if(k>temp->key){
            temp=temp->right;
        }
        else{
            temp=temp->left;
        }
    }
    return temp->val;
}
int SymbolTable::get_size(){
    return size;
}
SymEntry* SymbolTable::get_root(){
    return root;
}