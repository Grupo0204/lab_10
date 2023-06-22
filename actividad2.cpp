

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


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
void registrarProducto(vector<Producto>& inventario) {
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
                return;
            } else {
                cout << "No hay suficiente cantidad disponible para vender." << endl;
                return;
            }
        }
    }


    cout << "Producto no encontrado." << endl;
}


// Función para generar un informe de inventario
void generarInforme(const vector<Producto>& inventario) {
    cout << "----- Informe de Inventario -----" << endl;


    for (const auto& producto : inventario) {
        cout << "Nombre: " << producto.nombre << endl;
        cout << "Precio: " << producto.precio << endl;
        cout << "Cantidad disponible: " << producto.cantidad << endl;
        cout << "-------------------------------" << endl;
    }
}


int main() {
    vector<Producto> inventario;


    // Cargar el inventario desde el archivo secuencial (si existe)
    ifstream archivoInventario("inventario.txt");
    if (archivoInventario.is_open()) {
        string nombre;
        float precio;
        int cantidad;
        
        while (archivoInventario >> nombre >> precio >> cantidad) {
            Producto producto(nombre, precio, cantidad);
            inventario.push_back(producto);
        }
        archivoInventario.close();
        cout << "Inventario cargado exitosamente." << endl;
    } else {
        cout << "No se encontró el archivo de inventario. Se creará uno nuevo." << endl;
    }


    int opcion;


    do {
        cout << "----- Menú Principal -----" << endl;
        cout << "1. Registrar un nuevo producto" << endl;
        cout << "2. Actualizar información de un producto" << endl;
        cout << "3. Realizar una venta" << endl;
        cout << "4. Generar informe de inventario" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;


        switch (opcion) {
            case 1:
                registrarProducto(inventario);
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
                ofstream archivoInventario("inventario.txt", ios::out | ios::trunc);
                if (archivoInventario.is_open()) {
                    for (const auto& producto : inventario) {
                        archivoInventario << producto.nombre << " "
                                          << producto.precio << " "
                                          << producto.cantidad << endl;
                    }
                    archivoInventario.close();
                    cout << "Inventario guardado exitosamente." << endl;
                } else {
                    cout << "No se pudo abrir el archivo de inventario." << endl;
                }
                cout << "¡Hasta luego!" << endl;
                break;
            }
        }
    } while (opcion != 5);


    return 0;
}

