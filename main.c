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

// linkedlist untuk menyimpan nama kontak dan nomor hp
struct node {
    char *name;
    char *number;
    struct node *next;
};

struct node *contactRecord, *record;
// ukuran dari banyaknya node terus di ditambah ketika ada penambahan dan dikurang ketika ada pengurangan dan disimpan di variabel list_size
int list_size = 0;


// fungsi ini untuk menampilkan isi dari linkedlistnya
// fidel
void printContactRecord(){
    struct node * iterator = contactRecord;
    while (iterator!=NULL){
        printf("nama kontak  : %s\n", iterator->name);
        printf("nomor kontak : %s\n", iterator->number);
        printf("-------------------------------------------------------------\n");
        iterator=iterator->next;
    }
    printf("\n");
}

// fungsi ini untuk menyimpan nama dan nomor kontak baru ke akhir linkedlist nya
// tika
void saveContact(){
    int count, i;
    struct node * temp = contactRecord;
    printf("berapa banyak kontak yang ingin kamu simpan? ");
    scanf("%d", &count);
    while (temp->next != NULL){
        temp=temp->next;
    }
    for(i=0; i<count; i++){
        temp->next = malloc(sizeof(struct node));
        temp = temp->next;
        temp->name = malloc(50*sizeof(char));
        temp->number = malloc(50*sizeof(char));

        printf("nama kontak: ");
        scanf("%s", temp->name);
        printf("nomor kontak: ");
        scanf("%s", temp->number);
        list_size++;
    }
    temp->next = NULL;
    printf("\nberhasil disimpan\n");

}

// fungsi ini untuk menyimpan ke txt file
// abhi (saya sendiri)
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
        for(int i=0; i<list_size; i++){
            fprintf(fptr, "%s\n%s\n", iterator->name, iterator->number);
            iterator= iterator->next;
        }
    }

    fclose(fptr);
}


// fungsi ini untuk mengisi linkedlist nya dengan data yang ada di txt file ketika awal program baru mulai\
// Abhhi (saya senndiri)
void loadingData(){
    FILE * fp = fopen("data.txt", "r");
    if (fp == NULL){
        perror("error:");
        exit(1);
    }
    struct node * prev;
    record = contactRecord;
    record->name = malloc(50*sizeof(char));
    record->number = malloc(50*sizeof(char));
    while (fscanf(fp, "%s %s", record->name, record->number) > 0){
        record->next = malloc(sizeof(struct node));
        prev = record;
        record = record->next;
        record->name = malloc(50*sizeof(char));
        record->number = malloc(50*sizeof(char));
        list_size++;
    }
    prev->next = NULL;
    free(record);
    fclose(fp);
    return;
}


// fungsi ini untuk mengurutkan nama kontak berdasarkan abjad menggunakan bubblesort
// abhhhi (sayya senndiri)
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

// fungsi ini untuk mencari spesifik nama di linkdelistnya menggunakan linier search
// tika
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
            printf("nama kontak: %s\nnomor kontak: %s\n\n", iterator->name, iterator->number);
            return;
        }
        iterator = iterator->next;
    }
    printf("\nnggak ada bang\n\n");
    return;
}

// fungsi ini untuk mencari nomor spesifik di linkdelistnya menggunakan linier search
// tika
void searchNumber(char target[]){
    struct node * iterator = contactRecord;
    while (iterator != NULL){
        if (strcmp(iterator->number, target) == 0){
            printf("nama kontak: %s\nnomor kontak: %s\n\n", iterator->name, iterator->number);
            return;
        }
        iterator = iterator->next;

    }
    printf("\nnggak ada bang\n\n");
    return;
}

// fungsi ini untuk mengubah nomor kontak yang sudah di simpan dengan nomor kontak sebagai parameternya lalu dicari dan diubah
// fidel
void editNumber(char target[]){
    record = contactRecord;
    while (record != NULL){
        if (strcmp(record->number, target) == 0){
            printf("nomor kontak baru : ");
            scanf("%s", record->number);
            printf("\nberhasil diubah\n\n");
            return;
        }
        record = record->next;
    }
    printf("\nnggak ada bang\n\n");
    return;

}


// fungsi ini untuk mengubah nama kontak yang sudah di simpan dengan nama kontak sebagai parameternya lalu dicari dan diubah
// fidel
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
            printf("\nberhasil diubah\n\n");
            return;
        }
        record = record->next;
    }
    printf("\nnggak ada bang\n\n");
    return;

}

// fungsi ini untuk menghapus salah satu nodenya dengan nama kontak sebagai parameternya dicari dan dihapus
// fidel
void deleteNode(char target[]){
    struct node * temp = contactRecord, * prev;

    if (temp != NULL && strcmp(temp->name, target) == 0) {
        contactRecord = temp->next;
        free(temp);
        list_size--;
        printf("\nberhasil dihapus\n\n");
        return;
    }
    //int i = 1;
    while (temp != NULL && strcmp(temp->name, target) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL && strcmp(temp->name, target) == 0){
        prev->next = temp->next;
        free(temp);
        list_size--;
        printf("\nberhasil dihapus\n\n");
        return;
    } else {
        printf("\nnggak ada bang\n\n");
        return;
    }
}

int main(){
    contactRecord = malloc(sizeof(struct node));
    loadingData();
    sort();
    int run = 1;
    while (run == 1){
        int choice;
        printf("Aplikasi Buku Telepon By Kelompok 6\n");
        printf("1)simpan kontak\n2)edit nama kontak\n3)edit nomor kontak\n4)cari nama kontak\n5)cari nomor kontak\n6)hapus kontak\n7)tampilkan semua kontak\n0)keluar\n");
        scanf("%d", &choice);
        if (choice == 1){
            saveContact();
        }else if (choice == 2){
            char target[50];
            printf("nama kontak yang ingin diubah: ");
            scanf("%s", target);
            editName(target);
        } else if (choice == 3){
            char target[50];
            printf("nomor kontak yang ingin diubah: ");
            scanf("%s", target);
            editNumber(target);
        } else if (choice == 4){
            char target[50];
            printf("nama kontak yang ingin dicari: ");
            scanf("%s", target);
            searchName(target);
        } else if (choice == 5){
            char target[50];
            printf("nomor kontak yang ingin dicari: ");
            scanf("%s", target);
            searchNumber(target);
        } else if (choice == 6){
            char target[50];
            printf("nama kontak yang ingin dihapus: ");
            scanf("%s", target);
            deleteNode(target);
        } else if (choice == 7){
            printContactRecord();
        } else if (choice == 0){
            run = 0;
            break;
        } else {
            printf("masukkan sesuai pilihan\n\n");
        }
        sort();
    }
    printf("\nTerima Kasih :>");
    writeToFile();

    return 0;
}
