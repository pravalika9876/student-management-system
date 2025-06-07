#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

#define MAX 100

typedef struct {
    int roll;
    char name[50];
    char phone[20];
    char email[50];
    char date[15];
    float attendance;
    float totalMarks;
} Student;

Student students[MAX];
int count = 0;

// Color codes
void setColor(int code) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, code);
#else
    printf("\033[0;%dm", code);
#endif
}

void resetColor() {
#ifdef _WIN32
    setColor(7);
#else
    printf("\033[0m");
#endif
}

void pause() {
    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void addStudent() {
    system(CLEAR);
    setColor(10); printf("Adding New Student\n"); resetColor();

    if (count >= MAX) {
        setColor(12); printf("Student list full!\n"); resetColor();
        pause();
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &students[count].roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", students[count].name);
    printf("Enter Phone Number: ");
    scanf(" %[^\n]", students[count].phone);
    printf("Enter Email: ");
    scanf(" %[^\n]", students[count].email);
    printf("Enter Date of Enrollment (dd-mm-yyyy): ");
    scanf(" %[^\n]", students[count].date);
    printf("Enter Attendance Percentage: ");
    scanf("%f", &students[count].attendance);
    printf("Enter Total Marks: ");
    scanf("%f", &students[count].totalMarks);

    count++;
    setColor(10); printf("Student added successfully!\n"); resetColor();
    pause();
}

void viewStudents() {
    system(CLEAR);
    setColor(14); printf("Viewing All Students\n\n"); resetColor();

    if (count == 0) {
        setColor(12); printf("No student records found.\n"); resetColor();
        pause();
        return;
    }

    printf("%-5s %-20s %-15s %-25s %-12s %-10s %-10s\n",
           "Roll", "Name", "Phone", "Email", "EnrollDate", "Attend%", "Marks");
int i;
    for (i = 0; i < count; i++) {
        printf("%-5d %-20s %-15s %-25s %-12s %-10.2f %-10.2f\n",
               students[i].roll, students[i].name, students[i].phone,
               students[i].email, students[i].date,
               students[i].attendance, students[i].totalMarks);
    }
    pause();
}

void searchStudent() {
    system(CLEAR);
    int roll;
    setColor(11); printf("Search Student by Roll No\n"); resetColor();
    printf("Enter Roll Number: ");
    scanf("%d", &roll);
int i;
    for ( i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            setColor(10); printf("Student Found:\n"); resetColor();
            printf("Name: %s\nPhone: %s\nEmail: %s\nDate: %s\nAttendance: %.2f%%\nMarks: %.2f\n",
                   students[i].name, students[i].phone, students[i].email,
                   students[i].date, students[i].attendance, students[i].totalMarks);
            pause();
            return;
        }
    }
    setColor(12); printf("Student not found!\n"); resetColor();
    pause();
}

void updateStudent() {
    system(CLEAR);
    int roll;
    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);
int i;
    for ( i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("Updating record for %s\n", students[i].name);
            printf("Enter new Phone: ");
            scanf(" %[^\n]", students[i].phone);
            printf("Enter new Email: ");
            scanf(" %[^\n]", students[i].email);
            printf("Enter new Attendance Percentage: ");
            scanf("%f", &students[i].attendance);
            printf("Enter new Total Marks: ");
            scanf("%f", &students[i].totalMarks);
            setColor(10); printf("Record updated.\n"); resetColor();
            pause();
            return;
        }
    }
    setColor(12); printf("Student not found!\n"); resetColor();
    pause();
}

void deleteStudent() {
    system(CLEAR);
    int roll;
    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);
int i;
    for (i = 0; i < count; i++) {
        if (students[i].roll == roll) {
        	int j;
            for ( j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            setColor(10); printf("Student deleted.\n"); resetColor();
            pause();
            return;
        }
    }
    setColor(12); printf("Student not found!\n"); resetColor();
    pause();
}

void exportToCSV() {
    FILE *fp = fopen("students.csv", "w");
    if (!fp) {
        setColor(12); printf("Failed to create file.\n"); resetColor();
        pause();
        return;
    }

    fprintf(fp, "Roll,Name,Phone,Email,EnrollmentDate,Attendance,Marks\n");
    int i;
    for ( i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%s,%s,%s,%.2f,%.2f\n",
                students[i].roll, students[i].name, students[i].phone,
                students[i].email, students[i].date,
                students[i].attendance, students[i].totalMarks);
    }
    fclose(fp);
    setColor(10); printf("Exported to students.csv\n"); resetColor();
    pause();
}

void openCSV() {
#ifdef _WIN32
    system("start students.csv");
#elif _APPLE_
    system("open students.csv");
#else
    system("xdg-open students.csv");
#endif
}

int main() {
    int choice;
    do {
        system(CLEAR);
        setColor(14);
        printf("----- Student Management System -----\n");
        resetColor();
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search by Roll No\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Export to Excel (CSV)\n");
        printf("7. Open Excel File\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exportToCSV(); break;
            case 7: openCSV(); break;
            case 0:
                setColor(11); printf("Exiting...\n"); resetColor();
                break;
            default:
                setColor(12); printf("Invalid choice!\n"); resetColor();
                pause();
        }
    } while (choice != 0);

    return 0;
}
