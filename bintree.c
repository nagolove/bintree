#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct BinTreeNode {
    struct BinTreeNode *left, *right;
    int val;
} BinTreeNode;

FILE *dot_file = NULL;

static void dot_init(const char *dot_fname) {
    // {{{
    assert(dot_file == NULL);
    dot_file = fopen(dot_fname, "w");
    assert(dot_file);

    const char *preambule = 
        "digraph binary_tree {\n"
        "node [shape=circle, style=filled, color=\"lightblue\"]\n"  
        "edge [color=\"black\"]  // Определяем стиль ребер\n";

    fprintf(dot_file, "%s", preambule);
    // }}}
}

static void dot_shutdown() {
    // {{{
    assert(dot_file);
    fprintf(dot_file, "%s", "}");
    fclose(dot_file);
    dot_file = NULL;
    // }}}
}

static BinTreeNode *bintree_add(BinTreeNode *root, int val) {
    BinTreeNode *cur = root, *new = calloc(1, sizeof(*new));
    assert(new);
    new->val = val;

    if (!root)
        return new;

    while (true) {
        if (val >= cur->val) {
            if (!cur->right) {
                cur->right = new;
                return root;
            } else {
                cur = cur->right;
            }
        } else {
            if (!cur->left) {
                cur->left = new;
                return root;
            } else
                cur = cur->left;
        }
    }

    return root;
}

static void bintree_free(BinTreeNode *node) {
    if (!node) 
        return;

    if (node->left) {
        bintree_free(node->left);
    }
    if (node->right) {
        bintree_free(node->left);
    }

    free(node);
}


static void bintree_walk(BinTreeNode *node) {
    if (!node) 
        return;

    if (node->left) {
        fprintf(dot_file, "%d -> %d\n", node->val, node->left->val);
        bintree_walk(node->left);
    }
    if (node->right) {
        fprintf(dot_file, "%d -> %d\n", node->val, node->right->val);
        bintree_walk(node->left);
    }
}

static void test_1() {
    BinTreeNode *root = NULL;
    dot_init("test_1.dot");
    for (int i = 0; i < 10; i++) {
        root = bintree_add(root, 1);
    }
    bintree_walk(root);
    bintree_free(root);
    dot_shutdown();
}

int main(int argc, char **argv) {
    test_1();

    return EXIT_SUCCESS;
}
