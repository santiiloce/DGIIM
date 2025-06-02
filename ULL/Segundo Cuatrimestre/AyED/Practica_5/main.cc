#include <iostream>

#include "stack_l_t.h"
#include "queue_l_t.h"
#include "rpn_t.h"

int main(){
    queue_l_t<float> ejemplo, other, fuze;
    ejemplo.write();
    ejemplo.push(2);
    ejemplo.push(2);
    ejemplo.push(3);
    ejemplo.push(4);
    ejemplo.push(2);
    ejemplo.push(6);
    ejemplo.push(6);
    ejemplo.push(8);
    ejemplo.push(3);
    ejemplo.push(8);
    other.push(-1);
    other.push(-4);
    other.push(-5);
    other.push(-12);
    other.push(-112);
    other.push(-9);



    ejemplo.write();
    ejemplo.erase_repetition();
    ejemplo.write();
}