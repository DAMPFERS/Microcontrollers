#include <stdio.h>
#include <string.h>

int main(void){
    char a[] = "Hello Russia";
    for(int i = 0; i < strlen(a); i++){
        for(int j = 0; j < 8; j++){
            printf("%d", (a[i] >> (7-j)) & 0x01);
        }
        printf(" ");
    }
    return 0;
}