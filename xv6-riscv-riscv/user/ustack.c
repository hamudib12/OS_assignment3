//
// Created by Hamudi Brik on 02/06/2023.
//
#include "ustack.h"

typedef long Align;

union header{
    struct {
        union header *ptr; // next allocate buffer in the stack.
        uint size; // size of the current top of the stack (the last allocated buffer).
        uint length; // len of the buffer.
    }s;
    Align x;
};

typedef union header Header;

static uint remaining_memory = 0; // calculate the remaining free memory in the heap;
static Header *stack_top = 0; //static variable points to the top of the stack.

//---------------------------------------Stack operations----------------------------------------------
void push(Header* buffer){
    buffer->s.ptr = stack_top;
    stack_top = buffer;
}
Header* pop(){
    Header *prev = stack_top;
    stack_top = stack_top->s.ptr;
    return prev;
}
int isEmpty(){
    return stack_top == 0;
}

void* ustack_malloc(uint len){
    if(len > 512){
        return (void*) -1;
    }
    uint nunits = (len + sizeof(Header) - 1)/sizeof(Header) + 1;
    if(stack_top == 0){
        char *new_p;
        if((new_p = sbrk(PGSIZE)) == (char *)-1){
            return (void*) -1;
        }
        remaining_memory = PGSIZE;
        Header *p = (Header*)new_p;
        p->s.size = nunits;
        p->s.length = len;
        remaining_memory -= nunits * sizeof(Header);
        push(p);
        return (void*)stack_top + 1;
    }
    if(remaining_memory >= len){
        Header *p = stack_top + stack_top->s.size; // point to the next of the last allocated memory.
        p->s.size = nunits; // make the size of the new allocated memory as the len.
        p->s.length = len;
        push(p);
        remaining_memory -= nunits * sizeof(Header);
    }
    else{
        Header *p = stack_top + stack_top->s.size;
        if(sbrk(PGSIZE) == (char *)-1){
            return (void*) -1;
        }
        remaining_memory += PGSIZE;
        p->s.size = nunits;
        p->s.length = len;
        remaining_memory -= nunits * sizeof(Header);
        push(p);
    }
    return (void*) stack_top + 1;
}

int ustack_free(void){
    if(isEmpty()){
        return -1;
    }
    Header *free = pop();
    int len = (free->s.size) * sizeof (Header); // calculate the length of the buffer again from the number of memory units.
    uint len2 = free->s.length;
    remaining_memory += len;
    if(remaining_memory >= PGSIZE){
        if(sbrk(-PGSIZE) == (char *)-1){
            return -1;
        }
        remaining_memory -= PGSIZE;
    }
    return len2;
}