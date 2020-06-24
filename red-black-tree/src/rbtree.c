#include "rbtree.h"

#include <stdlib.h>
#include <string.h>

void print_double(Node_t *pNode) {
    printf("Data in node %d: %lf\n", pNode->key, *(double *)pNode->data);
}

void print_long_double(Node_t *pNode) {
    printf("Data in node %d: %Lf\n", pNode->key, *(long double *)pNode->data);
}

void print_str(Node_t *pNode) {
    printf("Data in node %d: %s\n", pNode->key, (char *)pNode->data);
}

RBT_t *RBT_new(PrintFunc_t *print_fn) {
    RBT_t *pRBT = NULL;
    pRBT = malloc(sizeof(RBT_t));
    pRBT->null = (Node_t *)malloc(sizeof(Node_t));
    pRBT->null->color = BLACK;
    pRBT->root = pRBT->null;
    pRBT->print_fn = print_fn;

    return pRBT;
}

void print_int(Node_t *pNode) {
    printf("Data in node %d: %d\n", pNode->key, *(int *)pNode->data);
}

RBT_t *RBT_new_int() {
    RBT_t *pRBT = RBT_new(print_int);
    return pRBT;
}

RBT_t *RBT_new_double() {
    RBT_t *pRBT = RBT_new(print_double);
    return pRBT;
}

RBT_t *RBT_new_long_double() {
    RBT_t *pRBT = RBT_new(print_long_double);
    return pRBT;
}

RBT_t *RBT_new_str() {
    RBT_t *pRBT = RBT_new(print_str);
}

void left_rotate(RBT_t *pRBT, Node_t *x) {
    // For left rotation check that right child is not NULL
    Node_t *y = x->right;
    x->right = y->left;
    if (y->left != pRBT->null) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == pRBT->null) {
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
    if (y->right != pRBT->null) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == pRBT->null) {
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
    if (u->parent == pRBT->null) {
        pRBT->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

int RBT_insert(RBT_t *pRBT, int key, void *data, size_t size) {
    if (pRBT != NULL) {
        Node_t *z;
        z = (Node_t *)malloc(sizeof(Node_t));

        z->key = key;

        // Set data
        z->data = malloc(size);
        memcpy(z->data, data, size);

        z->color = RED;
        z->left = pRBT->null;
        z->right = pRBT->null;
        z->parent = pRBT->null;

        Node_t *y = pRBT->null;
        Node_t *x = pRBT->root;

        while (x != pRBT->null) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == pRBT->null) {
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

    return RBT_ERROR_SUCCESS;
}

int insert_fixup(RBT_t *pRBT, Node_t *z) {
    int status = RBT_ERROR_SUCCESS;
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node_t *y = z->parent->parent->right;
            if (y->color == RED) {
                // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2
                    z = z->parent;
                    left_rotate(pRBT, z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(pRBT, z->parent->parent);
            }
        } else {
            Node_t *y = z->parent->parent->left;
            if (y->color == RED) {
                // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Case 2
                    z = z->parent;
                    right_rotate(pRBT, z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(pRBT, z->parent->parent);
            }
        }
    }
    pRBT->root->color = BLACK;
    return status;
}

int RBT_print_node(RBT_t *pRBT, int key) {
    Node_t *pNode = RBT_search(pRBT, key);
    int status;
    if (pNode == pRBT->null) {
        status = RBT_ERROR_NOT_FOUND;
    } else {
        pRBT->print_fn(pNode);
        status = RBT_ERROR_SUCCESS;
    }
    return RBT_ERROR_SUCCESS;
}

Node_t *RBT_search(RBT_t *pRBT, int k) {
    Node_t *x = pRBT->root;
    while (x != pRBT->null && k != x->key) {
        if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

Node_t *tree_minimum(RBT_t *pRBT, Node_t *x) {
    while (x->left != pRBT->null) {
        x = x->left;
    }
    return x;
}

Node_t *tree_maximum(RBT_t *pRBT, Node_t *x) {
    while (x->right != pRBT->null) {
        x = x->right;
    }
    return x;
}

int RBT_delete(RBT_t *pRBT, int key) {
    Node_t *z = RBT_search(pRBT, key);
    int result;
    if (z != pRBT->null) {
        Node_t *y = z;
        color_t yOriginalColor = y->color;
        Node_t *x;
        if (z->left == pRBT->null) {
            x = z->right;
            transplant(pRBT, z, z->right);
        } else if (z->right == pRBT->null) {
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

        // Free the node and its data
        free(z->data);
        free(z);

        result = RBT_ERROR_SUCCESS;
    } else {
        result = RBT_ERROR_NOT_FOUND;
    }

    return result;
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
    x->color = BLACK;
}

void add_null(Node_t *pNode, FILE *pFile, int *count) {
    fprintf(pFile,
            "\tnull%d [shape=box, label=\"null\", fontcolor=white, fillcolor=black, style=\"rounded, filled\"];\n",
            *count);
    fprintf(pFile, "\t%d -> null%d;\n", pNode->key, *count);
    *count = *count + 1;
}

void add_children(RBT_t *pRBT, Node_t *pNode, FILE *pFile, int *count, int has_null) {
    add_node_color(pNode, pFile);
    if (pNode->left != pRBT->null) {
        fprintf(pFile, "\t%d -> %d;\n", pNode->key, pNode->left->key);
        add_children(pRBT, pNode->left, pFile, count, has_null);
    } else {
        if (has_null == RBT_TRUE) {
            add_null(pNode, pFile, count);
        }
    }
    if (pNode->right != pRBT->null) {
        fprintf(pFile, "\t%d -> %d;\n", pNode->key, pNode->right->key);
        add_children(pRBT, pNode->right, pFile, count, has_null);
    } else {
        if (has_null == RBT_TRUE) {
            add_null(pNode, pFile, count);
        }
    }
}

void add_node_color(Node_t *pNode, FILE *pFile) {
    if (pNode->color == BLACK) {
        fprintf(pFile,
                "\t%d [fontcolor=white, fillcolor=black, style=filled];\n",
                pNode->key);
    } else {
        fprintf(pFile,
                "\t%d [fontcolor=white, fillcolor=red, style=filled];\n",
                pNode->key);
    }
}

int RBT_export_dot(RBT_t *pRBT, char *filename, int has_null) {
    char extension[] = ".dot";
    int filename_length = strlen(filename);
    int extension_length = strlen(extension);
    char new_filename[filename_length + extension_length + 2];
    strcpy(new_filename, filename);
    strcat(new_filename, extension);

    FILE *pFile = fopen(new_filename, "w+");
    // Start of the file
    fprintf(pFile, "digraph RBTree {\n");
    fprintf(pFile, "\tnode [shape=circle, fontname=\"Arial\"];\n");
    fprintf(pFile, "\tedge [arrowhead=none];\n");
    if (pRBT->root != pRBT->null) {
        int count = 0;
        add_children(pRBT, pRBT->root, pFile, &count, has_null);
    }
    fprintf(pFile, "}\n");
    fclose(pFile);

    return RBT_ERROR_SUCCESS;
}

void RBT_clear(RBT_t *pRBT, Node_t *pNode) {
    int left_null = pNode->left == pRBT->null;
    int right_null = pNode->right == pRBT->null;
    if (left_null && right_null) {
        free(pNode->data);
        free(pNode);
    } else {
        if (!left_null && !right_null) {
            RBT_clear(pRBT, pNode->left);
            RBT_clear(pRBT, pNode->right);
        } else if (!left_null && right_null) {
            RBT_clear(pRBT, pNode->left);
        } else if (left_null && !right_null) {
            RBT_clear(pRBT, pNode->right);
        }
        free(pNode->data);
        free(pNode);
    }
}

int RBT_destroy(RBT_t *pRBT) {
    int status;
    if (pRBT != NULL) {
        if (pRBT->root != pRBT->null) {
            RBT_clear(pRBT, pRBT->root);
        }
        free(pRBT->null);
        free(pRBT);
        status = RBT_ERROR_SUCCESS;
    } else {
        status = RBT_ERROR_NOT_FOUND;
    }

    return status;
}