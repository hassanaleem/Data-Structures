#ifndef __AVL_CPP
#define __AVL_CPP

#include <iostream>
#include <memory>
#include "avl.hpp"

// Constructor
template <class T, class S>
AVL<T,S>::AVL(bool isAVL){
	this->root = NULL;
    this->isAVL = isAVL;
}

// This function inserts a given node in the tree
template <class T, class S>
void AVL<T,S> :: insertNode(shared_ptr<node<T,S>> newNode){
    // if(!root)
    // {
    //     root = newNode;
    // }

    // else
    // {
    //     shared_ptr<node<T,S>> temp = root;

    //     while(temp)
    //     {
    //         if(newNode->key > temp->key)
    //         {
    //             if(!(temp->right))
    //             {
    //                 break;
    //             }
    //             temp = temp->right;
    //         }

    //         else
    //         {
    //             if(!(temp->left))
    //             {
    //                 break;
    //             }
    //             temp = temp->left;
    //         }
    //     }

    //     if(newNode->key > temp->key)
    //     {
    //         temp->right = newNode;
    //     }
    //     else
    //     {
    //         temp-> left = newNode;
    //     }
        
    // }
    // if(isAVL)
    // {
    //     balance(newNode);
    // }

    if(!root)
    {
        root = newNode;
    }
    else
        root = insertNodeHelper(root, newNode);
    
}

template <class T, class S>
shared_ptr<node<T,S>>  AVL<T,S> :: insertNodeHelper(shared_ptr<node<T,S>> temp, shared_ptr<node<T,S>> newNode)
{

    if(temp == NULL)
    {
        temp = newNode;
    }

    else if(newNode->key < temp->key)
    {
        temp->left = insertNodeHelper(temp->left, newNode);
    }

    else
    {
        temp->right = insertNodeHelper(temp->right, newNode);
    }

    if(isAVL)
    {
        return balance(temp);
    }

    return temp;
    

}


template <class T, class S>
int AVL<T, S> :: balanceFactor(shared_ptr<node<T,S>> currNode)
{
    int factor = 0;
    if(currNode)
    {
        factor = height(currNode->left)-height(currNode->right);
    }
    return factor;
}
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: rotateLeft(shared_ptr<node<T,S>> currNode)
{
    shared_ptr<node<T,S>> temp = currNode->right;
    currNode->right = temp->left;
    temp->left = currNode;  
    currNode = temp;
    currNode->height = height(currNode);
    temp->height = height(temp);
    return currNode;

}

template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> ::rotateRight(shared_ptr<node<T,S>> currNode)
{
    shared_ptr<node<T,S>> temp = currNode->left;
    currNode->left = temp->right; 
    temp->right = currNode; 
    currNode = temp;
    currNode->height = height(currNode);
    temp->height = height(temp);
    return temp;
}

template <class T, class S>
shared_ptr<node<T,S>>  AVL <T, S>:: balance(shared_ptr<node<T,S>> currNode){    
    if(currNode)
    {
        currNode->height = height(currNode);
    }    

    int bFactor = balanceFactor(currNode);

    // Left Heavy
    if(bFactor >= 2)
    {
        int leftBalanceFactor = balanceFactor(currNode->left);

        if(leftBalanceFactor < 0)
        {
            currNode->left = rotateLeft(currNode->left);
            currNode = rotateRight(currNode);
        }
        if(leftBalanceFactor >= 0)
        {
            currNode = rotateRight(currNode);
        } 
        
    }
    else if(bFactor <= -2)
    {
        int rightBalanceFactor = balanceFactor(currNode->right);
        if(rightBalanceFactor > 0)
        {
            currNode->right = rotateRight(currNode->right);
            currNode = rotateLeft(currNode);
        }
        
        if(rightBalanceFactor < 0)
        {
            currNode= rotateLeft(currNode);
        } 
        
    }
    
    return currNode;
}


// This function searches a node in a tree by its key
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S> :: searchNode(T k){
    shared_ptr<node<T,S>> temp = root;
    while(temp)
    {
        if(k == temp->key)
        {
            return temp;
        }

        if(k > temp->key)
        {
            temp = temp->right;
        }

        else
        {
            temp = temp->left; 
        }
    }
    return NULL;
}

template<class T, class S>
shared_ptr<node<T,S>> AVL<T,S>::removeMin(shared_ptr<node<T,S>> p)
{
    if(p == NULL)
    {
        return NULL;
    }
    else if(p->left == NULL)
    {
        //delete p;
        return p->right;
    }
    else 
    {
        p->left = removeMin(p->left);
    }
    return balance(p);
}

//deletes root recursively
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S>::deleteNodeHelper(shared_ptr<node<T,S>> currNode,T k){
        if(!currNode)
        {
            return NULL;
        }
        if(k < currNode->key)
        {
            currNode->left = deleteNodeHelper(currNode->left, k);
        }
        else
        {
            currNode->right = deleteNodeHelper(currNode->right, k);
        }

        if(k == currNode->key)
        {
            // No Child
            if(!currNode->left && !currNode->right)
            {
                currNode = NULL;
                return currNode;
            }
            // One Child
            if (!currNode->left )
            {
                shared_ptr<node<T,S>> temp; 
                temp = currNode->right;
                return temp;
                
            }

            if(!currNode->right)
            {
                shared_ptr<node<T,S>> temp; 
                temp = currNode->left;
                return temp;
            }
   
            // Two Children
            else
            {
                shared_ptr<node<T,S>> min = currNode->right;
                while(min->left) 
                {
                    min = min->left;
                }
                currNode->key = min->key;
                currNode->value = min->value;
                currNode->right = removeMin(currNode->right);
                currNode->height = height(currNode);
            }
        }
        if(isAVL)
            return balance(currNode);
        
        return currNode;
}

// This function deletes a given node from the tree
template <class T, class S>
void AVL<T,S>::deleteNode(T k){
   root = deleteNodeHelper(root, k);
}

// This function returns the root of the tree
template <class T, class S>
shared_ptr<node<T,S>> AVL<T,S>::getRoot(){
    return root;
}

// This function calculates and returns the height of the tree
template <class T, class S>
int AVL<T,S> :: height (shared_ptr<node<T,S>> p){

    if (!p)
    {
        return 0;  

    }  
    else if(p)
    {  
        int left = height(p->left) + 1;  
        int right = height(p->right) + 1;  
      
        if (right > left)
        {
            return(right);  

        } 
        else if(left >= right)
        {
            return(left);  
        }
    }  

    return 0;
}

#endif