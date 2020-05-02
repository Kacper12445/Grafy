#include "Grafy.cpp"



int main()
{
    char wybor;

    fstream Graf;
    ifstream wejscie;
    fstream pom;

    Wyswietl_menu();

    srand(time(NULL));      

    while(wybor != '3')
    {
        cin >> wybor;

        switch(wybor)
        {
            case '1':
            cout<<"Wybrales opcje nr.1"<<endl;
            Wez_dane(Graf);                         // Jesli pobrany został rowniez plik z danymi trzeba 
                                                    //zakomentować wywolanie tej funkcji aby nie tracic czasu na ponowne generowanie danych
            Zmierz(wejscie);
            
            cout<< "Koniec wykonywania, wybierz kolejną opcje"<<endl;
            Wyswietl_menu();
            break;

            case '2':
            cout<<"Wybrales opcje nr.2"<<endl;
            Stworz_i_Zmierz(pom);
            cout<< "Koniec wykonywania, wybierz kolejną opcje"<<endl;
            Wyswietl_menu();
            break;
            
            case '3':   
            cout<<"Wybrales wyjscie z programu"<<endl;
            break;

            default:
            cout<<"Nie ma takiej opcji"<<endl;
            
            break;          
        }
    }

    return 0;
}