#include "source.h"

int main() {
    int totalNombres;
    cout << "Nombres" << endl;
    string* nombres = cargarNombres(1468, totalNombres, "/nombres.txt");

    for (int i = 0; i < totalNombres; i++) {
        cout << i+1 << ". "<< nombres[i] << endl;
    }
    cout << "APELLIDOS" << endl;
    int totalApellidos;
    string* apellidos = cargarApellidos(30, totalApellidos, "/apellidos.txt");

    for (int i = 0; i < totalApellidos; i++) {
        cout << i+1 << ". "<< apellidos[i] << endl;
    }
    cout << apellidos[10] << endl;
    cout << "Paises" << endl;
    int totalPaises;
    string* paises = cargarPaises(15,totalPaises, "/paises.txt");
    for (int i = 0; i < totalPaises; i++) {
        cout << i+1 << ". "<< paises[i] << endl;
    }
    int totalPersonas = 0;
    Persona* personas = new Persona[10000000];
    generarPersonas(totalPersonas, 10000000, personas, nombres, apellidos, paises);
    for (int i = 0; i < totalPersonas; i++) {
        cout << personas[i].id << "-> "<< personas[i].nombre << " " << personas[i].apellido << " " << personas[i].pais << endl;
    }
    return 0;
}