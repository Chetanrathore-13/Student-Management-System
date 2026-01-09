#include <stdio.h>
#include <stdlib.h>
#include "student.h"

/* Add student */
void addStudent(void) {
    FILE *fp;
    Student s;

    fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("\nStudent added successfully!\n");
}

/* Display all students */
void displayStudents(void) {
    FILE *fp;
    Student s;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("\nID: %d", s.id);
        printf("\nName: %s", s.name);
        printf("\nAge: %d", s.age);
        printf("\nMarks: %.2f\n", s.marks);
        printf("----------------------");
    }

    fclose(fp);
}

/* Search student by ID */
void searchStudentById(int id) {
    FILE *fp;
    Student s;
    int found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nFile not found.\n");
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            printf("\nStudent Found!");
            printf("\nID: %d", s.id);
            printf("\nName: %s", s.name);
            printf("\nAge: %d", s.age);
            printf("\nMarks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent with ID %d not found.\n", id);
    }

    fclose(fp);
}

void updateStudentById(int id) {
    FILE *fp, *temp;
    Student s;
    int found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("\nError creating temp file.\n");
        fclose(fp);
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            printf("\nStudent Found. Enter new details:\n");

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            found = 1;
        }

        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nStudent updated successfully!\n");
    else
        printf("\nStudent with ID %d not found.\n", id);
}

void deleteStudentById(int id) {
    FILE *fp, *temp;
    Student s;
    int found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("\nError creating temp file.\n");
        fclose(fp);
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            found = 1;   // skip writing this record
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nStudent deleted successfully!\n");
    else
        printf("\nStudent with ID %d not found.\n", id);
}

void sortStudentsByMarks(void) {
    FILE *fp;
    Student *arr;
    int count = 0, i, j;
    Student temp;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    // Count number of students
    fseek(fp, 0, SEEK_END);
    count = ftell(fp) / sizeof(Student);
    rewind(fp);

    if (count == 0) {
        printf("\nNo students to sort.\n");
        fclose(fp);
        return;
    }

    // Allocate memory
    arr = (Student *)malloc(count * sizeof(Student));
    if (arr == NULL) {
        printf("\nMemory allocation failed.\n");
        fclose(fp);
        return;
    }

    // Read data into array
    fread(arr, sizeof(Student), count, fp);
    fclose(fp);

    // Bubble sort (descending by marks)
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (arr[j].marks < arr[j + 1].marks) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Display sorted students
    printf("\n--- Students Sorted by Marks (High to Low) ---\n");
    for (i = 0; i < count; i++) {
        printf("\nID: %d", arr[i].id);
        printf("\nName: %s", arr[i].name);
        printf("\nAge: %d", arr[i].age);
        printf("\nMarks: %.2f", arr[i].marks);
        printf("\n-----------------------------");
    }

    free(arr);
}
