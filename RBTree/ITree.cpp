#include "ITree.h"


namespace
{
    static bool compLT(const ClassData& a ,const ClassData& b)
    {
        return a < b;
    }

    static bool compEQ(const ClassData& a , const ClassData& b)
    {
        return a > b;
    }
}

INode_::INode_(ClassData *_data, INode_ *_left, INode_ *_right)
 : parent(nullptr)
{
    data = _data;
    left = _left;
    right =_right;
    color = RED;
    size = 1;

    if (left)  size += left->size;
    if (right) size += right->size;

}

INode_::INode_(ClassData *_data, INode_ *_left, INode_ *_right, INode_ *_parent)
: INode_( _data, _left , _right )
{
    parent = _parent;
}

INode_ *INode_::select(unsigned int rank, INode_ *nil)
{
       if (rank > size)
       {
           return nil;
       }

       unsigned int r_rank = left->size + 1;
       if (rank == r_rank)
       {
           return this;
       }
       else
       {
           if (rank < r_rank)
           {
               return this->left->select(rank, nil);
           }
           else
           {
               return this->right->select(rank - r_rank, nil);
           }
       }
}



//------------------------------------------------------------------//

ITree::ITree()
{
    
    // All the leaves of the tree are "guard"
     //(NIL), which greatly simplifies the codes
   
    NIL = new INode_(new ClassData("",0), nullptr, nullptr);
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->color = BLACK;
    NIL->size = 0;
    mRoot = NIL;
}

INode_ *ITree::Add(ClassData *data)
{
    
    //new node for data and insert in tree 
   

    // find where node belongs 
    INode_ *current = mRoot;
    INode_ *parent = nullptr;


    /// Find parent
    while (current != NIL)
    {
        if (compEQ(*data, *current->data))
        {
            return (current);
        }

        parent = current;
        current = compLT(*data, *current->data) ? current->left : current->right;

    }

    
    // @brief new_node
    // Memory allocation for a new node in the tree
    
    INode_ *new_node = new INode_(data , NIL , NIL , parent);

    if(parent)
    {
        new_node->size += parent->size;
    }

    // insert node in tree 
    if(parent)
    {
        if(compLT(*data, *parent->data))
        {
            parent->left = new_node;
        }
        else
        {
            parent->right = new_node;
        }
    }
    else
    {
        mRoot = new_node;
    }

    InsertFixup(new_node);
    return(new_node);
}

void ITree::Remove(INode_ *node)
{
    INode_ *x, *y;

   
    // delete node from tree 
   

    if (!node || node == NIL) return;


    if (node->left == NIL || node->right == NIL)
    {
        // y has a NIL node as a child
        y = node;
    }
    else
    {
        // find tree successor with a NIL node as a child 
        y = node->right;
        while (y->left != NIL) y = y->left;
    }

    // x is y's only child 
    if (y->left != NIL)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }

    // remove y from the parent chain
    x->parent = y->parent;
    if (y->parent)
    {
        if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
    }
    else
    {
        mRoot = x;
    }

    if (y != node)
    {
        node->data = y->data;
    }


    if (y->color == BLACK)
    {
        DeleteFixup(x);
    }

    /// Delete Node . Clear memory
    delete y;
    y= nullptr;
}


unsigned int ITree::Rank(INode_ *node)
{
    unsigned int res = node->left->size + 1;
    INode_* cur = node;
    while (cur != this->mRoot)
    {
        if (cur == cur->parent->right)
        {
            res += cur->parent->left->size + 1;
        }
        cur = cur->parent;
    }
    return res;
}




INode_ *ITree::Find(ClassData *data)
{
   
    //find node containing data  
    
    INode_ *current = mRoot;
    while(current != NIL)
    {
        if(compEQ(*data, *(current->data)))
        {
            return (current);
        }
        else
        {
            current = compLT (*data, *(current->data)) ?  current->left : current->right;
        }
    }

    cout<< "Not Found Node \n";
    return nullptr;
}

void ITree::Print( bool isAdditionalInformation )
{
    if(mRoot)
    {
        PrintResursiv("" , mRoot , false , isAdditionalInformation );
    }
    else
    {
        cout<< "Not is elemnts" << std::endl;
    }
}

void ITree::PrintResursiv(const string &prefix, const INode_ *node, bool isLeft ,bool isAdditionalInformation)
{
    if( node != NIL )
    {
        cout << prefix;
        cout <<  "└──";
        cout << node->data->mPriority;

        if(node->color == NodeColor::RED)
        {
            cout << "-(RED)-";
        }
        else if(node->color == NodeColor::BLACK)
        {
            cout << "-(BLACK)-";
        }

        cout << node->data->mName << "-";
        if(isAdditionalInformation) node->data->Print();
        cout << endl;;

        // enter the next tree level - left and right branch
        PrintResursiv( prefix + (isLeft ? "│   " : "    "), node->left, true  , isAdditionalInformation);
        PrintResursiv( prefix + (isLeft ? "│   " : "    "), node->right, false , isAdditionalInformation);
    }
}



//------------- Private Function -------------//

void ITree::RotateLeft(INode_ *x)
{
    INode_* y = x->right;

    /* establish x->right link */
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;

    /* establish y->parent link */
    if (y != NIL) y->parent = x->parent;
    if (x->parent)
    {
        if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
    }
    else
    {
        mRoot = y;
    }

    /* link x and y */
    y->left = x;
    if (x != NIL)
    {
        x->parent = y;
    }
}



void ITree::RotateRight(INode_ *x)
{
 
    // rotate node x to right  
    
    INode_ *y = x->left;

    // establish x->left link
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;

    // establish y->parent link 
    if (y != NIL) y->parent = x->parent;
    if (x->parent)
    {
        if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
    }
    else
    {
        mRoot = y;
    }

    // link x and y
    y->right = x;
    if (x != NIL) x->parent = y;
}



void ITree::InsertFixup(INode_ *x)
{
    
    //  maintain Red-Black tree balance  
    // after inserting node x           
   

    //check Red-Black properties
    while (x != mRoot && x->parent->color == RED)
    {
        //we have a violation
        if (x->parent == x->parent->parent->left)
        {
            INode_ *y = x->parent->parent->right;
            if (y->color == RED)
            {

                // uncle is RED 
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {

                // uncle is BLACK 
                if (x == x->parent->right)
                {
                    //make x a left child 
                    x = x->parent;
                    RotateLeft(x);
                }

                //recolor and rotate 
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                RotateRight(x->parent->parent);
            }
        }
        else
        {

            // mirror image of above code 
            INode_ *y = x->parent->parent->left;
            if (y->color == RED)
            {
                //uncle is RED
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {

                //uncle is BLACK
                if (x == x->parent->left)
                {
                    x = x->parent;
                    RotateRight(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                RotateLeft(x->parent->parent);
            }
        }
    }
    mRoot->color = BLACK;
}

void ITree::DeleteFixup(INode_ *x)
{
    
    // maintain Red-Black tree balance  
    //  after deleting node x           
     

    while (x != mRoot && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            INode_ *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                RotateLeft(x->parent);
                x = mRoot;
            }
        }
        else
        {
            INode_ *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    RotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RotateRight(x->parent);
                x = mRoot;
            }
        }
    }
    x->color = BLACK;
}







