/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
ExprTreeNode *Node_creator(string t)
{
    ExprTreeNode *temp = new ExprTreeNode();
    if (t == "+" or t == "-" or t == "*" or t == "/" or t == "%")
    {
        if (t == "+")
        {
            temp->type = "ADD";
        }
        else if (t == "-")
        {
            temp->type = "SUB";
        }
        else if (t == "*")
        {
            temp->type = "MUL";
        }
        else if (t == "/")
        {
            temp->type = "DIV";
        }
        else
        {
            temp->type = "MOD";
        }
    }
    else if ((t[0] == '-' and isdigit(t[1])) or isdigit(t[0]))
    { // to implement isnum.ASSUMING C TYPE VARIABLE can neither begin from digit or a minus symbol
        temp->type = "VAL";
        temp->val = new UnlimitedRational(new UnlimitedInt(t), new UnlimitedInt("1"));
    }
    else if (t == "(")
    {
        temp->type = "BKT";
    }
    else
    {
        temp->type = "VAR";
        temp->id = t;
    }
    return temp;
}

void Node_solver(ExprTreeNode *root, SymbolTable *symtable)
{
    if (root->left == nullptr and root->right == nullptr)
    {
        if (root->type == "VAL")
        {
            root->evaluated_value = root->val;
        }
        else if (root->type == "VAR")
        {
            root->evaluated_value = symtable->search(root->id);
        }
        return;
    }
    else
    {
        Node_solver(root->left, symtable);
        Node_solver(root->right, symtable);
        if (root->type == "ADD")
        {
            root->evaluated_value = UnlimitedRational::add(root->left->evaluated_value, root->right->evaluated_value);
        }
        else if (root->type == "SUB")
        {
            root->evaluated_value = UnlimitedRational::sub(root->left->evaluated_value, root->right->evaluated_value);
        }
        else if (root->type == "MUL")
        {
            root->evaluated_value = UnlimitedRational::mul(root->left->evaluated_value, root->right->evaluated_value);
        }
        else if (root->type == "DIV")
        {
            root->evaluated_value = UnlimitedRational::div(root->left->evaluated_value, root->right->evaluated_value);
        }
    }
    return;
}

Evaluator::Evaluator()
{
    symtable = new SymbolTable();
}
Evaluator::~Evaluator()
{
    while (expr_trees.empty()==false)
    {
        ExprTreeNode *t = expr_trees.back();
        delete t;
        expr_trees.pop_back();
    }
    //delete symtable;//note our eval function gives the same mem location as in equality evaluated no need to do anything with symtable if handeled evaluated tree;
}
void Evaluator::parse(vector<string> code)
{
    vector<ExprTreeNode *> stack; // we will be pushing at back and popping back only.
    ExprTreeNode *e = new ExprTreeNode(), *lv = new ExprTreeNode();
    e->type = "EQL";
    e->id = code[1];
    lv->type = "VAR";
    lv->id = code[0];
    e->left = lv;
    if (code.size() == 3)
    {
        string t = code[2];
        ExprTreeNode *rgt = Node_creator(t);
        e->right = rgt;
    }
    else
    {
        for (long unsigned int i = 2; i < code.size(); i++)
        {
            string t = code[i];
            if (t != ")")
            {
                stack.push_back(Node_creator(t));
            }
            else
            {
                ExprTreeNode *rgt = stack.back();
                stack.pop_back();
                ExprTreeNode *mid = stack.back();
                stack.pop_back();
                ExprTreeNode *lft = stack.back();
                stack.pop_back();
                stack.pop_back(); // popping the left bracket
                mid->right = rgt;
                mid->left = lft;
                stack.push_back(mid);
            }
        }
        e->right = stack.back();
        stack.pop_back();
    }

    expr_trees.push_back(e);
}
void Evaluator::eval()
{
    Node_solver(expr_trees.back()->right, symtable);
    symtable->insert(expr_trees.back()->left->id, expr_trees.back()->right->evaluated_value);
}