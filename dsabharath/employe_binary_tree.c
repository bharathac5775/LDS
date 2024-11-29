 #include <stdio.h> 

#include <stdlib.h> 

#include <string.h> 

 

typedef struct node { 

    int id; 

    char name[50]; 

    int age; 

    float salary; 

    struct node *llink; 

    struct node *rlink; 

} Employee; 

 

typedef Employee* emp; 

emp head = NULL; 

 

// Check if an employee ID already exists 

int employeeID_exists(int id) { 

    emp temp = head; 

    while (temp != NULL) { 

        if (temp->id == id) { 

            return 1; 

        } 

        temp = temp->rlink; 

    } 

    return 0; 

} 

 

// Insert a new employee into the doubly linked list 

void insert_employee() { 

    int id; 

    emp newnode, temp; 

 

    printf("Enter employee ID: "); 

    scanf("%d", &id); 

    if (employeeID_exists(id)) { 

        printf("Employee ID %d already exists. Duplicate IDs are not allowed.\n", id); 

        return; 

    } 

 

    newnode = (emp)malloc(sizeof(Employee)); 

    newnode->id = id; 

 

    printf("Enter employee name: "); 

    scanf("%s", newnode->name); 

 

    printf("Enter Age: "); 

    scanf("%d", &newnode->age); 

 

    printf("Enter Salary: "); 

    scanf("%f", &newnode->salary); 

 

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

 

// Search for an employee by ID and display details 

void search_employee(int id) { 

    emp temp = head; 

 

    while (temp != NULL) { 

        if (temp->id == id) { 

            printf("Employee found:\n"); 

            printf("ID: %d, Name: %s, Age: %d, Salary: %.2f\n", 

                   temp->id, temp->name, temp->age, temp->salary); 

            return; 

        } 

        temp = temp->rlink; 

    } 

    printf("Employee with ID %d not found.\n", id); 

} 

 

// Display employees between ages 20 and 25 and calculate average salary 

void display_employees_age_20_to_25() { 

    emp temp = head; 

    int count = 0; 

    float total_salary = 0; 

 

    printf("Employees between age 20 and 25:\n"); 

    while (temp != NULL) { 

        if (temp->age >= 20 && temp->age <= 25) { 

            printf("ID: %d, Name: %s, Age: %d, Salary: %.2f\n", 

                   temp->id, temp->name, temp->age, temp->salary); 

            total_salary += temp->salary; 

            count++; 

        } 

        temp = temp->rlink; 

    } 

 

    if (count == 0) { 

        printf("No employees found between age 20 and 25.\n"); 

    } else { 

        printf("Average Salary of Employees between age 20 and 25: %.2f\n", total_salary / count); 

    } 

} 

 

// Display all employees 

void display_all_employees() { 

    emp temp = head; 

    if (head == NULL) { 

        printf("No employees in the list.\n"); 

        return; 

    } 

 

    printf("\nAll Employee Details:\n"); 

    while (temp != NULL) { 

        printf("ID: %d, Name: %s, Age: %d, Salary: %.2f\n", 

               temp->id, temp->name, temp->age, temp->salary); 

        temp = temp->rlink; 

    } 

} 

 

int main() { 

    int id, choice, n; 

 

    printf("Enter the number of employees to insert: "); 

    scanf("%d", &n); 

 

    // Insert multiple employees 

    for (int i = 0; i < n; i++) { 

        printf("\nEnter details for employee %d:\n", i + 1); 

        insert_employee(); 

    } 

 

    while (1) { 

        printf("\n1. Insert Employee\n2. Search Employee\n3. Display All Employees\n4. Display Employees between Age 20 and 25 with Average Salary\n5. Exit\nEnter your choice: "); 

        scanf("%d", &choice); 

        switch (choice) { 

            case 1: 

                printf("Enter employee details:\n"); 

                insert_employee(); 

                display_all_employees(); 

                break; 

            case 2: 

                printf("Enter the employee ID to search: "); 

                scanf("%d", &id); 

                search_employee(id); 

                break; 

            case 3: 

                display_all_employees(); 

                break; 

            case 4: 

                display_employees_age_20_to_25(); 

                break; 

            case 5: 

                exit(0); 

            default: 

                printf("Invalid choice.\n"); 

        } 

    } 

 

    return 0; 

} 