#include <iostream>
#include <fstream>
#include <cstdlib>

#include <ctime>
#include <string>

using namespace std;
/*
*******************************************************************************
*                                   List                                   *
*   Struktura reprezantujaca listę sąsiedztwa dla pojedyńczego wierzchołka    *
*                                                                             *
*   v - Zmienna przechowuje parę wierzchołków, początkowy oraz końcowy        *
*   w - Zmienna przechowuje wagę krawędzi                                     *                                                               *
*                                                                             *
*******************************************************************************
*/      

struct List  
{
    int v;
    int w;    
    List* nastepny;
};


/*
************************************************************************************************************
*                                   Zapisz_do_pliku                                                        *
*   Funkcja zapisująca wygenerowane wartości wierzchołka w pliku                                           *
*                                                                                                          *
*   liczba_wyk - oznacza pozostała liczbe wykonacz po stworzeniu scieżki laczacej wszystkie wirzcholki     *
*                                                                                                          *
************************************************************************************************************
*/  

void Zapisz_do_pliku( int krawedzie, int wierzcholki, fstream& strumien) 
{
    int l_wyk = krawedzie - wierzcholki + 1;  
                                                        
    int tmp = 0;
    int n_wierzch = wierzcholki;
    int n = 0;
    

    strumien.open("Graf.txt", ios_base::app);           

    strumien << krawedzie << " " << wierzcholki << " " <<rand()%wierzcholki<<endl;
    
                                                        
    for(int i = 0; i < wierzcholki - 1; i++)

                                                        
    {
        strumien << i<< " "<<i+1<<" "<<rand()%100+1<<endl;
    }


    while(n < l_wyk) 
    {
        tmp = 0;

        while(n < l_wyk && tmp < n_wierzch - 2)
        {
            strumien << n_wierzch - 1<<" "<< tmp <<" "<<rand()%10+1<<endl;

            n++;
            tmp++;
        }
        n_wierzch--;
    }
    strumien.close();           

}


/*
************************************************************************************************************
*                                   Zapisz_do_zm                                                           *
*   Funkcja wykonuje to samo co funkcja Zapisz_do_pliku jednak ta zapisuje potrzebne dane do zmiennegj     *
*                                                                                                          *
*  graf2 = zmienna do której zapisuje liczby                                                                                                        *
*                                                                                                          *
************************************************************************************************************
*/
void Zapisz_do_zm(int krawedzie, int wierzcholki, int **graf2, int v_start) 
{
    int l_wyk = krawedzie - wierzcholki + 1;  
                                                        
    int tmp = 0;
    int n_wierzch = wierzcholki;
    int n = 0;

    graf2[0][0] = krawedzie;
    graf2[0][1] = wierzcholki;
    graf2[0][2] = v_start;

    int x = wierzcholki - 1 ;
                       
    for(int i = 0; i < wierzcholki; i++)
                                         
    {
        graf2[i+1][0] = i;
        graf2[i+1][1] = i+1;
        graf2[i+1][2] = rand()%100+1;
    }

    
    while(n < l_wyk) 
    {
        tmp = 0;

        while(n < l_wyk && tmp < n_wierzch - 2)
        {
            graf2[x+n][0] = n_wierzch -1;
            graf2[x+n][1] = tmp;
            graf2[x+n][2] = rand()%10+1;
            
            n++;
            tmp++;
        }
        n_wierzch--;
    }

    for(int i = 0 ; i<11; i++)
    {
        cout<<graf2[i][0]<<"    ";
        cout<<graf2[i][1]<<"    ";
        cout<<graf2[i][2]<<endl;
    }
}

/*
************************************************************************************************************
*                                          Wez_dane                                                        *
*   Funkcja wypisująca graf do pliku poprzez tablice wartości zadanych w projekcie                         *
*                                                                                                          *
*  wierzcholki - tablica ilosci wierzcholkow zadanych w poleceniu projektu                                 *
*  gestosc - tablica % wypelnien zadanych przypadkow                                                       *
*  max_krawedzi - tablica maksymalnych liczb krawedzi                                                      *
*  krawedzie - tablica liczb krawedzi dla kazdego z przypadkow zadanych w projekcie                        *                         
************************************************************************************************************
*/  

void Wez_dane(fstream& strumien)
{
    int wierzcholki[5] = {10, 50, 100, 500, 1000};  
    int gestosc[4] = {25, 50, 75, 100};         
    
    int max_krawedzi[5];                            
    int krawedzie[5][4];                            
    

    strumien.open("Graf.txt", ios_base::out);       
    strumien.close();                               
                                                    

    for (int i = 0; i < 5; i++) 
                               
    {
        max_krawedzi[i] = wierzcholki[i] * (wierzcholki[i] - 1) /2;
        for (int j = 0; j < 4; j++)
        {
            krawedzie[i][j] = gestosc[j] * max_krawedzi[i] /100;
            for(int k = 0; k < 100; k++) 
                Zapisz_do_pliku (krawedzie[i][j], wierzcholki[i], strumien);
        }
    }
}

/*
************************************************************************************************************
*                                   W_Sciezke                                                              *
*   Funkcja wyswietlajaca sciezke oraz jej koszt dojscia do kazdego z wierzcholkow .                       *
*                                                                                                          *
*                                                                                                          *
*                                                                                                          *
************************************************************************************************************
*/
void W_Sciezke(int* prev, int* koszt, int wierzch)
{
    int* wyswietlanie = new int [wierzch];  

    int n = 0;
    int m;

    for(int i = 0; i < wierzch; i++)                             
    {
        cout << i <<": ";
        for(m = i; m != -1 && n < wierzch; m = prev[m])
            wyswietlanie [n++] = m;

        while(n)
            cout << wyswietlanie[--n] << " ";

        cout << "$" << koszt[i] << endl;
    }
    delete [] wyswietlanie;             
}

/*
************************************************************************************************************
*                                   L_Bellman_Ford                                                         *
*   Algorytm Bellmana-forda dla listy - szukanie najkrotszej drogi                                         *
*   max_int - maksymalna wartosc int w 32bit -> 64bit 9223372036854775807                                  *
*   koszt - wskaznik na tablice dynamiczna kosztow dojscia                                                 *
*   prev - wskaznik na tablice dynamiczna poprzednikow                                                     *
************************************************************************************************************
*/

void L_Bellman_Ford( int kraw, int wierzch, int start, List** tab_list)
{
    List* neigh;

    int max_int = 10000000;           

    int *koszt = new int [wierzch];
    
    int *prev = new int [wierzch];

    for(int i = 0; i < wierzch; i++)
    {
        prev[i] = -1;             
        koszt[i] = max_int;     
    }

    koszt[start] = 0;           

    for(int j = 1; j < wierzch; j++)
    {
        for(int k = 0; k < wierzch; k++)                               
        {
            for(neigh = tab_list[k]; neigh; neigh = neigh -> nastepny)
            {
                if(koszt[k] != max_int && koszt[neigh -> v] > koszt[k] + neigh -> w)
                {
                    koszt[neigh -> v] = koszt[k] + neigh -> w;
                    prev[neigh -> v] = k;
                }
            }
        }
    }
   //cout <<"Lista sasiedztwa:\n";
    //W_Sciezke(prev, koszt, wierzch);                
                           
}

/*
************************************************************************************************************
*                                   M_Bellman_Ford                                                         *
*   Algorytm Bellmana-forda dla macierzy - szukanie najkrotszej drogi                                      *
*   max_int - maksymalna wartosc int w 32bit -> 64bit 9223372036854775807                                  *
*   koszt - wskaznik na tablice dynamiczna kosztow dojscia                                                 *
*   prev - wskaznik na tablice dynamiczna poprzednikow                                                     *
************************************************************************************************************
*/

void M_Bellman_Ford(int** tmp_graf, int kraw, int wierzch,  int start)
{

    int max_int = 10000000;           

    int* koszt;                 
    koszt = new int [wierzch];

    int* prev;                  
    prev = new int [wierzch];

    for(int i = 0; i < wierzch; i++)
    {
        prev[i] = -1;             
        koszt[i] = max_int;     
    }

    koszt[start] = 0;           

    for(int j = 1; j < wierzch; j++)
    {
        for(int k = 0; k < wierzch; k++)
        {
            for(int v = 0; v < wierzch; v++)    
            {
                if(koszt[k] != max_int && tmp_graf[v][k] != 0 && koszt[v] > koszt[k] + tmp_graf[v][k])
                {
                    koszt[v] = koszt [k] +  tmp_graf[v][k];
                    prev[v] = k;
                }
            }
        }
    }
    cout <<"Macierz sasiedztwa:\n";
    W_Sciezke(prev, koszt, wierzch);        
                            
}

/*
************************************************************************************************************
*                                   W_Lista                                                                *
*   Funkcja do wyswietlania listy                                                                          *
************************************************************************************************************
*/
void W_Lista(List** tab_list, int wierzch)
{
    
    List* lista_w;
    cout<< "lista:\n";
    for(int i = 0; i < wierzch; i++)
      {
        cout << "tab[" << i << "] =";
        lista_w = tab_list[i];
        while(lista_w)
        {
          cout << lista_w->v <<" ";
          lista_w = lista_w->nastepny;
        }
        cout << endl;
    }
    delete [] lista_w; 
}

/*
************************************************************************************************************
*                                   L_Graf                                                                 *
*   Funkcja tworzy graf za pomoca listy sasiedztwa                                                         *
*                                                                                                          *
*   v1 = wierzcholek startowy                                                                              *
*   v2 = wierzcholek koncowy                                                                               *
*   waga = waga krawedzi                                                       *                           *
************************************************************************************************************
*/
void L_Graf(int& kraw, int& wierzch, int& start, int** graf, List** tab_list, List* lista)
{
    int v1;
    int v2;
    int waga;
    for(int c = 0; c < wierzch; c++)   
    {
        tab_list[c] = NULL;

    }
    int x = min(kraw,wierzch) - 1 ;
    
    for(int c = 0; c <= x; c++)   
    {

        v1 = graf[c][0];    
        v2 = graf[c][1];
        waga = graf[c][2];

        lista = new List;

        lista->v = v2;
        
        lista->w = waga;

        lista->nastepny = tab_list[v1];
        tab_list[v1] = lista;

    }

   // W_Lista(tab_list, wierzch);     
}


/*
************************************************************************************************************
*                                   W_Macierz                                                              *
*   Funkcja do wyswietlania macierzy                                                                       *
************************************************************************************************************
*/
void W_Macierz(int** tmp_graf, int wierzch)
{
    for(int c = 0; c < wierzch; c++)
    {
        for(int v = 0; v < wierzch; v++)
        {
            cout << tmp_graf[c][v] <<" ";
        }
        cout<<endl;
    }
}

/*
************************************************************************************************************
*                                   M_Graf                                                                 *
*   Funkcja tworzy graf za pomoca macierzy sasiedztwa                                                      *
*                                                                                                          *
*   v1 = wierzcholek startowy                                                                              *
*   v2 = wierzcholek koncowy                                                                               *
*   waga = waga krawedzi                                                       *                           *
************************************************************************************************************
*/
void** M_Graf(int& kraw, int& wierzch, int& start, int** graf, int** tmp_graf)
{
    int v1;
    int v2;
    int waga;
    int p = 0;

    for (int v = 0; v < wierzch; ++v)   
    {

        for(int b = p; b < wierzch; ++b)
        {
            tmp_graf[v][b] = 0;
            tmp_graf[b][v] = 0;
        }
        p++;
    }

    int x = min(kraw,wierzch) -1;
    for (int v = 0; v <= x; ++v)
    {
        v1 = graf[v][0];        
        v2 = graf[v][1];
        waga = graf[v][2];

        tmp_graf[v1][v2] = waga;  
        
    }
    //W_Macierz(tmp_graf, wierzch);

}

/*
************************************************************************************************************
*                                   Wczytaj_z_Pliku                                                        *
*   Funkcja wczytujaca dane z pliku do zmiennej                                                            *
************************************************************************************************************
*/
void** Wczytaj_z_Pliku(int** graf, int& kraw, int& wierzch, int& start, ifstream& wejscie)
{
    for(int x = 0; x < kraw; x++)    
    {
        wejscie >> graf[x][0];
        wejscie >> graf[x][1];
        wejscie >> graf[x][2];

        
    }
}

/*
************************************************************************************************************
*                                   Wczytaj_Zm                                                             *
*   Funkcja wczytujaca dane ze zmiennej do grafu                                                           *
************************************************************************************************************
*/
/*
void** Wczytaj_Zm(int** graf, int& kraw, int& wierzch, int& start, int **graf2)
{
    int x = min(kraw, wierzch) -1 ;
   
    for(int i = 0; i <= x; i++)    
    {
        graf[i][0] = graf2[i][0];
        graf[i][1] = graf2[i][1];
        graf[i][2] = graf2[i][2];

       
    }
}
*/
int Licz_D(int kraw, int wierzch)
{
    int D;

    D = (100 * kraw*2)/(wierzch*(wierzch-1));
    return D;
}

/*
************************************************************************************************************
*                                  L_Znajdz_droge                                                          *
*   Funkcja szukająca drogi po na podstwie reprezentacji listy                                             *
************************************************************************************************************
*/
void L_Znajdz_droge(int** graf, int& kraw, int& wierzch, int& start, fstream& wyjscie)
{
    double czas_trwania;
    clock_t t_1;
    clock_t t_2;           

    int D = Licz_D(kraw, wierzch);
    
    List** tab_list;
    List* lista, *usuwanie;      
                                    

    tab_list = new List * [wierzch]; 

    L_Graf(kraw, wierzch, start, graf, tab_list, lista);   
                                                                


    t_1 = clock();                

    L_Bellman_Ford(kraw, wierzch, start, tab_list);   
                                                

    t_2 = clock() - t_1;        


      for(int i = 0; i < wierzch; i++) 
      {
        lista = tab_list[i];
        while(lista)
        {
          usuwanie = lista;
          lista = lista->nastepny;
          delete usuwanie;
        }
      }
        delete [] tab_list;   

    czas_trwania = (double) (t_2) / CLOCKS_PER_SEC;       

    
    wyjscie << "Czas trwania dla listy przy: "<<wierzch<<" wierzchołkach oraz  "<<D<<"% wypelnienia: "<<czas_trwania<<endl;
}

/*
************************************************************************************************************
*                                   M_Znajdz_droge                                                         *
*   Funkcja szukająca drogi po na podstwie reprezentacji macierzy                                          *
*   tmp_graf zmienna macierzy sasiedztwa                                                                   *
************************************************************************************************************
*/
void M_Znajdz_droge(int** graf, int& kraw, int& wierzch, int& start, fstream& wyjscie)
{
    double czas_trwania;
    clock_t t_1;
    clock_t t_2;             

    int** tmp_graf;                     
    
    tmp_graf = new int *[wierzch];

    for(int v = 0; v < wierzch; ++v)
    {
        tmp_graf[v] = new int [wierzch];
    }
    
    M_Graf(kraw, wierzch, start, graf, tmp_graf);   
    t_1 = clock();                         


    M_Bellman_Ford(tmp_graf, kraw, wierzch, start); 
                                              

    t_2 = clock() - t_1;        

    for(int v = 0; v < wierzch; ++v) 
    {
        delete [] tmp_graf[v];
    }
    delete [] tmp_graf;

    czas_trwania = (double) (t_2) / CLOCKS_PER_SEC;       

    
    wyjscie << " dla macierzy: "<<czas_trwania<<endl;
}

/*
************************************************************************************************************
*                                   Znajdz_droge                                                           *
*   Funkcja szukająca drogi po na podstwie obu reprezentacji grafu                                         *
************************************************************************************************************
*/
void Znajdz_droge(ifstream& wejscie)
{
    fstream wyjscie;
    int wierzch;
    int kraw;
    int start;
    int** graf;

    wyjscie.open("Wynik.txt", ios_base::app);  
                                                
    for(int i = 0; i < 2000; i++)
    {

        wejscie >> kraw;
        wejscie >> wierzch;             
        wejscie >> start;

        graf = new int* [kraw];    

        for(int c = 0; c < kraw; c++)
        {
            graf[c] = new int [3];
        }

        Wczytaj_z_Pliku(graf, kraw, wierzch, start, wejscie);          
        L_Znajdz_droge(graf, kraw, wierzch, start, wyjscie);        
        M_Znajdz_droge(graf, kraw, wierzch, start, wyjscie);      

        for(int z = 0; z < kraw; ++z) 
        {
            delete [] graf[z];
        }
        delete [] graf;
    }
    wyjscie.close();   
}

/*
************************************************************************************************************
*                                  Zmierz                                                                  *
*   Funkcja mierzaca czas grafu wczytanego z pliku                                                         *
************************************************************************************************************
*/
void Zmierz(ifstream& strumien)
{
    strumien.open("Graf.txt", ios_base::in); 
                                             
    Znajdz_droge(strumien);          

    strumien.close();                       
}

/*
************************************************************************************************************
*                                           Stworz_i_Zmierz                                                         *
*   Funkcja mierzaca czas grafu wczytanego ze zmiennej                                                     *
************************************************************************************************************
*/
void Stworz_i_Zmierz(fstream &wyjscie)
{

    int wierzcholki[1] = {10};//, 50, 100, 500, 1000};  
    int gestosc[4] = {25, 50, 75, 100};         

    int max_krawedzi[5];                            
    int krawedzie[1][4];                            
     

    int** graf;

    wyjscie.open("Wynik_GenProg2.txt", ios_base::app);  
                                               

        for(int i = 0; i < 1; i++)
        {
            
            max_krawedzi[i] = wierzcholki[i] * (wierzcholki[i] - 1) /2;

           

            for(int j = 0; j < 4; j++)
            {
                
                krawedzie[i][j] = gestosc[j] * max_krawedzi[i] /100;
                
                
                for(int k = 0; k < 100; k++)
                {
                    cout<<krawedzie[i][j]<<"        "<<endl;
                    graf = new int* [krawedzie[i][j]];    
                    
                    for(int c = 0; c < krawedzie[i][j]; c++)
                    {
                        graf[c] = new int [3];
                    }
                    int start = rand()%wierzcholki[i];
                        

                    Zapisz_do_zm(krawedzie[i][j], wierzcholki[i], graf, start);
                   
                    L_Znajdz_droge(graf, krawedzie[i][j], wierzcholki[i], start, wyjscie);        
                    
                    M_Znajdz_droge(graf, krawedzie[i][j], wierzcholki[i], start, wyjscie);  
                    
                
                    for(int z = 0; z < krawedzie[i][j]; z++) 
                    {

                        delete [] graf[z];                   
                        
                    }
                    delete [] graf;                   
                }
            }
        }

    wyjscie.close();    

}

void Wyswietl_menu()
{
    cout<<"1. Wykonaj zadanie posługując się grafem wczytanym z pliku "<<endl;
    cout<<"2. Wykonaj zadanie posługując się danymi wygenerowanymi w programie"<<endl;
    cout<<"3. Zakończ działanie programu"<<endl;
}
