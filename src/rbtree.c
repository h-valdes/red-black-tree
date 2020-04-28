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

Node_t *RBT_get_parent(RBT_t *pRBT, Node_t *pNode) {
    Node_t *pParent;
    if (pNode != NULL) {
        pParent = pNode->parent_node;
        if (pParent == NULL) {
            pParent = NULL;
        }
    } else {
        printf("GET PARENT: Node is NULL\n");
    }
    return pParent;
}

Node_t *RBT_get_grandparent(RBT_t *pRBT, Node_t *pNode) {
    Node_t *pGrandparent;
    if (pNode != NULL) {
        Node_t *pParent = RBT_get_parent(pRBT, pNode);
        if (pParent != NULL) {
            pGrandparent = RBT_get_parent(pRBT, pParent);
        }
    } else {
        printf("GET GRANDPARENT: Node is NULL\n");
    }
    return pGrandparent;
}

Node_t *RBT_get_sibling(RBT_t *pRBT, Node_t *pNode) {
    Node_t *pSibling;
    if(pNode != NULL) {
        Node_t *pParent = RBT_get_parent(pRBT, pNode);
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

Node_t *RBT_get_uncle(RBT_t *pRBT, Node_t *pNode) {
    Node_t *pUncle;
    if (pNode != NULL) {
        Node_t *pParent = RBT_get_parent(pRBT, pNode);
        if(pParent != NULL) {
            pUncle = RBT_get_sibling(pRBT, pParent);
        }
    } else {
        printf("GET UNCLE: Node is NULL\n");
    }
    return pUncle;
}

void RBT_left_rotate(RBT_t *pRBT, Node_t *x) {
    if(x != NULL) {
        printf("Left rotate\n");
        // For left rotation check that right child is not NULL
        Node_t *y = x->right_node;
        x->right_node = y->left_node;
        if(y->left_node != NULL) {
            y->left_node->parent_node = x;
        }
        y->parent_node = x->parent_node;
        if( x->parent_node == NULL) {
            pRBT->root_node = y;
        } else if(x == x->parent_node->left_node) {
            x->parent_node->left_node = y;
        } else {
            x->parent_node->right_node = y;
        }
        y->left_node = x;
        x->parent_node = y;
    }
}

void RBT_right_rotate(RBT_t *pRBT, Node_t *x) {
    if(x != NULL) {
        // For left rotation check that right child is not NULL
        printf("Right rotate\n");
        Node_t *y = x->left_node;
        x->left_node = y->right_node;
        if(y->right_node != NULL) {
            y->right_node->parent_node = x;
        }
        y->parent_node = x->parent_node;
        if( x->parent_node == NULL) {
            pRBT->root_node = y;
        } else if(x == x->parent_node->right_node) {
            x->parent_node->right_node = y;
        } else {
            x->parent_node->left_node = y;
        }
        y->right_node = x;
        x->parent_node = y;
    }
}

_Bool RBT_insert_node(RBT_t *pRBT, int key) {
    if(pRBT != NULL) {
        Node_t * z;
        z = (Node_t *) malloc(sizeof(Node_t));
        z->key = key;
        z->color = RED;
        z->left_node = NULL;
        z->right_node = NULL;
        z->parent_node = NULL;
        
        Node_t *y = NULL;
        Node_t *x = pRBT->root_node;

        while (x != NULL) {
            y = x;
            if (z->key < x->key) {
                x = x->left_node;
            } else {
                x = x->right_node;
            }
        }

        z->parent_node = y;
        if (y == NULL) {
            // Make the node the root of the tree
            pRBT->root_node = z;
            z->color = BLACK;
        } else {
            if (z->key < y->key) {
                y->left_node = z;
            } else {
                y->right_node = z;
            }
        }
        RBT_insert_fixup(pRBT, z);
        RBT_print_node(pRBT, z);
    }
    return 0;
}

_Bool RBT_insert_fixup(RBT_t *pRBT, Node_t *z) {
    _Bool status = 0;
    if(z != NULL) {
        Node_t *zParent = RBT_get_parent(pRBT, z);
        if (zParent != NULL) {
            // There is a parent
            while (zParent->color == RED) {                
                Node_t *zGrandParent = RBT_get_grandparent(pRBT, z);
                if (zGrandParent != NULL) {
                    if (zParent == zGrandParent->left_node) {
                        Node_t *y = zGrandParent->right_node;
                        if (y->color == RED) {
                            // Case 1
                            printf("INSERT FIXUP: Case 1\n");
                            zParent->color = BLACK;
                            y->color = BLACK;
                            zGrandParent->color = RED;
                            z = zGrandParent;
                        } else if (z == zParent->right_node) {
                            // Case 2
                            printf("INSERT FIXUP: Case 2\n");
                            z = zParent;
                            RBT_left_rotate(pRBT, z);
                        } else {
                            // Case 3
                            printf("INSERT FIXUP: Case 3\n");
                            zParent = RBT_get_parent(pRBT, z);            // New z's parent
                            zGrandParent = RBT_get_grandparent(pRBT, z);  // New z's grandparent
                            zParent->color = BLACK;
                            zGrandParent->color = RED;
                            RBT_right_rotate(pRBT, zGrandParent);
                        }
                    } else if(zParent == zGrandParent->right_node){
                        
                        
                    }
                } else {
                    // Grand parent is NULL
                    printf("Fixup: Grand Parent is null\n");
                    break;
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

void RBT_print_node(RBT_t *pRBT, Node_t *pNode) {
    if(pNode != NULL) {
        char trueFlag[5] = "True";
        char falseFlag[6] = "False";

        // Assign the color into a string
        char color[6];
        if(pNode->color == RED) {
            strcpy(color, "RED");
        } else if(pNode->color == BLACK) {
            strcpy(color, "BLACK");
        }

        // Assign the root flag
        char isRoot[6];
        Node_t *pParent = RBT_get_parent(pRBT, pNode);
        if(pParent == NULL) {
            strcpy(isRoot, trueFlag);
        } else {
            strcpy(isRoot, falseFlag);
        }

        // Assign the sibling flag
        char hasSibling[6];
        Node_t *pSibling = RBT_get_sibling(pRBT, pNode);
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

        printf("\n-- Node information -- \n");
        printf("key: %d\n", pNode->key);
        printf("color: %s\n", color); //
        printf("Is a root node?: %s\n", isRoot);
        printf("Has sibling?: %s\n", hasSibling);
        printf("Has a left node?: %s\n", hasLeftNode);
        printf("Has a right node?: %s\n", hasRightNode);
    }
}