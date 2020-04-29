#include "rbtree.h"

#include <string.h>
#include <stdlib.h>

RBT_t *RBT_new() {
    RBT_t *pRBT = NULL;
    pRBT = malloc(sizeof(RBT_t));
    pRBT->nil = (Node_t *) malloc(sizeof(Node_t));
    pRBT->nil->color = BLACK;
    pRBT->root = pRBT->nil;
    return pRBT;
}

Node_t *get_parent(RBT_t *pRBT, Node_t *pNode) {
    Node_t *pParent;
    if (pNode != NULL) {
        pParent = pNode->parent;
        if (pParent == NULL) {
            pParent = NULL;
        }
    } else {
        printf("GET PARENT: Node is NULL\n");
    }
    return pParent;
}

Node_t *get_grandparent(RBT_t *pRBT, Node_t *pNode) {
    Node_t *pGrandparent;
    if (pNode != NULL) {
        Node_t *pParent = get_parent(pRBT, pNode);
        if (pParent != NULL) {
            pGrandparent = get_parent(pRBT, pParent);
        }
    } else {
        printf("GET GRANDPARENT: Node is NULL\n");
    }
    return pGrandparent;
}

Node_t *get_sibling(RBT_t *pRBT, Node_t *pNode) {
    Node_t *pSibling;
    if(pNode != NULL) {
        Node_t *pParent = get_parent(pRBT, pNode);
        if(pParent != NULL) {
            Node_t *leftNode;
            Node_t *rightNode;
            leftNode = pParent->left;
            rightNode = pParent->right;
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

Node_t *get_uncle(RBT_t *pRBT, Node_t *pNode) {
    Node_t *pUncle;
    if (pNode != NULL) {
        Node_t *pParent = get_parent(pRBT, pNode);
        if(pParent != NULL) {
            pUncle = get_sibling(pRBT, pParent);
        }
    } else {
        printf("GET UNCLE: Node is NULL\n");
    }
    return pUncle;
}

void left_rotate(RBT_t *pRBT, Node_t *x) {
    printf("Left rotate\n");
    // For left rotation check that right child is not NULL
    Node_t *y = x->right;
    x->right = y->left;
    if (y->left != pRBT->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == pRBT->nil) {
        pRBT->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(RBT_t *pRBT, Node_t *x) {
    // For left rotation check that right child is not NULL
    printf("Right rotate\n");
    Node_t *y = x->left;
    x->left = y->right;
    if (y->right != pRBT->nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == pRBT->nil) {
        pRBT->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void transplant(RBT_t *pRBT, Node_t *u, Node_t *v) {
    if(u->parent == pRBT->nil) {
        pRBT->root = v;
    } else if(u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
        v->parent = u->parent;
    }
}

_Bool RBT_insert(RBT_t *pRBT, int key) {
    if(pRBT != NULL) {
        Node_t * z;
        z = (Node_t *) malloc(sizeof(Node_t));
        z->key = key;
        z->color = RED;
        z->left = pRBT->nil;
        z->right = pRBT->nil;
        z->parent = pRBT->nil;
        
        Node_t *y = pRBT->nil;
        Node_t *x = pRBT->root;

        while (x != pRBT->nil) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == pRBT->nil) {
            // Make the node the root of the tree
            pRBT->root = z;
            z->color = BLACK;
        } else {
            if (z->key < y->key) {
                y->left = z;
            } else {
                y->right = z;
            }
        }
        insert_fixup(pRBT, z);
        RBT_print_node(pRBT, z);
    }
    return 0;
}

_Bool insert_fixup(RBT_t *pRBT, Node_t *z) {
    _Bool status = 0;
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node_t *y = z->parent->parent->right;
            if (y->color == RED) {
                // Case 1
                printf("INSERT FIXUP: Case 1\n");
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2
                    printf("INSERT FIXUP: Case 2\n");
                    z = z->parent;
                    left_rotate(pRBT, z);
                }
                // Case 3
                printf("INSERT FIXUP: Case 3\n");
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(pRBT, z->parent->parent);
            } 
        } else {
            Node_t *y = z->parent->parent->left;
            if (y->color == RED) {
                // Case 1
                printf("INSERT FIXUP: Case 1\n");
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Case 2
                    printf("INSERT FIXUP: Case 2\n");
                    z = z->parent;
                    right_rotate(pRBT, z);
                }
                // Case 3
                printf("INSERT FIXUP: Case 3\n");
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(pRBT, z->parent->parent);
            }
        } 
    }
    pRBT->root->color = BLACK;
    return status;
}

Node_t *tree_minimum(RBT_t *pRBT, Node_t *x) {
    while(x->left != pRBT->nil){
		x = x->left;
	}
	return x;
}

void RBT_delete(RBT_t *pRBT, Node_t *z) {
    Node_t *y = z;
    color_t yOriginalColor = y->color;
    Node_t *x;
    if(z->left == pRBT->nil) {
        x = z->right;
        transplant(pRBT, z, z->right);
    } else if(z->right == pRBT->nil) {
        x = z->left;
        transplant(pRBT, z, z->left);
    } else {
        y = tree_minimum(pRBT, z->right);
        yOriginalColor = y->color;
        x = y->right;
        if(y->parent == z) {
            x->parent = y;
        } else {
            transplant(pRBT, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(pRBT, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(yOriginalColor == BLACK) {
        delete_fixup(pRBT, x);
    }
}

void delete_fixup(RBT_t *pRBT, Node_t *x) {
    while(x != pRBT->root && x->color == BLACK) {
        if(x == x->parent->left) {
            Node_t *w = x->parent->right;
            if(w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(pRBT, x->parent);
                w = x->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if(w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(pRBT, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(pRBT, x->parent);
                x = pRBT->root;
            }
        } else {
            Node_t *w = x->parent->left;
            if(w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(pRBT, x->parent);
                w = x->parent->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if(w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(pRBT, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(pRBT, x->parent);
                x = pRBT->root;
            }
        }
    }
}

void RBT_clear(Node_t *pNode) {
    if (pNode != NULL) {
        Node_t *leftNode = pNode->left;
        Node_t *rightNode = pNode->right;
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
    if(pRBT->root != NULL) {
        RBT_clear(pRBT->root);
    }
    free(pRBT->nil);
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
        Node_t *pParent = get_parent(pRBT, pNode);
        if(pParent == NULL) {
            strcpy(isRoot, trueFlag);
        } else {
            strcpy(isRoot, falseFlag);
        }

        // Assign the sibling flag
        char hasSibling[6];
        Node_t *pSibling = get_sibling(pRBT, pNode);
        if(pParent != NULL) {
            strcpy(hasSibling, trueFlag);
        } else {
            strcpy(hasSibling, falseFlag);
        }

        // Assign left node flag
        char hasLeftNode[6];
        if(pNode->left != NULL) {
            strcpy(hasLeftNode, trueFlag);
        } else {
            strcpy(hasLeftNode, falseFlag);
        }

        // Assign right node flag
        char hasRightNode[6];
        if(pNode->right != NULL) {
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