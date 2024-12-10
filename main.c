#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "Vector.h"

int main(void)
{
    // Node* node = init_node(0);
    // Node* node1 = init_node(1);
    //
    // node->left = node1;
    //
    //
    // Vector vec = init_vector();
    //
    // for (int i = 0; i < 20; i++) {
    //     append_to_vector(&vec, i + 1);
    // }
    //
    // for (int i = 0; i < vec.current_amount; i++) {
    //     printf("%d ", ((int*)vec.data)[i]);
    // }
    //
    // printf("\n");
    // free_vector(&vec);

    NodeVector* tree = init_tree();


    Node* root = init_node(0);

    tree->root = root;

    Node* node1 = init_node(5);
    Node* node2 = init_node(15);
    Node* node3 = init_node(3);
    Node* node4 = init_node(7);

    append_to_tree(tree->root, node1);
    append_to_tree(tree->root, node2);
    append_to_tree(tree->root, node3);
    append_to_tree(tree->root, node4);

    printf("Tree in in-order traversal:\n");
    print_tree(tree->root);
    printf("\n");

    Node* result = find_user(7, root);
    if (result) {
        printf("User with ID %d found.\n", result->id);
    } else {
        printf("User with ID %d not found.\n", 7);
    }

    free(node4);
    free(node3);
    free(node2);
    free(node1);
    free(root);
    free(tree);

    return 0;
}
