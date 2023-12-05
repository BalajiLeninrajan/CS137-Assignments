#include <stdio.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 100

struct Employee
{
    int id;
    int age;
    double salary;
};

void inputEmployees(struct Employee employees[], int n)
{
    printf("Enter the details of %d employees:\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("Employee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &employees[i].id);
        printf("Age: ");
        scanf("%d", &employees[i].age);
        printf("Salary: ");
        scanf("%lf", &employees[i].salary);
    }
}

void displayEmployees(struct Employee employees[], int n)
{
    printf("Employee Details:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Employee %d:\n", i + 1);
        printf("ID: %d\n", employees[i].id);
        printf("Age: %d\n", employees[i].age);
        printf("Salary: %.2lf\n", employees[i].salary);
    }
}

/*
    Calculates and returns the average salary of all employees
    Returns result
*/
double averageSalary(struct Employee employees[], int n)
{
    double total = 0;
    for (int i = 0; i < n; i++)
    {
        total += employees[i].salary;
    }
    return total / n;
}

/*
    Performs linear search to find youngest employee
    prints result
*/
void youngestEmployee(struct Employee employees[], int n)
{
    struct Employee youngest;
    int smallest_age = 1000;
    for (int i = 0; i < n; i++)
    {
        if (employees[i].age < smallest_age)
        {
            smallest_age = employees[i].age;
            youngest = employees[i];
        }
    }
    printf("Youngest Employee:\n");
    printf("ID: %d\n", youngest.id);
    printf("Age: %d\n", youngest.age);
    printf("Salary: %.2lf\n", youngest.salary);
}

/*
    Returns number of employees who have a salary within a given range
*/
int salaryInRange(struct Employee employees[], int n, double minSalary, double maxSalary)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (employees[i].salary >= minSalary && employees[i].salary <= maxSalary)
        {
            count++;
        }
    }
    return count;
}

/*
    Updates the salary of all employees, increaseing the salary by value increase
*/
void salaryRaise(struct Employee employees[], int n, double increase)
{
    for (int i = 0; i < n; i++)
    {
        employees[i].salary *= (1 + increase);
    }
}

int main()
{
    struct Employee employees[MAX_EMPLOYEES];
    int n;

    printf("Enter the number of employees (up to %d): ", MAX_EMPLOYEES);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_EMPLOYEES)
    {
        printf("Invalid number of employees.\n");
        return 1;
    }

    inputEmployees(employees, n);
    displayEmployees(employees, n);

    double avgSal = averageSalary(employees, n);
    printf("Average Salary: %.2lf\n", avgSal);

    youngestEmployee(employees, n);

    double minSalary, maxSalary;
    printf("Enter the salary range:\n");
    printf("Minimum Salary: ");
    scanf("%lf", &minSalary);
    printf("Maximum Salary: ");
    scanf("%lf", &maxSalary);

    int count = salaryInRange(employees, n, minSalary, maxSalary);
    printf("Number of employees in the given salary range: %d\n", count);

    salaryRaise(employees, n, 0.05);
    printf("Salaries after 0.05 raise\n");
    displayEmployees(employees, n);

    return 0;
}
