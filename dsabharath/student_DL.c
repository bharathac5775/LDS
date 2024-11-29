#include <stdio.h> 

#include <stdlib.h> 

#include <string.h> 

 

typedef struct node { 

    int studentID; 

    char name[50]; 

    float mathScore; 

    float scienceScore; 

    float englishScore; 

    struct node *llink; 

    struct node *rlink; 

} Student; 

 

typedef Student* student; 

student head = NULL; 

 

// Check if a student ID already exists 

int studentID_exists(int studentID) { 

    student temp = head; 

    while (temp != NULL) { 

        if (temp->studentID == studentID) { 

            return 1; 

        } 

        temp = temp->rlink; 

    } 

    return 0; 

} 

 

// Insert a new student into the doubly linked list 

void insert_student() { 

    int studentID; 

    student newnode, temp; 

 

    printf("Enter student ID: "); 

    scanf("%d", &studentID); 

    if (studentID_exists(studentID)) { 

        printf("Student ID %d already exists. Duplicate IDs are not allowed.\n", studentID); 

        return; 

    } 

 

    newnode = (student)malloc(sizeof(Student)); 

    newnode->studentID = studentID; 

 

    printf("Enter student name: "); 

    scanf("%s", newnode->name); 

 

    printf("Enter Math score: "); 

    scanf("%f", &newnode->mathScore); 

 

    printf("Enter Science score: "); 

    scanf("%f", &newnode->scienceScore); 

 

    printf("Enter English score: "); 

    scanf("%f", &newnode->englishScore); 

 

    newnode->llink = NULL; 

    newnode->rlink = NULL; 

 

    // Insert node at the end 

    if (head == NULL) { 

        head = newnode; 

    } else { 

        temp = head; 

        while (temp->rlink != NULL) { 

            temp = temp->rlink; 

        } 

        temp->rlink = newnode; 

        newnode->llink = temp; 

    } 

} 

 

// Search for a student by ID and display details 

void search_student(int studentID) { 

    student temp = head; 

 

    while (temp != NULL) { 

        if (temp->studentID == studentID) { 

            printf("Student found:\n"); 

            printf("ID: %d, Name: %s, Math: %.2f, Science: %.2f, English: %.2f\n", 

                   temp->studentID, temp->name, temp->mathScore, temp->scienceScore, temp->englishScore); 

            return; 

        } 

        temp = temp->rlink; 

    } 

    printf("Student with ID %d not found.\n", studentID); 

} 

 

// Display students who scored above 90 in both Math and Science 

void display_students_above_90() { 

    student temp = head; 

    int found = 0; 

 

    printf("Students who scored above 90 in Math and Science:\n"); 

    while (temp != NULL) { 

        if (temp->mathScore > 90 && temp->scienceScore > 90) { 

            printf("ID: %d, Name: %s, Math: %.2f, Science: %.2f, English: %.2f\n", 

                   temp->studentID, temp->name, temp->mathScore, temp->scienceScore, temp->englishScore); 

            found = 1; 

        } 

        temp = temp->rlink; 

    } 

    if (!found) { 

        printf("No students found with scores above 90 in both Math and Science.\n"); 

    } 

} 

 

// Display all students 

void display_all_students() { 

    student temp = head; 

    if (head == NULL) { 

        printf("No students in the list.\n"); 

        return; 

    } 

 

    printf("\nAll Student Details:\n"); 

    while (temp != NULL) { 

        printf("ID: %d, Name: %s, Math: %.2f, Science: %.2f, English: %.2f\n", 

               temp->studentID, temp->name, temp->mathScore, temp->scienceScore, temp->englishScore); 

        temp = temp->rlink; 

    } 

} 

 

int main() { 

    int studentID, choice, n; 

 

    printf("Enter the number of students to insert: "); 

    scanf("%d", &n); 

 

    // Insert multiple students 

    for (int i = 0; i < n; i++) { 

        printf("\nEnter details for student %d:\n", i + 1); 

        insert_student(); 

    } 

 

    while (1) { 

        printf("\n1. Insert Student\n2. Search Student\n3. Display All Students\n4. Display Students Scoring Above 90 in Math & Science\n5. Exit\nEnter your choice: "); 

        scanf("%d", &choice); 

        switch (choice) { 

            case 1: 

                printf("Enter student details:\n"); 

                insert_student(); 

                display_all_students(); 

                break; 

            case 2: 

                printf("Enter the student ID to search: "); 

                scanf("%d", &studentID); 

                search_student(studentID); 

                break; 

            case 3: 

                display_all_students(); 

                break; 

            case 4: 

                display_students_above_90(); 

                break; 

            case 5: 

                exit(0); 

            default: 

                printf("Invalid choice.\n"); 

        } 

    } 

 

    return 0; 

} 