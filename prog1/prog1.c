#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char title[50];
    float price;
    int isDeleted; 
} Book;

void storeRecords(const char *filename, int n);
void displayMthRecord(const char *filename, int m);
void deleteRecordWithFlag(const char *filename, int idToDelete);
void displayAllActiveRecords(const char *filename);

int main() {
    const char *filename = "library.bin";
    int n, m, idToDelete;

    printf("Enter the number of books to add: ");
    scanf("%d", &n);
    storeRecords(filename, n);

    printf("\n--- Current Active Books ---\n");
    displayAllActiveRecords(filename);

    printf("\nEnter the record number to fetch (1 to %d): ", n);
    scanf("%d", &m);
    displayMthRecord(filename, m);

    printf("\nEnter the Book ID to delete: ");
    scanf("%d", &idToDelete);
    deleteRecordWithFlag(filename, idToDelete);

    printf("\n--- Active Books After Deletion ---\n");
    displayAllActiveRecords(filename);

    return 0;
}

void storeRecords(const char *filename, int n) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    Book b;
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Book %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &b.id);
        printf("Title: ");
        scanf("%s", b.title);
        printf("Price: ");
        scanf("%f", &b.price);
        b.isDeleted = 0; 

        fwrite(&b, sizeof(Book), 1, file);
    }
    fclose(file);
    printf("\nSuccessfully stored %d records.\n", n);
}

void displayMthRecord(const char *filename, int m) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    Book b;
    long offset = (m - 1) * sizeof(Book);

    if (fseek(file, offset, SEEK_SET) == 0) {
        if (fread(&b, sizeof(Book), 1, file) == 1) {
            if (b.isDeleted == 1) {
                printf("\nRecord %d has been deleted.\n", m);
            } else {
                printf("\n--- Book %d Found ---\n", m);
                printf("ID: %d | Title: %s | Price: %.2f\n", b.id, b.title, b.price);
            }
        } else {
            printf("Error reading record %d.\n", m);
        }
    } else {
        printf("Error seeking to record %d.\n", m);
    }
    fclose(file);
}

void deleteRecordWithFlag(const char *filename, int idToDelete) {
    
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Error opening file for updating!\n");
        return;
    }

    Book b;
    long recordPosition;
    int found = 0;

    while (1) {
        recordPosition = ftell(file);

        if (fread(&b, sizeof(Book), 1, file) != 1) {
            break; 
        }

        if (b.id == idToDelete && b.isDeleted == 0) {
            b.isDeleted = 1; 

            fseek(file, recordPosition, SEEK_SET);

            fwrite(&b, sizeof(Book), 1, file);
            
            found = 1;
            break; 
        }
    }

    fclose(file);

    if (found) {
        printf("Book ID %d marked as deleted.\n", idToDelete);
    } else {
        printf("Active Book ID %d not found.\n", idToDelete);
    }
}

void displayAllActiveRecords(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    Book b;
    int count = 0;
    while (fread(&b, sizeof(Book), 1, file) == 1) {
        if (b.isDeleted == 0) {
            printf("ID: %d | Title: %s | Price: %.2f\n", b.id, b.title, b.price);
            count++;
        }
    }
    if (count == 0) {
        printf("No active records to display.\n");
    }
    fclose(file);
}