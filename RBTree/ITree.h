#ifndef ITREE_H
#define ITREE_H

/* red-black tree */
#include <string>
#include <iostream>

using namespace std;


struct ClassData
{
   /// container data ///
    string mName;
    double mPriority;

    /// Constructor
    ClassData(string _name = "" , int _priority = 0)
    : mName(_name) ,
      mPriority(_priority)
    {

    }

    /// Destructor
    virtual ~ClassData(){}

    /**
    * @brief operator <
    * @param rhs
    * @return
    * This comparison operator should be modified
    * to match the data stored in the tree nodes.
    */
    virtual bool operator <( const ClassData &rhs ) const
    {
        return mPriority < rhs.mPriority;
    }

    /**
    * @brief operator ==
    * @param rhs
    * @return
    * This comparison operator should be modified
    * to match the data stored in the tree nodes.
    */
    virtual bool operator > (const ClassData &rhs) const
    {
        return mPriority == rhs.mPriority;
    }

    /**
    * @brief Print
    * function of additional
    * information output in node object .
    * It must be return in the class of children
    */
    virtual void Print() const {}
};




/* Red-Black tree description */
typedef enum { BLACK, RED } NodeColor;

struct INode_
{
    /**
    *  Each node of type Node contains pointers to the left,
    *  to the right of two children, and a parent to an ancestor.
    */


    INode_ *left;         /* left child */
    INode_ *right;        /* right child */
    INode_ *parent;       /* parent */

    NodeColor color;      /* node color (BLACK, RED) */
    unsigned int size;    /* detph pen node */

    ClassData *data;           /* data stored in node */

    INode_(ClassData *_data, INode_* _left, INode_* _right);
    INode_(ClassData *_data, INode_* _left, INode_* _right, INode_* _parent);

    /**
    * @brief select
    * @param rank
    * @param nil
    * @return select node by rank in the tree
    */
    INode_* select(unsigned int rank, INode_* nil = nullptr);

};


class ITree
{

 private:

    INode_* NIL; /// sentinel initilization
    INode_* mRoot; ///tree root

    //-----------------------------------------//

    /**
    * @brief RotateLeft
    * @param x
    * turns the hierarchy of the current
    *  node to the left for the parent
    */
    void RotateLeft(INode_* x);

    /**
    * @brief RotateRight
    * @param x
    * turns the hierarchy of the current
    * node to the right for the parent
    */
    void RotateRight(INode_ *x);

    /**
    * @brief InsertFixup
    * @param x-node
    * The insertNode function requests memory for a new node,
    * sets the required values ​​for its fields,
    * and inserts it into the tree. Accordingly,
    *  it calls insertFixup,
    * which monitors the preservation of red-black properties.
    **/
    void InsertFixup(INode_ *x);

    /**
    * @brief DeleteFixup
    * @param x-node
    * The deleteNode function removes a node from the tree.
    * It calls deleteFixup,
    *  which restores red-black properties.
    */
    void DeleteFixup(INode_ *x);



 public :

    /// Constructor class tree
    ITree();

    //-----------------------------------------//

    /**
    * @brief Add
    * @param data
    * @return node
    * The Add(..) function requests memory for a new node,
    * sets the required values ​​for its fields, and inserts it into the tree.
    * Accordingly, it calls insertFixup,
    * which monitors the preservation of the red-black properties.
    */
    INode_ *Add(ClassData *data);


    /**
    * @brief Find
    * @param data
    * @return searches for the desired node in the tree.
    */
    INode_ *Find(ClassData *data);


    //-----------------------------------------//

    /**
    * @brief Remove
    * @param node
    * The Remove(..) function removes a node from the tree.
    * It calls DeleteFixup, which restores red-black properties.
    */
    void Remove(INode_ *node);

    //-----------------------------------------//

    /**
    * @brief Rank
    * @param node
    * @return
    * this function returns the rank
    * of the node to the tree
    */
    unsigned int Rank(INode_* node);

    //-----------------------------------------//

    /**
    * @brief GetRoot
    * @return  a pointer to but the root node of the tree
    */
    INode_ *GetRoot() const
    {
        return mRoot;
    }

    /**
    * @brief Print
    * @param isAdditionalInformation - output information about the node
    *
    */
    void Print( bool isAdditionalInformation = false);

    /**
    * @brief PrintResursiv
    * @param prefix
    * @param node
    * @param isLeft
    * @param isAdditionalInformation - output information about the node
    * displaying the hierarchy table to the console
    */
    void PrintResursiv(const std::string& prefix, const INode_* node, bool isLeft = false , bool isAdditionalInformation = false);



};

#endif // ITREE_H
