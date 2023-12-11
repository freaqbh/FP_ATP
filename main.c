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
    - data di simpan di txt file tpi gk bisa nyimpan spasi
    - loading data gk bisa loading spasi
    - simpan data di akhir linkedlist
    - print linkedlist
    - searching selesai (searching nama, searching nomor)
    - edit data
    - delete

    tahap yang belum
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
    struct node * iterator = contactRecord;
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


// bubblesort
void sort(){
    struct node * temp = contactRecord, *prev;
    int swapped;

    char nama1[50], nama2[50];
    char nomor1[50], nomor2[50];

    for (int i=0; i<list_size-1; i++){
            temp = contactRecord;
            swapped = 0;
        for (int j=0; j<list_size-i-1; j++){
            prev = temp;
            temp = temp->next;
            strcpy(nama1, prev->name);
            strcpy(nama2, temp->name);
            strcpy(nomor1, prev->number);
            strcpy(nomor2, temp->number);
            if (strcmp(nama2, nama1) < 0){
                strcpy(prev->name, nama2);
                strcpy(temp->name, nama1);
                strcpy(prev->number, nomor2);
                strcpy(temp->number, nomor1);
                swapped = 1;
            }
        }
        if (swapped == 0){
            break;
        }
    }
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
    printf("\ngk ada bang\n");
    return;
}

void searchNumber(char target[]){
    struct node * iterator = contactRecord;
    while (iterator != NULL){
        if (strcmp(iterator->number, target) == 0){
            printf("%s\n%s", iterator->name, iterator->number);
            return;
        }
        iterator = iterator->next;

    }
    printf("\ngk ada bang\n");
    return;
}

// edit
void editNumber(char target[]){
    record = contactRecord;
    while (record != NULL){
        if (strcmp(record->number, target) == 0){
            printf("nomor kontak baru : ");
            scanf("%s", record->number);
            printf("\nberhasil diubah\n");
            return;
        }
        record = record->next;
    }
    printf("\ngk ada bang\n");
    return;

}

void editName(char target[]){
    record = contactRecord;
    while (record != NULL){
        char str[50];
        strcpy(str, record->name);
        for (int i=0; str[i]; i++){
            str[i] = tolower(str[i]);
        }
        for (int i=0; target[i]; i++){
            target[i] = tolower(target[i]);
        }
        if (strcmp(str, target) == 0){
            printf("nama kontak baru : ");
            scanf("%s", record->name);
            printf("\nberhasil diubah\n");
            return;
        }
        record = record->next;
    }
    printf("\ngk ada bang\n");
    return;

}

// delete
void deleteNode(char target[]){
    struct node * temp = contactRecord, * prev;

    if (temp != NULL && strcmp(temp->name, target) == 0) {
        contactRecord = temp->next;
        free(temp);
        list_size--;
        printf("\nberhasil dihapus\n");
        return;
    }
    int i = 1;
    while (temp != NULL && strcmp(temp->name, target) != 0) {
        prev = temp;
        temp = temp->next;
        i++;
        if (i == list_size) break;
    }

    if (temp != NULL && strcmp(temp->name, target) == 0){
        prev->next = temp->next;
        free(temp);
        list_size--;
        printf("\nberhasil dihapus\n");
        return;
    } else {
        printf("\ngk ada bang\n");
        return;
    }
}

int main(){
    contactRecord = malloc(sizeof(struct node));
    loadingData();
    sort();
    printContactRecord();

    return 0;
}
