#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

/* ==================================================================== */
/* Helper Functions for Testing                                         */
/* ==================================================================== */

/* * Comparator for integers. 
 * Returns 1 if left < right, -1 if left > right, 0 if equal.
 */
int IntComparator(void* _left, void* _right) 
{
    int leftVal = *(int*)_left;
    int rightVal = *(int*)_right;

    if (leftVal < rightVal) {
        return 1;
    } else if (leftVal > rightVal) {
        return -1;
    }
    return 0;
}

/* * Action function to print integers. 
 * Returns 1 to continue iteration, 0 to stop.
 */
int PrintIntAction(void* _element, void* _context) 
{
    if (_element) {
        printf("%d ", *(int*)_element);
    }
    return 1; 
}

/* * Destroyer function to free the dynamically allocated integers 
 */
void IntDestroyer(void* _element) 
{
    if (_element) {
        free(_element);
    }
}

/* * Helper to allocate an integer on the heap 
 */
int* CreateInt(int val) 
{
    int* num = (int*)malloc(sizeof(int));
    if (num) {
        *num = val;
    }
    return num;
}

/* ==================================================================== */
/* Main Test Suite                                                      */
/* ==================================================================== */

int main(void) 
{
    BSTree* tree = NULL;
    BSTreeItr it = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int numValues = sizeof(values) / sizeof(values[0]);
    int i;
    int* removedData = NULL;

    printf("=== Starting BSTree Tests ===\n\n");

    /* 1. Create Tree */
    tree = BSTreeCreate(IntComparator);
    if (!tree) {
        printf("Failed to create tree.\n");
        return 1;
    }
    printf("[+] Tree created successfully.\n");

    /* 2. Insert Values */
    /*
     * Tree structure will look like this:
     * 50
     * /    \
     * 30      70
     * /  \    /  \
     * 20   40  60   80
     */
    printf("[+] Inserting values: ");
    for (i = 0; i < numValues; ++i) {
        printf("%d ", values[i]);
        BSTreeInsert(tree, CreateInt(values[i]));
    }
    printf("\n\n");

    /* 3. Test Traversals */
    printf("--- Traversals ---\n");
    printf("Pre-Order  (Expected: 50 30 20 40 70 60 80): ");
    BSTreeForEach(tree, BSTREE_TRAVERSAL_PREORDER, PrintIntAction, NULL);
    printf("\n");

    printf("In-Order   (Expected: 20 30 40 50 60 70 80): ");
    BSTreeForEach(tree, BSTREE_TRAVERSAL_INORDER, PrintIntAction, NULL);
    printf("\n");

    printf("Post-Order (Expected: 20 40 30 60 80 70 50): ");
    BSTreeForEach(tree, BSTREE_TRAVERSAL_POSTORDER, PrintIntAction, NULL);
    printf("\n\n");

    /* 4. Test Iterators (Begin, Next, Get) */
    printf("--- Iterators ---\n");
    printf("Iterating through tree using Next():\n");
    it = BSTreeItrBegin(tree);
    while (it != BSTreeItrEnd(tree)) {
        printf("%d ", *(int*)BSTreeItrGet(it));
        it = BSTreeItrNext(it);
    }
    printf("\n\n");

    /* 5. Test Removals */
    printf("--- Removals ---\n");
    
    /* Find and remove a leaf node (20) */
    it = BSTreeItrBegin(tree); /* 20 is the smallest, so it's at Begin */
    printf("Removing leaf node: %d\n", *(int*)BSTreeItrGet(it));
    removedData = (int*)BSTreeItrRemove(it);
    free(removedData); /* Free the allocated int */

    /* Find and remove a node with 2 children (70) */
    /* To find 70 quickly for the test, we'll traverse starting from Begin */
    it = BSTreeItrBegin(tree);
    while (it != BSTreeItrEnd(tree) && *(int*)BSTreeItrGet(it) != 70) {
        it = BSTreeItrNext(it);
    }
    if (it != BSTreeItrEnd(tree)) {
        printf("Removing node with 2 children: %d\n", *(int*)BSTreeItrGet(it));
        removedData = (int*)BSTreeItrRemove(it);
        free(removedData);
    }

    printf("In-Order after removals (Expected: 30 40 50 60 80): ");
    BSTreeForEach(tree, BSTREE_TRAVERSAL_INORDER, PrintIntAction, NULL);
    printf("\n\n");

    /* 6. Destroy Tree */
    printf("--- Cleanup ---\n");
    BSTreeDestroy(&tree, IntDestroyer);
    printf("[+] Tree destroyed and memory freed successfully.\n");
    
    if (tree == NULL) {
        printf("[+] Tree pointer safely set to NULL.\n");
    }

    printf("\n=== Tests Completed ===\n");
    return 0;
}