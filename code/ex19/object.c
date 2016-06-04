#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

int Object_init(void *self)
{
    // do nothing really
    return 1;
}

void Object_describe(void *self)
{
    Object *obj = self;
    printf("%s.\n", obj->description);
}

void Object_destroy(void *self)
{
    Object *obj = self;

    if(obj) {
        if(obj->description) free(obj->description);
        free(obj);
    }
}

void *Object_move(void *self, Direction direction)
{
    printf("You can't do that direction.\n");
    return NULL;
}

int Object_attack(void *self, int damage)
{
    printf("You can't attack that.\n");
    return 0;
}

void *Object_new(size_t size, Object proto, char *description)
{
    // setup the default functions in case they aren't set
    // This all happens on the stack (as proto is passed by value - so a seperate copy of it is created on the stack)
    if(!proto.init) proto.init = Object_init;
    if(!proto.describe) proto.describe = Object_describe;
    if(!proto.destroy) proto.destroy = Object_destroy;
    if(!proto.attack) proto.attack = Object_attack;
    if(!proto.move) proto.move = Object_move;

    // this seems weird, but we can make a struct of one size,
    // then point a different pointer at it to "cast" it
    Object *el = calloc(1, size); // So here we get a chunk of memory on the heap, the pointer is of type Object (calloc initializes all memory to 0)
    *el = proto; // set value on the heap (i.e. * is read as 'value of el', i.e. whatever el points at). This happens to be our chunk of memory (proto can be longer than sizeof(Object))

    // copy the description over
    el->description = strdup(description);

    // initialise it with whatever init we were given
    if(!el->init(el)) {
        // looks like it didn't initialise properlly
        el->destroy(el);
        return NULL;
    } else {
        // all done, we made an object of any type
        assert(el != NULL);
        return el;
    }
}
