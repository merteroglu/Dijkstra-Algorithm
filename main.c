#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 99999999

FILE *sehirKodlari,*sehirMesafeler;
char buff[255];
int toplamSehir = 0;

char **sehirKodlariDizisi;



int sehirKoduBul(char *sehirAdi)
{

    for(int i=1; i<toplamSehir+1; i++)
    {
        if(!strcmp(sehirKodlariDizisi[i],sehirAdi))
        {
            return i;
        }

    }
    return 0;
}

int dijsktra(int maliyetDizisi[toplamSehir+1][toplamSehir+1],int merkezSehir,int hedefSehir)
{
    int mesafe[toplamSehir+1],onceki[toplamSehir+1];
    int gidilmis[toplamSehir+1];
    int baslangic;
    char yol[toplamSehir+1];

    for(int i=0; i< toplamSehir+1; i++)
    {
        mesafe[i] = INF;  /// Tum mesafeler sonsuz
        onceki[i] = -1;   /// Onceki mesafeler -1 (gidilmemiş)
        gidilmis[i] = 0; /// Gidilmiş şehirler 0
    }

    baslangic = merkezSehir; /// Baslangic olarak merkez sehiri ayarla
    gidilmis[baslangic]=1;  /// Baslangic sehrine git
    mesafe[baslangic] = 0;  /// Baslangica gidis mesafesi 0
    int min , m , d,s = 0;
    while(gidilmis[hedefSehir] == 0 && s<=toplamSehir) /// Hedef sehire gidilene kadar devam et
    {
        min = INF; /// Min uzaklik sonsuz
        m = 0;
        for(int i=1; i< toplamSehir+1; i++) /// Matris 0 da sehir bilgisi yok o yuzden 1 den basla
        {
            d = mesafe[baslangic] + maliyetDizisi[baslangic][i]; /// Mesafeyi bul suan ki deger ve yeni yol
            if(d < mesafe[i] && gidilmis[i]==0)  /// Daha kisa ve gidilmemis ise onu sec
            {
                mesafe[i] = d; /// Yeni kisa yolu yaz
                onceki[i] = baslangic; /// Onceki mesafeyi tut
            }
            if(min>mesafe[i] && gidilmis[i]==0)  /// Min mesafe den kisa ve gidilmemis ise yeni min o
            {
                min = mesafe[i];
                m = i;
            }
        }
        baslangic = m; /// Yeni dugumu baslangica ata hedefe gidene kadar dongu devam
        gidilmis[baslangic] = 1; /// Gidildi yap
        s++;
    }

    baslangic = hedefSehir; /// Hedef sehirin kodunu baslangica ata
    int j = 0;

    while(baslangic != -1)   /// Hedef sehire gidene kadar olan yolu tut
    {
        yol[j++] = baslangic + 65; /// strrev kullanabilmek icin chara donüstür 65 ekleyerek
        baslangic = onceki[baslangic];
    }

    yol[j]='\0';
    strrev(yol); /// Terse çevir
    yoluYazdir(yol);
    return mesafe[hedefSehir]; /// En kisa yolu dondur
}

void yoluYazdir(char yol[50])
{

    for(int i = 0; i<50; i++)
    {
        if(yol[i] == '\0') /// Yol sona gelince dur
        {
            break;
        }
        if(i == 0)
        printf("%s",sehirKodlariDizisi[yol[i]-65]); /// ilk sehir ise basinda - olmasin
        else
        printf("-%s",sehirKodlariDizisi[yol[i]-65]); /// 65 çıkarıp inte çevir sehirKodları matrisinde ki indexten şehir adını yaz
    }

}

void dijkstra2(int merkezSehir,int komsulukDizisi[toplamSehir+1][toplamSehir+1])
{
    int MAX = toplamSehir + 1 ; /// Toplam sehir sayisinin bir fazlasını dizi olustururken kullanmak icin
    int mesafe[MAX],onceki[MAX];
    int gidilmis[MAX],sayac,min,sonraki=0,i,j;
    int n = toplamSehir+1;


    for(i=1; i<n; i++)
    {
        mesafe[i]= komsulukDizisi[merkezSehir][i]; /// merkez sehirden dier tüm sehirlere olan mesafeler
        onceki[i]= merkezSehir;
        gidilmis[i]= 0;
    }

    mesafe[merkezSehir]=0; /// baslangic sehiri mesafesi 0
    gidilmis[merkezSehir]=1; /// Baslangica gidildi isaretle
    sayac=1; /// Gidilen sehirleri say

    while(sayac<n-1) /// Gidilen sehir sayisi tüm sehir sayisina erisene kadar
    {
        min=INF; /// min mesafe sonsuz


        for(i=1; i<n; i++)
            if(mesafe[i]<min && !gidilmis[i])
            {
                min=mesafe[i];
                sonraki=i;
            }

        gidilmis[sonraki]=1;

        for(i=1; i<n; i++)
            if(!gidilmis[i])
                if(min+komsulukDizisi[sonraki][i]<mesafe[i])
                {
                    mesafe[i]=min+komsulukDizisi[sonraki][i];
                    onceki[i]=sonraki;
                }


        sayac++;
    }

    char yol[50];


    for(i=1; i<n; i++)
        if(i!=merkezSehir)
        {
            printf("\n%s 'e uzakligi = %d",sehirKodlariDizisi[i],mesafe[i]);
            printf("\nGidilen Yol :");
            yol[0] = i + 65;

            j=i;
            int t = 0;
            while(j!=merkezSehir)
            {
                yol[t++] = j + 65;
                j=onceki[j];
            }

            yol[t] = merkezSehir + 65;
            yol[++t]='\0';
            strrev(yol); /// Terse çevir
            yoluYazdir(yol);
            printf("\n");
        }








}

int sehirKodlariDosyasiniAc()
{

    sehirKodlari = fopen("\sehir kod.txt","r"); /// Exe yanında ki sehir kod txt i ac

    if(sehirKodlari == NULL) /// Acildi mi kontrol et
    {
        printf("Sehir kodlari dosyasi bulunamadi!\n");
        return -1;
    }

   /*
    Text dosyasında '-' ile ayrılan iki stringi tutmak icin degiskenler
    SehirAdi-Kod
    */
    char * kod;
    char * sehiradi;

     while( (fscanf(sehirKodlari, "%s", buff)) != EOF) /// Dosya sonuna gelene kadar oku
    {

        sehiradi = strtok(buff,"-"); /// Dosyadan okunan satiri buffer da tutmustuk onu '-' karakterine kadar ayiriyoruz
        kod = strtok(NULL,"-");  ///    Kaldigi yerden kalan kismi al
    }

    toplamSehir = atoi(kod); /// Son sehirin kodu toplam sehir sayisina esitle

    rewind(sehirKodlari); /// Dosyanin basina git

    sehirKodlariDizisi = (char **) malloc((toplamSehir+1) * sizeof(char *) ); /// Toplam sehir miktarı kadar matris olustur
    for(int j = 0;j<toplamSehir+1;j++) /// Matrisin sutunlari icin yer al
        sehirKodlariDizisi[j] = (char*)malloc(20*sizeof(char));

    while( (fscanf(sehirKodlari, "%s", buff)) != EOF) /// Dosya sonuna kadar oku
    {

        sehiradi = strtok(buff,"-");
        kod = strtok(NULL,"-");
        int i = atoi(kod);
     /// Parcalama islemi sonrası sehir kodunun oldugu index e sehir adini yaz
        strcpy(sehirKodlariDizisi[i],sehiradi);

        printf("%s - %s\n",kod,sehiradi);
    }

    fclose(sehirKodlari); /// dosyayi kapat
    return 1; /// islem basarili
}

int mesafelerDosyasiniAc(int komsulukDizisi[toplamSehir+1][toplamSehir+1])
{

    sehirMesafeler = fopen("\sehir mesafe.txt","r"); /// Sehir mesafe txt dosyasini bul ve ac

    if(sehirMesafeler == NULL) /// Acilamadi ise
    {
        printf("Sehir Mesafe dosyasi acilamadi!");
        return -1;
    }

   /// Dosya formati Sehir1-Sehir2-Mesafe
    char * sehir1;
    char * sehir2;
    char * mesafe;


    for(int i = 0; i<toplamSehir+1; i++)
    {
        for(int j = 0; j<toplamSehir+1; j++)
        {
            komsulukDizisi[i][j] = INF; ///Komsuluk matrisini olustur.İlk olarak hepsine sonsuz ata
        }
    }

    while((fscanf(sehirMesafeler,"%s",buff)) != EOF) /// Dosya sonuna kadar satir satir oku
    {
         /// Her satiri parcalara ayir
        sehir1 = strtok(buff,"-");
        sehir2 = strtok(NULL,"-");
        mesafe = strtok(NULL,"-");

        int x = sehirKoduBul(sehir1); /// Sehir adi dosyadan okunduktan sonra onun kodunu bul x e ata
        int y = sehirKoduBul(sehir2); /// Sehir adi dosyadan okunduktan sonra onun kodunu bul y e ata
        int w = atoi(mesafe); /// Aralarinda ki mesafeyi string ten int e cevir

        komsulukDizisi[x][y] = komsulukDizisi[y][x] = w; /// Iki sehrin kodlari matrisin indexleri olur degeri aralarinda ki mesafedir
        /// matris[1][2] demek 1 kodlu sehirden 2 kodlu sehire gidilecek mesafedir
    }
    fclose(sehirMesafeler); /// Dosyayi kapat
    return 1; /// islem basarili
}

int main()
{

    if(sehirKodlariDosyasiniAc() == -1) /// Dosya acilmazsa sonlandir
    {
        return -1;
    }

    int komsulukMatrisi[toplamSehir+1][toplamSehir+1]; /// Sehir sayisini ogrendikten sonra sehirsayisinin bir fazlası boyutunda matris olustur

    if(mesafelerDosyasiniAc(komsulukMatrisi) == -1) /// Mesafe dosyasi acilmazsa
    {
        return -1;
    }

    int merkezSehirKodu,hedefSehirKodu;

    PBAS:


    printf("Merkez sehir kodunu giriniz:");
    scanf("%d",&merkezSehirKodu);

    if(!(merkezSehirKodu>=1 && merkezSehirKodu <= toplamSehir)){
        printf("Lutfen sehir kodunu dogru giriniz!\n");
    }

    printf("Gitmek istediginiz sehir kodunu giriniz:");
    scanf("%d",&hedefSehirKodu);

    int sonuc = dijsktra(komsulukMatrisi,merkezSehirKodu,hedefSehirKodu);
    printf("-> En kisa mesafe:%d\n",sonuc);

    int kontrol;
    printf("Merkez sehirden tum sehirlere olan en kisa yolu bulmak icin 1 giriniz :");
    scanf("%d",&kontrol);

    if(kontrol == 1){
        dijkstra2(merkezSehirKodu,komsulukMatrisi);
    }

    printf("\nYeni giris yapmak icin 1 giriniz:");

    int giris;
    scanf("%d",&giris);
    printf("\n\n");

    if(giris == 1){
        goto PBAS;
    }



    return 0;
}
