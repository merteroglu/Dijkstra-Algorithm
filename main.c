#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 999999
#define N 23

int sehirKoduBul(char sehirKoduDizi[][50],char *sehirAdi,int maxSehir){

    for(int i=0;i<maxSehir;i++){
        if(!strcmp(sehirKoduDizi[i],sehirAdi)){
            return i;
        }

    }
    return 0;
}

int dijsktra(int maliyetDizisi[][N],int merkezSehir,int hedefSehir,char sehirDizisi[50][50])
{
    int mesafe[N],onceki[N],gidilmis[N]={0},baslangic;
    char yol[N];
    for(int i=1;i< N;i++)
    {
        mesafe[i] = INF;
        onceki[i] = -1;
    }
    baslangic = merkezSehir;
    gidilmis[baslangic]=1;
    mesafe[baslangic] = 0;
    int min , m , d;
    while(gidilmis[hedefSehir] ==0)
    {
        min = INF;
        m = 0;
        for(int i=1;i< N;i++)
        {
            d = mesafe[baslangic] + maliyetDizisi[baslangic][i];
            if(d < mesafe[i] && gidilmis[i]==0)
            {
                mesafe[i] = d;
                onceki[i] = baslangic;
            }
            if(min>mesafe[i] && gidilmis[i]==0)
            {
                min = mesafe[i];
                m = i;
            }
        }
        baslangic = m;
        gidilmis[baslangic] = 1;
    }
    baslangic = hedefSehir;
   int j = 0;
    while(baslangic != -1)
    {
        yol[j++] = baslangic+65;
        baslangic = onceki[baslangic];
    }

    yol[j]='\0';
    strrev(yol);
    //printf("%s", path);
    yoluYazdir(yol,sehirDizisi);
    return mesafe[hedefSehir];
}

void yoluYazdir(char path[50],char dizi[50][50]){

    for(int i = 0;i<50;i++){
        if(path[i] == '\0'){
            break;
        }
        printf("%s-",dizi[path[i]-65]);
    }

}

int main()
{
     char buff[255];

    FILE *sehirKodlari,*sehirMesafeler;

    sehirKodlari = fopen("\sehir kod.txt","r");

    if(sehirKodlari == NULL){
        printf("Sehir kodlari dosyasi bulunamadi!\n");
    }


    char * kod;
    char * sehiradi;

    char dizi[50][50];

    while( (fscanf(sehirKodlari, "%s", buff)) != EOF){

      sehiradi = strtok(buff,"-");
      kod = strtok(NULL,"-");
      int i = atoi(kod);
      strcpy(dizi[i],sehiradi);
      printf("%s - %s\n",kod,sehiradi);
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

   // printf("%d - %d - %d\n",1,3,maliyetDizi[1][3]);


    int sonuc = dijsktra(maliyetDizi,1,17,dizi);
    printf("\n%d",sonuc);

    return 0;
}
