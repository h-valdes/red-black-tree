#include "rbtree.h"

#include <stdlib.h>
#include <string.h>

RBT_t *RBT_new() {
    RBT_t *pRBT = NULL;
    pRBT = malloc(sizeof(RBT_t));
    pRBT->nil = (Node_t *)malloc(sizeof(Node_t));
    pRBT->nil->color = BLACK;
    pRBT->root = pRBT->nil;
    return pRBT;
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
    if (u->parent == pRBT->nil) {
        pRBT->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
        v->parent = u->parent;
    }
}

_Bool RBT_insert(RBT_t *pRBT, int key) {
    if (pRBT != NULL) {
        Node_t *z;
        z = (Node_t *)malloc(sizeof(Node_t));
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

Node_t *RBT_search(RBT_t *pRBT, int k) {
    Node_t *x = pRBT->root;
    while (x != pRBT->nil && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

Node_t *tree_minimum(RBT_t *pRBT, Node_t *x) {
    while (x->left != pRBT->nil) {
        x = x->left;
    }
    return x;
}

Node_t *tree_maximum(RBT_t *pRBT, Node_t *x) {
    while (x->right != pRBT->nil) {
        x = x->right;
    }
    return x;
}

void RBT_delete(RBT_t *pRBT, Node_t *z) {
    Node_t *y = z;
    color_t yOriginalColor = y->color;
    Node_t *x;
    if (z->left == pRBT->nil) {
        x = z->right;
        transplant(pRBT, z, z->right);
    } else if (z->right == pRBT->nil) {
        x = z->left;
        transplant(pRBT, z, z->left);
    } else {
        y = tree_minimum(pRBT, z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
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
    if (yOriginalColor == BLACK) {
        delete_fixup(pRBT, x);
    }
    free(z);
}

void delete_fixup(RBT_t *pRBT, Node_t *x) {
    while (x != pRBT->root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node_t *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(pRBT, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
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
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(pRBT, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
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

void add_nil(Node_t *pNode, FILE *pFile, int *count) {
    fprintf(pFile, "\tnil%d [shape=point];\n", *count);
    fprintf(pFile, "\t%d -> nil%d;\n", pNode->key, *count);
    *count = *count + 1;
}

void add_children(RBT_t *pRBT, Node_t *pNode, FILE *pFile, int *count) {
    add_node_color(pNode, pFile);
    if (pNode->left != pRBT->nil) {
        fprintf(pFile, "\t%d -> %d;\n", pNode->key, pNode->left->key);
        add_children(pRBT, pNode->left, pFile, count);
    } else {
        add_nil(pNode, pFile, count);
    }
    if (pNode->right != pRBT->nil) {
        fprintf(pFile, "\t%d -> %d;\n", pNode->key, pNode->right->key);
        add_children(pRBT, pNode->right, pFile, count);
    } else {
        add_nil(pNode, pFile, count);
    }
}

void add_node_color(Node_t *pNode, FILE *pFile) {
    if (pNode->color == BLACK) {
        fprintf(pFile, "\t%d [fontcolor=white, fillcolor=black, style=filled];\n", pNode->key);
    } else {
        fprintf(pFile, "\t%d [fontcolor=white, fillcolor=red, style=filled];\n", pNode->key);
    }
}

void RBT_export_dot(RBT_t *pRBT) {
    FILE *pFile = fopen("rbtree.dot", "w+");
    // Start of the file
    fprintf(pFile, "digraph RBTree {\n");
    fprintf(pFile, "\tnode [fontname=\"Arial\"];\n");
    if (pRBT->root != pRBT->nil) {
        int count = 0;
        add_children(pRBT, pRBT->root, pFile, &count);
    }
    fprintf(pFile, "}\n");
    fclose(pFile);
}

void RBT_clear(RBT_t *pRBT, Node_t *pNode) {
    if (pNode->left == pRBT->nil && pNode->right == pRBT->nil) {
        free(pNode);
    } else {
        if (pNode->left != pRBT->nil) {
            RBT_clear(pRBT, pNode->left);
        }
        if (pNode->right != pRBT->nil) {
            RBT_clear(pRBT, pNode->right);
        }
    }
}

void RBT_clear_tree(RBT_t *pRBT) {
    if (pRBT->root != pRBT->nil) {
        RBT_clear(pRBT, pRBT->root);
    }
    free(pRBT->nil);
    free(pRBT);
}