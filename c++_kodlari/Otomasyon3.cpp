#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <locale.h>
using namespace std;
struct Malzeme {
    char uzunluk[20];
    char genislik[20];
    char renk[20];
    char etiket_no[20];
    char tur[20];
};
void MalzemeEkleme();
void MalzemeListeleme();
void MalzemeArama();
void MalzemeSil();
void MalzemeDuzenle();
int main() {
    setlocale(LC_ALL, "Turkish");
    char anamenu;
    do {
        system("cls");
        cout << "|------------------------|" << endl;
        cout << "|-------Ho�geldiniz------|" << endl;
        cout << "|------Se�im Yap�n�z-----|" << endl;
        cout << "|----1-Malzeme Ekleme----|" << endl;
        cout << "|---2-Malzeme Listeleme--|" << endl;
        cout << "|-----3-Malzeme Arama----|" << endl;
        cout << "|-----4-Malzeme Sil------|" << endl;
        cout << "|----5-Malzeme D�zenle---|" << endl;
        cout << "|------------------------|" << endl;
        char secim;
        cin >> secim;
        switch (secim) {
            case '1':
			{
				MalzemeEkleme();
				break;
			} 
            case '2':
			{
				MalzemeListeleme();
			    break;
			} 
            case '3':
			{
			    MalzemeArama();
				break;
			}  
            case '4':
			{
				MalzemeSil();
				break;
			}  
            case '5':
			{
				MalzemeDuzenle();
				break;
			}  
            default: 
            cout << "Hatal� se�im yapt�n�z" << endl;
        }

        cout << "Anamen�ye d�nmek i�in=a , ��kmak i�in=�: ";
        anamenu=getche();
    } while (anamenu=='a' || anamenu=='A');
    return 0;
}
Malzeme mal;
void MalzemeEkleme() {
    ofstream yaz("malzeme.dat", ios::binary|ios::app);
    if (!yaz) {
        cout << "Dosya a��lamad�!" << endl;
        return;
    }
    char secim;
    cout << endl;
    cout << "Malzeme T�r� Se�(Tencere=1, Tava=2, Tabak=3): ";
    secim=getche();
    switch (secim) {
        case '1': 
		{
			strcpy(mal.tur, "Tencere");
			break;
		} 
        case '2':
		{
			strcpy(mal.tur, "Tava");
			break;
		}  
        case '3': 
		{
			strcpy(mal.tur, "Tabak");
			break;
		} 
        default:
    cout << endl;
    cout << "Hatal� se�im" << endl;
    return;
    }
    cout << endl;
    cout << "Uzunluk Giriniz: ";
    cin >> mal.uzunluk;
    cout << "Geni�lik Giriniz: ";
    cin >> mal.genislik;
    cout << "Renk Giriniz: ";
    cin >> mal.renk;
    cout << "Etiket No Giriniz: ";
    cin >> mal.etiket_no;
    yaz.write((char*)&mal,sizeof(Malzeme));
    yaz.close();
    cout << "Malzeme  eklendi." << endl;
}
void MalzemeListeleme() {
    ifstream oku("malzeme.dat", ios::binary);
    if (!oku) {
     cout << "Dosya a��lamad� veya kay�t bulunamad�" << endl;
     return;
    }
    int sayac = 0;
    while (oku.read((char*)&mal, sizeof(Malzeme))) {
     cout << "\n--- " << ++sayac << ". Malzeme ---" << endl;
     cout << "T�r: " << mal.tur                     << endl;
     cout << "Uzunluk: " << mal.uzunluk             << endl;
     cout << "Geni�lik: " << mal.genislik           << endl;
     cout << "Renk: " << mal.renk                   << endl;
     cout << "Etiket No: " << mal.etiket_no         << endl;
    }
    if (sayac == 0)
        cout << "Hi� malzeme kayd� yok." << endl;
    oku.close();
}
void MalzemeArama() {
    ifstream oku("malzeme.dat", ios::binary);
    if (!oku) {
        cout << "Dosya a��lamad� veya kay�t bulunamad�." << endl;
        return;
    }
    char aranan_etiket[20];
    cout << "\nAranacak malzemenin etiket numaras�n� giriniz: ";
    cin >> aranan_etiket;
    bool bulundu=false;
    while (oku.read((char*)&mal, sizeof(Malzeme))) {
        if (strcmp(mal.etiket_no, aranan_etiket) == 0) {
            bulundu = true;
            cout << "\n--- Malzeme Bulundu ---" << endl;
            cout << "T�r: " << mal.tur << endl;
            cout << "Uzunluk: " << mal.uzunluk << endl;
            cout << "Geni�lik: " << mal.genislik << endl;
            cout << "Renk: " << mal.renk << endl;
            cout << "Etiket No: " << mal.etiket_no << endl;
            break;
        }
    }
    if (!bulundu)
        cout << "Malzeme bulunamad�" << endl;
    oku.close();
}
void MalzemeSil() {
    ifstream oku("malzeme.dat", ios::binary);
    ofstream yaz("yedek.dat", ios::binary);

    if (!oku || !yaz) {
        cout << "Dosya i�lemi s�ras�nda hata olu�tu." << endl;
        return;
    }
    char silinecek_etiket[20];
    cout << "\nSilinecek malzemenin etiket numaras�n� giriniz: ";
    cin >> silinecek_etiket;
    bool silindi=false;
    while (oku.read((char*)&mal, sizeof(Malzeme))) {
        if (strcmp(mal.etiket_no, silinecek_etiket) != 0) {
            yaz.write((char*)&mal, sizeof(Malzeme));
        } else {
            silindi = true;
        }
    }
    oku.close();
    yaz.close();
    remove("malzeme.dat");
    rename("yedek.dat", "malzeme.dat");
    if (silindi)
        cout << "Malzeme ba�ar�yla silindi." << endl;
    else
        cout << "Malzeme bulunamad�." << endl;
}
void MalzemeDuzenle() {
    ifstream oku("malzeme.dat", ios::binary);
    ofstream yaz("yedek.dat", ios::binary);

    if (!oku || !yaz) {
        cout << "Dosya i�lemi s�ras�nda hata olu�tu." << endl;
        return;
    }
    char duzenlenecek_etiket[20];
    cout << "\nD�zenlenecek malzemenin etiket numaras�n� giriniz: ";
    cin >> duzenlenecek_etiket;
    bool duzenlendi = false;
    while (oku.read((char*)&mal, sizeof(Malzeme))) {
        if (strcmp(mal.etiket_no, duzenlenecek_etiket) == 0) {
            duzenlendi = true;
            cout << "Yeni bilgileri giriniz: " << endl;
            cout << "Uzunluk: ";
            cin >> mal.uzunluk;
            cout << "Geni�lik: ";
            cin >> mal.genislik;
            cout << "Renk: ";
            cin >> mal.renk;
            cout << "Etiket No: ";
            cin >> mal.etiket_no;
        }
        yaz.write((char*)&mal, sizeof(Malzeme));
    }
    oku.close();
    yaz.close();
    remove("malzeme.dat");
    rename("yedek.dat", "malzeme.dat");
    if (duzenlendi)
        cout << "Malzeme ba�ar�yla d�zenlendi." << endl;
    else
        cout << "Malzeme bulunamad�." << endl;
}

