#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

struct StudentInfo {
    char ID[10];
    char Name[20];
    char Email[30];
    char Phone[20];
    int NumberOfCourse;
};

struct CourseInfo {
    char StudentID[10];
    char Code[10];
    char Name[20];
};

struct StudentInfo Students[100];
struct CourseInfo Courses[500];

// Global variables
int TotalStudents = 0;
int TotalCourse = 0;
FILE *AllStudents; 
FILE *AllCourses;

// Admin credentials 
#define ADMIN_USERNAME "portal"
#define ADMIN_PASSWORD "pflab"


void Menu();
void AddNewStudent();
void ShowAllStudents();
int  SearchStudent(char StudentID[10]);
void EditStudent(int StudentFoundIndex);
void DeleteStudent(int StudentIndex);
void DeleteAllStudents();
void DeleteCourseByStudentID(char StudentID[10]);
void DeleteCourseByIndex(int CourseIndex);
void ExitProject();
void LoadStudentsFromFile();
void SaveStudentToFile(struct StudentInfo student);
void SaveAllStudentsToFile();
void LoadCoursesFromFile();
void SaveCourseToFile(struct CourseInfo course);
void SaveAllCoursesToFile();

int main() {

    system("COLOR 09");

    LoadStudentsFromFile();  
    LoadCoursesFromFile();   
    
    char username[50], password[50];
    int attempts = 5;  

    while (attempts > 0) {
        printf("\33[1m\n                 ENTER ADMIN USERNAME = ");
        scanf("%s", username);
        printf("\33[1m\n                   ENTER PASSWORD = ");
        scanf("%s", password);

        
        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("\nLOGIN SUCCESSFUL. WELCOME TO THE PORTAL!!\n\n");
            break;
        } else {
            printf("\nINVALID CREDENTIALS!!!\n");
            attempts--;
            if (attempts == 0) {
                printf("\nTOO MANY INVALID ATTEMPTS!!! PROGRAM IS CLOSING.\n");
                return 0; 
            } else {
                printf("\nInvalid credentials! You have %d attempt(s) left.\n", attempts);
            }
        }

    }


    int option;
    while (1) {
        Menu();
        printf("\nChoose an option: ");
        if (scanf("%d", &option) != 1) { 
            while (getchar() != '\n'); 
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        switch(option) {
            case 0: 
                ExitProject();
                return 0;
            case 1:
                AddNewStudent();
                break;
            case 2:
                ShowAllStudents();
                break;
            case 3: {
                char StudentID[10];
                printf("Enter student ID to search: ");
                scanf("%s", StudentID);
                int index = SearchStudent(StudentID);
                if (index >= 0) {
                    printf("STUDENT FOUND SUCCESSFULLY\n");
                } else {
                    printf("Student not found\n");
                }
                break;
            }
            case 4: {
                char StudentID[10];
                printf("Enter student ID to edit: ");
                scanf("%s", StudentID);
                int index = SearchStudent(StudentID);
                if (index >= 0) {
                    EditStudent(index);
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 5: {
                char StudentID[10];
                printf("Enter student ID to delete: ");
                scanf("%s", StudentID);
                int index = SearchStudent(StudentID);
                if (index >= 0) {
                    DeleteStudent(index);
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 6:
                DeleteAllStudents();
                break;
            case 7:
                system("cls");  
                break;
            default:
                printf("Invalid option\n");
        }
    }

    return 0;
}

void Menu() {
    printf("                             ========================================\n");
    printf("                                UNIVERSITY PORTAL MANAGEMENT SYSTEM \n");
    printf("                             =========================================\n \n");
    printf("                               [1] ADD NEW STUDENT\n");
    printf("                               [2] SHOW ALL STUDENTS\n");
    printf("                               [3] SPECIFIC STUDENT INFORMATION\n");
    printf("                               [4] EDIT STUDENT INFORMATION\n");
    printf("                               [5] TERMINATE STUDENT\n");
    printf("                               [6] DELETE ALL STUDENTS\n");
    printf("                               [7] CLEAR PORTAL SCREEN\n");
    printf("                               [0] EXIT PORTAL\n");
}

void AddNewStudent() {
    char StudentID[10];
    char Name[20];
    char Phone[20];
    char Email[30];
    int NumberOfCourses;

    
    printf("Enter student ID: ");
    scanf("%s", StudentID);
    printf("Enter student Name: ");
    scanf(" %[^\n]s", Name);
    printf("Enter student Phone: ");
    scanf("%s", Phone);
    printf("Enter student Email: ");
    scanf("%s", Email);
    printf("Enter number of courses (1-4): ");
    scanf("%d", &NumberOfCourses);

  
    struct StudentInfo newStudent = {0};
    strcpy(newStudent.ID, StudentID);
    strcpy(newStudent.Name, Name);
    strcpy(newStudent.Phone, Phone);
    strcpy(newStudent.Email, Email);
    newStudent.NumberOfCourse = NumberOfCourses;
    
    Students[TotalStudents++] = newStudent;
    SaveStudentToFile(newStudent);  

   
    for (int i = 0; i < NumberOfCourses; i++) {
        struct CourseInfo newCourse;
        printf("Enter Course %d Code: ", i + 1);
        scanf("%s", newCourse.Code);
        printf("Enter Course %d Name: ", i + 1);
        scanf(" %[^\n]s", newCourse.Name);
        strcpy(newCourse.StudentID, StudentID);

        Courses[TotalCourse++] = newCourse;
        SaveCourseToFile(newCourse); 
    }

    printf("Student and courses added successfully\n");
}

void ShowAllStudents() {
    printf("\nStudents List:\n");
    for (int i = 0; i < TotalStudents; i++) {
         printf("\n");
        printf("ID: %s \nName: %s \nEmail: %s \nPhone: %s \nCourses: %d\n", 
               Students[i].ID, Students[i].Name, Students[i].Email, Students[i].Phone, Students[i].NumberOfCourse);
              
    }
}

int SearchStudent(char StudentID[10]) {
    for (int i = 0; i < TotalStudents; i++) {
        if (strcmp(Students[i].ID, StudentID) == 0) {
          
            printf("\n");
            printf("Student ID: %s\n", Students[i].ID);
            printf("Name: %s\n", Students[i].Name);
            printf("Email: %s\n", Students[i].Email);
            printf("Phone: %s\n", Students[i].Phone);
            printf("Number of courses: %d\n", Students[i].NumberOfCourse);
            
            printf("\nCourses:\n");
            for (int j = 0; j < TotalCourse; j++) {
                if (strcmp(Courses[j].StudentID, StudentID) == 0) {
                    printf("Course Code: %s\nCourse Name: %s\n", Courses[j].Code, Courses[j].Name);
                }
            }
            return i;  
        }
    }
    return -1; 
}

void EditStudent(int StudentFoundIndex) {
    int choice;
    printf("Editing student: %s\n", Students[StudentFoundIndex].Name);
    printf("[1] Edit Name\n");
    printf("[2] Edit Email\n");
    printf("[3] Edit Phone\n");
    printf("[4] Edit Courses\n");
    printf("[0] Cancel\n");
    printf("Choose an option to edit: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            printf("Enter new Name: ");
            scanf(" %[^\n]s", Students[StudentFoundIndex].Name);
            break;
        case 2:
            printf("Enter new Email: ");
            scanf("%s", Students[StudentFoundIndex].Email);
            break;
        case 3:
            printf("Enter new Phone: ");
            scanf("%s", Students[StudentFoundIndex].Phone);
            break;
        case 4: {
            printf("Editing courses for student: %s\n", Students[StudentFoundIndex].Name);

            
            printf("\nCurrent Courses:\n");
            int courseCount = 0;
            for (int i = 0; i < TotalCourse; i++) {
                if (strcmp(Courses[i].StudentID, Students[StudentFoundIndex].ID) == 0) {
                    printf("[%d] Course Code: %s, Course Name: %s\n", ++courseCount, Courses[i].Code, Courses[i].Name);
                }
            }

            if (courseCount == 0) {
                printf("No courses found for this student.\n");
                break;
            }

            printf("Enter course number to edit (0 to cancel): ");
            int courseNumber;
            scanf("%d", &courseNumber);

            if (courseNumber > 0 && courseNumber <= courseCount) {
                int current = 0;
                for (int i = 0; i < TotalCourse; i++) {
                    if (strcmp(Courses[i].StudentID, Students[StudentFoundIndex].ID) == 0) {
                        current++;
                        if (current == courseNumber) {
                            printf("Editing Course Code: %s, Course Name: %s\n", Courses[i].Code, Courses[i].Name);
                            printf("Enter new Course Code: ");
                            scanf("%s", Courses[i].Code);
                            printf("Enter new Course Name: ");
                            scanf(" %[^\n]s", Courses[i].Name);
                            break;
                        }
                    }
                }
            } else {
                printf("Invalid course number or canceled.\n");
            }
            break;
        }
        case 0:
            printf("Canceling edit.\n");
            return;
        default:
            printf("Invalid option.\n");
            break;
    }

    
    SaveAllStudentsToFile();
    SaveAllCoursesToFile();
    printf("Student data updated and saved.\n");
}

void DeleteStudent(int StudentIndex) {
    printf("Deleting student: %s\n", Students[StudentIndex].Name);

    
    DeleteCourseByStudentID(Students[StudentIndex].ID);

    
    for (int i = StudentIndex; i < TotalStudents - 1; i++) {
        Students[i] = Students[i + 1];
    }
    TotalStudents--;
    SaveAllStudentsToFile();
    SaveAllCoursesToFile();
    printf("Student deleted.\n");
}

void DeleteAllStudents() {
    printf("Deleting all students and associated courses...\n");
    TotalStudents = 0;
    TotalCourse = 0;
    SaveAllStudentsToFile();
    SaveAllCoursesToFile();
    printf("All students and courses have been deleted.\n");
}

void DeleteCourseByStudentID(char StudentID[10]) {
    for (int i = 0; i < TotalCourse; i++) {
        if (strcmp(Courses[i].StudentID, StudentID) == 0) {
            DeleteCourseByIndex(i);
            i--;  
        }
    }
}

void DeleteCourseByIndex(int CourseIndex) {
    for (int i = CourseIndex; i < TotalCourse - 1; i++) {
        Courses[i] = Courses[i + 1];
    }
    TotalCourse--;
    SaveAllCoursesToFile();
}

void SaveStudentToFile(struct StudentInfo student) {
    AllStudents = fopen("students.txt", "a");
    if (AllStudents == NULL) {
        printf("Error opening file for saving\n");
        exit(1);
    }
    fprintf(AllStudents, "%s,%s,%s,%s,%d\n", student.ID, student.Name, student.Email, student.Phone, student.NumberOfCourse);
    fclose(AllStudents);
}

void SaveAllStudentsToFile() {
    AllStudents = fopen("students.txt", "w");
    if (AllStudents == NULL) {
        printf("Error opening file for saving students\n");
        exit(1);
    }
    for (int i = 0; i < TotalStudents; i++) {
        fprintf(AllStudents, "%s,%s,%s,%s,%d\n", Students[i].ID, Students[i].Name, Students[i].Email, Students[i].Phone, Students[i].NumberOfCourse);
    }
    fclose(AllStudents);
}

void SaveCourseToFile(struct CourseInfo course) {
    AllCourses = fopen("courses.txt", "a");
    if (AllCourses == NULL) {
        printf("Error opening file for saving courses\n");
        exit(1);
    }
    fprintf(AllCourses, "%s,%s,%s\n", course.StudentID, course.Code, course.Name);
    fclose(AllCourses);
}

void SaveAllCoursesToFile() {
    AllCourses = fopen("courses.txt", "w");
    if (AllCourses == NULL) {
        printf("Error opening file for saving courses\n");
        exit(1);
    }
    for (int i = 0; i < TotalCourse; i++) {
        fprintf(AllCourses, "%s,%s,%s\n", Courses[i].StudentID, Courses[i].Code, Courses[i].Name);
    }
    fclose(AllCourses);
}

void LoadStudentsFromFile() {
    AllStudents = fopen("students.txt", "r");
    if (AllStudents == NULL) {
        printf("No student records found.\n");
        return;
    }

    while (fscanf(AllStudents, "%[^,],%[^,],%[^,],%[^,],%d\n", 
                   Students[TotalStudents].ID,
                   Students[TotalStudents].Name,
                   Students[TotalStudents].Email,
                   Students[TotalStudents].Phone,
                   &Students[TotalStudents].NumberOfCourse) == 5) {
        TotalStudents++;
    }
    fclose(AllStudents);
}

void LoadCoursesFromFile() {
    AllCourses = fopen("courses.txt", "r");
    if (AllCourses == NULL) {
        printf("No previous course records found.\n");
        return;
    }

    while (fscanf(AllCourses, "%[^,],%[^,],%[^\n]\n", 
                   Courses[TotalCourse].StudentID, 
                   Courses[TotalCourse].Code, 
                   Courses[TotalCourse].Name) == 3) {
        TotalCourse++;
    }
    fclose(AllCourses);
}

void ExitProject() {
    printf("Saving data and exiting...\n");
    SaveAllStudentsToFile();
    SaveAllCoursesToFile();
    printf("Data saved. Goodbye.\n");
}
