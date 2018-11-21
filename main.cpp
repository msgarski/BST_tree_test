#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

struct Node
{
    int klucz;
    char ch[10];
    Node *right;
    Node *left;

};
//********************************************************************************************
//********************************************************************************************
struct Stos
{
    Node *prarodzic=nullptr;
    Stos *next=nullptr;
};
Stos *top=nullptr; //tutaj, czy wew funkcji szukania?

//funkcje do obslugi stosu:

//funkcja wstawiajaca na stos:
void push(Node *root)
{
    Stos *topStos=new Stos;
    topStos->prarodzic=root;
    topStos->next=top;
    top=topStos;
}
//funkcja zdejmujaca ze stosu:
Node* pop(void)
{
    Node *p;
    Stos *temp;
    if(top!=NULL)
    {
    temp=top;
    p=top->prarodzic;
    top=top->next;
    printf("Wartosc zdjeta ze stosu to:\n%d", p);
    }
    else
    {
     cout<<"Stos jest pusty..."<<endl;
    }
    delete temp;
    return p;
}
//ta funkcja nie jest potrzebna :
//funkcja podaje co jest na szczycie stosu:
void peek(void)
{
    if(top!=NULL)
        cout<<"Oto szczyt stosu: "<<(*top).prarodzic;
    else
        cout<<"stos jest pusty..."<<endl<<endl;
}
//*****************************************************************************************************
//*****************************************************************************************************
/*
void stan_aktualny(Node *root, int t)
{
    int i;
    if(root)
    {
        stan_aktualny(root->left, t);
        {
            {
                if(root->klucz>=-10000&&root->klucz<=10000)
                {
                    i=root->klucz+10000;
                    t[i]=1;
                }
            }
        }
        stan_aktualny(root->right, t);
    }
}

*/

/*
Node * inicjalizacja(Node **root)
{
}
*/


void wstawienie(Node **root, int klucz)//gotowa do sprawdzenia oprócz tablicy
{
//alokacja pamieci na nowy wezel listy
        Node *nowy= new Node;
        if(!nowy)
        {
            cout<<"Nie udalo sie utworzyc nowego wezla drzewa!\n Brak pamieci!"<<std::endl;
            return;
        }
        //cout<<"alokacja udana "<<endl;//linia do wykasowannia
//inicjalizacja liczbowych zmiennych wezla:
        nowy->klucz=klucz;
        //potrzeba jeszcze wypelnic tablice....
        nowy->right=nullptr;
        nowy->left=nullptr;
        //cout<<"nadanie wartosci udane "<<endl;//linia dowykasowania
//zaczynamy szukac miejsca na nowy wezel
        Node *p=*root;
        Node *rodzic=nullptr;
        if(!*root)
        {
            *root=nowy;
            return;
        }
        while(p!=nullptr)
        {
            if(p->klucz==klucz) //powtorzenie wstawianego klucza
            {
                cout<<"BLAD! W drzewie jest juz wezel o kluczu = "<<klucz<<endl<<endl;
                return;
            }
            rodzic=p;
            if(p->klucz>klucz)
                p=p->left;
            else
                p=p->right;
        }
        if(rodzic->klucz>klucz)
            rodzic->left=nowy;
        else
            rodzic->right=nowy;
        return;
}


void wstawienie_X_elementow(Node **root, int X)
{
    int los;
    int tabl_losowych[20001];


    //przejscie przez drzewo aby zaktualizowac tablice wystepujacych juz w drzewie kluczzy


        for(int i=0; i<X; i++)
        {
            //losowanie unikalnej liczby i przes³anie jej do wezla listy
            do
                {
                    los=(rand()%21001);
                }
                while(tabl_losowych[los]);
                tabl_losowych[los]=1;        //zapamietanie wylosowania danej liczb
            //wywolanie funkcji wstawiajacej dla wylosowanego klucza
            wstawienie(root, los);
        }
        return;
}

void szukaj(Node *root, int szukany)
{
    //Stos *pop=nullptr;

    int sukces=0;
    if(!root)
    {
        cout<<"Drzewo nie zawiera zadnych elementow!"<<endl<<endl;
        return;
    }
    Node *p=root;
    push(root);
    while(p!=nullptr)
    {
        if(p->klucz==szukany)
        {
            cout<<"Znaleziono szukany klucz "<<szukany<<endl;
            sukces=1;
            break;
        }
        else
        {
            //push(p)

            if(p->klucz<szukany)
                p=p->right;
            else //if(p->klucz>szukany)
                p=p->left;
            //pop(p)
        }
    }
    if(!sukces)
        cout<<"Nie znaleziono wezla o kluczu = "<<szukany<<endl<<endl;

    return;
}


void usuwanie(Node **root, int x)
{
Node *parent_p=nullptr; //to rodzic p, ktory sie przyda, gdy trzeba bedzie podpiac poprzednika w miejsce p
Node *p=*root;        //wskaznik wedrujacy p
//szukanie p i jednoczesne podciaganie za soba rodzica_p:
    while(p!=nullptr&&x!=p->klucz) //rob to, co w petli, az bedzie sukces lub sciana
    {
        parent_p=p;
        if(p->klucz<x)
            p=p->right;
        else
            p=p->left;
    }
    //znalazl p, a jego rodzic to parent_p

    if (!p)     //jednak nie znalazl  p, wychodzimy z funkcji
    {
        cout<<"Nie udalo sie znalezc klucza o szukanym kluczu"<<endl<<endl;
        return;
    }
// I przypadek znalezienia p:
    //  czy p jest lisciem??, czyli czy ma potomstwo?
    if(p->left==nullptr&&p->right==nullptr)
    {//tak, jest lisciem!!
        if(p==*root) //a moze tez jest przy okazji rootem?
        {
            root==nullptr;
            delete p;   //zwalniamy pamiec po p
            return;
        }
        else if(parent_p->right==p)//nie jest rootem, wiec:
            parent_p->right==nullptr;
        else
            parent_p->left==nullptr;
        delete p;
        return;
    }

// II przypadek:
    // p nie jest lisciem, ani lisciem-wezlem
    //moze byc gdzies w srodku drzewa i...

    //ma tylko lewe poddrzewo:
    if(!p->right)
    {
        if(p==*root)
        {
            *root=p->left;
            delete p;
        }
        else if(parent_p->right=p)
            parent_p->right=p->left;
        else
            parent_p->left-p->left;
        delete p;
        return;
    }

    //lub ma tylko prawe poddrzeewo:
    if(!p->left)
    {
        if(p==*root)
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
    //mamy poprzednika, teraz go obejrzymy i wytniemy...
    if(poprzednik=p->left) //gdy poprzednik jest tuz obok p, po lewej stronie,
    {
        if(p=*root) //a p jest rootem
        {
            *root=p->left;
            (*root)->right=p->right;
            delete p;
            return;
        }
        else    //poprzednik obok, a p nie jest rootem
        {
            if(parent_p->right=p)
                parent_p->right=poprzednik;
            else if(parent_p->left=p)   //tu mozna zrezygnowac z tego warunku i tylko else
                parent_p->left=poprzednik;
            poprzednik->right=p->right;
            delete p;
        }

        //no i ostatni przypadek
        //gdy poprzednik jest gdzies na koncu...
        //wyluskanie poprzednika:
        rodzic_poprzednika->right=poprzednik->left;
        poprzednik->left=nullptr;

        //wstawienie poprzednika na miejsce p:
        if(p->klucz<parent_p->klucz)
            parent_p->left=poprzednik;
        else
            parent_p->right=poprzednik;

        //laczenenie poprzednika z innymi wezlami
        poprzednik->right=p->right;
        poprzednik->left=p->left;

        delete p;
    }
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

void inorder(Node *root)
{
    if(root)
    {
        inorder(root->left);
        cout<<root->klucz<<" ";
        inorder(root->right);
    }
    return;
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




int main()
{
    //Stos *top=nullptr;

    Node *drzewo=nullptr;

    wstawienie(&drzewo, 100);
    inorder(drzewo);
     cout<<endl;
    wstawienie(&drzewo, 50);
    inorder(drzewo);
     cout<<endl;
    wstawienie(&drzewo, 200);
    inorder(drzewo);
     cout<<endl;
    wstawienie(&drzewo, 100);

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
    inorder(drzewo);
      cout<<endl;
szukaj(drzewo, 13);
  cout<<endl;
  szukaj(drzewo, 55);
usuwanie(&drzewo, 200);
inorder(drzewo);
      cout<<endl;

cout<<" root-klucz "<<(*drzewo).klucz<<endl;


    return 0;
}
