#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() 
{
    string nombreArchivo;
    cout<<"Ingrese el nombre del archivo: ";
    cin>>nombreArchivo;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) 
    {
        string linea;
        while (getline(archivo, linea)) 
        {
            cout<<linea<<endl;
        }
        archivo.close();
    } 
    else 
    {
        cout<<"No se pudo abrir el archivo"<<endl;
    }
    return 0;
}


