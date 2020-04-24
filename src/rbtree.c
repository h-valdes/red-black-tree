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
            tempNode->parent_node = pNode;
            pNode->parent_node = y; 
        } else {
            printf("LEFT ROTATE: rotation not possible\n");
        }
    }
}

void RBT_right_rotate(Node_t *pNode) {
    if(pNode != NULL) {
        // For right rotation check that left child
        Node_t *y = pNode->left_node;
        if(y != NULL) {
            Node_t *tempNode = NULL;
            if(y->right_node != NULL) {
                tempNode = y->right_node;
            }
            y->parent_node = RBT_get_parent(pNode);
            pNode->left_node = tempNode;
            tempNode->parent_node = pNode;
            pNode->parent_node = y;
        } else {
            printf("RIGHT ROTATE: rotation not possible\n");
        }
    }
}

_Bool RBT_insert_node(RBT_t *pRBT, int key) {
    if(pRBT != NULL) {
        printf("Start inserting: %d\n", key);
        Node_t * z;
        z = (Node_t *) malloc(sizeof(Node_t));
        z->key = key;
        z->color = RED;
        z->left_node = NULL;
        z->right_node = NULL;
        z->parent_node = NULL;
        // In case there are no root, set first node as root
        if(pRBT->root_node == NULL) {
            z->color = BLACK;
            pRBT->root_node = z;
        } else {
            // Root already exists
            printf("Insert not root\n");
            Node_t *x = pRBT->root_node;
            Node_t *y = NULL;
            while( x != NULL) {
                y = x;
                if(z->key < x->key) {
                    x = x->left_node;
                } else {
                    x = x->right_node;
                }
            }
            z->parent_node = y;
            if(y == NULL) {
                pRBT->root_node = z;
            } else {
                if(z->key < y->key) {
                    y->left_node = z;
                } else {
                    y->right_node = z;
                }
            }
            z->left_node = NULL;
            z->right_node = NULL;
            z->color = RED;
            RBT_insert_fixup(pRBT, z);
        }
        printf("End insert node with key: %d\n", key);
    }
    return 0;
}

_Bool RBT_insert_fixup(RBT_t *pRBT, Node_t *z) {
    _Bool status = 0;
    if(z != NULL) {
        printf("Start fixup on key: %d\n", z->key);
        Node_t *zParent = RBT_get_parent(z);
        while(zParent->color == RED) {
            Node_t *zGrandParent = RBT_get_grandparent(z);
            if(zParent == zGrandParent->left_node) {
                Node_t *y = zGrandParent->right_node;
                if(y->color == RED) {
                    // Case 1
                    printf("INSERT FIXUP: Case 1\n");
                    zParent->color = BLACK;
                    y->color = BLACK;
                    zGrandParent->color = RED;
                    z = zGrandParent;
                } else if(z == zParent->right_node) {
                    // Case 2
                    printf("INSERT FIXUP: Case 2\n");
                    z = zParent;
                    RBT_left_rotate(z);
                } else {
                    // Case 3
                    printf("INSERT FIXUP: Case 3\n");
                    zParent = RBT_get_parent(z);// New z's parent
                    zGrandParent = RBT_get_grandparent(z); // New z's grandparent
                    zParent->color = BLACK;
                    zGrandParent->color = RED;
                    RBT_right_rotate(zGrandParent);
                }
            }
        }
    }
    return status;
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