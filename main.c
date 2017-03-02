#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 999999
#define N 23
#define MAX 23

FILE *sehirKodlari,*sehirMesafeler;
char buff[255];
int toplamSehir;

char sehirKodlariDizisi[50][50];
int komsulukDizisi[50][50];

int sehirKoduBul(char sehirKoduDizi[][50],char *sehirAdi){

    for(int i=1;i<toplamSehir+1;i++){
        if(!strcmp(sehirKoduDizi[i],sehirAdi)){
            return i;
        }

    }
    return 0;
}

int dijsktra(int maliyetDizisi[][N],int merkezSehir,int hedefSehir,char sehirDizisi[50][50]){
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

    while(baslangic != -1){
        yol[j++] = baslangic+65;
        baslangic = onceki[baslangic];
    }

    yol[j]='\0';
    strrev(yol);
    //printf("%s", path);
    yoluYazdir(yol,sehirDizisi);
    return mesafe[hedefSehir];
}

void yoluYazdir(char yol[50],char sehirKodlari[50][50]){

    for(int i = 0;i<50;i++){
        if(yol[i] == '\0'){
            break;
        }
        printf("%s-",sehirKodlari[yol[i]-65]);
    }

}

void dijkstra2(,int startnode)
{

    int cost[MAX][MAX],distance[MAX],pred[MAX];
    int visited[MAX],count,mindistance,nextnode,i,j;
    int n = toplamSehir;
    for(i=1;i<n;i++)
        for(j=1;j<n;j++)
            if(komsulukDizisi[i][j]==0)
                cost[i][j]=INF;
            else
                cost[i][j]=komsulukDizisi[i][j];

    for(i=1;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }

    distance[startnode]=0;
    visited[startnode]=1;
    count=1;

    while(count<n-1)
    {
        mindistance=INF;


        for(i=1;i<n;i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }

            visited[nextnode]=1;
            for(i=1;i<n;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }

    for(i=1;i<n;i++)
        if(i!=startnode)
        {
            printf("\n%s 'e uzakligi = %d",sehirKodlariDizisi[i],distance[i]);
            printf("\nGidilen Yol : %s",sehirKodlariDizisi[i]);

            j=i;
            do
            {
                j=pred[j];
                printf("<-%s",sehirKodlariDizisi[j]);
            }while(j!=startnode);

        }
}

int sehirKodlariDosyasiniAc(){

    sehirKodlari = fopen("\sehir kod.txt","r");

    if(sehirKodlari == NULL){
        printf("Sehir kodlari dosyasi bulunamadi!\n");
        return -1;
    }


    char * kod;
    char * sehiradi;



    while( (fscanf(sehirKodlari, "%s", buff)) != EOF){

      sehiradi = strtok(buff,"-");
      kod = strtok(NULL,"-");
      int i = atoi(kod);
      strcpy(sehirKodlariDizisi[i],sehiradi);
      printf("%s - %s\n",kod,sehiradi);
    }

     toplamSehir = atoi(kod);

    fclose(sehirKodlari);
    return 1;
}

int mesafelerDosyasiniAc(){

    sehirMesafeler = fopen("\sehir mesafe.txt","r");

    if(sehirMesafeler == NULL){
        printf("Sehir Mesafe dosyasi acilamadi!");
        return -1;
    }

    char * sehir1;
    char * sehir2;
    char * mesafe;


     for(int i = 0;i<toplamSehir;i++){
        for(int j = 0;j<toplamSehir;j++){
        komsulukDizisi[i][j] = INF;
        }
    }

    while((fscanf(sehirMesafeler,"%s",buff)) != EOF){

        sehir1 = strtok(buff,"-");
        sehir2 = strtok(NULL,"-");
        mesafe = strtok(NULL,"-");

        int x = sehirKoduBul(sehirKodlariDizisi,sehir1);
        int y = sehirKoduBul(sehirKodlariDizisi,sehir2);
        int w = atoi(mesafe);
        komsulukDizisi[x][y] = komsulukDizisi[y][x] = w;
    }
    fclose(sehirMesafeler);
    return 1;
}

int main(){

   if(sehirKodlariDosyasiniAc() == -1){
        return;
   }

   if(mesafelerDosyasiniAc() == -1){
        return;
   }



    //int sonuc = dijsktra(maliyetDizi,1,17,dizi);
    //printf("\n%d",sonuc);
    dijkstra2(1);
    return 0;
}
