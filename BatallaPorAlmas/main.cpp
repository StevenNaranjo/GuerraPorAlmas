#include "source.h"
#include <chrono>
int main() {
    int totalNombres;
    cout << "Nombres" << endl;
    string* nombres = cargarArchivo(1468, totalNombres, "/nombres.txt");

    for (int i = 0; i < totalNombres; i++) {
        cout << i+1 << ". "<< nombres[i] << endl;
    }
    cout << "APELLIDOS" << endl;
    int totalApellidos;
    string* apellidos = cargarArchivo(30, totalApellidos, "/apellidos.txt");

    for (int i = 0; i < totalApellidos; i++) {
        cout << i+1 << ". "<< apellidos[i] << endl;
    }
    cout << "Profesiones" << endl;
    int totalProfesiones;
    string* profesiones = cargarArchivo(20, totalProfesiones, "/profesiones.txt");
    for(int i = 0; i < totalProfesiones; i++){
        cout << i+1 << ". "<< profesiones[i] << endl;
    }
    cout << "Creencias" << endl;
    int totalCreencias;
    string* creencias = cargarArchivo(20, totalCreencias, "/creencias.txt");
    for(int i = 0; i < totalCreencias; i++){
        cout << i+1 << ". "<< creencias[i] << endl;
    }
    cout << "Paises" << endl;
    int totalPaises;
    string* paises = cargarArchivo(15,totalPaises, "/paises.txt");
    for (int i = 0; i < totalPaises; i++) {
        cout << i+1 << ". "<< paises[i] << endl;
    }
    int totalPersonas = 0;
    Persona* personas = new Persona[50000000];
    //generarPersonas(totalPersonas, 1, personas, nombres, apellidos, paises, creencias, profesiones);
    //for (int i = 0; i < totalPersonas; i++) {
    //    personas[i].imprimir();
    //    //cout << personas[i].id << "-> "<< personas[i].nombre << " " << personas[i].apellido << " " << personas[i].pais << endl;
    //}
    cout << "Prueba:" << endl;
    auto tiempoInicio = std::chrono::high_resolution_clock::now();
    generarPersonas(totalPersonas, 50000000, personas, nombres, apellidos, paises, creencias, profesiones);

    auto tiempoFin = std::chrono::high_resolution_clock::now();

    // Calcula la duración en milisegundos
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(tiempoFin - tiempoInicio);

    // Imprime la duración en milisegundos
    std::cout << "La función miFuncion() tardó " << duracion.count() << " milisegundos en ejecutarse." << std::endl;
        generarPersonas(totalPersonas, 1, personas, nombres, apellidos, paises, creencias, profesiones);
    //for (int i = 0; i < totalPersonas; i++) {
    //    personas[i].imprimir();
    //    //cout << personas[i].id << "-> "<< personas[i].nombre << " " << personas[i].apellido << " " << personas[i].pais << endl;
    //}
    return 0;
}