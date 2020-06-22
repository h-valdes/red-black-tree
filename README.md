# Red-Black Tree

This is an implementation in C of the Data Structure Red-Black Tree for the 
Seminar "Exploring Data Structures in C" at the Technische Bergakademie Freiberg
(TUBAF).

The code is based on the pseudocode from the book "Introduction to Algorithms" 
by Thomas H. Cormen et al.

## Table of contents
- [Build](##Build)
    * [Release](###Release)
    * [Debug](###Debug)
- [API](##API)
    * [Create a tree](###Create%20a%20tree)
    * [Insert a new node](###Insert%20a%20new%20node)
    * [Delete a node](###Delete%20a%20node)
    * [Search a node](###Search%20a%20node)
    * [Print node data](###Print%20node%20data)
    * [Export a DOT file](###Export%20a%20DOT%20file)


This structure is intended to be generic (the data and not the keys). 
There is a a generic form to create a new tree and wrappers around it.
For example:

```c
// &print_data is a pointer to the function who knows how to cast your data
// in order to print it
RBT_new(&print_data); 
RBT_new_int();
```

It can export a DOT file in order to visualize the graph in Graphviz.

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
Delete a node by passing the node
```c
RBT_delete(intTree, pNode);
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
Generate a DOT file (Graphviz) from the tree
```c
RBT_export_dot(newTree, "newTree");
```

Clear the whole tree
```c
RBT_destroy(newTree);
```

## Export DOT file into a PNG Image (You need to install Grahpviz)

```
dot rbtree.dot -Tpng -o rbtree.png
```