#pragma once

#include <iostream>
#include <algorithm>

template<class T>
class AVL {

struct node {
    T value;
    int height;

    struct node* left;
    struct node* right;

    node(T v) : value(v), left(NULL), right(NULL), height(1) {}
};

private:
    struct node* root = NULL;

public:
    int getHeight(struct node* node) {
        if(node ==  NULL) return 0;

        return node->height;
    }

    int getBalance(struct node* node) {
        if(node == NULL) return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    struct node* leftRotate(struct node* node) {
        struct node* right_node = node->right;

        node->right = right_node->left;
        right_node->left = node;

        node->height = std::max(getHeight(node->left),   
                    getHeight(node->right)) + 1;

        right_node->height = std::max(getHeight(right_node->left),
                    getHeight(right_node->right)) + 1;

        return right_node;
    }

    struct node* rightRotate(struct node* node) {
        struct node* left_node = node->left;

        node->left = left_node->right;
        left_node->right = node;

        node->height = std::max(getHeight(node->left),   
                    getHeight(node->right)) + 1;

        left_node->height = std::max(getHeight(left_node->left),
                    getHeight(left_node->right)) + 1;

        return left_node;
    }

    void printLeftOrder() {
        printLeft(root);
    }

    void printLeft(struct node* node) {
        if(node == NULL) return;

        printLeft(node->left);
        std::cout << node->value << std::endl;
        printLeft(node->right);
    }
    
    void insertNode(T value) {
        std::cout << "Inserting " << value << "..." << std::endl; 
        root = insert(root, value);

        std::cout <<"Correctly inserted." << std::endl;
    }

    struct node* getLeftMost(struct node* node) {
        struct node* current = node;

        while(current != NULL) current = node->left;
        return current;
    }

    struct node* getRightMost(struct node* node) {
        struct node* current = node;

        while(current != NULL) current = node->right;
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

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        return balanceTree(node, value);
    }

    struct node* balanceTree(struct node* node, T value) {
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

    void removeNode(T value) {
        root = remove(root, value);
    }

    struct node* remove(struct node* node, T value) {
        if(node == NULL) return node;

        if(value < node-> value) {
            remove(node->left, value);
        }
        else if( value > node->value) {
            remove(node->right, value);
        }
        else { // value found
            if( (node->left == NULL) ||
                (node->right == NULL) ) {
                struct node* temp = node->left ?
                            node->left :
                            node->right;
    
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                }
                else // One child case
                    *node = *temp; // Copy the contents of
                            // the non-empty child
                free(temp);
            }
            else {
                struct node* temp = getLeftMost(root->right);

                node->value = node->value;
                node->right = remove(node->right, temp->value);
            }
        }

        if(node == NULL) return node;
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        
        return balanceTree(node, value);
    }
};