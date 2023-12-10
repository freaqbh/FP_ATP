#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


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
    tahap yang berhasil
    - data di simpan di txt file
    - loading data
    - simpan data di akhir linkedlist
    - print linkedlist
    - searching selesai

    tahap yang belum
    - sorting
    - edit data
    - delete
    - final touch
*/
struct node {
    char *name;
    char *number;
    struct node *next;
};

struct node *contactRecord, *record;
int list_size = 0;

void printContactRecord(){
    struct node * iterator = record;
    while(iterator != NULL)
    {
        printf("%s\n", iterator->name);
        printf("%s\n", iterator->number);
        iterator=iterator->next;
    }
}

void saveContact(){
    int count, i;
    printf("berapa banyak kontak yang ingin kamu simpan? ");
    scanf("%d", &count);
    for(i=0; i<count; i++){
        if(record==NULL)
        {
            record = contactRecord;
        }
        else
        {
            record->next = malloc(sizeof(struct node));
            record = record->next;
        }
        record->name = malloc(50*sizeof(char));
        record->number = malloc(50*sizeof(char));
        printf("nama kontak: ");
        scanf(" %[^\n]s", record->name);
        printf("nomor kontak: ");
        scanf("%s", record->number);
        list_size++;
    }
    record->next = NULL;
    printf("\nberhasil disimpan\n");

}

void writeToFile(){
    FILE * fptr;
    fptr = fopen("data.txt", "w");
    struct node * iterator = contactRecord;

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

void loadingData(){
    FILE * fp = fopen("data.txt", "r");
    if (fp == NULL){
        perror("error:");
        exit(1);
    }

    record = contactRecord;
    record->name = malloc(50*sizeof(char));
    record->number = malloc(50*sizeof(char));
    while (fscanf(fp, "%s %s", record->name, record->number) > 0){
        record->next = malloc(sizeof(struct node));
        record = record->next;
        record->name = malloc(50*sizeof(char));
        record->number = malloc(50*sizeof(char));
        list_size++;
    }
    record->next = NULL;
    record->name = NULL;
    record->number = NULL;
    fclose(fp);
}


// sortingnya agak bingung
void swap(struct node* ptr1, struct node* ptr2){
    struct node* tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}

void sort(int count){

}

// searching
void searchName(char target[]){
    struct node * iterator = contactRecord;
    while (iterator != NULL){
        char str[50];
        strcpy(str, iterator->name);
        for (int i=0; str[i]; i++){
            str[i] = tolower(str[i]);
        }
        for (int i=0; target[i]; i++){
            target[i] = tolower(target[i]);
        }
        if (strcmp(str, target) == 0){
            printf("%s\n%s", iterator->name, iterator->number);
            return;
        }
        iterator = iterator->next;
    }

}

void searchNumber(char target[]){
    // belum bang lagi mikir ganti number jdi integer
}

int main()
{
    contactRecord = malloc(sizeof(struct node));
    loadingData();
    char str[50];
    scanf("%s", str);
    searchName(str);

    return 0;
}
