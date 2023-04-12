#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the book struct
struct book
{
    char title[50];
    char author[50];
    char isbn[20];
    float price;
    struct book *next;
};

// Function prototypes
void add_book(struct book **inventory, FILE *file);
void delete_book(struct book **inventory, char isbn[], FILE *file);
void search_book(struct book *inventory, char isbn[], FILE *file);
void print_inventory(struct book *inventory, FILE *file);
// void load_inventory(struct book **inventory, FILE *file);

int main()
{

    struct book *inventory = NULL;
    int choice;
    char isbn[20];
    FILE *file;

    file = fopen("inventory.txt", "a+");

//   load_inventory(&inventory, file);

    do
    {
        printf("--- Bookstore Management System ---\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Print Inventory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_book(&inventory, file);
            break;
        case 2:
            printf("Enter ISBN of the book to be deleted: ");
            scanf("%s", isbn);
            delete_book(&inventory, isbn, file);
            break;
        case 3:
            printf("Enter ISBN of the book to be searched: ");
            scanf("%s", isbn);
            search_book(&inventory, isbn, file);
            break;
        case 4:
            print_inventory(inventory, file);
            break;
        case 5:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice, try again.\n");
            break;
        }
    }
    while (choice != 5);

    fclose(file);

    //return 0;
}

// Function to add a book to the inventory

void add_book(struct book **inventory, FILE *file)
{
    struct book *new_book = malloc(sizeof(struct book));

    printf("Enter book title: ");
    scanf(" %[^\n]s", new_book->title);

    printf("Enter book author: ");
    scanf(" %[^\n]s", new_book->author);

    printf("Enter book ISBN: ");
    scanf("%s", new_book->isbn);

    printf("Enter book price: ");
    scanf("%f", &new_book->price);

    new_book->next = *inventory;
    *inventory = new_book;
    file = fopen("inventory.txt", "a+");
    fprintf(file,"Title: %s\nAuthor: %s\nIsbn: %s\nPrice: %.2f\n\n", new_book->title, new_book->author, new_book->isbn, new_book->price);

    printf("Book added to inventory.\n");
}

// Function to delete a book from the inventory
void delete_book(struct book **inventory, char isbn[], FILE *file)
{
    file = fopen("inventory.txt", "a+");
    struct book *current = *inventory;
    struct book *previous = NULL;

    while (current != NULL && strcmp(current->isbn, isbn) != 0)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Book not found in inventory.\n");
    }
    else
    {
        if (previous == NULL)
        {
            *inventory = current->next;
        }
        else
        {
            previous->next = current->next;
        }

        fprintf(file, "%s", current->isbn);
    }
}

// Function to search for a book in the inventory

void search_book(struct book *inventory, char isbn[], FILE *file)
{
    struct book *current = inventory;

    while (current != NULL && strcmp(current->isbn, isbn) != 0)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Book found in inventory:\n");
        printf("Title: %s\n", current->title);
        printf("Author: %s\n", current->author);
        printf("ISBN: %s\n", current->isbn);
        printf("Price: $%.2f\n", current->price);
    }
    file = fopen("inventory.txt", "a+");
    fprintf(file, "%s,%s,%s,%.2f\n", current->title, current->author, current->isbn, current->price);

}


// Function to print the entire inventory
void print_inventory(struct book *inventory, FILE *file)
{
    file = fopen("inventory.txt", "a+");
    if (inventory == NULL)
    {
        printf("Inventory is empty.\n");
    }

    else
    {

        printf("--- Book Inventory ---\n");
        struct book *current = inventory;
        file = fopen("inventory.txt", "a+");
         while (current != NULL)
        {
            printf("Title: %s\n", current->title);
            printf("Author: %s\n", current->author);
            printf("ISBN: %s\n", current->isbn);
            printf("Price: $%.2f\n", current->price);
            printf("\n");
            current = current->next;
           fprintf(file, "%s,%s,%s,%.2f\n", current->title, current->author, current->isbn, current->price);
        }



    }
}

