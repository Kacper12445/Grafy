#include "Grafy.cpp"





int main()
{
    char wybor;

    fstream Graf;
    ifstream wejscie;
    fstream pom;


    srand(time(NULL));     
    Wyswietl_menu();

    while(wybor != '3')
    {
        cin >> wybor;

        switch(wybor)
        {
            case '1':
            cout<<"Wybrales opcje nr.1"<<endl;
            cout<< "Koniec wykonywania, wybierz kolejną opcje"<<endl;
            
            Zmierz(wejscie);
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