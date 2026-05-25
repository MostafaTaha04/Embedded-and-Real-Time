#include "bstree.h"
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    void* m_data;
    Node* m_left;
    Node* m_right;
    Node* m_parent;
};

struct BSTree {
    Node       m_sentinel;
    Comparator m_less;
};


static void DestroyNodes(Node* _node, void (*_destroyer)(void*)) 
{
    if (!_node) {
        return;
    }
    
    DestroyNodes(_node->m_left, _destroyer);
    DestroyNodes(_node->m_right, _destroyer);
    
    if (_destroyer && _node->m_data) {
        _destroyer(_node->m_data);
    }
    
    free(_node);
}


BSTree* BSTreeCreate(Comparator _less) 
{
    BSTree* tree;
    
    if (!_less) {
        return NULL;
    }
    
    tree = (BSTree*)malloc(sizeof(BSTree));
    if (!tree) {
        return NULL;
    }
    
    
    tree->m_sentinel.m_data = NULL;
    tree->m_sentinel.m_left = NULL;  
    tree->m_sentinel.m_right = NULL; 
    tree->m_sentinel.m_parent = NULL;
    
    tree->m_less = _less;
    
    return tree;
}

void BSTreeDestroy(BSTree** _tree, void (*_destroyer)(void*)) 
{
    if (!_tree || !*_tree) {
        return;
    }
    
    DestroyNodes((*_tree)->m_sentinel.m_left, _destroyer);
    
    free(*_tree);
    *_tree = NULL;
}



BSTreeItr BSTreeInsert(BSTree* _tree, void* _item) 
{
    Node* current;
    Node* parent;
    Node* new_node;
    int cmp_result;

    if (!_tree) {
        return NULL;
    }

    parent = &_tree->m_sentinel;
    current = _tree->m_sentinel.m_left;


    while (current != NULL) {
        parent = current;
        cmp_result = _tree->m_less(_item, current->m_data);
        
        if (cmp_result == 1) {        
            current = current->m_left;
        } else if (cmp_result == -1) { 
            current = current->m_right;
        } else {                     
            return BSTreeItrEnd(_tree);
        }
    }

    new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return BSTreeItrEnd(_tree);
    }

    new_node->m_data = _item;
    new_node->m_left = NULL;
    new_node->m_right = NULL;
    new_node->m_parent = parent;

    if (parent == &_tree->m_sentinel) {
        parent->m_left = new_node;    
    } else if (cmp_result == 1) {
        parent->m_left = new_node;
    } else {
        parent->m_right = new_node;
    }

    return (BSTreeItr)new_node;
}


BSTreeItr BSTreeItrBegin(const BSTree* _tree) 
{
    Node* current;
    if (!_tree) {
        return NULL;
    }
    
    current = (Node*)&_tree->m_sentinel;

    if (current->m_left == NULL) {
        return (BSTreeItr)current; 
    }

    current = current->m_left;
    while (current->m_left != NULL) {
        current = current->m_left;
    }
    
    return (BSTreeItr)current;
}

BSTreeItr BSTreeItrEnd(const BSTree* _tree) 
{
    if (!_tree) {
        return NULL;
    }

    return (BSTreeItr)&_tree->m_sentinel;
}

BSTreeItr BSTreeItrNext(BSTreeItr _it) 
{
    Node* node = (Node*)_it;
    Node* parent;

    if (!node || node->m_parent == NULL) { 
        return _it;
    }
    
    if (node->m_right != NULL) {
        node = node->m_right;
        while (node->m_left != NULL) {
            node = node->m_left;
        }
        return (BSTreeItr)node;
    }
    

    parent = node->m_parent;
    while (parent != NULL && node == parent->m_right) {
        node = parent;
        parent = parent->m_parent;
    }
    
    return (BSTreeItr)parent;
}

BSTreeItr BSTreeItrPrev(BSTreeItr _it) 
{
    Node* node = (Node*)_it;
    Node* parent;
    
    if (!node) {
        return NULL;
    }

    if (node->m_parent == NULL) { 
        node = node->m_left; 
        if (!node) return _it; /* Tree is empty */
        while (node->m_right != NULL) {
            node = node->m_right;
        }
        return (BSTreeItr)node;
    }

    if (node->m_left != NULL) {
        node = node->m_left;
        while (node->m_right != NULL) {
            node = node->m_right;
        }
        return (BSTreeItr)node;
    }

    parent = node->m_parent;
    while (parent != NULL && parent->m_parent != NULL && node == parent->m_left) {
        node = parent;
        parent = parent->m_parent;
    }
    
   
    if (parent != NULL && parent->m_parent == NULL) {
        return _it; 
    }
    
    return (BSTreeItr)parent;
}

void* BSTreeItrGet(BSTreeItr _it) 
{
    Node* node = (Node*)_it;

    if (!node || node->m_parent == NULL) {
        return NULL;
    }
    return node->m_data;
}

void* BSTreeItrRemove(BSTreeItr _it) 
{
    Node* node = (Node*)_it;
    Node* child;
    Node* parent;
    void* removed_data;


    if (!node || node->m_parent == NULL) {
        return NULL;
    }

    removed_data = node->m_data;


    if (node->m_left == NULL || node->m_right == NULL) {
        child = (node->m_left != NULL) ? node->m_left : node->m_right;
        parent = node->m_parent;

        if (parent->m_left == node) {
            parent->m_left = child;
        } else {
            parent->m_right = child;
        }

        if (child != NULL) {
            child->m_parent = parent;
        }
        free(node);
    } 

    else {

        Node* successor = node->m_right;
        while (successor->m_left != NULL) {
            successor = successor->m_left;
        }

        node->m_data = successor->m_data;


        parent = successor->m_parent;
        child = successor->m_right;

        if (parent->m_left == successor) {
            parent->m_left = child;
        } else {
            parent->m_right = child;
        }

        if (child != NULL) {
            child->m_parent = parent;
        }
        free(successor);
    }

    return removed_data;
}

static Node* TraversePreOrder(Node* _node, ActionFunction _action, void* _context) 
{
    Node* result;
    if (!_node) return NULL;
    
    if (_action(_node->m_data, _context) == 0) return _node;
    
    result = TraversePreOrder(_node->m_left, _action, _context);
    if (result) return result;
    
    return TraversePreOrder(_node->m_right, _action, _context);
}

static Node* TraverseInOrder(Node* _node, ActionFunction _action, void* _context) 
{
    Node* result;
    if (!_node) return NULL;
    
    result = TraverseInOrder(_node->m_left, _action, _context);
    if (result) return result;
    
    if (_action(_node->m_data, _context) == 0) return _node;
    
    return TraverseInOrder(_node->m_right, _action, _context);
}

static Node* TraversePostOrder(Node* _node, ActionFunction _action, void* _context) 
{
    Node* result;
    if (!_node) return NULL;
    
    result = TraversePostOrder(_node->m_left, _action, _context);
    if (result) return result;
    
    result = TraversePostOrder(_node->m_right, _action, _context);
    if (result) return result;
    
    if (_action(_node->m_data, _context) == 0) return _node;
    
    return NULL;
}

BSTreeItr BSTreeForEach(const BSTree* _tree, BSTreeTraversalMode _mode, ActionFunction _action, void* _context) 
{
    Node* stop_node = NULL;
    
    if (!_tree || !_action) {
        return NULL;
    }
    
    switch (_mode) {
        case BSTREE_TRAVERSAL_PREORDER:
            stop_node = TraversePreOrder(_tree->m_sentinel.m_left, _action, _context);
            break;
        case BSTREE_TRAVERSAL_INORDER:
            stop_node = TraverseInOrder(_tree->m_sentinel.m_left, _action, _context);
            break;
        case BSTREE_TRAVERSAL_POSTORDER:
            stop_node = TraversePostOrder(_tree->m_sentinel.m_left, _action, _context);
            break;
    }
    
    if (stop_node) {
        return (BSTreeItr)stop_node;
    }
    
    return BSTreeItrEnd(_tree);
}