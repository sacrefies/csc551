#include <stdio.h>

/**************************************/
/* Do swapping                        */
/**************************************/
void swap(char* data) {
    char tmp = data[0];
    data[0] = data[3];
    data[3] = tmp;
    tmp = data[1];
    data[1] = data[2];
    data[2] = tmp;
}

int main(int argc, char* argv[]) {
    int  k = 0x0a0b0c0d;
    printf("k before swap is: %08x\n", k);
    swap((char*)&k);
    printf("k after swap is: %08x\n", k);

    return 0;
}