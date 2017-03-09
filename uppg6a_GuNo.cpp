//Använd nedanstående mall för din redovisningsfil:
//
//(Allt mellan /* och */ är kommentarer i C++-koden)
//
/*
================================================================================
Datorer och programmering, DoP, 10 hsp, termin/år:_VT2016_

Inlämningsuppgift nr _6a_

Namn: _Gunnar_Norström_

Personummer: _800329-7119_

Fyll i (alt. stryk det som INTE är relevant) av nedanstående:

Den fil som jag lämnar in går att kompilera och
programmet fungerar för alla de testdata som finns för uppgiften: Ja/Nej
     Om Nej, beskriv vilka testdata som ger problem:  _Ja_

Jag har använt kompilator/editor (namn/version) _Code::Blocks 10.05_

Jag har använt följande dator (t.ex. PC, Mac, Annat):        _PC_
      med operativsystemet (t.ex. WindowsXP, Windows7,...) : __Windows10_

Jag har arbetat ungefär __ca_20__ timmar med denna uppgift
================================================================================
*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

//Globala konstanter
const int MAX_KOMPISAR = 10;
const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

//Externa funktioner
int callMeny();

//Klasser
//Lagrar uppgifter om en person
class Person
{
private:
    string namn;
    double betalat_andras;
    double skyldig;

public:
    Person();
    Person(string n, double b, double s);
    double haemta_betalat();
    double haemta_skyldig();
    string haemta_namn();
    void skrivUt();
};

//Lista över personer som deltar
class PersonLista
{
private:
    int antal_pers;
    Person pers[MAX_PERSONER];

public:
    PersonLista();
    ~PersonLista();
    void laggTillEn(Person pny);
    void skrivUtOchFixa();
    double summaSkyldig();
    double summaBetalat();
    bool finnsPerson(const string &namn);
};

//Information om en specifik transaktion
class Transaktion
{
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int ant_kompisar;
    string kompisar[MAX_KOMPISAR];

public:
    Transaktion();
    ~Transaktion();
    string haemta_namn();
    double haemta_belopp();
    int haemta_ant_kompisar();
    bool finnsKompis(string namnet);
    bool laesEnTrans(istream &is);
    void skrivEnTrans(ostream &os);
    double haemta_skuld(string namnet);
};

//Lista över samtliga transaktioner
class TransaktionsLista
{
private:
    Transaktion trans[MAX_TRANSAKTIONER];
    int antalTrans;

public:
    TransaktionsLista();
    ~TransaktionsLista();
    void laesin(istream &is);
    void skrivut(ostream &os);
    void laggTill(Transaktion &t);
    double totalkostnad();
    double liggerUteMed(string namnet);
    double aerSkyldig(string namnet);
    PersonLista FixaPersoner();     //Då klassen PeronLista åberopas måste den existera när den åberopas
};


int main()
{
    //Variabler
    int menyval = -1;   //Startar på -1 som icke-val
    int antalTransSession = 0;  //Hjälp konstant för att hantera antalet transaktioner
    string namnet;

    Transaktion transEnkel;
    TransaktionsLista tLista;
    PersonLista perslista;
    Transaktion nya_trans[MAX_TRANSAKTIONER];

    //Hantering av filen resa.txt
    ifstream infil("resa.txt");
    ofstream utfil("resa.txt", ios_base::app);  //app = se till att börja i slutet av strömmen
    tLista.laesin(infil);
    infil.close();

    //Hantera menyval
    while(menyval != 0)
    {
        cout << "V\x84lj i menyn nedan:" << endl << endl;
        cout << "0. Avsluta. Alla transaktioner sparas p\x86 fil." << endl;
        cout << "1. L\x84s in en transaktion fr\x86n tangentbordet." << endl;
        cout << "2. Skriv ut information om alla transaktioner." << endl;
        cout << "3. Ber\x84kna totala kostnaden." << endl;
        cout << "4. Hur mycket \x84r en viss person skyldig?" << endl;
        cout << "5. Hur mycket ligger en viss person ute med?" << endl;
        cout << "6. Lista alla personer mm och FIXA!" << endl << endl;

        menyval = callMeny();

        //Switch, fungerade inte så bra med if (GLÖM INTE BREAK)
        switch(menyval)
        {
            case 0: cout << "\nProgrammet avslutas. Nya transaktioner skrivs till fil." << endl;
                    for(int i = 0; i < antalTransSession; i++)
                    {
                        nya_trans[i].skrivEnTrans(utfil);
                    }
                    utfil.close();
                break;
            case 1: transEnkel.laesEnTrans(cin);
                    tLista.laggTill(transEnkel);
                    nya_trans[antalTransSession] = transEnkel;
                    antalTransSession++;
                break;
            case 2: cout << "\nSkriver info om samtliga transaktioner:" << endl;
                    tLista.skrivut(cout);
                    cout << endl;
                break;
            case 3: cout << "\nAktivitetens totalkostnad: " << tLista.totalkostnad() << " kr." << endl << endl;
                break;
            case 4: cout << "Ange namn: "; cin >> namnet;
                    cout << namnet << " \x84r skyldig: " << tLista.aerSkyldig(namnet) << " kr." << endl << endl;
                break;
            case 5: cout << "Ange namn: "; cin >> namnet;
                    cout << namnet << " ligger ute med: " << tLista.liggerUteMed(namnet) << " kr." << endl << endl;
                break;
            case 6: perslista = tLista.FixaPersoner();
                    cout << endl;
                    perslista.skrivUtOchFixa();
                    cout << endl;
                break;
        }
    }
    return 0;
}

//Extern funktion för att hantera meny.
int callMeny()
{
    int val;
    cout << "Menyval: ";
    cin >> val;
    return val;
}

//Implementering av Klasser
//Klassen Person
Person::Person()
{
    namn = "";
    betalat_andras = 0;
    skyldig = 0;
}

Person::Person(string n, double b, double s)
{
    namn = n;
    betalat_andras = b;
    skyldig = s;
}

double Person::haemta_betalat()
{
    return betalat_andras;
}

double Person::haemta_skyldig()
{
    return skyldig;
}

string Person::haemta_namn()
{
    return namn;
}

void Person::skrivUt()
{
    cout << namn << " ligger ute med: " << betalat_andras << " och \x84r skyldig: " << skyldig;
    if(betalat_andras > skyldig)
    {
        cout << ". Ska ha " << betalat_andras - skyldig << " fr\x86n potten." << endl;
    }
    else
    {
        cout << ". Ska betala " << skyldig - betalat_andras << " till potten." << endl;
    }
}

//Klassen PersonLista
PersonLista::PersonLista()
{
    antal_pers = 0;     //Listan startar med 0 deltagare i listan
}

PersonLista::~PersonLista()
{

}

void PersonLista::laggTillEn(Person pny)
{
    pers[antal_pers] = pny;
    antal_pers++;
}

void PersonLista::skrivUtOchFixa()
{
    //Går genom varje pers (person) i personlistan och skriver ut denna.
    for(int i = 0; i < antal_pers; i++)
    {
        pers[i].skrivUt();
    }
}

double PersonLista::summaSkyldig()
{
    double skyldig = 0;

    for(int i = 0; i < antal_pers; i++)
    {
        skyldig += pers[i].haemta_skyldig();
    }

    return skyldig;
}

double PersonLista::summaBetalat()
{
    double betalat = 0;

    for(int i = 0; i < antal_pers; i++)
    {
        betalat += pers[i].haemta_betalat();
    }

    return betalat;
}

bool PersonLista::finnsPerson(const string &namn)
{
    for(int i = 0; i < antal_pers; i++)
    {
        if(pers[i].haemta_namn() == namn)
        {
            return true;
        }
    }

    return false;
}

//Klassen Transaktion
Transaktion::Transaktion()
{
    datum = "";
    typ = "";
    namn = "";
    belopp = 0;
    ant_kompisar = 0;

    for(int i = 0; i < ant_kompisar; i++)
    {
        kompisar[i] = "";
    }
}

Transaktion::~Transaktion()
{

}

string Transaktion::haemta_namn()
{
    return namn;
}

double Transaktion::haemta_belopp()
{
    return belopp;
}

int Transaktion::haemta_ant_kompisar()
{
    return ant_kompisar;
}

double Transaktion::haemta_skuld(string namnet)
{
    double skuld = 0;

    for(int i = 0; i < ant_kompisar; i++)
    {
        if(kompisar[i] == namnet)
        {
            skuld = belopp / (ant_kompisar + 1);
        }
    }
    return skuld;
}

bool Transaktion::laesEnTrans(istream &is)
{
    is >> datum >> typ >> namn >> belopp >> ant_kompisar;
    for(int i = 0; i < ant_kompisar; i++)
    {
        is >> kompisar[i];
    }
    return !is.eof();
}

void Transaktion::skrivEnTrans(ostream &os)
{
    os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" << ant_kompisar<< "\t";
    for(int i = 0; i < ant_kompisar; i++)
    {
        os << kompisar[i] << "\t";
    }
    os << endl;
}

bool Transaktion::finnsKompis(string namnet)
{
    for(int i = 0; i < ant_kompisar; i++)
    {
        if(kompisar[i].find(namnet, 0) != std::string::npos)
        {
            return true;
        }
    }
}

//Klassen TransaktionsLista
TransaktionsLista::TransaktionsLista()
{
    antalTrans = 0;
}

TransaktionsLista::~TransaktionsLista()
{

}

void TransaktionsLista::laesin(istream &is)
{
    Transaktion transEnkel;
    while(transEnkel.laesEnTrans(is))
    {
        laggTill(transEnkel);
    }
}

void TransaktionsLista::skrivut(ostream &os)
{
    for(int i = 0; i < antalTrans; i++)
    {
        trans[i].skrivEnTrans(os);
    }
}

void TransaktionsLista::laggTill(Transaktion &t)
{
    trans[antalTrans] = t;
    antalTrans++;
}

double TransaktionsLista::totalkostnad()
{
    double totalkostnad = 0;

    for(int i = 0; i < antalTrans; i++)
    {
        totalkostnad += trans[i].haemta_belopp();
    }
    return totalkostnad;
}

double TransaktionsLista::liggerUteMed(string namnet)
{
    double betalat = 0;

    for(int i = 0; i < antalTrans; i++)
    {
        if(trans[i].haemta_namn() == namnet)
        {
            betalat += (trans[i].haemta_belopp() - (trans[i].haemta_belopp() / (trans[i].haemta_ant_kompisar() + 1)));
        }
    }
    return betalat;
}

double TransaktionsLista::aerSkyldig(string namnet)
{
    double skyldig = 0;

    for(int i = 0; i < antalTrans; i++)
    {
        if (trans[i].finnsKompis(namnet))
        {
            skyldig += trans[i].haemta_skuld(namnet);
        }

    }

    return skyldig ;
}

PersonLista TransaktionsLista::FixaPersoner()
{
    PersonLista perslista;
    string persnamn;
    double persskuld;
    double persbetalat;

    for(int i = 0; i < antalTrans; i++)
    {
        if(!perslista.finnsPerson(trans[i].haemta_namn()))
        {
            persnamn = trans[i].haemta_namn();
            persskuld =+ aerSkyldig(persnamn);
            persbetalat =+ liggerUteMed(persnamn);
            Person nypers = Person(persnamn, persbetalat, persskuld);
            perslista.laggTillEn(nypers);
        }
    }

    return perslista;
}

// -------------------------------------------------------
// Rapport om uppgiften
/*
================================================================================
Här följer programkörningar för alla testdata:
==============================================
Testdata1: Körning nr 1.
Välj i menyn nedan:

0. Avsluta. Alla transaktioner sparas på fil.
1. Läs in en transaktion från tangentbordet.
2. Skriv ut information om alla transaktioner.
3. Beräkna totala kostnaden.
4. Hur mycket är en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA!

Menyval: 2

Skriver info om samtliga transaktioner:
050615  transp  Eva     6000    5       Bosse   Kristin Paul    Torsten Stina
050721  mat     Eva     300     2       Bosse   Kristin
050721  mat     Paul    400     2       Torsten Stina
050721  transp  Bosse   5000    3       Eva     Kristin Paul
050721  transp  Stina   5000    1       Torsten
050722  boende  Kristin 200     1       Eva
050722  mat     Eva     300     2       Kristin Bosse
050723  mat     Torsten 300     2       Paul    Stina
050724  mat     Paul    200     1       Stina
050725  transp  Eva     600     3       Bosse   Kristin Paul

Välj i menyn nedan:

0. Avsluta. Alla transaktioner sparas på fil.
1. Läs in en transaktion från tangentbordet.
2. Skriv ut information om alla transaktioner.
3. Beräkna totala kostnaden.
4. Hur mycket är en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA!

Menyval: 6

Eva ligger ute med: 5850 och är skyldig: 1350. Ska ha 4500 från potten.
Paul ligger ute med: 366.667 och är skyldig: 2500. Ska betala 2133.33 till potten.
Bosse ligger ute med: 3750 och är skyldig: 1350. Ska ha 2400 från potten.
Stina ligger ute med: 2500 och är skyldig: 1333.33. Ska ha 1166.67 från potten.
Kristin ligger ute med: 100 och är skyldig: 2600. Ska betala 2500 till potten.
Torsten ligger ute med: 200 och är skyldig: 3633.33. Ska betala 3433.33 till potten.

Välj i menyn nedan:

0. Avsluta. Alla transaktioner sparas på fil.
1. Läs in en transaktion från tangentbordet.
2. Skriv ut information om alla transaktioner.
3. Beräkna totala kostnaden.
4. Hur mycket är en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA!

Testdata1: Körning nr 2.
Välj i menyn nedan:

0. Avsluta. Alla transaktioner sparas på fil.
1. Läs in en transaktion från tangentbordet.
2. Skriv ut information om alla transaktioner.
3. Beräkna totala kostnaden.
4. Hur mycket är en viss person skyldig?
5. Hur mycket ligger en viss person ute med?
6. Lista alla personer mm och FIXA!

Menyval: 6

Eva ligger ute med: 600 och är skyldig: 100. Ska ha 500 från potten.
Bosse ligger ute med: 100 och är skyldig: 600. Ska betala 500 till potten.

Välj i menyn nedan:

================================================================================
Här skriver du en kort rapport om uppgiften:
- ett eller ett par stycken om vad uppgiften gick ut på,
Uppgiften går nog ut på att lära sig hantera flera olika objekt av klasser och kommunicera mellan dessa.

- vilka svårigheter som fanns,
Att greppa hela projektet, kändes väldigt svårt när man började.

- vad du tyckte var besvärligt
Att hålla ordning på allt och att greppa programmet från börja. Kändes som det skulle vara väldigt svårt när jag började programmera.

- och hur du löste problemen.
Med papper och penna, rita upp strukturen, efter detta gick det mycket lättare.
Dock kändes uppgiften som mycket svårare än förra uppgiften.

Om det finns frågor att besvara i uppgiften ska det göras här.

*/
