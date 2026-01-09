#ifndef STUDENT_H
#define STUDENT_h

typedef struct 
{
    int id;
    char name[50];
    int age;
    float  marks;
} Student;

void addStudent(void);
void displayStudents(void);
void searchStudentById(int id);
void updateStudentById(int id);
void deleteStudentById(int id);
void sortStudentsByMarks(void);


#endif
