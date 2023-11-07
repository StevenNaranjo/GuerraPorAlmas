#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include "source.h"
using namespace std;
using namespace filesystem;



struct Persona {
    int id;
    int generacion;
    int cantidadAmigos;
    string nombre;
    string apellido;
    string pais;
    string creencia;
    string profesion;
    string fechaNacimiento;
    string estado;
    string demonio;
    string angel;
    string horaMuerte;
    ListaAmigos* amigos;
    int* redesSociales = new int[7]; //[Tinder, iFood, Twitter, Instagram, Facebook, linkedIn,Netflix]
    int* pecados = new int[7];       //[Lujuria, Gula, Ira,     Soberbia, Envidia,   Avaricia, Pereza]

    Persona() {
        id = 0;
        generacion = 0;
        cantidadAmigos = 0;
        nombre = "";
        apellido = "";
        pais = "";
        creencia = "";
        profesion = "";
        fechaNacimiento = "";
        estado = "";
        amigos = NULL;
    }
    void publicarEnRedSocial(int redSocial){
        string nombreRedes[] = {"Tinder", "iFood", "Twitter", "Instagram", "Facebook", "LinkedIn", "Netflix"};
        string pecados[] = {"Lujuria", "Gula", "Ira", "Soberbia", "Envidia", "Avaricia", "Pereza"};
        cout << "El humano: " << id << ". " << nombre << " " << apellido << " Ha hecho una nueva publicacion en: " << nombreRedes[redSocial]<< endl;
        cout <<" Fanastimo de: " << nombreRedes[redSocial] << " = " << obtenerFavoritismo(redSocial) << endl;
        ListaAmigos* aux = amigos;
        Nodo* auxAMIGO = aux->retornarPrimerNodo();
        //cout << aux->persona->nombre;

    }
    int obtenerFavoritismo(int redSocial){
        int favoritismo = 1;
        for(int i = 0; i < 7; i++){
            if(redesSociales[redSocial] > redesSociales[i]){
                favoritismo++;
            }
        }
        return favoritismo;
    }
    void imprimir() {
        if (this->id == 0) {
            cout << "No hay datos" << endl;
            return;
        } else {
            cout << "ID: " << id << endl;
            cout << "Generacion: " << generacion << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Apellido: " << apellido << endl;
            cout << "Pais: " << pais << endl;
            cout << "Creencia: " << creencia << endl;
            cout << "Profesion: " << profesion << endl;
            cout << "Fecha de Nacimiento: " << fechaNacimiento << endl;
            cout << "Estado: " << estado << endl;
        }
    }
};

void generarPersonas(int& totalPersonas, int& generacion, int personasAGenerar, Persona* personas, string* nombres, string* apellidos, string* paises, string* creencias, string* profesiones) {
    int totalNombres = 1468;
    int totalApellidos = 30;
    int totalProfesiones = 20;
    int totalCreencias = 10;
    int totalPaises = 15;

    // Asegurarse de que hay suficiente espacio en el arreglo personas

    random_device rd; // Genera una semilla pseudoaleatoria
    seed_seq seeder{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()}; // Secuencia de semilla basada en la semilla generada
    mt19937 rng(seeder); // Generador de números aleatorios
    srand(time(NULL));
    for (int i = 0; i < personasAGenerar; i++) {
        int index = totalPersonas + i; // Calcular el índice actual
        personas[index].id = index+1;
        personas[index].generacion = generacion;
        personas[index].cantidadAmigos = rand()%(100-0);
;
        personas[index].nombre = nombres[rng() % totalNombres];
        personas[index].apellido = apellidos[rng() % totalApellidos];
        personas[index].pais = paises[rng() % totalPaises];
        personas[index].creencia = creencias[rng() % totalCreencias];
        personas[index].profesion = profesiones[rng() % totalProfesiones];
        personas[index].fechaNacimiento = obtenerHoraActual();
        personas[index].estado = "Vivo";
        personas[index].amigos = NULL;
        for (int j = 0; j < 7; j++) {
            personas[index].redesSociales[j] = rand()%(100-0);
        }
        for (int j = 0; j < 7; j++) {
            personas[index].pecados[j] = 0;
        }
    }
    generacion++;
    totalPersonas += personasAGenerar; // Actualizar el contador totalPersonas
}