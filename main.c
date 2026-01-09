#include <stdio.h>
#include "student.h"

int main()
{
    int choice, id;

    do
    {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Sort Students by Marks\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            printf("Enter ID to search: ");
            scanf("%d", &id);
            searchStudentById(id);
            break;
        case 4:
            printf("Enter ID to update: ");
            scanf("%d", &id);
            updateStudentById(id);
            break;
        case 5:
            printf("Enter ID to delete: ");
            scanf("%d", &id);
            deleteStudentById(id);
            break;
        case 6:
            sortStudentsByMarks();
            break;

        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);
}