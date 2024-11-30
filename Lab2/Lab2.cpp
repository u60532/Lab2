/****************************************Biblioteki***************************************/
#include <iostream>     
#include <vector>         
#include <memory>       
#include <string>  
/******************************Wzorzec Fabryki Abstrakcyjnej******************************/
class LogBazowy {                                                                          // Deklaracja bazy logow.
public:                                                                                  
    virtual std::string pobierzSformatowanaWiadomosc() const = 0;                          // Metoda wirtualna do pobierania sformatowanej wiadomości logu.
    virtual ~LogBazowy() {}                                                                // Wirtualny destruktor klasy bazowej.
};                                                                                         
/*******************************Klasa info, logi typu info********************************/
class Info : public LogBazowy {                                                            // dziedziczy po LogBazowy.
public:                                                    
    Info(const std::string& tekst) : tresc(tekst) {}                                       // Konstruktor przyjmujący tekst do zapisania w logu.
    std::string pobierzSformatowanaWiadomosc() const override {                            // Nadpisana metoda do zwrócenia sformatowanego logu.
        return "[INFO]: " + tresc;                                                         // Zwraca tekst logu w formacie: [INFO]: tekst
    }
private:
    std::string tresc;                                                                     // Przechowuje treść logu.
};
/************************Klasa Ostrzezenie, logi typu ostrzezenie*************************/
class Ostrzezenie : public LogBazowy {                                                     // dziedziczy po LogBazowy
public:
    Ostrzezenie(const std::string& tekst) : tresc(tekst) {}                                // Konstruktor przyjmujący tekst do zapisania w logu.
    std::string pobierzSformatowanaWiadomosc() const override {                            // Nadpisana metoda do zwrócenia sformatowanego logu.
        return "[OSTRZEZENIE]: " + tresc;                                                  // Zwraca tekst logu w formacie: [OSTRZEZENIE]: tekst
    }
private:
    std::string tresc;  // Przechowuje treść logu.
};
/*******************************Klasa Blad, logi typu Blad********************************/
class Blad : public LogBazowy {                                                           // Klasa Blad dziedziczy po LogBazowy.
public:
    Blad(const std::string& tekst) : tresc(tekst) {}                                      // Konstruktor przyjmujący tekst do zapisania w logu.
    std::string pobierzSformatowanaWiadomosc() const override {                           // Nadpisana metoda do zwrócenia sformatowanego logu.
        return "[BLAD]: " + tresc;                                                        // Zwraca tekst logu w formacie: [BLAD]: tekst
    }
private:
    std::string tresc;                                                                    // Przechowuje treść logu.
};
/*Klasa fabryka logow, logi typu Blad. tworzy odpowiednie obiekty logów na podstawie typu*/
class FabrykaLogow {   
public:
    // Metoda fabryczna do tworzenia odpowiednich obiektów logów
    static std::shared_ptr<LogBazowy> stworzLog(const std::string& typLogu, const std::string& trescWiadomosci) {
        if (typLogu == "info") {                                                          // Sprawdza, czy typ logu to "info"
            return std::make_shared<Info>(trescWiadomosci);                               // Tworzy i zwraca log typu "info"
        }
        else if (typLogu == "ostrzezenie") {                                              // Sprawdza, czy typ logu to "ostrzezenie"
            return std::make_shared<Ostrzezenie>(trescWiadomosci);                        // Tworzy i zwraca log typu "ostrzezenie"
        }
        else if (typLogu == "blad") {                                                     // Sprawdza, czy typ logu to "blad"
            return std::make_shared<Blad>(trescWiadomosci);                               // Tworzy i zwraca log typu "blad"
        }
        return nullptr;                                                                   // Jeśli typ logu jest nieznany, zwraca wskaźnik null.
    }
};
/***********************************Wzorzec Singleton************************************/
// Klasa menedżera logów, która będzie przechowywać i zarządzać logami.
class MenedzerLogow {  
public:
    static MenedzerLogow& instancja() {                                                   // Statyczna metoda, która zwraca jedyną instancję klasy (wzorzec Singleton).
        static MenedzerLogow instancja;                                                   // Tworzy statyczną instancję klasy, która zostanie utworzona tylko raz.
        return instancja;                                                                 // Zwraca referencję do tej instancji.
    }
    // Metoda dodająca nowy log.
    void dodajLog(const std::string& typ, const std::string& wiadomosc) {  
        auto log = FabrykaLogow::stworzLog(typ, wiadomosc);                               // Tworzy nowy log przy pomocy fabryki logów.
        if (log) {                                                                        // Jeśli log został poprawnie utworzony
            wpisyLogow.push_back(log);                                                    // Dodaje log do wektora przechowującego logi.
            std::cout << "Log zapisany: " << log->pobierzSformatowanaWiadomosc() << std::endl;  // Wyświetla zapisany log.
        }
        else {
            std::cout << "Nieznany typ logu!" << std::endl;                               // Jeśli log jest niezidentyfikowany, wyświetla błąd.
        }
    }
    // Metoda do wyświetlania wszystkich zapisanych logów.
    void wyswietlLogi() const {      
        if (wpisyLogow.empty()) {                                                         // Sprawdza, czy lista logów jest pusta
            std::cout << "Brak zapisanych logow." << std::endl;                           // Jeśli lista jest pusta, wyświetla komunikat.
            return;                                                                       // Kończy funkcję.
        }
        std::cout << "Wszystkie zapisane logi:\n";                                        // Wypisuje nagłówek listy logów.
        for (const auto& log : wpisyLogow) {                                              // Dla każdego logu w wektorze logów
            std::cout << log->pobierzSformatowanaWiadomosc() << std::endl;                // Wyświetla sformatowaną wiadomość logu.
        }
    }

private:
    MenedzerLogow() {}    // Prywatny konstruktor zapewnia, że instancja jest tworzona tylko raz (Singleton).
    ~MenedzerLogow() {}   // Prywatny destruktor

    MenedzerLogow(const MenedzerLogow&) = delete;             // Usuwa możliwość kopiowania instancji Singletona.
    MenedzerLogow& operator=(const MenedzerLogow&) = delete;  // Usuwa możliwość przypisania instancji Singletona.

    std::vector<std::shared_ptr<LogBazowy>> wpisyLogow;   // Wektor przechowujący wskaźniki do logów.
};

// **Test Singletona**

// Funkcja do testowania, czy rzeczywiście mamy tylko jedną instancję Menedzera Logów.
void sprawdzSingleton() {   
    MenedzerLogow& menedzer1 = MenedzerLogow::instancja();  // Pobiera pierwszą instancję Menedzera Logów.
    MenedzerLogow& menedzer2 = MenedzerLogow::instancja();  // Pobiera drugą instancję Menedzera Logów.

    if (&menedzer1 == &menedzer2) {  // Sprawdza, czy obie referencje wskazują na tę samą instancję.
        std::cout << "Test Singletona zakonczony sukcesem: Menedzer logow to ta sama instancja.\n";  // Jeśli tak, wyświetla komunikat o sukcesie.
    }
    else {
        std::cout << "Test Singletona nie powiodl sie: Menedzer logow to rozne instancje.\n";        // Jeśli nie, wyświetla błąd.
    }
}

int main() {
    // Test Singletona
    sprawdzSingleton();  // Testuje, czy Menedzer Logów działa jako Singleton.

    std::string wyborUzytkownika;  // Zmienna do przechowywania wyboru użytkownika.
    MenedzerLogow& menedzer = MenedzerLogow::instancja();  // Pobiera instancję Menedzera Logów.
    // Pętla główna programu
    while (true) {  
        std::cout << "\nWybierz opcje:\n";             // Wyświetla menu dla użytkownika.
        std::cout << "1. Dodaj nowy log\n";            // Opcja dodania nowego logu.
        std::cout << "2. Wyswietl wszystkie logi\n";   // Opcja wyświetlenia zapisanych logów.
        std::cout << "3. Zakoncz program\n";           // Opcja zakończenia programu.
        std::cout << "Twoj wybor: ";                   // Prosi o wybór.
        std::getline(std::cin, wyborUzytkownika);      // Pobiera odpowiedź użytkownika.

        if (wyborUzytkownika == "1") {                 // Jeśli użytkownik wybrał opcję 1 (dodanie logu)
            std::string typLogu, trescLogu;            // Zmienne do przechowywania typu logu i treści.
            std::cout << "Podaj typ logu (info, ostrzezenie, blad): ";  // Prosi o podanie typu logu.
            std::getline(std::cin, typLogu);           // Pobiera typ logu.
            std::cout << "Podaj tresc logu: ";         // Prosi o podanie treści logu.
            std::getline(std::cin, trescLogu);         // Pobiera treść logu.
            menedzer.dodajLog(typLogu, trescLogu);     // Dodaje log przy użyciu menedżera logów.
        }
        else if (wyborUzytkownika == "2") {            // Jeśli użytkownik wybrał opcję 2 (wyświetlenie logów)
            menedzer.wyswietlLogi();                   // Wyświetla zapisane logi.
        }
        else if (wyborUzytkownika == "3") {            // Jeśli użytkownik wybrał opcję 3 (zakończenie programu)
            std::cout << "Zakonczenie programu.\n";    // Wyświetla komunikat o zakończeniu programu.
            break;                                     // Kończy pętlę.
        }
        else {                                         // Jeśli użytkownik podał nieprawidłową opcję
            std::cout << "Nieprawidlowy wybor! Sprobuj ponownie.\n";  // Wyświetla błąd.
        }
    }

    return 0;   // Zwraca 0, kończąc program.
}
