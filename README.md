# Implementation of Red-Black Trees

Note: This is still a work in progress.

This is an implementation in C based on the Pseudocode from the book "Introduction to Algorithms" by Thomas H. Cormen, Charles E. Leiserson, Ronald Rivest, Clifford Stein.

It can export a DOT file in order to visualize the graph in Graphviz.

## Build
```
mkdir build
cd build
cmake ..
make
```

## Run the executable
```
./rbtree
```

## Export DOT file into a PNG Image (You need to install Grahpviz)

```
dot rbtree.dot -Tpng -o rbtree.png
```

## API

Define a function to print the type of your data
```
void print_int_data(void *data){
    printf("Data: %d\n", *(int *)data);
}
```

New tree, pass the function pointer to print the data
```
RBT_t *newTree = RBT_new(&print_int_data);
```

Insert a new node in the tree by key with a value
```
RBT_insert(newTree, 1, &(int){10});
```

Search a node by key
```
RBT_search(newTree, 3);
```

Generate a DOT file (Graphviz) from the tree
```
RBT_export_dot(newTree);
```

Delete a node by passing the node
```
RBT_delete(newTree, x);
```

Clear the whole tree
```
RBT_clear_tree(newTree);
```