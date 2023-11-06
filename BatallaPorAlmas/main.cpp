#include "source.h"
#include <chrono>
int main() {
    auto tiempoInicio = std::chrono::high_resolution_clock::now();
    Mundo* world = new Mundo(100000);
    world->generarPersonasMundo(5000);
    world->cargarAmigosMundo();
    auto tiempoFin = std::chrono::high_resolution_clock::now();
    // Calcula la duración en milisegundos
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(tiempoFin - tiempoInicio);
    world->personas[1].amigos->imprimir();
    cout << world->personas[1].cantidadAmigos << endl;
    // Imprime la duración en milisegundos
    cout <<"\n"<< world->totalPersonas << endl;
    std::cout << "La función miFuncion() tardó " << duracion.count() << " milisegundos en ejecutarse." << std::endl;
    
    for(int i = 0; i < world->totalPersonas; i++){
        cout << world->personas[i].id << ". " << world->personas[i].nombre << endl;
    }
    for(int i = 0; i < 7; i++){
        cout << world->personas->redesSociales[i] << ", ";
    }
    cout << endl;
    
    world->personas[0].publicarEnRedSocial(0);
    //world->personas[0].publicarEnRedSocial(1);
    //world->imprimirPersonas();
    //world->generarPersonasMundo(100);
    //world->cargarAmigosMundo();
    //world->generarPersonasMundo(100);
    //world->cargarAmigosMundo(); 
    //world->imprimirPersonas();
    world->personas[0].amigos->imprimir();

    delete world;

    return 0;
}