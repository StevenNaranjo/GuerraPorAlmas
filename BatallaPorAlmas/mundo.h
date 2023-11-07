
#include "persona.h"


struct Mundo{
    Persona* personas;
    int totalPersonas;
    int generacion;
    int humanosConAmigos;
    int totalNombres;
    int totalApellidos;
    int totalProfesiones;
    int totalCreencias;
    int totalPaises;
    string* nombres;
    string* apellidos;
    string* paises;
    string* creencias;
    string* profesiones;
    Mundo(int tamañoMundo){
        totalPersonas = 0;  // Asegúrate de que totalPersonas se inicie en 0
        generacion = 0;
        humanosConAmigos = 0;
        personas = new Persona[tamañoMundo];
        nombres = cargarArchivo(1468, totalNombres, "/nombres.txt");
        apellidos = cargarArchivo(30, totalApellidos, "/apellidos.txt");
        paises = cargarArchivo(15, totalPaises, "/paises.txt");
        creencias = cargarArchivo(10, totalCreencias, "/creencias.txt");
        profesiones = cargarArchivo(20, totalProfesiones, "/profesiones.txt");
    }
    void generarPersonasMundo(int personasAGenerar){
        generarPersonas(totalPersonas, generacion, personasAGenerar, personas, nombres, apellidos, paises, creencias, profesiones);
    }
    void cargarAmigosMundo(){
        cargarAmigos(personas, totalPersonas, humanosConAmigos);
    }
    void imprimirPersonas(){
        for (int i = 0; i < totalPersonas; i++) {
            personas[i].imprimir();
        }
    }
};