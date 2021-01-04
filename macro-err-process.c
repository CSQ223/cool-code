/*
 * err process: about how to use macro-spanning deal with error code and error message
 */
#include <stdio.h>

#define FOREACH_ERR(F) \
    F(0,    OK,         "ok")            \
    F(1000, UNKNOWN,    "Unknown error") \
    F(1001, NULL_PARAM, "Null parameter")

enum {
#define F(errcode, name, errmsg) ERR_##name = errcode,
    FOREACH_ERR(F)
#undef F
};

const char* get_errmsg(int err_code) {
    switch(err_code) {
#define F(errcode, name, errmsg)\
        case errcode: return errmsg;
        FOREACH_ERR(F)
#undef F
        default:
            return "Undefined error";
    }
}

int main() {
    int err_code;
    scanf("%d", &err_code);
    
    printf("%s\n", get_errmsg(err_code));

    return 0;
}
