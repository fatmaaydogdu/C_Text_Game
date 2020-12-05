#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Soru Soru;
typedef struct SkorKaydi SkorKaydi;

struct Soru {
    int ID;
    char *soru_metni;
    char *A, *B, *C, *D;
    char dogru_cevap;
    Soru *sonraki;
};

struct SkorKaydi {
    char *kullanici_adi;
    int skor;
    SkorKaydi *sonraki;
};

int soruID, soru_miktari;
Soru *ilk_soru;
SkorKaydi *ilk_skor;

void soru_listesine_ekle(Soru *yeni_soru) {
    if (ilk_soru == NULL) {
        ilk_soru = yeni_soru;
    } else {
        Soru *soru;
        for (soru = ilk_soru; soru->sonraki != NULL; soru = soru->sonraki);
        soru->sonraki = yeni_soru;
    }
    soru_miktari++;
}

char *dosyadan_metin_oku(char *str, FILE *file) {
    str = calloc(100, sizeof(char));

    int i;
    char c;
    for (i = 0; fscanf(file, "%c", &c); i++) {
        if (c == '\n') {
            if (i == 0) {
                i = -1;
                continue;
            }
            str[i] = '\0';
            break;
        } else {
            str[i] = c;
        }
    }

    return str;
}

void listeyi_temizle(Soru *soru) {
    if (soru == NULL) return;

    listeyi_temizle(soru->sonraki);
    free(soru);
}

void sorulari_dosyadan_oku() {
    listeyi_temizle(ilk_soru);
    soru_miktari = 0;
    ilk_soru = NULL;

    char sorular_txt[] = "Sorular.txt";
    FILE *soru_dosyasi = fopen(sorular_txt, "r");

    if (soru_dosyasi == NULL) {
        return;
    }

    int ID;
    fscanf(soru_dosyasi, "%d-) ", &ID);

    while (!feof(soru_dosyasi)) {
        Soru *soru = (Soru *) malloc(sizeof(Soru));
        if (ID != 0) {
            soru->ID = ID;
            ID = 0;
        } else {
            fscanf(soru_dosyasi, "%d-) ", &soru->ID);
        }
        soruID = soru->ID + 1;
        soru->soru_metni = dosyadan_metin_oku(soru->soru_metni, soru_dosyasi);
        fscanf(soru_dosyasi, "A) ");
        soru->A = dosyadan_metin_oku(soru->A, soru_dosyasi);
        fscanf(soru_dosyasi, "B) ");
        soru->B = dosyadan_metin_oku(soru->B, soru_dosyasi);
        fscanf(soru_dosyasi, "C) ");
        soru->C = dosyadan_metin_oku(soru->C, soru_dosyasi);
        fscanf(soru_dosyasi, "D) ");
        soru->D = dosyadan_metin_oku(soru->D, soru_dosyasi);
        fscanf(soru_dosyasi, "Cevap: ");
        fscanf(soru_dosyasi, "%c", &soru->dogru_cevap);

        char c;
        fscanf(soru_dosyasi, "%c\n", &c);

        soru->sonraki = NULL;

        soru_listesine_ekle(soru);
    }

    fclose(soru_dosyasi);
}

int islem_secimi() {
    int secim;

     printf("\t\t ***TEST OYUNUMUZA HOSGELDINIZ*** \n");
     printf("\n\t\t________________________________________");
     printf("\n\t\t________________________________________");
     printf("\n\t\t________________________________________");
     printf("\n\t\t________________________________________");
     printf("\n\t\t________________________________________");
     printf("\n\t\t > Soru eklemek icin 1'i seciniz");
     printf("\n\t\t > Soru silmek icin 2'yi seciniz");
     printf("\n\t\t > Sorulari gormek icin ve guncellemek icin 3'u seciniz");
     printf("\n\t\t > Oyun oynamak icin 4'u seciniz");
     printf("\n\t\t > Skorlari gormek icin 5'i seciniz");
     printf("\n\t\t > Oyundan cikmak icin 6'yi seciniz");
     printf("\n\t\t________________________________________\n\n");
     
     printf("\n\t\t >> Cevaplarinizi buyuk harf ile belirtiniz >>\n");
     printf("\n\t\t >>Yapmak istediginiz islemi seciniz>>");
    scanf("%d", &secim);

    return secim;
}

char *metin_oku(char *str) {
    str = calloc(100, sizeof(char));

    int i;
    char c;
    for (i = 0; (c = getc(stdin)); i++) {
        if (c == '\n') {
            if (i == 0) {
                i = -1;
                continue;
            }
            str[i] = '\0';
            break;
        } else {
            str[i] = c;
        }
    }

    return str;
}

void soru_dosyasini_guncelle() {
    char sorular_txt[] = "Sorular.txt";
    FILE *soru_dosyasi = fopen(sorular_txt, "w");
    Soru *soru;

    for (soru = ilk_soru; soru != NULL; soru = soru->sonraki) {
        fprintf(soru_dosyasi, "%d-) %s\nA) %s\nB) %s\nC) %s\nD) %s\nCevap: %c\n\n",
                soru->ID, soru->soru_metni, soru->A, soru->B, soru->C, soru->D, soru->dogru_cevap);
    }

    fclose(soru_dosyasi);
}

void soru_ekle() {
    Soru *yeni_soru = (Soru *) malloc(sizeof(Soru));
    yeni_soru->ID = soruID++;
    yeni_soru->sonraki = NULL;

    printf("Bir soru girin:");
    yeni_soru->soru_metni = metin_oku(yeni_soru->soru_metni);
    printf("A:");
    yeni_soru->A = metin_oku(yeni_soru->A);
    printf("B:");
    yeni_soru->B = metin_oku(yeni_soru->B);
    printf("C:");
    yeni_soru->C = metin_oku(yeni_soru->C);
    printf("D:");
    yeni_soru->D = metin_oku(yeni_soru->D);
    printf("Dogru cevap:");
    scanf("%c", &yeni_soru->dogru_cevap);

    soru_listesine_ekle(yeni_soru);

    soru_dosyasini_guncelle();

    printf("Soru basariyla eklendi.\n");
}

void soru_silinme_kontrol(int basarili) {
    if (basarili) {
        soru_dosyasini_guncelle();
        soru_miktari--;
        printf("Soru basariyla silindi.\n");
    } else {
        printf("Soru bulunamadi.\n");
    }
}

void soru_sil() {
    int silinecekID;
    Soru *soru, *temp;
    for (soru = ilk_soru; soru != NULL; soru = soru->sonraki) {
        printf("%d-) %s\n", soru->ID, soru->soru_metni);
    }

    if (ilk_soru == NULL) {
        printf("Kayitli soru yok\n");
        return;
    }

    printf("Silmek istediginiz sorunun ID'sini girin:");
    scanf("%d", &silinecekID);

    if (ilk_soru->ID == silinecekID) {
        temp = ilk_soru;
        ilk_soru = ilk_soru->sonraki;
        free(temp);
        soru_silinme_kontrol(1);
        return;
    }

    for (soru = ilk_soru; soru->sonraki != NULL; soru = soru->sonraki) {
        if (soru->sonraki->ID == silinecekID) {
            temp = soru->sonraki;
            soru->sonraki = soru->sonraki->sonraki;
            free(temp);
            soru_silinme_kontrol(1);
            return;
        }
    }
    soru_silinme_kontrol(0);
}

void goster_ve_guncelle() {
    if (ilk_soru == NULL) {
        printf("Kayitli soru yok\n");
        return;
    }

    char sorular_txt[] = "Sorular.txt";
    FILE *soru_dosyasi = fopen(sorular_txt, "r");
    while (!feof(soru_dosyasi)) {
        char c;
        fscanf(soru_dosyasi, "%c", &c);
        putchar(c);
    }

    fclose(soru_dosyasi);

    printf("Guncellemek istediginiz soru ID'sini girin:");
    int ID;
    scanf("%d", &ID);

    Soru *soru;
    for (soru = ilk_soru; soru != NULL; soru = soru->sonraki) {
        if (soru->ID == ID) {
            printf("Yeni soru metnini girin:");
            soru->soru_metni = metin_oku(soru->soru_metni);
            printf("A:");
            soru->A = metin_oku(soru->A);
            printf("B:");
            soru->B = metin_oku(soru->B);
            printf("C:");
            soru->C = metin_oku(soru->C);
            printf("D:");
            soru->D = metin_oku(soru->D);
            printf("Dogru cevap:");
            scanf("%c", &soru->dogru_cevap);

            soru_dosyasini_guncelle();

            printf("Soru basariyla guncellendi.\n");
            return;
        }
    }

    printf("Soru bulunamadi.\n");
}

void skor_dosyasini_guncelle() {
    char skorlar_txt[] = "Skorlar.txt";
    FILE *skor_dosyasi = fopen(skorlar_txt, "w");
    SkorKaydi *kayit;

    for (kayit = ilk_skor; kayit != NULL; kayit = kayit->sonraki) {
        fprintf(skor_dosyasi, "Kullanici adi: %s\nSkor: %d\n\n", kayit->kullanici_adi, kayit->skor);
    }

    fclose(skor_dosyasi);
}

void skor_listesine_ekle(SkorKaydi *kayit) {
    SkorKaydi *temp, *kontrol;
    if (ilk_skor == NULL) ilk_skor = kayit;
    else if (kayit->skor > ilk_skor->skor) {
        temp = ilk_skor;
        ilk_skor = kayit;
        kayit->sonraki = temp;
    } else {
        for (kontrol = ilk_skor; ; kontrol = kontrol->sonraki) {
            if (kontrol->sonraki == NULL) {
                kontrol->sonraki = kayit;
                break;
            } else if (kayit->skor > kontrol->sonraki->skor) {
                temp = kontrol->sonraki;
                kontrol->sonraki = kayit;
                kayit->sonraki = temp;
                break;
            }
        }
    }

    skor_dosyasini_guncelle();
}

void skorlari_dosyadan_oku() {
    ilk_skor = NULL;

    char skorlar_txt[] = "Skorlar.txt";
    FILE *skor_dosyasi = fopen(skorlar_txt, "r");

    if (skor_dosyasi == NULL) {
        return;
    }

    fscanf(skor_dosyasi, "");

    while (!feof(skor_dosyasi)) {
        SkorKaydi *kayit = (SkorKaydi *) malloc(sizeof(SkorKaydi));
        fscanf(skor_dosyasi, "Kullanici adi: ");
        kayit->kullanici_adi = dosyadan_metin_oku(kayit->kullanici_adi, skor_dosyasi);
        fscanf(skor_dosyasi, "Skor: ");
        fscanf(skor_dosyasi, "%d", &kayit->skor);

        char c;
        fscanf(skor_dosyasi, "%c\n", &c);

        kayit->sonraki = NULL;

        skor_listesine_ekle(kayit);
    }

    fclose(skor_dosyasi);
}

void oyun_oyna() {
    if (soru_miktari < 5) {
        printf("Oyun icin en az 5 soru gerekli.\n");
        return;
    }

    char cevap_anahtari[5];
    char kullanici_cevaplari[5];

    SkorKaydi *yeni_kayit = (SkorKaydi *) malloc(sizeof(SkorKaydi));
    yeni_kayit->sonraki = NULL;
    yeni_kayit->skor = 0;

    int i, j;
    for (i = 0; i < 5; i++) {
        fflush(stdin);

        Soru *soru, *temp;
        int index = rand() % (soru_miktari - i);

        if (index == 0) {
            temp = ilk_soru;
            ilk_soru = ilk_soru->sonraki;
        } else {
            for (j = 0, soru = ilk_soru; j < index - 1; j++, soru = soru->sonraki);
            temp = soru->sonraki;
            soru->sonraki = soru->sonraki->sonraki;
        }

        cevap_anahtari[i] = temp->dogru_cevap;
        printf("Soru %d-) %s?\nA) %s\nB) %s\nC) %s\nD) %s\nCevabiniz:", i + 1, temp->soru_metni, temp->A, temp->B, temp->C,
               temp->D);
        free(temp);

        scanf("%c", &kullanici_cevaplari[i]);

        if (cevap_anahtari[i] == kullanici_cevaplari[i]) yeni_kayit->skor++;
    }

    sorulari_dosyadan_oku();

    fflush(stdin);
    printf("Oyun bitti, skorunuz: %d\nKullanici adinizi girin:", yeni_kayit->skor);
    yeni_kayit->kullanici_adi = metin_oku(yeni_kayit->kullanici_adi);

    skor_listesine_ekle(yeni_kayit);
    printf("Skor listesine basariyla eklendi.\n");
}

void yuksek_skorlari_goruntule() {
    printf("En yuksek uc skor goruntuleniyor:\n");
    SkorKaydi *kayit;
    int i;
    for (i = 0, kayit = ilk_skor; i < 3; i++, kayit = kayit->sonraki) {
        printf("Kullanici adi: %s\nSkor: %d\n\n", kayit->kullanici_adi, kayit->skor);
    }
}

int main() {
    soruID = 1;
    soru_miktari = 0;

    srand(time(0));

    sorulari_dosyadan_oku();
    skorlari_dosyadan_oku();

    int secim;
    do {
        fflush(stdin);
        secim = islem_secimi();
        switch (secim) {
            case 1:
                soru_ekle();
                break;
            case 2:
                soru_sil();
                break;
            case 3:
                goster_ve_guncelle();
                break;
            case 4:
                oyun_oyna();
                break;
            case 5:
                yuksek_skorlari_goruntule();
                break;
            case 6:
                printf("Program sonlandiriliyor\n");
                break;
            default:
                printf("Gecersiz giris\n");
                break;
        }
    } while (secim != 6);

    return 0;
}
