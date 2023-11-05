#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <filesystem> 
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;
using namespace filesystem;
struct Persona;
struct ListaAmigos;
struct ListaPecados;


string obtenerRuta(string nombreDirectorio) {
    // Usar current_path desde el espacio de nombres std::filesystem
    string DirActual = current_path();
    int final = DirActual.find_last_of("/");
    string DirNuevo = DirActual.substr(0, final);
    DirNuevo = DirNuevo + "/" + nombreDirectorio;
    return DirNuevo;
}

string* cargarArchivo(int cantidadDatos, int& totalDatos, string nombreArchivo) {
    // Se obtiene la ruta de la carpeta llamada "Datos".
    string rutaCarpeta = obtenerRuta("Datos");
    
    // Se construye la ruta completa del archivo a partir de la carpeta y el nombre del archivo.
    string rutaCompleta = rutaCarpeta + nombreArchivo;
    
    // Se imprime la ruta completa del archivo en la consola.
    cout << "Ruta del archivo: " << rutaCompleta << endl;

    // Se define la capacidad máxima del arreglo basada en cantidadDatos.
    const int capacidad = cantidadDatos;
    
    // Se crea un arreglo dinámico de strings con la capacidad especificada.
    string* array = new string[capacidad];
    
    // Se abre el archivo ubicado en la ruta completa.
    ifstream archivo(rutaCompleta);
    
    // Se inicializa el contador totalDatos a 0 para hacer seguimiento de la cantidad de datos cargados.
    totalDatos = 0;

    // Comprueba si el archivo se ha abierto correctamente.
    if (archivo.is_open()) {
        // Utiliza un bucle para leer líneas del archivo y almacenarlas en el arreglo.
        while (totalDatos < capacidad && getline(archivo, array[totalDatos])) {
            totalDatos++;
        }
        archivo.close();// Cierra el archivo después de leer todos los datos.
    } else {// Si el archivo no se puede abrir, se imprime un mensaje de error en la consola.
        cerr << "No se pudo abrir el archivo." << std::endl;
    }
    return array;  // Devuelve el puntero al arreglo dinámico que contiene los datos cargados desde el archivo.
}

/*
struct Nodo{
    Persona persona;
    Nodo* siguiente;
};
*/

struct ListaPecados {
    ListaPecados() {
        cout << "Esto es una lista simple de pecados" << endl;
    }
};

struct ListaAmigos {
    ListaAmigos() {
        cout << "Esto es una lista simple de amigos" << endl;
    }
};

//array estatico de pecados
struct Persona{
    int id;
    int generacion;
    string nombre;
    string apellido;
    string pais;
    string creencia;
    string profesion;
    string fechaNaciemiento;
    string estado;
    //ListaAmigos amigos;
    //ListaPecados pecados;
    Persona() {
        id = 0;
        generacion = 0;
        nombre = "";
        apellido = "";
        pais = "";
        creencia = "";
        profesion = "";
        fechaNaciemiento = "";
        estado = "";
    }
    void imprimir(){
        cout << "ID: " << id << endl;
        cout << "Generacion: " << generacion << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Apellido: " << apellido << endl;
        cout << "Pais: " << pais << endl;
        cout << "Creencia: " << creencia << endl;
        cout << "Profesion: " << profesion << endl;
        cout << "Fecha de Nacimiento: " << fechaNaciemiento << endl;
        cout << "Estado: " << estado << endl;
    }
};

void generarPersonas(int& totalPersonas, int personasAGenerar, Persona* personas, string* nombres, string* apellidos, string* paises, string* creencias, string* profesiones) {
    int totalNombres = 1468;
    int totalApellidos = 30;
    int totalProfesiones = 20;
    int totalCreencias = 10;
    int totalPaises = 15;

    // Asegurarse de que hay suficiente espacio en el arreglo personas

    random_device rd; // Genera una semilla pseudoaleatoria
    seed_seq seeder{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()}; // Secuencia de semilla basada en la semilla generada
    mt19937 rng(seeder); // Generador de números aleatorios

    for (int i = 0; i < personasAGenerar; i++) {
        int index = totalPersonas + i; // Calcular el índice actual

        personas[index].id = index + 1;
        personas[index].generacion = 1;
        personas[index].nombre = nombres[rng() % totalNombres];
        personas[index].apellido = apellidos[rng() % totalApellidos];
        personas[index].pais = paises[rng() % totalPaises];
        personas[index].creencia = creencias[rng() % totalCreencias];
        personas[index].profesion = profesiones[rng() % totalProfesiones];
        personas[index].fechaNaciemiento = "01/01/2000";
        personas[index].estado = "Vivo";
    }
    totalPersonas += personasAGenerar; // Actualizar el contador totalPersonas
}



