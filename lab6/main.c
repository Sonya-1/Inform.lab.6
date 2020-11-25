#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* data;
    char* next;
} node_t;

typedef struct {
    node_t* head;
    node_t* last;
    size_t size;
} list_t;

int char_index(char c, char* str) {
    if (str == NULL) {
        printf("Error 1001: Invalid function call");
        exit(1);
    }

    int i;

    for (i = 0; str[i] > 0; i++) {
        if (c == str[i]) {
            return i;
        }

    }
    if (c == 0) {
        return i;
    }
    return -1;
}


void push(list_t* l, char* str) {
    if (l == NULL || str == NULL) {
        printf("Error 1002: Invalid function call");
        exit(1);
    }
    node_t* n;
    n = (node_t*)malloc(sizeof(node_t));

    if (n == NULL) {
        printf("Allocation error");
        exit(1);
    }

    n->data = str;
    n->next = NULL;

    if (l->head == NULL) {
        l->head = n;
    }
    else {
        l->last->next = (char*)n;
    }
    l->last = n;
    l->size++;
}

char* substring(char* str, int start, int end) {
    int len = end - start;

    if (str == NULL || len < 1 || start < 0 || end < 0) {
        printf("Error 1003: Invalid function call");
        exit(1);
    }

    char* word = (char*)malloc((len + 1) * sizeof(word));

    if (word == NULL) {
        printf("Allocation error");
        exit(1);
    }
    word[len] = 0;

    for (int j = 0; j < len; j++) {
        word[j] = str[start + j];
    }
    return word;
}

void split(list_t* l, char* str, char* separators) {

    if (l == NULL || str == NULL || separators == NULL) {
        printf("Error 1004: Invalid function call");
        exit(1);
    }

    int i, start = 0;

    l->head = NULL;
    l->size = 0;

    for (i = 0; ; i++) {
        if (char_index(str[i], separators) >= 0) {
            if (i - start > 0) {
                push(l, substring(str, start, i));
            }
            start = i + 1;
        }

        if (str[i] == 0) {
            break;
        }
    }
}



char* pop(list_t* l) {
    if (l == NULL || l->size < 1) {
        printf("Error 1005: Empty list");
        exit(1);
    }

    node_t* n = l->head;
    char* str = n->data;

    l->head = (node_t*)n->next;
    l->size -= 1;
    free(n);

    return str;
}

char* read_file(char* file_name) {
    if (file_name == NULL) {
        printf("Error 1006: file_name is NULL");
        exit(1);
    }
    FILE* fp;
    int i, n;
    const int max_file_size = 10000;

    char* buffer = (char*)malloc(max_file_size * sizeof(*buffer));

    if (buffer == NULL) {
        printf("Allocation error");
        exit(1);
    }

    for (i = 0; i < max_file_size; i++) {
        buffer[i] = 0;
    }

    fp = fopen(file_name, "r");

    if (fp == NULL || fp == 0) {
        perror("ERROR 1007");
        return NULL;
    }

    n = fread(buffer, max_file_size, 1, fp);

    fclose(fp);

    if (n > 0) {
        printf("ERROR 1008: File too long %i", n);
        return NULL;
    }
    return buffer;
}


void concat(list_t* l, list_t* l2) {
    node_t* n = l->last;

    n->next = (char*)l2->head;
    l->last = l2->last;
    l->size += l2->size;
}


void print_list(list_t* l) {
    char* str;
    int i = 0;

    while (l->size > 0) {
        str = pop(l);
        printf("%i\t%s\n", i, str);
        free(str);
        i += 1;
    }
}


int main() {
    char my_file[] = "/tmp/file.txt";
    char my_file2[] = "/tmp/file2.txt";
    char* arr, * arr2;
    char* separators = " \t\n,.;:!?/~`@#$%^&*(){}[]\"|'/<>-=_+1234567890";
    list_t l, l2;

    arr = read_file(my_file);
    arr2 = read_file(my_file2);

    if (arr == NULL || arr2 == NULL) {
        return 1;
    }

    split(&l, arr, separators);
    split(&l2, arr2, separators);
    concat(&l, &l2);
    print_list(&l);

    return 0;
}