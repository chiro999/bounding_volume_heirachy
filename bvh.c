#include <stdio.h>
#include <stdlib.h> 

// Structure for representing a 3D point or AABB
typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    Vector3 min;
    Vector3 max;
} AABB;

// BVH node structure
typedef struct BVHNode {
    AABB bbox;
    struct BVHNode* left;
    struct BVHNode* right;
} BVHNode;

// Function to create a BVH node
BVHNode* createBVHNode(AABB bbox) {
    BVHNode* node = (BVHNode*)malloc(sizeof(BVHNode)); // Allocate memory for the node
    node->bbox = bbox;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to build a BVH recursively
BVHNode* buildBVH(AABB* objects, int start, int end) {
    if (start == end) {
        return createBVHNode(objects[start]);
    }

    int mid = (start + end) / 2;
    BVHNode* left = buildBVH(objects, start, mid);
    BVHNode* right = buildBVH(objects, mid + 1, end);

    // Calculate the bounding box of the combined group
    AABB combinedBox;
    combinedBox.min.x = fminf(left->bbox.min.x, right->bbox.min.x);
    combinedBox.min.y = fminf(left->bbox.min.y, right->bbox.min.y);
    combinedBox.min.z = fminf(left->bbox.min.z, right->bbox.min.z);
    combinedBox.max.x = fmaxf(left->bbox.max.x, right->bbox.max.x);
    combinedBox.max.y = fmaxf(left->bbox.max.y, right->bbox.max.y);
    combinedBox.max.z = fmaxf(left->bbox.max.z, right->bbox.max.z);

    BVHNode* node = createBVHNode(combinedBox);
    node->left = left;
    node->right = right;

    return node;
}

// Function to traverse and print BVH nodes
void traverseBVH(BVHNode* node, int depth) {
    if (node == NULL) {
        return;
    }

    // Print indentation based on depth
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }

    // Print node's bounding box coordinates
    printf("Node: (%.2f, %.2f, %.2f) - (%.2f, %.2f, %.2f)\n",
           node->bbox.min.x, node->bbox.min.y, node->bbox.min.z,
           node->bbox.max.x, node->bbox.max.y, node->bbox.max.z);

    // Traverse left and right subtrees
    traverseBVH(node->left, depth + 1);
    traverseBVH(node->right, depth + 1);
}

int main() {
    // Example AABBs
    AABB objects[] = {
        {{1, 1, 1}, {2, 2, 2}},
        {{3, 3, 3}, {4, 4, 4}},
        {{0, 0, 0}, {5, 5, 5}}
    };

    // Build the BVH and get the root node
    BVHNode* root = buildBVH(objects, 0, 2);

    // Traverse and print the BVH nodes
    traverseBVH(root, 0);

    // Free memory (TODO: Implement cleanup logic)

    return 0;
}