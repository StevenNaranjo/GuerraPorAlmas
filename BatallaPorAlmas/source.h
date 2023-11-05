#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem> 
#include <stdlib.h>
#include <time.h>

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

string* cargarNombres(int cantidadNombres,int& totalNombres, string nombreArchivo) {
    string rutaCarpeta = obtenerRuta("Datos");
    string rutaCompleta = rutaCarpeta + nombreArchivo;
    cout << rutaCompleta << endl;
    const int capacidad = cantidadNombres;
    string* nombres = new string[capacidad];
    ifstream archivo(rutaCompleta);
    totalNombres = 0;

    if (archivo.is_open()) {
        while (totalNombres < capacidad && archivo >> nombres[totalNombres]) {
            totalNombres++;
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << std::endl;
    }

    return nombres;
}

string* cargarApellidos(int cantidadApellidos, int& totalApellidos, string nombreArchivo) {
    string rutaCarpeta = obtenerRuta("Datos");
    string rutaCompleta = rutaCarpeta + nombreArchivo;
    cout << rutaCompleta << endl;
    const int capacidad = cantidadApellidos;
    string* apellidos = new string[capacidad];
    ifstream archivo(rutaCompleta);
    totalApellidos = 0;

    if (archivo.is_open()) {
        while (totalApellidos < capacidad && archivo >> apellidos[totalApellidos]) {
            totalApellidos++;
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << std::endl;
    }

    return apellidos;
}
string* cargarPaises(int cantidadPaises, int& totalPaises, string nombreArchivo) {
    string rutaCarpeta = obtenerRuta("Datos");
    string rutaCompleta = rutaCarpeta + nombreArchivo;
    cout << rutaCompleta << endl;
    const int capacidad = cantidadPaises;
    string* paises = new string[capacidad];
    ifstream archivo(rutaCompleta);
    totalPaises = 0;

    if (archivo.is_open()) {
        while (totalPaises < capacidad && getline(archivo, paises[totalPaises])) {
            totalPaises++;
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << std::endl;
    }

    return paises;
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
    string Profesion;
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
        Profesion = "";
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
        cout << "Profesion: " << Profesion << endl;
        cout << "Fecha de Nacimiento: " << fechaNaciemiento << endl;
        cout << "Estado: " << estado << endl;
    }
};

void generarPersonas(int& totalPersonas, int personasAGenerar, Persona* personas, string* nombres, string* apellidos, string* paises) {
    srand(time(NULL));
    for (int i = 0; i < personasAGenerar; i++) {
        Persona persona;
        persona.id = i + 1;
        persona.nombre = nombres[rand() % 1468];
        persona.apellido = apellidos[rand() % 30];
        persona.pais = paises[rand() % 15];
        persona.creencia = "Catolico";
        persona.Profesion = "Ingeniero";
        persona.fechaNaciemiento = "01/01/2000";
        persona.estado = "Vivo";
        personas[i] = persona;
        totalPersonas++;
    }
}

