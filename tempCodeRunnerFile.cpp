//Kullandığım kütüphaneler
#include <iostream> 
#include <fstream> // Dosya okuma/yazma işlemleri için
#include <cstring> //  String işlemleri için
#include <cctype> // Karakter kontrol fonksiyonları için

using namespace std;

// Üye girişi bilgilerini tutan yapı
struct uye {
    char isim[20];  //Üyenin ismi
    double kilo;   //Üyenin kilosu
    double boy;   //Üyenin boyu
    int yas; // Üyenin yaşı
    char cinsiyet;  //Üyenin cinsiyeti ( E veya K şeklinde giriş yapılmalı)
};

// Besinlerin kalorisini hesaplamak için bilgilerini tutan yapı
struct BesinKalorisiHesaplama {
    char besinadi[30];
    int kalorimiktari; // 100 gram için kalori değerlerini girdim
};
 //Diyet listesinin öğünleri tutan yapı
struct DiyetListesi {
    string sabah;
    string araOgun;
    string ogle;
    string aksam;
};

uye guncelUyeler; //Güncel kullanıcı bilgilerini tutar. Tekrar tekrar kayıt oluşturmamak için kullandım.
uye uyeler[50]; // En fazla 50 üye girişi alabilir olarak ayarladım.
int uyeSayisi = 0; //Başlangıçta üye sayısnı 0 olarak ayarladım. Kaç kullanıcı olduğunu tutar.

//Besinlerin kalori değerlerini tutan dizi.Her besinin 100 gram için kalori bilgisini tutar.
//Alt alta çok fazla yer kaplar diye yan yana sıraladım diziyi
BesinKalorisiHesaplama kaloriBilgisi[] = {
    {"elma", 52}, {"muz", 89}, {"yogurt", 59}, {"ekmek", 265}, {"tavuk", 165},
    {"brokoli", 34}, {"yumurta", 155}, {"sut", 42}, {"ayran", 40}, {"mercimek", 116},
    {"pilav", 130}, {"kofte", 267}, {"salata", 15}, {"ceviz", 654}, {"bal", 304},
    {"zeytin", 115}, {"domates", 18}, {"salatalik", 16}, {"biber", 20}, {"patates", 77},
    {"makarna", 131}, {"kavun", 34}, {"karpuz", 30}, {"portakal", 47}, {"üzüm", 69},
    {"fındık", 628}, {"badem", 579}, {"fıstık", 567}, {"kuruincir", 249}, {"kurukayısı", 241},
    {"lahana", 25}, {"ıspanak", 23}, {"marul", 15}, {"mantar", 22}, {"bezelye", 81},
    {"fasulye", 127}, {"nohut", 164}, {"bulgur", 342}, {"kurufasulye", 333}, {"balık", 206},
    {"hindi", 135}, {"kırmızıet", 250}, {"pizza", 266}, {"hamburger", 295}, {"patateskizartmasi", 312},
    {"börek", 320}, {"poğaça", 350}, {"çorba", 75}, {"gazoz", 42}, {"kola", 44},
    {"çikolata", 546}, {"bisküvi", 475}, {"waffle", 291}, {"dondurma", 207}, {"çaysekerli", 27},
    {"çayşekersiz", 0}, {"kahvesekerli", 35}, {"kahveşekersiz", 2}, {"enerjiİcecegi", 45},
    {"meyvesuyu", 46}, {"şalgam", 20}, {"kefir", 41}, {"barbunya", 127}, {"yumurtabeyazi", 52},
    {"yumurtasarisi", 322}
};
// Kalori dizisinde kaç eleman olduğunu hesaplar
int kalorimiktari = sizeof(kaloriBilgisi) / sizeof(BesinKalorisiHesaplama); 

//Önceden kayıtlı olan üyeleri kontrol eder.Üyeleri dosyadan okuyarak diziye ekler.
void oncedenKaydolanUyeler() {
    ifstream dosya("uyeler.txt"); //Dosya açma
    if (!dosya) return; //dosya yoksa eğer çık komutu verdim

 // Dosya sonuna kadar her kullanıcı bilgisi alınır ve diziye aktarılır
    while (dosya >> uyeler[uyeSayisi].isim
                >> uyeler[uyeSayisi].kilo
                >> uyeler[uyeSayisi].boy
                >> uyeler[uyeSayisi].yas
                >> uyeler[uyeSayisi].cinsiyet)
    {
        uyeSayisi++;// Her kullanıcıdan sonra sayaç artırılır
    }

    dosya.close(); // Dosya kapatılır
}
//Üyeleri kaydetmemizi sağlayan fonksiyon. Kayıtlı tüm üyeleri "uyeler.txt" dosyasına yazar
void uyeleriKaydetme() {
    ofstream dosya("uyeler.txt"); // Dosya yazma modunda açılır
    for (int i = 0; i < uyeSayisi; i++) {
          // Her kullanıcı bilgisi dosyaya yazılır
        dosya << uyeler[i].isim << endl;
        dosya << uyeler[i].kilo << endl;
        dosya << uyeler[i].boy << endl;
        dosya << uyeler[i].yas << endl;
        dosya << uyeler[i].cinsiyet << endl;
    }
    dosya.close();  // Dosya kapatılır
}
// Yeni üye ekler veya mevcut üyenin bilgilerini günceller
void uyeGuncelleme (const uye &u) {
    bool bulunduMu = false; // Üyenin mevcut olup olmadığını tutar. 
    for (int i = 0; i < uyeSayisi; i++) {
        if (strcmp(uyeler[i].isim, u.isim) == 0) { // İsimler aynıysa
            uyeler[i] = u; // Eski kayıt güncellenir
            bulunduMu = true; // Üye bulundu
            break;
        }
    }
    if (!bulunduMu) // Üye yeni ise
        uyeler[uyeSayisi++] = u; // Yeni kayıt yapılır

    uyeleriKaydetme(); // Güncellenen liste dosyaya yazılır
}

// Besin adı ve miktara göre toplam kalori hesabı yapar
int kaloriHesapla(const char* yemek, double miktar) {
    char kucuk[30]; // Küçük harfli besin adını tutmak için
    strcpy(kucuk, yemek);  // Girilen besin adını kucuk değişkenine kopyala
    for (int i = 0; kucuk[i]; i++) {// Her karakter için kontrol
        if (kucuk[i] >= 'A' && kucuk[i] <= 'Z') {
            kucuk[i] += ('a' - 'A'); // Büyük harfleri küçük harfe çevir
        }
    }

    for (int i = 0; i < kalorimiktari; i++) { // Kalori dizisinde arama yapılır
        if (strcmp(kucuk, kaloriBilgisi[i].besinadi) == 0) { // Besin adı eşleşirse
            int* ptrkalorimiktari = &kaloriBilgisi[i].kalorimiktari; // Kalori miktarına pointer
            return (*ptrkalorimiktari) * miktar / 100; // Hesaplanan kalori döndürülür
        }
    }

    cout << "Besin bulunamadı!\n";  // Eşleşme yoksa kullanıcıya uyarı verir
    return 0; // Kalori 0 olarak döndürülür
}


// Kullanıcının BKI (vücut kitle indeksi) değerine göre uygun diyet listesini döndüren fonksiyon
DiyetListesi getListe(double bki) {
    DiyetListesi liste; // Geri döndürülecek diyet listesi nesnesi oluşturuluyor
// BKI'ye göre uygun liste belirleniyor
    if (bki <= 18.5) { //Zayıf için 
        liste.sabah = "Peynir, zeytin, 2 dilim tam buğday ekmeği, 1 haşlanmış yumurta, süt";
        liste.araOgun = "Kuru incir, ceviz, muz";
        liste.ogle = "Kıymalı makarna, yoğurt, 1 dilim ekmek";
        liste.aksam = "Etli sebze yemeği, pirinç pilavı, salata";
    } else if (bki > 18.5 && bki <= 24.9) {  //Normal kilolu için
        liste.sabah = "Yulaf ezmesi, süt, meyve";
        liste.araOgun = "Elma, badem";
        liste.ogle = "Izgara tavuk, sebze yemeği, ayran";
        liste.aksam = "Mercimek çorbası, bulgur pilavı, salata";
    } else if (bki >= 25.0 && bki <= 29.9) { //Fazla kilolu için
        liste.sabah = "1 haşlanmış yumurta, domates, salatalık, 1 dilim tam buğday ekmeği";
        liste.araOgun = "1 avuç çiğ badem, yeşil çay";
        liste.ogle = "Izgara köfte, haşlanmış sebze, yoğurt";
        liste.aksam = "Zeytinyağlı sebze yemeği, çorba, salata";
    } else if (bki >= 30.0 && bki <= 34.9) { //1. derece Obezite için
        liste.sabah = "Sebzeli omlet, şekersiz çay";
        liste.araOgun = "Salatalık, kefir";
        liste.ogle = "Izgara hindi göğsü, yeşil salata, yoğurt";
        liste.aksam = "Sebze çorbası, haşlanmış bakliyat";
    } else if (bki >= 35.0 && bki <= 39.9) { //2. derece Obezite için
        liste.sabah = "Haşlanmış yumurta, lor peyniri, domates";
        liste.araOgun = "Maydanozlu ayran";
        liste.ogle = "Izgara balık, bol yeşillik, limonlu su";
        liste.aksam = "Kabak yemeği, yoğurt";
    } else { //3. derece Obezite için
        liste.sabah = "Proteinli sebze smoothie";
        liste.araOgun = "Su, şekersiz bitki çayı";
        liste.ogle = "Haşlanmış sebze, yoğurt";
        liste.aksam = "Sebze çorbası, yağsız salata";
    }

    return liste; // Hazırlanan liste geri döndürülür
}

// Kullanıcının aldığı kaloriyi hesaplayan fonksiyon
void kaloriHesaplama() {
    double miktar; // Miktar: gram cinsinden girilen besin miktarı
    double toplam = 0; // Başlangıçta toplam kaloriyi 0 aldık
    char yemek[30]; // Girilen besin adı
    char devam; // Kullanıcı devam etmek istiyor mu? ('E' veya 'H')

    do {
        cout << "\nBesin adı girin: ";
        cin >> yemek;
        cout << "\nNe kadar yediniz gram cinsinden yazınız: ";
        cin >> miktar;

        if (miktar <= 0) { // Geçersiz miktar kontrolü
            cout << "Hatalı giriş!\n";
            continue;
        }
 
        toplam += kaloriHesapla(yemek, miktar); // Kaloriyi hesapla ve topla
        cout << "Başka bir şey yediniz mi? (E / H): ";
        cin >> devam; // Döngü devam edecek mi?
    } while (devam == 'E' || devam == 'e'); // Kullanıcı devam etmek isterse döngü devam eder
// guncelUyeler'i pointer olarak tanımlıyoruz
    uye* ptrUye = &guncelUyeler;
    double hedef; // Hedef kalori için pointer üzerinden erişim

    if (ptrUye->cinsiyet == 'E' || ptrUye->cinsiyet == 'e') {
        hedef = 10 * ptrUye->kilo + 6.25 * (ptrUye->boy * 100) - 5 * ptrUye->yas + 5; //Erkekler için
    } else {
        hedef = 10 * ptrUye->kilo + 6.25 * (ptrUye->boy * 100) - 5 * ptrUye->yas - 161; //Kadınlar için
    }
// Toplam alınan ve önerilen kalori bilgileri yazdırılır
    cout << "\nToplam aldığınız kalori: " << toplam << " kcal\n";
    cout << "Günlük önerilen kalori ihtiyacı: " << hedef << " kcal\n";
}

// Programın başlangıç noktası
int main() {
    oncedenKaydolanUyeler(); // Daha önce kayıtlı kullanıcıları dosyadan oku
    cout << "Merhaba,Vücuduna güzel bak programına hoşgeldiniz!" << endl;
    cout << "Sizi hatırlamam için ya da kaydınızı başlatmam için İsminizi giriniz:" << endl;
    
    string ad; // Kullanıcının adı
    int secim;// Menü seçimi
    getline(cin, ad); // Kullanıcıdan ad alınır

    bool bulunduMu = false; // Kullanıcı daha önce kayıtlı mı kontrolü
// Kullanıcının kayıtlı olup olmadığını kontrol et
    for (int i = 0; i < uyeSayisi; i++) {
        if (strcmp(uyeler[i].isim, ad.c_str()) == 0) {
            guncelUyeler = uyeler[i]; //Kayıtlıysa güncel kullanıcıya aktarılır
            bulunduMu = true;
            break;
        }
    }
  // Kayıtlı değilse yeni bilgiler alınır
    if (!bulunduMu) {
        strcpy(guncelUyeler.isim, ad.c_str());
        cout << "Lütfen kilonuzu girin: ";
        cin >> guncelUyeler.kilo;
        cout << "Lütfen boyunuzu girin metre cinsinden : ";
        cin >> guncelUyeler.boy;
        cout << "Lütfen yaşınızı girin: ";
        cin >> guncelUyeler.yas;
        cout << "Lütfen cinsiyetinizi girin (E/K): ";
        cin >> guncelUyeler.cinsiyet;

        cin.ignore(); // Girişte kalan '\n' karakterini temizler, sonraki girişin bozulmasını önler

        uyeGuncelleme(guncelUyeler); // Yeni kullanıcı kaydedilir
    }
// Ana menü döngüsü
ANA_MENU:
    cout << "\n ----MENÜ----\n";
    cout << "1. BKI (Boy Kitle İndeksi) Hesapla\n";
    cout << "2. Diyet Listesi\n";
    cout << "3. Kalori Hesapla\n";
    cout << "4. Çıkış\n\n";
    cout << "Seçiminiz: ";
    cin >> secim;

    switch (secim) {
        case 1: { // Eğer kullanıcı 1'i seçtiyse, Beden Kitle İndeksi (BKI) hesaplanır
    double bki = guncelUyeler.kilo / (guncelUyeler.boy * guncelUyeler.boy);  // BKI hesaplanır: kilo / (boy * boy)
    cout << "BKI: " << bki << endl; // Hesaplanan BKI değeri ekrana yazdırılır

    if (bki <= 18.5) // BKI 18.5 ve altındaysa zayıf olarak değerlendirilir
        cout << "Durum: Zayıf\n";
    else if (bki > 18.5 && bki <= 24.9) // BKI 18.5 - 24.9 arasıysa normal
        cout << "Durum: Normal kilolu\n";
    else if (bki >= 25.0 && bki <= 29.9) // BKI 25.0 - 29.9 arasıysa fazla kilolu
        cout << "Durum: Fazla kilolu\n";
    else if (bki >= 30.0 && bki <= 34.9) // BKI 30.0 - 34.9 arasıysa 1. derece obez
        cout << "Durum: 1. Derece Obezite\n";
    else if (bki >= 35.0 && bki <= 39.9) // 35.0 - 39.9 arası aşırı obez
        cout << "Durum: 2. Derece Obezite (Aşırı obez)\n";
    else // 40 ve üzeriyse morbid obez
        cout << "Durum: 3. Derece Obezite (Morbid obezite)\n";

    break;
}

        case 2: {
            double bki = guncelUyeler.kilo / (guncelUyeler.boy * guncelUyeler.boy);
            DiyetListesi liste = getListe(bki); // BKI'ye göre liste al
            cout << "\n--- Diyet Listeniz ---\n";
            cout << "Sabah: " << liste.sabah << endl;
            cout << "Ara Öğün: " << liste.araOgun << endl;
            cout << "Öğle: " << liste.ogle << endl;
            cout << "Akşam: " << liste.aksam << endl;
            break;
        }
        case 3:
            kaloriHesaplama();  // Kalori hesaplama arayüzüne gir
            break;
        case 4:
            uyeGuncelleme(guncelUyeler); // Çıkmadan önce kullanıcı bilgileri güncellenir
            cout << "Çıkış yapılıyor...\n"; // Program sonlandırılır
            return 0;
        default:
            cout << "Hatalı seçim!\n"; // Geçersiz menü seçimi
    } 

    goto ANA_MENU;  // Menüye geri dön
}
