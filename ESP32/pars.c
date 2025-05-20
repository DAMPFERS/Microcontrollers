#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_FILE_SIZE (10 * 1024 * 1024)  // до 10 МБ
#define MAX_FUNCTIONS 16

typedef struct {
    uint8_t name_func;
    uint8_t num_vars;
    uint8_t *bit_vector;
    int bit_vector_len;
    uint16_t var_mask;
} Function;

typedef struct {
    int id;
    int type;
    int speed;
    char *text;
    Function functions[MAX_FUNCTIONS];
    int function_count;
} BinFile;





char *read_file(const char *filename, long *out_size);          // Функция для чтения всего файла в буфер
int parse_int(const char *buf, const char *label);              // Парсинг целочисленного поля по метке
char *parse_quoted_text(const char *buf, const char *label);    // Парсинг строки TEXT между кавычками
void parse_funcs(const char *buf);                              // Парсинг блока FUNC…END
void parse_func2(const char *buf);


int main() {
    // if (argc < 2) {
    //     printf("Использование: %s <файл.bin>\n", argv[0]);
    //     return 1;
    // }
    long size;
    char *buf = read_file("test.bin", &size);
    if (!buf) return 1;

    int id    = parse_int(buf, "ID=");
    int type  = parse_int(buf, "TYPE=");
    int speed = parse_int(buf, "SPEED=");
    printf("ID    = %d\n", id);
    printf("TYPE  = %d\n", type);
    printf("SPEED = %d\n", speed);

    char *text = parse_quoted_text(buf, "TEXT=");
    if (text) {
        printf("TEXT  = \"%s\"\n", text);
        free(text);
    } else {
        printf("TEXT не найден\n");
    }

    // parse_func2(buf);

    free(buf);
    return 0;
}


// Функция для чтения всего файла в буфер
char *read_file(const char *filename, long *out_size) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("Не удалось открыть файл");
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size <= 0 || size > MAX_FILE_SIZE) {
        printf("Неподходящий размер файла: %ld\n", size);
        fclose(f);
        return NULL;
    }
    char *buf = malloc(size + 1);
    if (!buf) {
        perror("malloc");
        fclose(f);
        return NULL;
    }
    fread(buf, 1, size, f);
    fclose(f);
    buf[size] = '\0';
    if (out_size) *out_size = size;
    return buf;
}

// Парсинг целочисленного поля по метке
int parse_int(const char *buf, const char *label) {
    char *p = strstr(buf, label);
    if (!p) return -1;
    p += strlen(label);
    return (int)strtol(p, NULL, 10);
}

// Парсинг строки TEXT между кавычками
char *parse_quoted_text(const char *buf, const char *label) {
    char *p = strstr(buf, label);
    if (!p) return NULL;
    p = strchr(p, '"');
    if (!p) return NULL;
    char *q = strchr(p + 1, '"');
    if (!q) return NULL;
    size_t len = q - p - 1;
    char *out = malloc(len + 1);
    if (!out) return NULL;
    memcpy(out, p + 1, len);
    out[len] = '\0';
    return out;
}

// Парсинг блока FUNC…END
/*
void parse_funcs(const char *buf) {


    // // Сначала создаём изменяемую копию буфера
    // size_t len = strlen(buf);
    // char *buf_copy = malloc(len + 1);
    // if (!buf_copy) {
    //     perror("malloc");
    //     return;
    // }
    // strcpy(buf_copy, buf); // копируем строку

    // Нормализуем: заменим \r на пробел или \n
    // for (char *p = buf_copy; *p; ++p) {
    //     if (*p == '\r' || *p == '\n') *p = ' ';
    // }

    // Далее работаем с buf_copy вместо buf
    char *start = strstr(buf, "FUNC");
    if (!start) {
        printf("Блок FUNC не найден\n");
        free(buf);
        return;
    }

    char *end = strstr(start, "END");
    if (!end) {
        printf("Блок END не найден\n");
        end = start + strlen(start);
    }

    printf("Найден блок FUNC:\n");
    // Копируем блок между FUNC и END в отдельный буфер
    size_t block_len = end - start;
    printf("%ld\n", block_len);
    char *block = malloc(block_len + 1);
    if (!block) {
        perror("malloc");
        return;
    }
    memcpy(block, start, block_len);
    block[block_len] = '\0';

    // Работаем послойно по строкам
    char *line_ctx;
    char *line = strtok_r(block, "\r\n", &line_ctx);
    while (line) {
        if (line[0] == 'F' && isdigit((unsigned char)line[1])) {
            int func_id;
            if (sscanf(line, "F%d=", &func_id) == 1) {
                printf(" Function F%d:\n", func_id);
                // Извлечение всех 0x.. значений
                char *params = strchr(line, '=');
                if (params) {
                    params++;
                    int values[32];
                    int cnt = 0;
                    char *token_ctx;
                    char *token = strtok_r(params, ";", &token_ctx);
                    while (token && cnt < 32) {
                        char *h = strstr(token, "0x");
                        if (h) {
                            unsigned int v = (unsigned int)strtoul(h, NULL, 0);
                            values[cnt++] = v;
                        }
                        token = strtok_r(NULL, ";", &token_ctx);
                    }
                    if (cnt >= 1) {
                        int var_count = values[0];
                        printf("  Число переменных: %d\n", var_count);
                        int total_vals = 1 << var_count;
                        int vec_bytes = (total_vals + 7) / 8;
                        printf("  Вектор истинности (%d байт):", vec_bytes);
                        for (int i = 1; i <= vec_bytes && i < cnt; ++i) {
                            printf(" 0x%02X", values[i]);
                        }
                        printf("\n");
                        if (cnt >= 1 + vec_bytes + 2) {
                            printf("  Маска: 0x%02X 0x%02X\n",
                                values[1 + vec_bytes], values[2 + vec_bytes]);
                        }
                    } else {
                        printf("  Пустой набор значений\n");
                    }
                }
            }
        }
        line = strtok_r(NULL, "\r\n", &line_ctx);
    }

    free(block);
    // free(buf_copy);
}*/



void parse_func2(const char *buf){


    Function f = {0};
    int start;
    int end;

    for(end = 0; !((*(buf+end) == 'E') && (*(buf+end + 1) == 'N') && (*(buf+end + 2) == 'D')); ++end)
        if(((*(buf+end) == 'F') && (*(buf+end + 1) == 'U') && (*(buf+end + 2) == 'N') && (*(buf+end + 3) == 'C')))
            start = end + strlen("FUNC\n\r");
    

    size_t len = (size_t)(end - start);
    char *buf_func = malloc(len);
    if (!buf_func) {
        perror("malloc");
        return;
    }

    for(int i = start; i < end; ++i){
        // printf("%c", *(buf+i));
        *(buf_func + i - start) = *(buf+i);
        printf("%c", *(buf_func + i - start)); 
    }

    uint8_t count_func = 0;
    for(int i = start; i < end; ++i){
        if((*(buf+i) == '\r') && (*(buf+i+1) == '\n')) 
            count_func++;  
    }

    char *funcs = malloc((size_t)count_func);
    if (!funcs) {
        perror("malloc");
        return;
    }


    char num_vars;
    char *a;
    a = buf;

    for( ; count_func > 0; count_func--){
        if(*buf_func == 'F'){
            // ++a;
            // *funcs = *buf_func;
        } 
        
        // if(*++buf_func == '=')
            // num_vars = *++buf_func; 
    }
    
    printf("%c", a[0]);

    
        
    
    free(buf_func);
    return;
}