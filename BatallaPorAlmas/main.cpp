#include "source.h"
#include <chrono>
int main() {
    auto tiempoInicio = std::chrono::high_resolution_clock::now();
    Mundo* world = new Mundo(100000);
    world->generarPersonasMundo(100000);
    world->cargarAmigosMundo();
    auto tiempoFin = std::chrono::high_resolution_clock::now();
    // Calcula la duración en milisegundos
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(tiempoFin - tiempoInicio);
    world->personas[1].amigos->imprimir();
    cout << world->personas[1].cantidadAmigos << endl;
    // Imprime la duración en milisegundos
    cout << world->totalPersonas << endl;
    std::cout << "La función miFuncion() tardó " << duracion.count() << " milisegundos en ejecutarse." << std::endl;

    //world->imprimirPersonas();
    //world->generarPersonasMundo(100);
    //world->cargarAmigosMundo();
    //world->generarPersonasMundo(100);
    //world->cargarAmigosMundo(); 
    //world->imprimirPersonas();

    delete world;

    return 0;
}