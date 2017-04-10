#if !defined (NULL)
#define NULL 0
#endif

#if !defined (AVLTREE_H)
#define AVLTREE_H

#include "Drawable.h"
#include "AVLTreeIterator.h"
#include "Line.h"

#include <iostream>
using namespace std;

template < class T >
class AVLTree : public Drawable
{
   
   private:
      AVLTreeNode<T>* root;

      bool avlFlag;
      int sz;

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);

      void setRootNode(AVLTreeNode<T>* tNode);  //you can get by without using these methods, refer to root directly
      AVLTreeNode<T>* getRootNode();
      int getHeight(AVLTreeNode<T>* tNode);  //from lab
      int isBalanced(AVLTreeNode<T>* tNode);
      bool checkBalanceFactors(AVLTreeNode<T>* tNode);

      void destroyItem(AVLTreeNode<T>* tNode);
      void destroy();

      AVLTreeNode<T>* insertItem(AVLTreeNode<T>* tNode, T* item);
      //AVLTreeNode<T>* removeItem(AVLTreeNode<T>* tNode, String* searchKey);
      //AVLTreeNode<T>* removeNode(AVLTreeNode<T>* tNode);
      //AVLTreeNode<T>* removeLeftMost(AVLTreeNode<T>* tNode);
      T* findLeftMost(AVLTreeNode<T>* tNode);

      AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* tNode);

      //write and use methods to do each of the four rotations (SR, SL, DLR, DRL)

      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode);
    
      AVLTreeNode<T>* DoubleLeftRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DoubleRightLeft(AVLTreeNode<T>* tNode);
    
      AVLTreeNode<T>* avlFixAddLeft(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* avlFixAddRight(AVLTreeNode<T>* tNode);
      //AVLTreeNode<T>* avlFixRemoveLeft(AVLTreeNode<T>* tNode);
      //AVLTreeNode<T>* avlFixRemoveRight(AVLTreeNode<T>* tNode);
      AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left);  //changes balance factors, calls the other DLR to do two rotations
      AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right);  //changes balance factors, calls the other DRL to do two rotations

      virtual void drawRec(AVLTreeNode<T>* tNode, wxDC&  dc, Line* line, int x_parent, int x_curr, int y_curr);

   public:
      AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
      ~AVLTree();

      int size();
      void insert(T* item);
      //void remove(String* sk);
      T* retrieve(String* sk);

      bool isEmpty();
      void makeEmpty();
      T* getRootItem();
      AVLTreeIterator<T>* iterator();

      int getHeight();
      bool isBalanced();
      bool checkBalanceFactors();

      void draw(wxDC&  dc, int width, int height);
      void mouseClicked(int x, int y);

};

template < class T >
void AVLTree<T>::setRootNode(AVLTreeNode<T>* tNode)
{
    root = tNode;
}

template < class T >
AVLTree<T>::AVLTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
    root = NULL;
    sz = 0;
    avlFlag = false;
    
    compare_items = comp_items;
    compare_keys = comp_keys;
}

template < class T >
AVLTree<T>::~AVLTree()
{
    destroy();
}

template < class T >
void AVLTree<T>::destroy()
{
    destroyItem(root);
}

template < class T >
void AVLTree<T>::destroyItem(AVLTreeNode<T>* tNode)
{
    if(tNode != NULL)
    {
        destroyItem(tNode->getLeft());
        destroyItem(tNode->getRight());
        delete tNode;
    }
}

template < class T >
int AVLTree<T>::size()
{
    return sz;
}

template < class T >
T* AVLTree<T>::retrieve(String* sk)
{
    AVLTreeNode<T>* tNode = getRootNode();
    
    while (tNode != NULL)
    {
        T* item = tNode->getItem();
        int comp = (*compare_keys) (sk, item);
        
        if(comp == 0)
        {
            return item;
        }
        
        else if(comp < 0)
        {
            tNode = tNode->getLeft();
        }
        
        else
        {
            tNode = tNode->getRight();
        }
    }
    
    return NULL;
}

template < class T >
bool AVLTree<T>::isEmpty()
{
    if (sz == 0)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

template < class T >
AVLTreeIterator<T>* AVLTree<T>::iterator()
{
    return new AVLTreeIterator<T>(root);
}

template < class T >
T* AVLTree<T>::getRootItem()
{
    T* item = root->getItem();
    return item;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::getRootNode()
{
    return root;
}

template < class T >
int AVLTree<T>::getHeight()
{
    return getHeight(root);
}

template < class T >
int AVLTree<T>::getHeight(AVLTreeNode<T>* tNode)
{
    if(tNode == NULL)
    {
        return 0;
    }
    
    int leftHeight = getHeight(tNode->getLeft());
    int rightHeight = getHeight(tNode->getRight());
    
    if(leftHeight >= rightHeight)
    {
        return leftHeight + 1;
    }
    
    else
    {
        return rightHeight + 1;
    }
}

template < class T >
bool AVLTree<T>::isBalanced()
{
    return isBalanced(root);
}

template < class T >
int AVLTree<T>::isBalanced(AVLTreeNode<T>* tNode)
{
    if(tNode == NULL)
    {
        return true;
    }
    
    int leftHeight = getHeight(tNode->getLeft());
    int rightHeight = getHeight(tNode->getRight());
    
    if(leftHeight == rightHeight)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

template < class T >
bool AVLTree<T>::checkBalanceFactors()
{
    return checkBalanceFactors(root);
}

template < class T >
bool AVLTree<T>::checkBalanceFactors(AVLTreeNode<T>* tNode)
{
    AVL node_balance = tNode->getBalanceFactor();
    
    if (node_balance == BALANCED || node_balance == LEFT_HEAVY || node_balance == RIGHT_HEAVY)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

template < class T >
void AVLTree<T>::insert(T* item)
{
    root = insertItem(root, item);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::insertItem(AVLTreeNode<T>* tNode, T* item)
{
    if(tNode == NULL)
    {
        sz++;
        avlFlag = true;
        return new AVLTreeNode<T>(item);
    }
    
    T* temp = tNode->getItem();
    int comp = (*compare_items) (item, temp);
    
    if(comp == 0)
    {
        return tNode;
    }
    
    else if(comp < 0)
    {
        tNode->setLeft(insertItem(tNode->getLeft(), item));
        return avlFixAddLeft(tNode);
    }
    
    else
    {
        tNode->setRight(insertItem(tNode->getRight(), item));
        return avlFixAddRight(tNode);
    }
}


template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateLeft(AVLTreeNode<T>* tNode)
{
    AVLTreeNode<T>* right = tNode->getRight();
    AVLTreeNode<T>* right_Left = right->getLeft();
    right->setLeft(tNode);
    tNode->setRight(right_Left);
    
    return right;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::rotateRight(AVLTreeNode<T>* tNode)
{
    AVLTreeNode<T>* left = tNode->getLeft();
    AVLTreeNode<T>* left_Right = left->getRight();
    left->setRight(tNode);
    tNode->setLeft(left_Right);
    
    return left;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::SingleRight(AVLTreeNode<T>* tNode)
{
    AVLTreeNode<T>* left = tNode->getLeft();
    left->setBalanceFactor(BALANCED);
    tNode->setBalanceFactor(BALANCED);
    
    return rotateRight(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::SingleLeft(AVLTreeNode<T>* tNode)
{
    AVLTreeNode<T>* right = tNode->getRight();
    right->setBalanceFactor(BALANCED);
    tNode->setBalanceFactor(BALANCED);
    
    return rotateLeft(tNode);
}

template < class T >
AVLTreeNode<T>* DLR(AVLTreeNode<T>* tNode, AVLTreeNode<T>* left)
{
    return DoubleLeftRight(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DoubleLeftRight(AVLTreeNode<T>* tNode)
{
    AVLTreeNode<T>* left = tNode->getLeft();
    AVLTreeNode<T>* left_Right = left->getRight();
    AVL left_BF = left->getBalanceFactor();
    AVL left_Right_BF = left_Right->getBalanceFactor();
    
    if (left_Right_BF == BALANCED)
    {
        left->setBalanceFactor(BALANCED);
        left_Right->setBalanceFactor(BALANCED);
        tNode->setBalanceFactor(BALANCED);
        
        tNode->setLeft(rotateLeft(left));
        
        return rotateRight(tNode);
    }
    else if (left_Right_BF == LEFT_HEAVY)
    {
        left->setBalanceFactor(BALANCED);
        left_Right->setBalanceFactor(BALANCED);
        tNode->setBalanceFactor(RIGHT_HEAVY);
        
        tNode->setLeft(rotateLeft(left));
        
        return rotateRight(tNode);
    }
    else
    {
        left->setBalanceFactor(LEFT_HEAVY);
        left_Right->setBalanceFactor(BALANCED);
        tNode->setBalanceFactor(BALANCED);
        
        tNode->setLeft(rotateLeft(left));
        
        return rotateRight(tNode);
    }
}

template < class T >
AVLTreeNode<T>* DRL(AVLTreeNode<T>* tNode, AVLTreeNode<T>* right)
{
    return DoubleRightLeft(tNode);
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::DoubleRightLeft(AVLTreeNode<T>* tNode)
{
    AVLTreeNode<T>* right = tNode->getRight();
    AVLTreeNode<T>* right_Left = right->getLeft();
    AVL right_BF = right->getBalanceFactor();
    AVL right_Left_BF = right_Left->getBalanceFactor();
    
    if (right_Left_BF == BALANCED)
    {
        right->setBalanceFactor(BALANCED);
        right_Left->setBalanceFactor(BALANCED);
        tNode->setBalanceFactor(BALANCED);
        
        tNode->setRight(rotateRight(right));
        
        return rotateLeft(tNode);
    }
    else if (right_Left_BF == RIGHT_HEAVY)
    {
        right->setBalanceFactor(BALANCED);
        right_Left->setBalanceFactor(BALANCED);
        tNode->setBalanceFactor(LEFT_HEAVY);
        
        tNode->setRight(rotateRight(right));
        
        return rotateLeft(tNode);
    }
    else
    {
        right->setBalanceFactor(RIGHT_HEAVY);
        right_Left->setBalanceFactor(BALANCED);
        tNode->setBalanceFactor(BALANCED);
        
        tNode->setRight(rotateRight(right));
        
        return rotateLeft(tNode);
    }
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddLeft(AVLTreeNode<T>* tNode)
{
    if (avlFlag)
    {
        tNode->insertLeft();
        AVL BF = tNode->getBalanceFactor();
        
        if (BF == BALANCED)
        {
            avlFlag = false;
        }
        else if (BF == LEFT_UNBALANCED)
        {
            AVLTreeNode<T>* left= tNode->getLeft();
            AVL left_BF = left->getBalanceFactor();
            
            if (left_BF == LEFT_HEAVY)
            {
                avlFlag = false;
                return SingleRight(tNode);
            }
            else
            {
                avlFlag = false;
                return DLR(tNode, tNode->getLeft());
            }
        }
    }
    
    return tNode;
}

template < class T >
AVLTreeNode<T>* AVLTree<T>::avlFixAddRight(AVLTreeNode<T>* tNode)
{
    if (avlFlag)
    {
        tNode->insertRight();
        AVL BF = tNode->getBalanceFactor();
        
        if (BF == BALANCED)
        {
            avlFlag = false;
        }
        else if (BF == RIGHT_UNBALANCED)
        {
            AVLTreeNode<T>* right = tNode->getRight();
            AVL right_BF = right->getBalanceFactor();
            
            if (right_BF == RIGHT_HEAVY)
            {
                avlFlag = false;
                return SingleLeft(tNode);
            }
            else
            {
                avlFlag = false;
                return DRL(tNode, tNode->getRight());
            }
        }
    }
    
    return tNode;
}

//the below methods have been completed for you

template < class T >
void AVLTree<T>::draw(wxDC&  dc, int width, int height)
{
	Line line(new Color(0, 0, 0), 5.0);
	drawRec(getRootNode(), dc, &line, width, width/2, 20);
}

template < class T >
void AVLTree<T>::drawRec(AVLTreeNode<T>* tNode, wxDC& dc, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(dc, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), dc, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), dc, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(dc, x_curr, y_curr);
   }
}

template < class T >
void AVLTree<T>::mouseClicked(int x, int y) {}

#endif
