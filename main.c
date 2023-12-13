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
*/

// linkedlist untuk menyimpan nama kontak dan nomor hp
struct node {
    char *name; // node nama kontak
    char *number; // node nomor kontak
    struct node *next;
};

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

struct node *contactRecord, *record; // contactRecord sebagai head node nya, record sebagai ptr nya

// ukuran dari banyaknya node terus di ditambah ketika ada penambahan dan dikurang ketika ada pengurangan dan disimpan di variabel list_size
int list_size = 0;

// fungsi ini untuk menampilkan isi dari linkedlistnya
// fidel
void printContactRecord(){
    struct node * iterator = contactRecord; // node iterator di assign ke head nodenya
    while (iterator!=NULL){ // terus di loop sampai node terakhir
        printf("nama kontak  : %s\n", iterator->name);
        printf("nomor kontak : %s\n", iterator->number);
        printf("-------------------------------------------------------------\n");
        iterator=iterator->next; // pindah ke node setelahnya
    }
    printf("\n");
}

// fungsi ini untuk menyimpan nama dan nomor kontak baru ke akhir linkedlist nya
// tika
void saveContact(){
    int count, i;
    struct node * temp = contactRecord; // membuat node temp untuk menyimpan di akhir nodenya
    printf("berapa banyak kontak yang ingin kamu simpan? ");
    scanf("%d", &count);
    while (temp->next != NULL){ // loop ini untuk pindah ke node terakhir
        temp=temp->next;
    }
    for(i=0; i<count; i++){
        temp->next = malloc(sizeof(struct node)); // node setelahnya di memory allocate untuk diisi oleh data baru
        temp = temp->next;
        temp->name = malloc(50*sizeof(char));
        temp->number = malloc(50*sizeof(char));

        printf("nama kontak: "); // bagian untuk mengisi nodenya dengan data baru
        scanf("%s", temp->name);
        printf("nomor kontak: ");
        scanf("%s", temp->number);
        list_size++; // list_size terus di update
    }
    temp->next = NULL; // ketika selesai node->next diisi oleh NULL sebagai tanda akhir dari linkedlistnya
    printf("\nberhasil disimpan\n\n");

}

// fungsi ini untuk menyimpan ke txt file
// abhi (saya sendiri)
void writeToFile(){
    FILE * fptr;
    fptr = fopen("data.txt", "w"); // untuk membuka filenya dan diisi oleh data yang ada di linkedlistnya
    struct node * iterator = contactRecord;

    if(fptr==NULL)
    {
        perror("Error:");
    }

    else
    {
        while(iterator!=NULL){ // di loop sampai node terakhir
            fprintf(fptr, "%s\n%s\n", iterator->name, iterator->number); // fprintf untuk mengisi ke txt filenya
            iterator= iterator->next;
        }
    }

    fclose(fptr); // menutup filenya setelah diisi
}


// fungsi ini untuk mengisi linkedlist nya dengan data yang ada di txt file ketika awal program baru mulai\
// Abhhi (saya senndiri)
void loadingData(){
    FILE * fp = fopen("data.txt", "r"); // membuka file sebagai read mode
    if (fp == NULL){
        perror("error:");
        exit(1);
    }
    struct node * prev; // node untuk mengtrack node sebelumnnya
    record = contactRecord; // record sebagai ptr dari head
    record->name = malloc(50*sizeof(char));
    record->number = malloc(50*sizeof(char));
    while (fscanf(fp, "%s %s", record->name, record->number) > 0){ // fscanf untuk mengisi linkedlist dari txt file sampai fscanf return EOF(end of field)
        record->next = malloc(sizeof(struct node));
        prev = record; // prev sebagai node sebelumnya dari node record
        record = record->next; // record lanjut di assign ke node setelahnya
        record->name = malloc(50*sizeof(char));
        record->number = malloc(50*sizeof(char));
        list_size++; // list_size terus diupdate
    }
    prev->next = NULL; // untuk menutup linkedlistnya dengan NULL
    free(record); // record harus dihapus agar tidak ada node yang tidak diinginkan
    fclose(fp); // untuk menutup txt filenya
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
            temp = contactRecord; // temp terus mulai lagi dari headnya
            swapped = 0;
        for (int j=0; j<list_size-i-1; j++){
            prev = temp; // prev sebagai node sebelumnya
            temp = temp->next; // temp lanjut ke node setelahnya
            strcpy(nama1, prev->name);  // strcpy untuk mengcopy data dari node ke string nama
            strcpy(nama2, temp->name);
            strcpy(nomor1, prev->number);
            strcpy(nomor2, temp->number);
            if (strcmp(nama2, nama1) < 0){ // strcmp untuk mengurutkan string secara abjad dengan return dari strcmp < 0
                strcpy(prev->name, nama2); // untuk swap nilainya
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
    while (iterator != NULL){ // cari terus sampai akhir nodenya
        char str[50];
        strcpy(str, iterator->name);
        // tolower untuk membuat string target dan string dari node nama menjadi huruf kecil agar menghilangkan sensitive case nya pada saat melakukan search
        for (int i=0; str[i]; i++){
            str[i] = tolower(str[i]);
        }
        for (int i=0; target[i]; i++){
            target[i] = tolower(target[i]);
        }

        if (strcmp(str, target) == 0){ // jika strcmp mengembalikan 0 berarti string kedua tersebut bernilai sama
            printf("nama kontak: %s\nnomor kontak: %s\n\n", iterator->name, iterator->number);
            return;
        }
        iterator = iterator->next; // untuk pindah ke node setelahnya
    }
    printf("\nnggak ada bang\n\n"); // jika tidak ditemukan
    return;
}

// fungsi ini untuk mencari nomor spesifik di linkdelistnya menggunakan linier search
// tika
void searchNumber(char target[]){
    struct node * iterator = contactRecord;
    while (iterator != NULL){ // cari terus sampai akhir nodenya
        if (strcmp(iterator->number, target) == 0){ // jika strcmp mengembalikan 0 berarti string kedua tersebut bernilai sama
            printf("nama kontak: %s\nnomor kontak: %s\n\n", iterator->name, iterator->number);
            return;
        }
        iterator = iterator->next; // untuk pindah ke node setelahnya

    }
    printf("\nnggak ada bang\n\n"); // jika tidak ditemukan
    return;
}

// fungsi ini untuk mengubah nomor kontak yang sudah di simpan dengan nomor kontak sebagai parameternya lalu dicari dan diubah
// fidel
void editNumber(char target[]){
    record = contactRecord;
    while (record != NULL){ // cari terus sampai akhir nodenya
        if (strcmp(record->number, target) == 0){ // jika strcmp mengembalikan 0 berarti string kedua tersebut bernilai sama
            printf("nomor kontak baru : ");
            scanf("%s", record->number); // isi node tersebut dengan nilai yang baru
            printf("\nberhasil diubah\n\n");
            return;
        }
        record = record->next; // untuk pindah ke node setelahnya
    }
    printf("\nnggak ada bang\n\n"); // jika tidak ditemukan
    return;

}


// fungsi ini untuk mengubah nama kontak yang sudah di simpan dengan nama kontak sebagai parameternya lalu dicari dan diubah
// fidel
void editName(char target[]){
    record = contactRecord;
    while (record != NULL){ // cari terus sampai akhir nodenya
        char str[50];
        strcpy(str, record->name);
        // tolower untuk membuat string target dan string dari node nama menjadi huruf kecil agar menghilangkan sensitive case nya pada saat melakukan search
        for (int i=0; str[i]; i++){
            str[i] = tolower(str[i]);
        }
        for (int i=0; target[i]; i++){
            target[i] = tolower(target[i]);
        }
        if (strcmp(str, target) == 0){ // jika strcmp mengembalikan 0 berarti string kedua tersebut bernilai sama
            printf("nama kontak baru : ");
            scanf("%s", record->name); // isi node tersebut dengan nilai yang baru
            printf("\nberhasil diubah\n\n");
            return;
        }
        record = record->next; // untuk pindah ke node setelahnya
    }
    printf("\nnggak ada bang\n\n"); // jika tidak ditemukan
    return;

}

// fungsi ini untuk menghapus salah satu nodenya dengan nama kontak sebagai parameternya dicari dan dihapus
// fidel
void deleteNode(char target[]){
    struct node * temp = contactRecord, * prev;

    // jika head tersebut merupakan data yang harus dihapus
    if (temp != NULL && strcmp(temp->name, target) == 0) {
        contactRecord = temp->next; // headnya pindah ke node temp setelahnya
        free(temp); // node tempnya di hapus
        list_size--; // list_size terus diupdate
        printf("\nberhasil dihapus\n\n");
        return;
    }

    // jika yang dihapus berada di tengah
    while (temp != NULL && strcmp(temp->name, target) != 0) { // jika ditemukan maka akan keluar dari loop
        prev = temp; // prev sebagai node sebelumnya
        temp = temp->next; // temp sebagai node yang sekarang
    }

    if (temp != NULL && strcmp(temp->name, target) == 0){ // jika ditemukan
        prev->next = temp->next; // membuat prev->next nya ke temp->nextnya agar node tempnya bisa dihapus
        free(temp); // menghapus node yang sekarang
        list_size--; // list_size terus diupdate
        printf("\nberhasil dihapus\n\n");
        return;
    } else {
        printf("\nnggak ada bang\n\n");
        return;
    }
}

int main(){
    contactRecord = malloc(sizeof(struct node));
    loadingData(); // awal mulai program loading data
    sort(); // untuk sort datanya
    int run = 1;
    while (run == 1){
        int choice;
        printf("Aplikasi Buku Telepon By Kelompok 6\n");
        printf("1)simpan kontak\n2)edit nama kontak\n3)edit nomor kontak\n4)cari nama kontak\n5)cari nomor kontak\n6)hapus kontak\n7)tampilkan semua kontak\n0)keluar\n");
        scanf("%d", &choice);
        if (choice == 1){
            clearScreen();
            saveContact();
            sort();
        }else if (choice == 2){
            clearScreen();
            char target[50];
            printf("nama kontak yang ingin diubah: ");
            scanf("%s", target);
            editName(target);
            sort();
        } else if (choice == 3){
            clearScreen();
            char target[50];
            printf("nomor kontak yang ingin diubah: ");
            scanf("%s", target);
            editNumber(target);
        } else if (choice == 4){
            clearScreen();
            char target[50];
            printf("nama kontak yang ingin dicari: ");
            scanf("%s", target);
            searchName(target);
        } else if (choice == 5){
            clearScreen();
            char target[50];
            printf("nomor kontak yang ingin dicari: ");
            scanf("%s", target);
            searchNumber(target);
        } else if (choice == 6){
            clearScreen();
            char target[50];
            printf("nama kontak yang ingin dihapus: ");
            scanf("%s", target);
            deleteNode(target);
        } else if (choice == 7){
            clearScreen();
            sort();
            printContactRecord();
        } else if (choice == 0){
            run = 0;
            break;
        } else {
            printf("masukkan sesuai pilihan\n\n");
        }
    }
    printf("\nTerima Kasih :>");
    writeToFile(); // selesai programnya jalan disimpan ke txt file

    return 0;
}
