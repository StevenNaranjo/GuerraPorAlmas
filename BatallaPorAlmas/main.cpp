#include "source.h"

#include <chrono>
int main() {
    auto tiempoInicio = std::chrono::high_resolution_clock::now();
    Mundo* world = new Mundo(1000000);
    world->generarPersonasMundo(500);
    world->cargarAmigosMundo();
    auto tiempoFin = std::chrono::high_resolution_clock::now();
    // Calcula la duración en milisegundos
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(tiempoFin - tiempoInicio);
    world->personas[1].amigos->imprimir();
    cout << world->personas[1].cantidadAmigos << endl;
    // Imprime la duración en milisegundos
    cout <<"\n"<< world->totalPersonas << endl;
    std::cout << "La función miFuncion() tardó " << duracion.count() << " milisegundos en ejecutarse." << std::endl;
    world->generarPersonasMundo(500);
    world->cargarAmigosMundo();
    world->generarPersonasMundo(500);
    world->cargarAmigosMundo();
    for(int i = 0; i < world->totalPersonas; i++){
        cout << world->personas[i].id << ". " << world->personas[i].nombre << endl;
    }
    for(int i = 0; i < 7; i++){
        cout << world->personas->redesSociales[i] << ", ";
    }
    cout << endl;
    
    world->publicarEnRedSocial(0, world->personas[0]);
    world->publicarEnRedSocial(0, world->personas[0]);
    world->publicarEnRedSocial(0, world->personas[0]);
    cout << "------------------" << endl;
    world->publicarEnRedSocial(1, world->personas[1]);
    //world->personas[0].publicarEnRedSocial(1);
    //world->imprimirPersonas();
    //world->generarPersonasMundo(100);
    //world->cargarAmigosMundo();
    //world->generarPersonasMundo(100);
    //world->cargarAmigosMundo(); 
    //world->imprimirPersonas();
    world->personas[0].amigos->imprimir();
    cout << world->personas[0].cantidadAmigos << endl;
    cout << "_________________1_________" << endl;
    world->personas[1].amigos->imprimir();
    cout << world->personas[1].cantidadAmigos << endl;
    cout << "_________________2_________" << endl;
    world->personas[0].imprimir();
    world->publicarEnRedSocial(1, world->personas[1499]);
    int totalNodos = world->totalPersonas / 100 + 1; // 1% de totalPersonas + 1
    int niveles = calcularCantidadNiveles(totalNodos);
    TreeNode* root = construirABB(0, world->totalPersonas - 1, world->personas);
    cout << "_________________2_________" << endl;
    // Imprimir información del último nivel del árbol
    int* indices = new int[totalNodos];
    imprimirUltimoNivel(root, niveles - 1, 0, indices);
    buscarPersonaPorID(root, 5, world->personas)->imprimir();
    buscarPersonaPorID(root, 1000, world->personas)->imprimir();
    buscarPersonaPorID(root, 1500, world->personas)->imprimir();
    cout << buscarPersonaPorID(root, 1500, world->personas)->cantidadAmigos<<endl;
    buscarPersonaPorID(root, 1500, world->personas)->amigos->imprimir();
    cout << "_________________2_________" << endl;
    world->personas[1499].amigos->imprimir();
    cout << "_________________2_________" << endl;
    cout << world->totalPersonas << endl;
    world->publicarEnRedSocial(1, world->personas[1499]);
    world->personas[1499].amigos->imprimir();
    cout << world->personas[1499].cantidadAmigos << endl;
    world->personas[1499].imprimir();
    delete world;

    return 0;
}