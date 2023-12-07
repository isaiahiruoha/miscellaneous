#include <stdio.h>

// Struct Example
struct Student {
    char name[50];
    int age;
    float marks;
}; // This differs from an union in that it can hold all of the values at a time

// Typedef Example
typedef struct Student Student;
// This allows us to use Student as a type instead of having to type struct Student every time

// Enum Example
enum Weekday {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};
// This allows us to use the names of the days instead of having to remember the numbers, monday would be 0, tuesday would be 1, etc.

// Union Example
union Data {
    int i;
    float f;
    char str[20];
};
// This differs from a struct in that it can only hold one of the values at a time

// Pointer Examples
void pointerExample() {
    int var = 20;
    int *ip;
    ip = &var;
    printf("Address of var variable: %p\n", &var);
    printf("Address stored in ip variable: %p\n", ip);
    printf("Value of *ip variable: %d\n", *ip);
}

// Struct Pointer Example With Arrow Syntax
void structPointerExample() {
    struct Student student = {"John", 18, 90.5};
    struct Student *studentPointer;
    studentPointer = &student;
    printf("Name: %s\n", studentPointer->name); // This is the same as (*studentPointer).name
    printf("Age: %d\n", studentPointer->age);
    printf("Marks: %f\n", studentPointer->marks);
} 

int main () {
    // Function calls and examples printed
    pointerExample();
    structPointerExample();
    return 0;
}