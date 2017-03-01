#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 999999

int sehirKoduBul(char sehirKoduDizi[][50],char *sehirAdi,int maxSehir){

    for(int i=0;i<maxSehir;i++){
        if(!strcmp(sehirKoduDizi[i],sehirAdi)){
            return i;
        }

    }
    return 0;
}


int main()
{
    FILE *sehirKodlari,*sehirMesafeler;

    sehirKodlari = fopen("\sehir kod.txt","r");

    if(sehirKodlari == NULL){
        printf("Sehir kodlari dosyasi bulunamadi!\n");
    }

    char buff[255];
    char * kod;
    char * sehiradi;

    char dizi[50][50];

    while( (fscanf(sehirKodlari, "%s", buff)) != EOF){

      sehiradi = strtok(buff,"-");
      kod = strtok(NULL,"-");
      int i = atoi(kod);
      strcpy(dizi[i],sehiradi);
      //printf("%s , %s\n",sehiradi,kod);
    }

    int toplamSehir = atoi(kod) + 1;
        ///printf("Toplam sehir sayisi : %d\n",toplamSehir);

    fclose(sehirKodlari);


    sehirMesafeler = fopen("\sehir mesafe.txt","r");
    char * sehir1;
    char * sehir2;
    char * mesafe;

    int maliyetDizi[toplamSehir][toplamSehir];

     for(int i = 0;i<toplamSehir;i++){
        for(int j = 0;j<toplamSehir;j++){
        maliyetDizi[i][j] = INF;
        }
    }

    while((fscanf(sehirMesafeler,"%s",buff)) != EOF){

        sehir1 = strtok(buff,"-");
        sehir2 = strtok(NULL,"-");
        mesafe = strtok(NULL,"-");

        int x = sehirKoduBul(dizi,sehir1,toplamSehir);
        int y = sehirKoduBul(dizi,sehir2,toplamSehir);
        int w = atoi(mesafe);
        maliyetDizi [x][y] = maliyetDizi[y][x] = w;
        //printf("%s , %s , %s\n",sehir1,sehir2,mesafe);

    }

    for(int i = 0;i<toplamSehir;i++){
        for(int j = 0;j<toplamSehir;j++){
          if(maliyetDizi[i][j] != INF){
           // printf("%d - %d : %d\n",i,j,maliyetDizi[i][j]);
          }

        }
    }


    return 0;
}
