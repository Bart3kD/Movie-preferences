#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "Vector.h"

int main(void) {
    Node* root = init_node(10);

    append_to_tree(root, init_node(2));
    append_to_tree(root, init_node(1));
    append_to_tree(root, init_node(6));
    append_to_tree(root, init_node(8));
    append_to_tree(root, init_node(9));
    append_to_tree(root, init_node(13));
    append_to_tree(root, init_node(11));
    append_to_tree(root, init_node(17));

    printf("Original tree (in-order): ");
    print_tree(root);
    printf("\n");

    root = delete_node(root, 10); // Delete the root node

    printf("Tree after deleting 10 (in-order): ");
    print_tree(root);
    printf("\n");

    return 0;
}
