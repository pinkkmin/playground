#include <iostream>
#include <stdio.h>

uintptr_t  start_address = 0x0;
uintptr_t  end_addresss = 0x0;
void foo() {
    int a = 9;
    end_addresss = reinterpret_cast<uintptr_t>(&a);
    printf("foo:0x%x\n", &end_addresss);
}

void bar () {
    int b = 8;
    start_address = reinterpret_cast<uintptr_t>(&b);
    printf("bar:0x%x\n", start_address);
    foo();
}

int main() {
    int c  =4;
    printf("main:0x%x\n", reinterpret_cast<uintptr_t>(&c));
    bar();

    if(start_address > end_addresss) {
        printf ("stack grow: hight address ---> low address \n");
    }
    else {
        printf ("stack grow: hight address <--- low address \n");
    }
    return 0;
}

/* stack(call stack) layout IS NOT stack frame(ABI) layout */