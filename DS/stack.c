#include "stack.h"
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, calloc, realloc, free */
#include <assert.h> /* assert */

#define STACK_MAGIC 0xDEADC0DE

struct Stack {
    void** items;       /* Array of pointers to elements */
    size_t capacity;    /* Current max number of items */
    size_t size;        /* Current number of items in stack */
    size_t blockSize;   /* Growth/Shrink factor */
    size_t originalCap; /* Base capacity to prevent shrinking below initial size */
    unsigned int magic; /* Validation token */
};

Stack* StackCreate(size_t _initialCapacity, size_t _blockSize) {
    Stack* stack;
    void** items = NULL;

    /* If both are zero, return NULL as per header warning */
    if (_initialCapacity == 0 && _blockSize == 0) {
        return NULL;
    }

    stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        return NULL;
    }

    if (_initialCapacity > 0) {
        items = (void**)malloc(_initialCapacity * sizeof(void*));
        if (items == NULL) {
            free(stack);
            return NULL;
        }
    }

    stack->items = items;
    stack->capacity = _initialCapacity;
    stack->originalCap = _initialCapacity;
    stack->size = 0;
    stack->blockSize = _blockSize;
    stack->magic = STACK_MAGIC;

    return stack;
}

void StackDestroy(Stack** _stack, void (*_elementDestroy)(void* _item)) {
    size_t i;

    /* Check for NULL pointers or already freed stacks */
    if (_stack == NULL || *_stack == NULL || (*_stack)->magic != STACK_MAGIC) {
        return; 
    }

    /* Destroy elements if a destroy function was provided */
    if (_elementDestroy != NULL) {
        for (i = 0; i < (*_stack)->size; ++i) {
            _elementDestroy((*_stack)->items[i]);
        }
    }

    /* Free the internal array */
    free((*_stack)->items);
    
    /* Invalidate magic number before freeing the struct to catch stale pointers */
    (*_stack)->magic = 0; 
    free(*_stack);
    *_stack = NULL;
}

StackResult StackPush(Stack* _stack, void* _item) {
    void** temp;
    size_t newCapacity;

    if (_stack == NULL || _stack->magic != STACK_MAGIC) {
        return STACK_UNITIALIZED_ERROR;
    }

    /* Check if stack is full */
    if (_stack->size == _stack->capacity) {
        /* Fixed size stack check */
        if (_stack->blockSize == 0) {
            return STACK_ALLOCATION_ERROR; 
        }

        /* Calculate new capacity and reallocate */
        newCapacity = _stack->capacity + _stack->blockSize;
        temp = (void**)realloc(_stack->items, newCapacity * sizeof(void*));
        if (temp == NULL) {
            return STACK_ALLOCATION_ERROR;
        }
        
        _stack->items = temp;
        _stack->capacity = newCapacity;
    }

    _stack->items[_stack->size] = _item;
    _stack->size++;

    return STACK_SUCCESS;
}

StackResult StackPop(Stack* _stack, void** _pValue) {
    void** temp;
    size_t newCapacity;

    if (_stack == NULL || _stack->magic != STACK_MAGIC) {
        return STACK_UNITIALIZED_ERROR;
    }
    
    /* Assert as requested by the header warning */
    assert(_pValue != NULL); 

    if (_stack->size == 0) {
        return STACK_IS_EMPTY;
    }

    *_pValue = _stack->items[_stack->size - 1];
    _stack->size--;

    /* Shrink logic: shrink if empty space >= 2 blocks, and capacity is > original */
    if (_stack->blockSize > 0 && 
        _stack->capacity > _stack->originalCap && 
        (_stack->capacity - _stack->size) >= (_stack->blockSize * 2)) {
        
        newCapacity = _stack->capacity - _stack->blockSize;
        temp = (void**)realloc(_stack->items, newCapacity * sizeof(void*));
        
        /* If realloc fails during shrink, keep old capacity (non-fatal) */
        if (temp != NULL) { 
            _stack->items = temp;
            _stack->capacity = newCapacity;
        }
    }

    return STACK_SUCCESS;
}

StackResult StackTop(Stack* _stack, void** _pValue) {
    if (_stack == NULL || _stack->magic != STACK_MAGIC) {
        return STACK_UNITIALIZED_ERROR;
    }
    
    assert(_pValue != NULL);

    if (_stack->size == 0) {
        return STACK_IS_EMPTY;
    }

    *_pValue = _stack->items[_stack->size - 1];

    return STACK_SUCCESS;
}

size_t StackSize(const Stack* _stack) {
    if (_stack == NULL || _stack->magic != STACK_MAGIC) {
        return 0;
    }
    return _stack->size;
}

size_t StackCapacity(const Stack* _stack) {
    if (_stack == NULL || _stack->magic != STACK_MAGIC) {
        return 0;
    }
    return _stack->capacity;
}

int StackIsEmpty(Stack* _stack) {
    if (_stack == NULL || _stack->magic != STACK_MAGIC) {
        return 1;
    }
    return _stack->size == 0 ? 1 : 0;
}

size_t StackPrint(const Stack* _stack, StackElementAction _action, void* _context) {
    size_t i;
    size_t invocations = 0;

    if (_stack == NULL || _stack->magic != STACK_MAGIC || _action == NULL) {
        return 0;
    }

    /* Iterating bottom to top */
    for (i = 0; i < _stack->size; ++i) {
        invocations++;
        if (_action(_stack->items[i], i, _context) == 0) {
            break;
        }
    }
    
    return invocations;
}

int checkBalancedBrackets(const char* str){
    Stack* stack;
    char c;
    size_t i = 0;
    StackResult res;

    stack = StackCreate(20, 10);
    if (stack == NULL) {
        return STACK_ALLOCATION_ERROR; 
    }
    
    for(i = 0; str[i] != '\0'; i++){
        c = str[i];
        BracketCheck(stack, c);
    }
    if(StackIsEmpty){
        res = STACK_IS_BALANCED;
    }else{
        res = STACK_ISNT_BALANCED;
    }
    StackDestroy(&stack, NULL);
    return res;
}

void BracketCheck(Stack* stack, const char* c){
    if(c == '(' || c =='[' || c == '{'){
        StackPush(stack, c); 
    }
    if(c == ')' && StackPop(stack, c) == '(')
    {
        StackPop(stack, c);
    }
    if(c == ']' && StackPop(stack, c) == '[')
    {
        StackPop(stack, c);
    }
    if(c == '}' && StackPop(stack, c) == '{')
    {
        StackPop(stack, c);
    }
    
}

int postfixEvaluate(const char* expression){
    Stack* stack;
    size_t i = 0;
    char c;
    void* popped_val; 
    int operand1, operand2, result;

    stack = StackCreate(20, 10);
    if (stack == NULL) {
        return 0;
    }

    for(i = 0; expression[i] != '\0'; i++){
        c = expression[i];
        
        if (c == ' ') {
            continue; 
        }

        if(c >= '0' && c <= '9'){
            StackPush(stack, (void*)(size_t)(c - '0')); 
        } else {
            if (StackPop(stack, &popped_val) != STACK_SUCCESS) {
                StackDestroy(&stack, NULL);
                return 0;
            }
            operand2 = (int)(size_t)popped_val;

            if (StackPop(stack, &popped_val) != STACK_SUCCESS) {
                StackDestroy(&stack, NULL);
                return 0; 
            }
            operand1 = (int)(size_t)popped_val;

            switch(c) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': 
                    if (operand2 == 0) {
                        StackDestroy(&stack, NULL);
                        return 0; 
                    }
                    result = operand1 / operand2; 
                    break;
                default: 
                    StackDestroy(&stack, NULL);
                    return 0;
            }
            
            StackPush(stack, (void*)(size_t)result);
        }
    }
    
    if (StackPop(stack, &popped_val) == STACK_SUCCESS) {
        result = (int)(size_t)popped_val;
    } else {
        result = 0;
    }
    
    StackDestroy(&stack, NULL);
    return result;
}

int main() {;
    const char* testExpr = "235*+";
    

    int evalResult = postfixEvaluate(testExpr);

    /* Output results for demonstration */
    printf("Postfix Evaluation Result: %d\n", evalResult);

    return 0;
}