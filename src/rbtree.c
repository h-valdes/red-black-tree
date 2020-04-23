#include "rbtree.h"

#include <string.h>
#include <stdlib.h>

RBT_t *RBT_new_tree() {
    RBT_t *pRBT = NULL;
    pRBT = malloc(sizeof(RBT_t));
    if (pRBT != NULL) {
        pRBT->root_node = NULL;
    }
    return pRBT;
}

Node_t *RBT_get_parent(Node_t *pNode) {
    Node_t *pParent;
    if (pNode != NULL) {
        pParent = pNode->parent_node;
        if (pParent == NULL) {
            pParent = NULL;
            printf("There is no parent\n");
        }
    } else {
        printf("GET PARENT: Node is NULL\n");
    }
    return pParent;
}

Node_t *RBT_get_grandparent(Node_t *pNode) {
    Node_t *pGrandparent;
    if (pNode != NULL) {
        Node_t *pParent = RBT_get_parent(pNode);
        if (pParent != NULL) {
            pGrandparent = RBT_get_parent(pParent);
            if (pGrandparent == NULL) {
                printf("There is no grand parent\n");
            }
        }
    } else {
        printf("GET GRANDPARENT: Node is NULL\n");
    }
    return pGrandparent;
}

Node_t *RBT_get_sibling(Node_t *pNode) {
    Node_t *pSibling;
    if(pNode != NULL) {
        Node_t *pParent = RBT_get_parent(pNode);
        if(pParent != NULL) {
            Node_t *leftNode;
            Node_t *rightNode;
            leftNode = pParent->left_node;
            rightNode = pParent->right_node;
            if(leftNode != NULL && leftNode != pParent){
                pSibling = leftNode;
            } else if(rightNode != NULL && rightNode != pParent) {
                pSibling = rightNode;
            } else {
                pSibling = NULL;
            }
        }
    }
    return pSibling;
}

Node_t *RBT_get_uncle(Node_t *pNode) {
    Node_t *pUncle;
    if (pNode != NULL) {
        Node_t *pParent = RBT_get_parent(pNode);
        if(pParent != NULL) {
            pUncle = RBT_get_sibling(pParent);
            if(pUncle == NULL) {
                printf("There is no uncle\n");
            }
        }
    } else {
        printf("GET UNCLE: Node is NULL\n");
    }
    return pUncle;
}

void RBT_left_rotate(Node_t *pNode) {
    if(pNode != NULL) {
        // For left rotation check that right child is not NULL
        Node_t *y = pNode->right_node; 
        if(y != NULL) {
            Node_t *tempNode = NULL;
            if(y->left_node != NULL) {
                tempNode = y->left_node;
            }
            y->parent_node = RBT_get_parent(pNode);
            pNode->right_node = tempNode;
            pNode->parent_node = y; 
        } else {
            printf("LEFT ROTATE: rotation not possible\n");
        }
    }
}

_Bool RBT_insert_node(RBT_t *pRBT, int key) {
    if(pRBT != NULL) {
        Node_t * pNewNode;
        pNewNode = (Node_t *) malloc(sizeof(Node_t));
        pNewNode->key = key;
        pNewNode->color = RED;
        pNewNode->left_node = NULL;
        pNewNode->right_node = NULL;
        pNewNode->parent_node = NULL;
        if(pRBT->root_node == NULL) {
            pRBT->root_node = pNewNode;
        } else {
            printf("There is already a root node!\n");
        }
    }
    return 0;
}

void RBT_clear(Node_t *pNode) {
    if (pNode != NULL) {
        Node_t *leftNode = pNode->left_node;
        Node_t *rightNode = pNode->right_node;
        if (leftNode == NULL && rightNode == NULL) {
            free(pNode);
        } else {
            if(leftNode != NULL) {
                RBT_clear(leftNode);
            }
            if(rightNode != NULL) {
                RBT_clear(rightNode);
            }
        }
    }
}

void RBT_clear_tree(RBT_t *pRBT) {
    if(pRBT->root_node != NULL) {
        RBT_clear(pRBT->root_node);
    }
    free(pRBT);
}

void RBT_print_node(Node_t *pNode) {
    if(pNode != NULL) {
        char trueFlag[5] = "True";
        char falseFlag[6] = "False";

        // Assign the color into a string
        char color[5];
        if(pNode->color == RED) {
            strcpy(color, "RED");
        } else if(pNode->color == BLACK) {
            strcpy(color, "BLACK");
        }

        // Assign the root flag
        char isRoot[6];
        Node_t *pParent = RBT_get_parent(pNode);
        if(pParent == NULL) {
            strcpy(isRoot, trueFlag);
        } else {
            strcpy(isRoot, falseFlag);
        }

        // Assign the sibling flag
        char hasSibling[6];
        Node_t *pSibling = RBT_get_sibling(pNode);
        if(pParent != NULL) {
            strcpy(hasSibling, trueFlag);
        } else {
            strcpy(hasSibling, falseFlag);
        }

        // Assign left node flag
        char hasLeftNode[6];
        if(pNode->left_node != NULL) {
            strcpy(hasLeftNode, trueFlag);
        } else {
            strcpy(hasLeftNode, falseFlag);
        }

        // Assign right node flag
        char hasRightNode[6];
        if(pNode->right_node != NULL) {
            strcpy(hasRightNode, trueFlag);
        } else {
            strcpy(hasRightNode, falseFlag);
        }

        printf("-- Node information -- \n");
        printf("key: %d\n", pNode->key);
        printf("color: %s\n", color);
        printf("Is a root node?: %s\n", isRoot);
        printf("Has sibling?: %s\n", hasSibling);
        printf("Has a left node?: %s\n", hasLeftNode);
        printf("Has a right node?: %s\n", hasRightNode);
    }
}