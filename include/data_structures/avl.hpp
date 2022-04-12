#pragma once

#include <iostream>
#include <algorithm>

template<class T>
class AVL {

protected:
    struct node {
        T value;
        int height;

        struct node* left;
        struct node* right;

        node(T v) : value(v), left(NULL), right(NULL), height(1) {}
    };
    struct node* root = NULL;
public:

    int size() {
        if(root == NULL) return 0;
        return root->height;
    }

    int getHeight(struct node* node) {
        if(node ==  NULL) return 0;

        return node->height;
    }

    int getBalance(struct node* node) {
        if(node == NULL) return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    struct node* leftRotate(struct node* node) {

        struct node* to_swap = node->right;
        struct node* to_swap_left = to_swap->left;

        to_swap->left = node;
        node->right = to_swap_left;
        
        node->height = std::max(getHeight(node->left),   
                    getHeight(node->right)) + 1;

        to_swap->height = std::max(getHeight(to_swap->left),
                    getHeight(to_swap->right)) + 1;

        return to_swap;
    }

    struct node* rightRotate(struct node* node) {

        struct node* to_swap = node->left;
        struct node* to_swap_right = to_swap->right;

        to_swap->right = node;
        node->left = to_swap_right;

        node->height = std::max(getHeight(node->left),   
                    getHeight(node->right)) + 1;

        to_swap->height = std::max(getHeight(to_swap->left),
                    getHeight(to_swap->right)) + 1;

        return to_swap;
    }

    void printInOrder() {
        print(root);
    }

    void print(struct node* node) {
        if(node == NULL) return;

        print(node->left);
        std::cout << node->value << std::endl;
        print(node->right);
    }
    
    void insertNode(T value) {
        root = insert(root, value);
    }

    T getLeftMostValue() {
        struct node* current = root;
  
        while(current->left != NULL) {
            current = current->left;
        }

        return current->value;
    }

    void toArray(std::vector<T>* res) {
        toArrayNode(root, res);
    }   

    void toArrayNode(struct node* node, std::vector<T>* res) {
        if(node == NULL) return;

        toArrayNode(node->left, res);
        res->push_back(node->value);
        toArrayNode(node->right, res);
    }

    T getRightMostValue() {
        struct node* current = root;

        while(current->right != NULL) {
            current = current->right;
        } 
        return current->value;
    }

    struct node* getLeftMost(struct node* node) {
        struct node* current = node;
  
        while(current->left != NULL) {
            current = current->left;
        }

        return current;
    }

    struct node* getRightMost(struct node* node) {
        struct node* current = node;

        while(current->right != NULL) {
            current = current->right;
        } 
        return current;
    }

    struct node* insert(struct node* node, T value) {
        if(node == NULL) return new struct node(value);
        
        if(value < node->value) {
            node->left = insert(node->left, value);
        }
        else if(value > node->value) {
            node->right = insert(node->right, value);
        }
        else {
            return node;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && value < node->left->value)
            return rightRotate(node);
    
        // Right Right Case
        if (balance < -1 && value > node->right->value)
            return leftRotate(node);
    
        // Left Right Case
        if (balance > 1 && value > node->left->value) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    
        // Right Left Case
        if (balance < -1 && value < node->right->value) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }


    T pop() {
        T to_pop = getLeftMost(root)->value;
        removeNode(to_pop);
        return to_pop;
    }

    void removeNode(T value) {
        root = remove(root, value);
    }

    struct node* remove(struct node* node, T value) {
        if(node == NULL) return node;

        if(value < node->value) {
            node->left = remove(node->left, value);
        }
        else if( value > node->value) {
            node->right = remove(node->right, value);
        }
        else { // value found
            if( (node->left == NULL) || (node->right == NULL) ) {
                struct node* temp = node->left ?
                            node->left :
                            node->right;
    
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                }
                else *node = *temp;

                free(temp);
            }
            else {
                struct node* temp = getLeftMost(root->right);

                node->value = temp->value;
                node->right = remove(node->right, temp->value);
            }
        }

        if(node == NULL) return node;
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        
        int balance = getBalance(node);
 
        // Left Left Case
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        // Left Right Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        // Right Left Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
};