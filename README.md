README - Projekt

    Wzorce Projektowe:
    1. **Fabryka Abstrakcyjna** (Abstract Factory):
        - Celem tego wzorca jest umożliwienie tworzenia różnych typów obiektów logów (np. INFO, OSTRZEŻENIE, BŁĄD) w sposób elastyczny.
        - Klasa `FabrykaLogow` odpowiada za tworzenie odpowiednich obiektów logów w zależności od podanego typu (info, ostrzeżenie, błąd).
        - Każdy log ma swoją klasę, dziedziczącą po wspólnej klasie bazowej `LogBazowy`, co umożliwia łatwe rozszerzanie o nowe typy logów w przyszłości.

    2. **Singleton**:
        - Wzorzec Singleton zapewnia, że w aplikacji istnieje tylko jedna instancja klasy `MenedzerLogow`.
        - Menedżer logów (klasa `MenedzerLogow`) odpowiada za zarządzanie logami, ich dodawanie oraz wyświetlanie.
        - Singleton zapobiega tworzeniu wielu obiektów tej klasy, zapewniając centralne miejsce do przechowywania logów w aplikacji.

    Funkcjonalność:
    - Program umożliwia użytkownikowi:
      1. Dodawanie nowych logów o różnych typach (INFO, OSTRZEŻENIE, BŁĄD).
      2. Wyświetlanie wszystkich zapisanych logów.
      3. Sprawdzenie, czy instancja menedżera logów jest unikalna (czy działa wzorzec Singleton).

    Struktura Programu:
    1. **LogBazowy**: Klasa bazowa dla wszystkich typów logów, zawiera metodę wirtualną `pobierzSformatowanaWiadomosc()`.
    2. **Info, Ostrzezenie, Blad**: Klasy reprezentujące różne typy logów, każda implementuje metodę `pobierzSformatowanaWiadomosc()`.
    3. **FabrykaLogow**: Fabryka logów odpowiedzialna za tworzenie instancji logów na podstawie podanego typu.
    4. **MenedzerLogow**: Klasa Singletona, która zapewnia jedną instancję do przechowywania logów i zarządzania nimi.

    Wykorzystanie:
    1. **Dodawanie logów**:
        - Użytkownik może wprowadzić typ logu (np. info, ostrzeżenie, błąd) oraz jego treść.
        - Program zapisuje logi do wektora, a także wyświetla sformatowaną wiadomość.

    2. **Wyświetlanie logów**:
        - Program umożliwia użytkownikowi wyświetlenie wszystkich zapisanych logów.

    3. **Test Singletona**:
        - Program testuje, czy menedżer logów rzeczywiście używa jedną instancję (wzorzec Singleton).

    Przykład działania programu:
    ------------------------------------
    Wybierz opcje:
    1. Dodaj nowy log
    2. Wyswietl wszystkie logi
    3. Zakoncz program
    Twoj wybor: 1
    Podaj typ logu (info, ostrzezenie, blad): info
    Podaj tresc logu: Aplikacja uruchomiona pomyślnie
    Log zapisany: [INFO]: Aplikacja uruchomiona pomyślnie

    Wybierz opcje:
    1. Dodaj nowy log
    2. Wyswietl wszystkie logi
    3. Zakoncz program
    Twoj wybor: 2
    Wszystkie zapisane logi:
    [INFO]: Aplikacja uruchomiona pomyślnie

    Wybierz opcje:
    1. Dodaj nowy log
    2. Wyswietl wszystkie logi
    3. Zakoncz program
    Twoj wybor: 3
    Zakonczenie programu.

    Technologie:
    - C++ (z wykorzystaniem wskaźników inteligentnych `shared_ptr` do zarządzania pamięcią)
    - Wzorce projektowe: Fabryka Abstrakcyjna, Singleton

    Kompilacja:
    - Program można skompilować przy użyciu dowolnego kompilatora C++ (np. GCC, Clang).
    - Przykładowa komenda kompilacji (w systemie Unix):
        g++ -std=c++11 -o system_logow main.cpp
    - Uruchomienie programu:
        ./system_logow

    Autor: Fabian Kolodziejek
