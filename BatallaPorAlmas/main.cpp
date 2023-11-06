#include "source.h"
#include <chrono>
int main() {
    auto tiempoInicio = std::chrono::high_resolution_clock::now();
    Mundo* world = new Mundo(100000);
    world->generarPersonasMundo(1000);
    world->cargarAmigosMundo();
    auto tiempoFin = std::chrono::high_resolution_clock::now();
    // Calcula la duración en milisegundos
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(tiempoFin - tiempoInicio);
    world->personas[1].amigos->imprimir();
    cout << world->personas[1].cantidadAmigos << endl;
    for(int i = 0; i <7; i++ )
    {
        cout << *world->personas[i].redesSociales << ", ";
    }
    for(int i = 0; i <7; i++ )
    {
        cout << *world->personas[i].pecados << ", ";
    }
    // Imprime la duración en milisegundos
    cout <<"\n"<< world->totalPersonas << endl;
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