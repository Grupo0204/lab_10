#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>


using namespace std;


// Definición de la estructura de datos para el producto
class Producto {
public:
    string nombre;
    float precio;
    int cantidad;


    Producto() {}


    Producto(const string& nombre, float precio, int cantidad) {
        this->nombre = nombre;
        this->precio = precio;
        this->cantidad = cantidad;
    }
};


// Función para registrar un nuevo producto en el inventario
void registrarProducto(vector<Producto>& inventario, unordered_map<string, int>& indice, ofstream& archivoRegistros) {
    string nombre;
    float precio;
    int cantidad;


    cout << "Ingrese el nombre del producto: ";
    cin >> nombre;
    cout << "Ingrese el precio del producto: ";
    cin >> precio;
    cout << "Ingrese la cantidad disponible del producto: ";
    cin >> cantidad;


    Producto nuevoProducto(nombre, precio, cantidad);
    inventario.push_back(nuevoProducto);


    // Guardar el nuevo producto en el archivo de registros
    archivoRegistros << nombre << "," << inventario.size() - 1 << endl;


    // Actualizar el índice
    indice[nombre] = inventario.size() - 1;


    cout << "Producto registrado exitosamente." << endl;
}


// Función para actualizar la información de un producto existente en el inventario
void actualizarProducto(vector<Producto>& inventario) {
    string nombre;
    int opcion;


    cout << "Ingrese el nombre del producto a actualizar: ";
    cin >> nombre;


    // Buscar el producto por nombre en el inventario
    for (int i = 0; i < inventario.size(); i++) {
        if (inventario[i].nombre == nombre) {
            cout << "Producto encontrado." << endl;
            cout << "Seleccione la información que desea actualizar:" << endl;
            cout << "1. Precio" << endl;
            cout << "2. Cantidad" << endl;
            cin >> opcion;


            switch (opcion) {
                case 1:
                    cout << "Ingrese el nuevo precio: ";
                    cin >> inventario[i].precio;
                    cout << "Precio actualizado exitosamente." << endl;
                    break;
                case 2:
                    cout << "Ingrese la nueva cantidad disponible: ";
                    cin >> inventario[i].cantidad;
                    cout << "Cantidad actualizada exitosamente." << endl;
                    break;
                default:
                    cout << "Opción inválida." << endl;
                    break;
            }


            return;
        }
    }


    cout << "Producto no encontrado." << endl;
}


// Función para realizar una venta de un producto
void realizarVenta(vector<Producto>& inventario) {
    string nombre;


    cout << "Ingrese el nombre del producto a vender: ";
    cin >> nombre;


    // Buscar el producto por nombre en el inventario
    for (int i = 0; i < inventario.size(); i++) {
        if (inventario[i].nombre == nombre) {
            if (inventario[i].cantidad > 0) {
                inventario[i].cantidad--;
                cout << "Venta realizada exitosamente." << endl;
            } else {
                cout << "No hay suficiente stock del producto." << endl;
            }
            return;
        }
    }


    cout << "Producto no encontrado." << endl;
}


// Función para generar el informe de inventario
void generarInforme(const vector<Producto>& inventario) {
    cout << "----- Informe de Inventario -----" << endl;


    for (const auto& producto : inventario) {
        cout << "Nombre: " << producto.nombre << endl;
        cout << "Precio: " << producto.precio << endl;
        cout << "Cantidad disponible: " << producto.cantidad << endl;
        cout << "-------------------------------" << endl;
    }
}


// Función para buscar un producto por nombre utilizando el índice
void buscarProducto(const unordered_map<string, int>& indice, const vector<Producto>& inventario, const string& nombre) {
    auto it = indice.find(nombre);
    if (it != indice.end()) {
        int indiceRegistro = it->second;
        const Producto& producto = inventario[indiceRegistro];


        cout << "Nombre: " << producto.nombre << endl;
        cout << "Precio: " << producto.precio << endl;
        cout << "Cantidad disponible: " << producto.cantidad << endl;
    } else {
        cout << "Producto no encontrado." << endl;
    }
}


int main() {
    vector<Producto> inventario;
    unordered_map<string, int> indice;


    // Cargar el inventario y el índice desde el archivo
    ifstream archivoRegistros("registros.csv");
    if (archivoRegistros.is_open()) {
        string linea;


        while (getline(archivoRegistros, linea)) {
            stringstream ss(linea);
            string nombre;
            string ubicacion;


            getline(ss, nombre, ',');
            getline(ss, ubicacion, ',');


            int indiceRegistro = stoi(ubicacion);


            Producto producto(nombre, 0.0f, 0);  // Precio y cantidad se actualizarán posteriormente


            // Agregar el producto al índice
            indice[nombre] = indiceRegistro;


            // Agregar el producto al inventario (solo se almacena la referencia en el índice)
            inventario.push_back(producto);
        }


        archivoRegistros.close();
    } else {
        cout << "No se encontró el archivo de registros. Se creará uno nuevo." << endl;
    }


    int opcion;


    do {
        cout << "----- Menú Principal -----" << endl;
        cout << "1. Registrar un nuevo producto" << endl;
        cout << "2. Actualizar información de un producto" << endl;
        cout << "3. Realizar una venta" << endl;
        cout << "4. Generar informe de inventario" << endl;
        cout << "5. Buscar un producto" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;


        switch (opcion) {
            case 1:
                {
                    ofstream archivoRegistros("registros.csv", ios::out | ios::app);
                    if (archivoRegistros.is_open()) {
                        registrarProducto(inventario, indice, archivoRegistros);
                        archivoRegistros.close();
                    } else {
                        cout << "No se pudo abrir el archivo de registros." << endl;
                    }
                }
                break;
            case 2:
                actualizarProducto(inventario);
                break;
            case 3:
                realizarVenta(inventario);
                break;
            case 4:
                generarInforme(inventario);
                break;
            case 5:
                {
                    string nombre;
                    cout << "Ingrese el nombre del producto a buscar: ";
                    cin >> nombre;
                    buscarProducto(indice, inventario, nombre);
                }
                break;
            case 6:
                {
                    ofstream archivoRegistros("registros.csv", ios::out | ios::trunc);
                    if (archivoRegistros.is_open()) {
                        for (const auto& producto : inventario) {
                            archivoRegistros << producto.nombre << "," << indice[producto.nombre] << endl;
                        }
                        archivoRegistros.close();
                        cout << "Registros guardados exitosamente." << endl;
                    } else {
                        cout << "No se pudo abrir el archivo de registros." << endl;
                    }
                }
                cout << "¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción inválida." << endl;
                break;
        }
    } while (opcion != 6);


    return 0;
}


