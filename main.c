#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
buku telepon

- Buat buku telpon
- Menyimpan nama dan no. HP
- Misal ada kontak baru bisa di add
- Bisa melakukan sorting (misal berdasar abjad, dll) ; ketika mengurutkan bisa dipilih mengurutkan menggunakan sort apa (bubble, quick, dll)
- Misal ada kontak yang tidak diinginkan bisa dihapus
- Bisa mencari kontak seseorang
- Bisa menampilkan semua kontak yang ada
- kalau salah ketik bisa diedeit

Linkedlist
Sorting : Minimal 2 sorting
Minimal requirements, boleh ditambah
Upload source code ; jangan lupa dikasih comment, codingannya jgn kosongan
*/


/*
    - data di simpan di txt file

    refrensi

    - handling txt file
        https://www.geeksforgeeks.org/basics-file-handling-c/
        https://www.programiz.com/c-programming/c-file-input-output
        https://www.tutorialspoint.com/cprogramming/c_file_io.htm
        https://solarianprogrammer.com/2019/04/03/c-programming-read-file-lines-fgets-getline-implement-portable-getline/#:~:text=The%20standard%20way%20of%20reading,GitHub%20repo%20for%20this%20article.
*/
struct node {
    char *name;
    char *number;
    struct node *next;
};



void printContactRecord(struct node * head)
{
    struct node * iterator = head;
    while(iterator != NULL)
    {
        printf("nama kontak: %s\n", iterator->name);
        printf("nomor kontak: %s\n", iterator->number);
        iterator=iterator->next;
    }
}

void appendToFile(struct * node head)
{
    FILE * fptr;
    fptr = fopen("data.txt", "a");
    struct node * iterator = head;

    if(fptr==NULL)
    {
        perror("Error:");
    }

    else
    {
        while(iterator!= NULL)
        {
            fprintf(fptr, "%s\n%s\n", iterator->name, iterator->number);
            iterator= iterator->next;
        }
    }

    fclose(fptr);
    }

void saveContact(struct * node head){
    int count, i;
    printf("berapa banyak kontak yang ingin kamu simpan? ");
    scanf("%d", &count);
    struct node * newRecord;
    for(i=0; i<count; i++)
    {
        if(i==0)
        {
            newRecord = head;
        }
        else
        {
            newRecord->next = malloc(sizeof(struct node));
            newRecord = newRecord->next;
        }
        newRecord->name = malloc(50*sizeof(char));
        newRecord->number = malloc(50*sizeof(char));
        printf("nama kontak: ");
        scanf(" %[^\n]s", newRecord->name);
        printf("nomor kontak: ");
        scanf("%s", newRecord->number);
    }
    newRecord->next = NULL;
    printf("\n\n");
    appendToFile();
    free(newRecord);
    printf("\nberhasil disimpan");

}

// loading data harus di masukkan ke linked list utama, gimana caranyaaa????

void insert_end(char nama[], char nomor[]) {
    struct node * new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        exit(1);
    }
    new_node->next = NULL;
    new_node->name = nama;
    new_node->number = nomor;

    if (head == NULL) {
        head = new_node;
        printf("\n");
        return;
    }

    struct node * curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_node;
}

void loadingData(){
    FILE * fp = fopen("data.txt", "r");
    if (fp == NULL){
        perror("error:");
        exit(1);
    }

    char nama[50], nomor[50];

    while (fscanf(fp, "%s %s", nama, nomor) > 0){

    }
    fclose(fp);
}

int main()
{
    struct node *contactRecord = malloc(sizeof(struct node));

    loadingData();
    printContactRecord(contactRecord);
    return 0;
}
