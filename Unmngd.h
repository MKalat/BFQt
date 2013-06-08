#ifndef UNMNGD_H
#define UNMNGD_H

#endif // UNMNGD_H
struct POMIDOR
{
    wchar_t BF_VER[16]; // wersja bazy danych
    int  najw_ID; // wazne przy dodawaniu nowego rekordu - tutaj jest zapisywana zawartosc pola Film.ID
};

struct Obsada
{
    int ID;
    int IDPDB;
    wchar_t imie_nazw[501];
    wchar_t rola[201];
};
struct Ocena
    {
        int ID;
        int IDPDB;
        wchar_t nazwa[201];
        wchar_t tytul_tekstu[201];
        wchar_t autor_tekstu[201];
        wchar_t strona_www[501];
        wchar_t ocena_krytyka[201];
    };


struct Producent
    {
        int ID;
        int IDPDB;
        wchar_t nazwa_firmy[501];
        wchar_t adres[501];
        wchar_t telefon[31];
        wchar_t fax[31];
        wchar_t email[201];
        wchar_t strona_www[501];
        wchar_t narodowosc[201];
    };
struct Dystrybutor
    {
        int ID;
        int IDPDB;
        wchar_t nazwa_firmy[501];
        wchar_t adres[501];
        wchar_t telefon[31];
        wchar_t fax[31];
        wchar_t email[201];
        wchar_t strona_www[501];
        wchar_t narodowosc[201];
    };
struct Lok_zdjeciowe
    {
        int ID;
        int IDPDB;
        wchar_t nazwa_obiektu[501];
        wchar_t kraj[501];
        wchar_t miejscowosc[501];
        wchar_t region[501];
        wchar_t pora_roku[501];
        wchar_t data[21];
    };
struct Wypozycz_Innym
    {
        int ID;
        int IDPDB;
        wchar_t data_wypozyczenia[21];
        wchar_t data_oddania[21];
        wchar_t stan_przed_wypozycz[501];
        wchar_t stan_po_oddaniu[501];
        wchar_t osoba[501];
        wchar_t Nr_kat[501];
    };
struct Wypozycz_Od_Innych
    {
        int ID;
        int IDPDB;
        wchar_t data_wypozyczenia[21];
        wchar_t data_oddania[21];
        wchar_t stan_przed_wypozycz[501];
        wchar_t stan_po_oddaniu[501];
        wchar_t osoba[501];
        wchar_t Nr_kat[501];
    };

struct Film
{
    int ID;
    wchar_t tytul[501];
    wchar_t oryginalny_tytul[501];
    wchar_t gatunek_filmu[201];
    wchar_t skan_przod_path[241];
    wchar_t skan_tyl_path[241];
    wchar_t WOF_sciezka_dz[201];
    wchar_t WOF_obsada[201];
    wchar_t WOF_zdjecia[201];
    wchar_t WOF_w_art[201];
    wchar_t WOF_calosc[201];
    wchar_t O_rezyser_imie_nazw[501];
    wchar_t O_rezyser_narod[501];
    wchar_t O_scenariusz_imie_nazw[501];
    wchar_t O_scenariusz_narod[501];
    wchar_t O_operator_imie_nazw[501];
    wchar_t O_operator_narod[501];
    wchar_t O_muzyka_imie_nazw[501];
    wchar_t O_muzyka_narod[501];
    wchar_t DOE_cena[101];
    wchar_t DOE_wartosc_akt[101];
    wchar_t DOE_data_zakupu[21];
    wchar_t DOE_data_utraty[21];
    wchar_t DOE_data_skatalogowania[21];
    wchar_t DOE_rodzaj_nosnika[201];
    wchar_t DOE_Nr_kat[501];
    wchar_t DOE_WKF_imie[501];
    wchar_t DOE_WKF_nazwisko[501];
    wchar_t DOE_WKF_adres[501];
    wchar_t DOE_MN_nazwa[501];
    wchar_t DOE_MN_adres[501];
    wchar_t DOE_MN_telefon[31];
    wchar_t DOE_MN_email[201];
    wchar_t DOE_MN_www[501];
    wchar_t DOE_MN_fax[31];
    wchar_t IOF_rok_produkcji[21];
    wchar_t IOF_data_premiery[21];
    wchar_t IOF_czas_trwania[51];
    wchar_t IOF_jezyk_lektora[1001];
    wchar_t IOF_jezyk_napisow[1001];
    wchar_t IOF_format_wysw[51];
    wchar_t IOF_system_kodowania_obrazu[51];
    wchar_t IOF_kraj_produkcji_filmu[1001];
    wchar_t IOF_KODEK_nazwa[201];
    wchar_t IOF_KODEK_typ[201];
    wchar_t IOF_KODEK_wersja[201];
    wchar_t IOF_ZABEZP_nazwa[201];
    wchar_t IOF_ZABEZP_typ[201];
    wchar_t IOF_ZABEZP_wersja[201];
    wchar_t IOF_DZWIEK_nazwa[201];
    wchar_t IOF_DZWIEK_typ[201];
    wchar_t IOF_DZWIEK_wersja[201];

};

struct Film2
{
    int ID;
    wchar_t opis[4096]; // zmiana wzgedem 1.0.2.0




};
