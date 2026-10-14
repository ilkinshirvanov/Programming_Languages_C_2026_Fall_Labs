
/*
 * Name: Ilkin
 * Surname: Shirvanov
 * Student ID: 251ADB133
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
  char name[50];
  int id;
  float gpa;
} Student;

void read_line(char* buffer, size_t size) {
  if (fgets(buffer, size, stdin) != NULL) {
    buffer[strcspn(buffer, "\n")] = '\0';
  } else {
    buffer[0] = '\0';
  }
}

int load_students(Student arr[], int max) {
  FILE* fp = fopen("students.txt", "r");
  if (fp == NULL) {
    return 0;
  }

  char line[256];
  int count = 0;

  while (count < max && fgets(line, sizeof(line), fp) != NULL) {
    Student s;

    if (sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa) == 3) {
      if (s.name[0] != '\0') {
        arr[count++] = s;
      }
    }
  }

  fclose(fp);
  return count;
}

int save_students(const Student arr[], int count) {
  FILE* fp = fopen("students.txt", "w");
  if (fp == NULL) {
    return -1;
  }

  for (int i = 0; i < count; i++) {
    if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
      fclose(fp);
      return -1;
    }
  }

  if (fclose(fp) != 0) {
    return -1;
  }

  return 0;
}

void add_student(Student arr[], int* count) {
  if (*count >= MAX_STUDENTS) {
    printf("Cannot add more students (limit reached).\n");
    return;
  }

  char name[256];
  char id_text[100];
  char gpa_text[100];
  char* end;
  long id;
  float gpa;

  printf("Enter name:");
  read_line(name, sizeof(name));

  printf("Enter ID:");
  read_line(id_text, sizeof(id_text));

  printf("Enter GPA:");
  read_line(gpa_text, sizeof(gpa_text));

  if (name[0] == '\0' || strchr(name, ',') != NULL) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  id = strtol(id_text, &end, 10);
  if (id_text[0] == '\0' || *end != '\0' || id < 1 || id > 2147483647L) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  gpa = strtof(gpa_text, &end);
  if (gpa_text[0] == '\0' || *end != '\0' || gpa < 0.0f || gpa > 4.0f) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  snprintf(arr[*count].name, sizeof(arr[*count].name), "%.49s", name);
  arr[*count].id = (int)id;
  arr[*count].gpa = gpa;
  (*count)++;

  printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }

  printf("%-5s %-20s %s\n", "ID", "Name", "GPA");

  for (int i = 0; i < count; i++) {
    printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
  }
}

int main(void) {
  Student students[MAX_STUDENTS];
  int count = load_students(students, MAX_STUDENTS);

  printf("Loaded %d student(s) from students.txt\n", count);

  char choice_text[32];
  char* end;
  long choice;

  while (1) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");
    printf("Select an option:");

    read_line(choice_text, sizeof(choice_text));
    choice = strtol(choice_text, &end, 10);

    if (choice_text[0] == '\0' || *end != '\0') {
      if (feof(stdin)) {
        choice = 3;
      } else {
        printf("Invalid input.\n");
        continue;
      }
    }

    if (choice == 1) {
      list_students(students, count);
    } else if (choice == 2) {
      add_student(students, &count);
    } else if (choice == 3) {
      if (save_students(students, count) != 0) {
        fprintf(stderr, "Error saving students.\n");
        return 1;
      }
      printf("Data saved. Goodbye!\n");
      break;
    } else {
      printf("Invalid input.\n");
    }
  }

  return 0;
}
