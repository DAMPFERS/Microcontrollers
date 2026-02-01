#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *add(const char *a, const char *b) {
    size_t a_index = strlen(a);
    size_t b_index = strlen(b);
    size_t max_size = a_index >= b_index ? a_index : b_index;
    if (a_index == b_index) {
        max_size = (a[0] - '0') + (b[0] - '0') > 9 ? max_size + 1 : max_size;
    }
   
    char *res = calloc(max_size+1, sizeof(char));
    
    if (a_index > b_index)
        memcpy(res, a, sizeof(a));
    else if (a_index < b_index)
        memcpy(res, b, sizeof(b));
    else 
        for(size_t i = 0; i < max_size; i++)
            res[i] = '0';
    printf("%d\n%d\n%s\n", max_size, sizeof(res), res);
    int cary = 0;
    while (1) {
        printf("%d %d %d (%d)\n", a_index, b_index, max_size, cary);
        if ((a_index > 0) && (b_index > 0)) {
            int s = (a[(a_index--) - 1] - '0') + (b[(b_index--) - 1] - '0') + cary;
            cary = s > 9 ? 1 : 0;
            s = s > 9 ? s - 10: s;

            res[(max_size--) - 1] = s + '0';
        }
        else if (max_size > 0) {
            int c = (res[max_size-1] - '0' + cary) > 9 ? 1 : 0;
            res[max_size-1] = (res[max_size-1] - '0' + cary) > 9 ? '0' : ( res[max_size-1] + cary);
            cary = c;
            max_size--;
        }
        else return res;      
    }

}



int main(void) {
    char* a = add("9999", "1");
    printf("%s\n", a);
    free(a);
    return 0;
}