
#include <stdio.h>

#ifdef offsetof
    #undef offsetof
    #define offsetof(TYPE, FIELD) ((size_t) &((TYPE *)0)->FIELD)
#else
    #define offsetof(TYPE, FIELD) ((size_t) &((TYPE *)0)->FIELD)
#endif

#ifdef container_of
    #undef container_of
    #define container_of(ptr, TYPE, FIELD) ({ \
        const typeof( ((TYPE*)0)->FIELD) *__mptr = (ptr);                  \
        (TYPE*)( (char*)__mptr - offsetof(TYPE, FIELD) );})
#else
    #define container_of(ptr, TYPE, FIELD) ({ \
        const typeof( ((TYPE*)0)->FIELD) *__mptr = (ptr);                  \
        (TYPE*)( (char*)__mptr - offsetof(TYPE, FIELD) );})
#endif

typedef struct _person {
    char name[12];
    int  age;
    double salary;
} Person;

int main() {
    
    printf("the offset of age in Person = %d\n", offsetof(Person, age));
    Person xuwei = {.name="xuwei", .age=23, .salary = 3000.0};
    
    double *s = &(xuwei.salary);
    Person *ptr = container_of(s, Person, salary);
    
    printf("xuwei's address = %p\n", &xuwei);
    printf("prt's value = %p\n", ptr);
    
    // lambda表达式
    int a = ({
        int func(Person* person){
            person->age = 24;
            return person->age;
        }
        func(ptr);});
    
    printf("a = %d\n", a);
    printf("xuwei's age = %d\n", xuwei.age);
    return 0;
}
