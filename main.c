#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function declarations
void add();
void list();
void edit();
void delete1();
void search();
void login();

struct CustomerDetails {
    char roomnumber[10];
    char name[20];
    char address[25];
    char phonenumber[15];
    char nationality[15];
    char email[20];
    char period[10];
    char arrivaldate[10];
} s;

void login() {
    int attempts = 0;
    char uname[10], pword[10];
    const char user[] = "user";
    const char pass[] = "pass";

    while (attempts < 3) {
        printf("\n************************** LOGIN FORM **************************\n");
        printf("Enter Username: ");
        scanf("%9s", uname);
        printf("Enter Password: ");
        scanf("%9s", pword);

        if (strcmp(uname, user) == 0 && strcmp(pword, pass) == 0) {
            printf("\nWelcome! Login successful.\n");
            return;
        } else {
            printf("\nSorry, login unsuccessful. Try again.\n");
            attempts++;
        }
    }

    if (attempts >= 3) {
        printf("\nSorry, too many login attempts. Exiting.\n");
        exit(1);
    }
}

int main() {
    char choice;

    login();
    while (1) {
        printf("\n************************** MAIN MENU **************************\n");
        printf("1 -> Book a room\n");
        printf("2 -> View Customer Record\n");
        printf("3 -> Delete Customer Record\n");
        printf("4 -> Search Customer Record\n");
        printf("5 -> Edit Record\n");
        printf("6 -> Exit\n");
        printf("Enter your choice: ");
        choice = getchar();
        getchar();  // To consume the newline character

        switch (choice) {
            case '1':
                add();
                break;
            case '2':
                list();
                break;
            case '3':
                delete1();
                break;
            case '4':
                search();
                break;
            case '5':
                edit();
                break;
            case '6':
                printf("\nThank you for using our service.\n");
                exit(0);
                break;
            default:
                printf("\nIncorrect Input. Please try again.\n");
                break;
        }
    }
}

void add() {
    FILE *f = fopen("add.txt", "a+");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (1) {
        printf("\nEnter Customer Details:\n");
        printf("Enter Room number: ");
        scanf("%9s", s.roomnumber);
        printf("Enter Name: ");
        scanf("%19s", s.name);
        printf("Enter Address: ");
        scanf("%24s", s.address);
        printf("Enter Phone Number: ");
        scanf("%14s", s.phonenumber);
        printf("Enter Nationality: ");
        scanf("%14s", s.nationality);
        printf("Enter Email: ");
        scanf("%19s", s.email);
        printf("Enter Period (days): ");
        scanf("%9s", s.period);
        printf("Enter Arrival date (dd/mm/yyyy): ");
        scanf("%9s", s.arrivaldate);

        fwrite(&s, sizeof(s), 1, f);
        printf("\n1 Room is successfully booked!\n");

        printf("\nPress 'q' to quit or any other key to add another customer: ");
        char choice = getchar();
        getchar();  // To consume the newline
        if (tolower(choice) == 'q') break;
    }

    fclose(f);
}

void list() {
    FILE *f = fopen("add.txt", "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n%-10s%-20s%-25s%-15s%-15s%-20s%-10s%-12s\n", "Room No.", "Name", "Address", "Phone", "Nationality", "Email", "Period", "Arrival Date");
    for (int i = 0; i < 118; i++) printf("-");

    while (fread(&s, sizeof(s), 1, f) == 1) {
        printf("\n%-10s%-20s%-25s%-15s%-15s%-20s%-10s%-12s", s.roomnumber, s.name, s.address, s.phonenumber, s.nationality, s.email, s.period, s.arrivaldate);
    }

    printf("\n");
    fclose(f);
}

void delete1() {
    FILE *f = fopen("add.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (f == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char roomnumber[10];
    printf("Enter the Room Number to delete: ");
    scanf("%9s", roomnumber);

    int found = 0;
    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) != 0) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(temp);
    remove("add.txt");
    rename("temp.txt", "add.txt");

    if (found) {
        printf("\nCustomer record deleted successfully.\n");
    } else {
        printf("\nRoom number not found.\n");
    }
}

void search() {
    FILE *f = fopen("add.txt", "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char roomnumber[10];
    printf("Enter the Room Number to search: ");
    scanf("%9s", roomnumber);

    int found = 0;
    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            found = 1;
            printf("\nRoom Number: %s\nName: %s\nAddress: %s\nPhone: %s\nNationality: %s\nEmail: %s\nPeriod: %s\nArrival Date: %s\n", 
                    s.roomnumber, s.name, s.address, s.phonenumber, s.nationality, s.email, s.period, s.arrivaldate);
            break;
        }
    }

    if (!found) {
        printf("\nCustomer record not found.\n");
    }

    fclose(f);
}

void edit() {
    FILE *f = fopen("add.txt", "r+");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char roomnumber[10];
    printf("Enter the Room Number to edit: ");
    scanf("%9s", roomnumber);

    int found = 0;
    while (fread(&s, sizeof(s), 1, f) == 1) {
        if (strcmp(s.roomnumber, roomnumber) == 0) {
            found = 1;
            printf("Enter new details for the customer:\n");
            printf("Enter Room number: ");
            scanf("%9s", s.roomnumber);
            printf("Enter Name: ");
            scanf("%19s", s.name);
            printf("Enter Address: ");
            scanf("%24s", s.address);
            printf("Enter Phone Number: ");
            scanf("%14s", s.phonenumber);
            printf("Enter Nationality: ");
            scanf("%14s", s.nationality);
            printf("Enter Email: ");
            scanf("%19s", s.email);
            printf("Enter Period (days): ");
            scanf("%9s", s.period);
            printf("Enter Arrival date (dd/mm/yyyy): ");
            scanf("%9s", s.arrivaldate);

            fseek(f, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, f);
            printf("\nCustomer record updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("\nRoom number not found.\n");
    }

    fclose(f);
}
