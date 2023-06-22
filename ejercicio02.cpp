#include <iostream>
#include <stdexcept>
using namespace std;

int divide(int num1, int num2) {
    if (num2 == 0) {
        throw runtime_error("No se puede dividir por cero.");
    }
    return num1 / num2;
}


int main() {
    int num1, num2;
    
    // Llamada a la función "divide" y manejo de excepciones
    try {
        num1 = 10;
        num2 = 2;
        int result = divide(num1, num2);
        cout << num1 << " / " << num2 << " = " << result << endl;
        num1 = 8;
        num2 = 0;
        result = divide(num1, num2);
        cout << num1 << " / " << num2 << " = " << result << endl; // Esta línea no se ejecutará debido a la excepción
    } catch (const runtime_error& error) {
        cout << "Error: " << error.what() << endl;
    }
    
    return 0;
}
