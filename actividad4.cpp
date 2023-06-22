#include <iostream>
using namespace std;

// Clase de excepción personalizada para diferencias distintas de cero
class NonZeroException {
public:
    int value;

    NonZeroException(int val) : value(val) {}

    const char* what() const {
        return "Error: Non-zero values.";
    }
};

// Función de suma genérica
template <typename Tipo>
Tipo suma(Tipo a, Tipo b) {
    if (a != b)
        throw NonZeroException(a);
    return a + b;
}

int main() {
    cout << "Iniciar try-catch" << endl;
    try {
        cout << "Se encuentra en el bloque try" << endl;
        cout << "1: " << suma(1, 3) << endl;
        cout << "2: " << suma(1, 1) << endl;
        cout << "3: " << suma(1.4, 1.2) << endl;
    } catch (const NonZeroException& e) {
        cout << e.what() << " Value: " << e.value << endl;
        // Realizar acciones correctivas, si es necesario
    } catch (...) {
        cout << "Se produjo un error desconocido." << endl;
    }
    
    return 0;
}

