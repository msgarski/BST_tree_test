#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>

using namespace std;

int licznik=0;
int k;
bool tab[20001]{};
struct Node
{
    int klucz;
    char ch[10]{};
    Node *right;
    Node *left;

};
//******************************************************************************************************************
//funkcja do zaznaczania w tablicy istniejacych wezlow
    void inorder_stan(Node *root, bool *a)
{
         if(root)
        {
            inorder_stan(root->left, a);        //rekurencyjnie w porzadku poprzecznym przechodzi drzewo
                                                //i wracajac zaznacza w przekazanej tablicy wystapienia
            a[root->klucz+10000]=true;          //kluczy w odwiedzonych wezlach
            inorder_stan(root->right, a);
        }

    return;
}
//**********************************************************************************************************************
//funkcja do zamiany liczby int na tablice char
void int_to_char(int liczba, char *table_char)  //pobiera adres tablicy z wezla i wypelnia ja
{
    //char*table_char=new char[11]{};
    char znak;                                  //tu zapiszemy znak liczby: - lub +
    int i=9;                                    //juz nie pamietam, dlaczego tu jest 9 a nie 10
    (liczba<0)?znak='-': znak='+';              //zapisanie znaku liczby do zmiennej char
    (liczba<0)?liczba=-liczba: liczba;          //w funkcji lepiej pracowac na bezznakowych wartosciach
    //cout<<"liczba po abs "<<liczba<<endl;
    while(liczba)                               //petla dopoki mamy jeszcze co rozkladac na czynniki
    {
        switch(liczba%10)                       //odcinamy koncowki liczby i przypisujemy im char
        {
            case 0: table_char[i]='0'; break;
            case 1: table_char[i]='1'; break;
            case 2: table_char[i]='2'; break;
            case 3: table_char[i]='3'; break;
            case 4: table_char[i]='4'; break;
            case 5: table_char[i]='5'; break;
            case 6: table_char[i]='6'; break;
            case 7: table_char[i]='7'; break;
            case 8: table_char[i]='8'; break;
            case 9: table_char[i]='9'; break;
        }
        liczba/=10;
        i--;
    }
    //for(int k=0; k<10; k++)
        //cout<<table_char[k]<<" ";
    table_char[i]=znak;
    //cout<<"funkcja dziala"<<endl;
    //for(int k=0; k<10; k++)
        //cout<<table_char[k]<<" ";
        //cout<<"wychodzimy z funkcji"<<endl;
    return; //table_char;
}

//********************************************************************************************************
void wstawienie(Node **root, int klucz)//gotowa do sprawdzenia oprócz tablicy
{
//zaczynamy szukac miejsca na nowy wezel
        Node *p=*root;
        Node *rodzic=nullptr;
        if(*root)
        {
            while(p!=nullptr)
            {
                if(p->klucz==klucz) //powtorzenie wstawianego klucza
                {
                    cout<<"BLAD! W drzewie jest juz wezel o kluczu = "<<klucz<<endl<<endl;
                    p=nullptr;
                    return;
                }
                rodzic=p;
                if(p->klucz>klucz)
                    p=p->left;
                else
                    p=p->right;
            }
        }
//alokacja pamieci na nowy wezel listy
        Node *nowy= new Node;
        if(!nowy)
        {
            cout<<"Nie udalo sie utworzyc nowego wezla drzewa!\n Brak pamieci!"<<std::endl;
            return;
        }

//inicjalizacja liczbowych zmiennych wezla:
        nowy->klucz=klucz;
        //potrzeba jeszcze wypelnic tablice....
        int_to_char(klucz, nowy->ch);
        nowy->right=nullptr;
        nowy->left=nullptr;
        if(!*root)
        {
            *root=nowy;
            return;
        }
        else if(rodzic->klucz>klucz)
            rodzic->left=nowy;
        else
            rodzic->right=nowy;

        return;
}

//***********************************************************************************************************
void wstawienie_X_elementow(Node **root, int X)
{
    int los;
    bool tabl_losowych[20001];
    srand(time(0));

    //przejscie przez drzewo aby zaktualizowac tablice wystepujacych juz w drzewie kluczzy
    inorder_stan(*root, tabl_losowych);

        for(int i=0; i<X; i++)
        {
            //losowanie unikalnej liczby i przes³anie jej do wezla listy
            do
            {
                los=(rand()%20001);
            }
            while(tabl_losowych[los]);
            tabl_losowych[los]=true;        //zapamietanie wylosowania danej liczb

            //wywolanie funkcji wstawiajacej dla wylosowanego klucza
            wstawienie(root, los-10000);
        }
        return;
}
//****************************************************************************************************************
void szukaj(Node *root, int szukany)
{
    int sukces=0;
    if(!root)
    {
        cout<<"Drzewo nie zawiera zadnych elementow!"<<endl<<endl;
        return;
    }
    Node *p=root;
    while(p!=nullptr)
    {
        if(p->klucz==szukany)
        {
            cout<<"Znaleziono szukany klucz "<<szukany<<endl;
            cout<<"Oto zawartosc jego tablicy: ";

            for(int i=0; i<10; i++)
            {
                if(p->ch[i])
                cout<<p->ch[i]<<" ";
            }
            sukces=1;
            break;
        }
        else
        {
            if(p->klucz<szukany)
                p=p->right;
            else
                p=p->left;
        }
    }
    if(!sukces)     //to chyba niepotrzebne
        cout<<"Nie znaleziono wezla o kluczu = "<<szukany<<endl<<endl;

    return;
}

//********************************************************************************************************************
void usuwanie(Node **root, int x)
{
Node *parent_p=nullptr; //to rodzic p, ktory sie przyda, gdy trzeba bedzie podpiac poprzednika w miejsce p
Node *p=*root;        //wskaznik wedrujacy p
cout<<"Rozpoczynam usuwanie wezla o kluczu: "<<x<<endl;
if(!*root)
{
    cout<<"Drzewo nie zawiera zadnych wezlow!"<<endl;
    return;
}
//szukanie p i jednoczesne podciaganie za soba rodzica_p:
    while(p!=nullptr&&x!=p->klucz)      //rob to, co w petli, az bedzie sukces lub sciana
    {
        parent_p=p;
        if(p->klucz<x)
            p=p->right;
        else
            p=p->left;
    }
    //zakonczyl szukanie, ale czy znalazl???:
    if (!p)     //jednak nie znalazl  p, wychodzimy z funkcji
    {
        cout<<"Nie udalo sie znalezc wezla o tym kluczu"<<endl<<"Nie zostal wiec usuniety..."<<endl<<endl;
        return;
    }
    //jadnak znalazl p, a jego rodzic to parent_p

//dotad ok******************************************************************************************
// I przypadek znalezienia p:
    //  czy p jest lisciem??, czyli czy ma potomstwo?
    if(p->left==nullptr&&p->right==nullptr)
    {                               //tak, jest lisciem!!
        cout<<"Usuwany wezel jest lisciem(bezpotomny)"<<endl;
        if(p==*root)                //a moze tez jest przy okazji rootem?
        {
            cout<<"a przy okazji to root"<<endl;
            *root=nullptr;          //zerujemy roota
            delete p;               //zwalniamy pamiec po p
            cout<<"Usuniety..."<<endl<<endl;
            return;
        }
        else if(parent_p->right==p) //nie jest rootem, wiec:
            parent_p->right=nullptr;
        else
        {
            parent_p->left=nullptr;
            cout<<" parent p = "<<parent_p->klucz<<endl;
        }
        delete p;
        return;
    }
//dotad ok************************************************************************************************

// II przypadek:
    // p nie jest lisciem, ani lisciem-rootem
    //moze byc gdzies w srodku drzewa i...

    //ma tylko lewe poddrzewo:
    if(!p->right)
    {
        if(p==*root)            //TEGO NIE SPRAWDZILEM
        {
            *root=p->left;
            delete p;
        }
        else if(parent_p->right==p)
            parent_p->right=p->left;
        else
            parent_p->left=p->left;
        delete p;
        return;
    }
//dotad ok**************************************************************************************

    //lub ma tylko prawe poddrzeewo:
    if(!p->left)
    {
        if(p==*root)        //TEGO NIE SPRAWDZILEM
        {
            *root=p->right;
            delete p;
        }
        else if(parent_p->right=p)
            parent_p->right=p->right;
        else
            parent_p->left=p->right;
        delete p;
        return;
    }
//dotad ok************************************************************************************************
    //skoro tutaj jestesmy, to znaczy, ze
    //p ma oba poddrzewa, wiec nie bedzie latwo...

    //trzeba znalezc jego poprzednika (lub nastepnika), my szukamy poprzednika
    //podciagamy za soba rodzica szukanego poprzednika
    Node* poprzednik=p->left;
    Node *rodzic_poprzednika=p;
    while(poprzednik->right)
    {
        rodzic_poprzednika=poprzednik;
        poprzednik=poprzednik->right;
    }
    cout<<" poprzednik wezla "<<x<<" to wezel "<<poprzednik->klucz<<endl;
    //cout<<"a p to : "<<p->klucz<<" a jego rodzic to: "<<parent_p->klucz<<endl;
    cout<<"a root to "<<(*root)->klucz<<endl;
    //mamy poprzednika, teraz go obejrzymy i wytniemy...
    //dotad ok**************************************************************************************************
    if(poprzednik==p->left) //gdy poprzednik jest tuz obok p, po lewej stronie,
    {
        if(p==*root) //a p jest rootem
        {
            *root=p->left;
            (*root)->right=p->right;
            delete p;
            return;
        }
        else    //poprzednik tuz obok, a p nie jest rootem
        {
            cout<<"czy tu jest?"<<endl;
            if(parent_p->right==p) //wysypuje sie tutaj
            {
                parent_p->right=poprzednik;
                cout<<"czy tu tez jest?"<<endl;
            }
            else if(parent_p->left==p)   //tu mozna zrezygnowac z tego warunku i tylko else
                parent_p->left=poprzednik;

            poprzednik->right=p->right;
            delete p;
            return;
        }
    }
//dotad ok***********************************************************************************************
        //no i ostatni przypadek
        //gdy poprzednik jest gdzies na koncu...
        //wyluskanie poprzednika:
        cout<<"rodzic poprzednika: "<<rodzic_poprzednika->klucz<<endl;
        rodzic_poprzednika->right=poprzednik->left;
        poprzednik->left=nullptr;
        if(p->klucz==(*root)->klucz)
    {
        poprzednik->left=(*root)->left;
        poprzednik->right=(*root)->right;
        *root=poprzednik;
        delete p;
        return;
    }
        //wstawienie poprzednika na miejsce p:
        if(p->klucz<parent_p->klucz)
            parent_p->left=poprzednik;
        else
            parent_p->right=poprzednik;

        //laczenenie poprzednika z innymi wezlami
        poprzednik->right=p->right;
        poprzednik->left=p->left;
        delete p;
    return;
}

//funkcje przelatujace przez drzewo
void preorder(Node *root)
{
    if(root)
    {
        cout<<root->klucz<<" ";
        preorder(root->left);
        preorder(root->right);
    }
    return;
}
void preorder_licz(Node *root)
{
    licznik=0;
    preorder(root);
    cout<<endl<<"licznik preorder = "<<licznik<<endl;
    if(!licznik)
        cout<<"Drzewo nie zawiera zadnych elementow!"<<endl<<endl;
}
//zwykla funkcja inorder
void inorder(Node *root)
{
         if(root)
        {
            inorder(root->left);
            cout<<root->klucz<<" "<<"zawartosc jego tablicy: ";
            for(int i=0; i<10; i++)
            {
                if(root->ch[i])
                cout<<root->ch[i]<<" ";
            }
            cout<<endl;
            licznik++;
            inorder(root->right);
        }

    return;
}

//funkcja inorder do zliczania odwiedzonych wezlow
void inorder_licz(Node *root)
{
    licznik=0;
    inorder(root);
    cout<<endl<<"licznik inorder = "<<licznik<<endl;
    if(!licznik)
        cout<<"Drzewo nie zawiera zadnych elementow!"<<endl<<endl;
}


void postorder(Node *root)
{
    if(root)
    {
        postorder(root->left);
        postorder(root->right);
        cout<<root->klucz<<" ";
    }
    return;
}
void postorder_licz(Node *root)
{
    licznik=0;
    postorder(root);
    cout<<endl<<"licznik inorder = "<<licznik<<endl;
    if(!licznik)
        cout<<"Drzewo nie zawiera zadnych elementow!"<<endl<<endl;
}
void inicjacja()        //czy to potrzebna?
{
    Node *drzewo=nullptr;
}





int main()
{
srand(time(0));
//inicjacja();
Node *drzewo=nullptr;
//sprawdzenie malego drzewa

//szukaj(drzewo, 30);


usuwanie(&drzewo, 30);


wstawienie(&drzewo, -9999);
wstawienie(&drzewo, 30);
wstawienie(&drzewo, 10);
//wstawienie(&drzewo, 40);




inorder_licz(drzewo);
usuwanie(&drzewo, 50);

cout<<"co zostalo:"<<endl;
//inorder_licz(drzewo);


szukaj(drzewo, -9999);
cout<<endl;
cout<<"tu ok"<<endl;

wstawienie_X_elementow(&drzewo, 100);
cout<<endl;
inorder_licz(drzewo);

    /*
    wstawienie(&drzewo, 100);
    inorder_licz(drzewo);
     cout<<endl;
    wstawienie(&drzewo, 50);
    inorder(drzewo);

    wstawienie(&drzewo, 50);
    wstawienie(&drzewo, 50);
     cout<<endl;
    wstawienie(&drzewo, 200);
    inorder_licz(drzewo);
     cout<<endl;
    //wstawienie(&drzewo, 100);

     cout<<endl;
 wstawienie(&drzewo, 25);

      cout<<endl;
 wstawienie(&drzewo, 75);

       cout<<endl;
 wstawienie(&drzewo, 12);

  wstawienie(&drzewo, -2);

   wstawienie(&drzewo, 13);

    wstawienie(&drzewo, 60);

     wstawienie(&drzewo, 99);

      wstawienie(&drzewo, 150);

       wstawienie(&drzewo, 300);

        wstawienie(&drzewo, 250);

         wstawienie(&drzewo, 400);
                  wstawienie(&drzewo, 500);
         wstawienie(&drzewo, 58);
                  wstawienie(&drzewo, 58);

    szukaj(drzewo, 300);
*/




    return 0;
}
