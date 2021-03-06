# Red-Black Tree

This is an implementation in C of the data structure Red-Black Tree for the 
Seminar ["Exploring data structures in C"](https://github.com/JayTee42/tubaf-csem-2020) 
at the Technische Bergakademie Freiberg (TUBAF).

The code is based on the pseudocode from the book "Introduction to Algorithms" 
by Thomas H. Cormen et al.

The Benchmarking use as comparisson the data structures (AVL, BST and RBT)
implemented by the Github-User lbrito1 in the repository 
[cstuff](https://github.com/lbrito1/cstuff).

This structure is intended to be generic (the data and not the keys). 
There is a a generic form to create a new tree and wrappers around it.

It can export a DOT file in order to visualize the graph in Graphviz.


## Table of contents
- [Build](#Build)
    * [Release](#Release)
    * [Debug](#Debug)
- [API](#API)
    * [Create a tree](#Create-a-tree)
    * [Insert a new node](#Insert-a-new-node)
    * [Delete a node](#Delete-a-node)
    * [Destroy a tree ](#Destroy-a-tree)
    * [Search a node](#Search-a-node)
    * [Print node data](#Print-node-data)
    * [Export a DOT file](#Export-a-DOT-file)
- [Export DOT file into a PNG Image](#Export-DOT-file-into-a-PNG-Image)

## Build

### Release
```bash
# Inside of the clone repository
cd red-black-tree
mkdir Release
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Debug
```bash
# Inside of the clone repository
cd red-black-tree
mkdir Debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

## API

### Create a tree

Define a function to print the type of your data
```c
void print_data(Node_t *pNode){
    printf("Data: %d\n", *(int *)pNode->data);
}
```

Create a custom tree. You need to pass the function pointer to print the data
that you are going to use.
```c
RBT_t *newTree = RBT_new(&print_data);
```

Or use some of the predefined wrappers around the C types
```c
RBT_t *intTree = RBT_new_int();
```
### Insert a new node
Insert a new node in the tree by key with a value
```c
int new_value = 10;
RBT_insert(intTree, 1, &new_value, sizeof(new_value));
```

### Delete a node
Delete a node by passing a key of the node
```c
RBT_delete(intTree, key);
```

### Destroy a tree
Clear a whole tree
```c
RBT_destroy(newTree);
```

### Search a node
Search a node by key
```c
RBT_search(newTree, 3);
```


### Print node data
Print a node by key
```c
RBT_print_node(newTree, 3);
```

### Export a DOT file
Generate a DOT file (Graphviz) from the tree.
It can exports with or without the Leafs (Null-Nodes).

Without Leafs:
```c
RBT_export_dot(newTree, filename, RBT_FALSE);
```

With Leafs:
```c
RBT_export_dot(newTree, filename, RBT_TRUE);
```
The output file has the format filename.dot (only the name needs to be passed).

## Export DOT file into a PNG Image
Graphviz is required in order to export into a PNG.

```
dot rbtree.dot -Tpng -o rbtree.png
```
There is a [cool extension](https://marketplace.visualstudio.com/items?itemName=joaompinto.vscode-graphviz) 
in VScode Marketplace that can show and export the DOT files.