#include <stdio.h> 

#include <stdlib.h> 

#include <string.h> 

 

typedef struct node *employee; 

typedef struct node { 

    int empid; 

    char name[50]; 

    float salary; 

    char designation[50]; 

    employee link; 

}; 

 

employee first = NULL; 

 

// Function to check if an employee ID already exists 

int empid_exists(int empid) { 

    employee temp = first; 

    while (temp != NULL) { 

        if (temp->empid == empid) { 

            return 1; 

        } 

        temp = temp->link; 

    } 

    return 0; 

} 

 

// Function to insert N employees initially 

void insert_initial(int n) { 

    for (int i = 0; i < n; i++) { 

        insert_employee(); 

    } 

} 

 

// Function to insert a single employee 

void insert_employee() { 

    int empid; 

    employee newnode = (employee)malloc(sizeof(struct node)); 

 

    printf("Enter employee ID: "); 

    scanf("%d", &empid); 

 

    // Check if the empid already exists 

    if (empid_exists(empid)) { 

        printf("Employee ID %d already exists. Duplicate IDs are not allowed.\n", empid); 

        free(newnode);  // Free the allocated memory if not used 

        return; 

    } 

 

    newnode->empid = empid; 

 

    printf("Enter employee name: "); 

    scanf("%s", newnode->name); 

 

    printf("Enter employee salary: "); 

    scanf("%f", &newnode->salary); 

 

    printf("Enter employee designation: "); 

    scanf("%s", newnode->designation); 

 

    newnode->link = first; 

    first = newnode; 

    printf("Employee added successfully.\n"); 

} 

 

void search_employee(int id) { 

    employee temp = first; 

 

    while (temp != NULL) { 

        if (temp->empid == id) { 

            printf("Employee found:\n"); 

            printf("ID: %d, Name: %s, Salary: %.2f, Designation: %s\n", temp->empid, temp->name, temp->salary, temp->designation); 

            return; 

        } 

        temp = temp->link; 

    } 

    printf("Employee with ID %d not found.\n", id); 

} 

 

void average_salary_manager() { 

    employee temp = first; 

    int count = 0; 

    float total_salary = 0.0; 

 

    while (temp != NULL) { 

        if (strcmp(temp->designation, "Manager") == 0) { 

            total_salary += temp->salary; 

            count++; 

        } 

        temp = temp->link; 

    } 

 

    if (count == 0) { 

        printf("No employees with designation 'Manager' found.\n"); 

    } else { 

        printf("Average salary of Managers: %.2f\n", total_salary / count); 

    } 

} 

 

void display_list() { 

    employee temp = first; 

    if (first == NULL) { 

        printf("Employee list is empty.\n"); 

        return; 

    } 

 

    printf("\nEmployee List:\n"); 

    while (temp != NULL) { 

        printf("ID: %d, Name: %s, Salary: %.2f, Designation: %s\n", temp->empid, temp->name, temp->salary, temp->designation); 

        temp = temp->link; 

    } 

} 

 

int main() { 

    int n, id, ch; 

 

    printf("Enter the number of employees to insert initially: "); 

    scanf("%d", &n); 

    insert_initial(n); 

 

    while (1) { 

        printf("\n1. Insert Employee\n2. Search Employee\n3. Display All Employees\n4. Average Salary of Managers\n5. Exit\nEnter your choice: "); 

        scanf("%d", &ch); 

        switch (ch) { 

            case 1: 

                insert_employee(); 

                break; 

            case 2: 

                printf("Enter the employee ID to search: "); 

                scanf("%d", &id); 

                search_employee(id); 

                break; 

            case 3: 

                display_list(); 

                break; 

            case 4: 

                average_salary_manager(); 

                break; 

            case 5: 

                exit(0); 

            default: 

                printf("Invalid choice...\n"); 

                break; 

        } 

    } 

    return 0; 

} 