#include "Enclave_t.h"
#include <string.h>
#include <stdio.h>
#include "../eType.h"

struct eObj *obj, *obj2, *obj3;

int printf(const char *fmt, ...) {
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
    return (int) strnlen(buf, BUFSIZ - 1) + 1;
}

void ecall_create() {
    obj = (struct eObj *) malloc(sizeof(struct eObj));
    obj->flag = 1;
    memcpy(obj->ch, "hello", 6);
    printf("obj: %p %s\n", obj, obj->ch);
}

void ecall_evil(){
    obj2 = (struct eObj *) malloc(sizeof(struct eObj));
    obj2->flag = 1;
    memcpy(obj2->ch, "uaf2", 5);
    printf("obj2: %p %s\n", obj2, obj2->ch);

    obj3 = (struct eObj *) malloc(sizeof(struct eObj));
    obj3->flag = 1;
    memcpy(obj3->ch, "uaf3", 5);
    printf("obj3: %p %s\n", obj3, obj3->ch);
}

void ecall_use() {
    if (obj == 0) {
        return;
    }
    if (obj->flag == 1) {
        printf("obj->ch=%s\n", obj->ch);
    } else {
        printf("obj->flag=%d\n", obj->flag);
    }
}

void ecall_destroy() {
    if (obj == 0)
        return;
    free(obj);
}

