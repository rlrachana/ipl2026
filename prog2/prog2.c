#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

typedef struct {
    int id;
    char name[30];
    float gpa;
} Student;

void saveRecordsASCII(const char *filename, Student arr[], int n);
void createSeekArray(const char *filename, long seekPositions[], int *recordCount);
void displayRecordAtPosition(const char *filename, long position);

int main() {
    const char *filename = "students.txt";

    Student students[] = {
        {101, "Alice", 3.81},
        {102, "Bob", 3.45},
        {103, "Charlie", 3.92},
        {104, "Diana", 3.68}
    };
    int numStudents = sizeof(students) / sizeof(students[0]);

    printf("Saving records to '%s'...\n", filename);
    saveRecordsASCII(filename, students, numStudents);

    long seekPositions[MAX_RECORDS];
    int recordCount = 0;
    
    printf("Generating seek positions index...\n");
    createSeekArray(filename, seekPositions, &recordCount);

    printf("\nGenerated Index Table:\n");
    printf("---------------------------\n");
    printf("Record Index | File Offset (Bytes)\n");
    printf("---------------------------\n");
    for (int i = 0; i < recordCount; i++) {
        printf("    %d        |     %ld\n", i, seekPositions[i]);
    }
    printf("---------------------------\n\n");

    int targetIndex = 2; 
    if (targetIndex <= recordCount) {
        printf("Fetching record at index %d (Offset %ld):\n", targetIndex, seekPositions[targetIndex]);
        displayRecordAtPosition(filename, seekPositions[targetIndex]);
    } else {
        printf("Index out of bounds.\n");
    }

    return 0;
}

void saveRecordsASCII(const char *filename, Student arr[], int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d %s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }

    fclose(file);
}

void createSeekArray(const char *filename, long seekPositions[], int *recordCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for reading");
        return;
    }

    char buffer[100];
    *recordCount = 0;

    long currentPos = ftell(file);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        seekPositions[*recordCount] = currentPos;
        (*recordCount)++;

        currentPos = ftell(file);
    }

    fclose(file);
}

void displayRecordAtPosition(const char *filename, long position) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for reading");
        return;
    }

    if (fseek(file, position, SEEK_SET) != 0) {
        perror("Error seeking to position");
        fclose(file);
        return;
    }

    Student s;
    if (fscanf(file, "%d %s %f", &s.id, s.name, &s.gpa) == 3) {
        printf("ID: %d | Name: %s | GPA: %.2f\n", s.id, s.name, s.gpa);
    } else {
        printf("Error: Could not parse record data.\n");
    }

    fclose(file);
}