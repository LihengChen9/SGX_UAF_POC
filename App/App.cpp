#include "Enclave_u.h"
#include "sgx_urts.h"
#include <stdio.h>

#define ENCLAVE_FILENAME "enclave.signed.so"
sgx_enclave_id_t global_eid = 0;

void ocall_print_string(const char *str) {
    printf("%s", str);
}

int main() {
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, NULL, NULL, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
        printf("Error: creating enclave\n");
        return -1;
    }

    ret = ecall_create(global_eid);
    if (ret != SGX_SUCCESS) {
        printf("Error: Making an ecall_create()\n");
        return -1;
    }

    ret = ecall_destroy(global_eid);
    if (ret != SGX_SUCCESS) {
        printf("Error: Making an ecall_destroy()\n");
        return -1;
    }

    ret = ecall_evil(global_eid);
    if (ret != SGX_SUCCESS) {
        printf("Error: Making an ecall_evil()\n");
        return -1;
    }

    ret = ecall_use(global_eid);
    if (ret != SGX_SUCCESS) {
        printf("Error: Making an ecall_use()\n");
        return -1;
    }

    ret = sgx_destroy_enclave(global_eid);
    if (ret != SGX_SUCCESS) {
        printf("Error: destroying enclave\n");
        return -1;
    }

    return 0;
}
