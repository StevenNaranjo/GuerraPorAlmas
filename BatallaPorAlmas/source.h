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
string obtenerHoraActual();
string obtenerRuta(string nombreDirectorio);
string* cargarArchivo(int cantidadDatos, int& totalDatos, string nombreArchivo);
void generarPersonas(int& totalPersonas, int& generacion, int personasAGenerar, Persona* personas, string* nombres, string* apellidos, string* paises, string* creencias, string* profesiones);
void cargarAmigos(Persona* personas, int totalPersonas);

string obtenerHoraActual(){
    time_t tiempoActual = time(nullptr);
    struct tm *tiempo = localtime(&tiempoActual);

    int horas = tiempo->tm_hour;
    int minutos = tiempo->tm_min;
    int segundos = tiempo->tm_sec;
    int dia = tiempo->tm_mday;
    int mes = tiempo->tm_mon + 1; // Sumamos 1 para que el mes esté en el rango correcto (1-12)
    int anio = tiempo->tm_year + 1900; // Sumamos 1900 para obtener el año correcto

    // Formateamos la hora y la fecha para que tengan siempre dos dígitos
    string hora = (horas < 10 ? "0" : "") + to_string(horas);
    string minuto = (minutos < 10 ? "0" : "") + to_string(minutos);
    string segundo = (segundos < 10 ? "0" : "") + to_string(segundos);
    string fecha = (dia < 10 ? "0" : "") + to_string(dia) + "-" +
                    (mes < 10 ? "0" : "") + to_string(mes) + "-" +
                    std::to_string(anio);

    string horaActual = fecha + " " +hora + ":" + minuto + ":" + segundo + " " ;

    return horaActual;
}
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
    //cout << "Ruta del archivo: " << rutaCompleta << endl;

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
    ListaAmigos* amigos;

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
        amigos = nullptr;
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
    }
    generacion++;
    totalPersonas += personasAGenerar; // Actualizar el contador totalPersonas
}
// Define una estructura Nodo que contiene un puntero a Persona y un puntero al siguiente Nodo.
struct Nodo {
    Persona* persona;
    Nodo* siguiente;
};

// Define una estructura ListaAmigos que mantiene una lista de amigos para una persona.
struct ListaAmigos {
    Persona* persona;
    Nodo* amigo;

    ListaAmigos() {
        persona = nullptr;
        amigo = nullptr;
    }

    void agregar(Persona* persona) {
        Nodo* nuevo = new Nodo();
        nuevo->persona = persona;
        nuevo->siguiente = nullptr;

        if (amigo == nullptr) {
            amigo = nuevo;
        } else {
            Nodo* aux = amigo;
            while (aux->siguiente != nullptr) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevo;
        }
    }

    void imprimir() {
        if (amigo == nullptr) {
            cout << "No hay amigos" << endl;
            return;
        } else {
            Nodo* aux = amigo;
            while (aux != nullptr) {
                cout << aux->persona->id << ". " << aux->persona->nombre << " " << aux->persona->apellido << endl;
                aux = aux->siguiente;
            }
        }
    }
};

// Función para cargar amigos para cada persona en función de ciertas condiciones.
void cargarAmigos(Persona* personas, int totalPersonas, int& humanosConAmigos) {
    int index = humanosConAmigos;
    for (int i = index; i < totalPersonas; i++) {
        int totalAmigos = personas[i].cantidadAmigos;
        int j = 0;
        int contador = 0;
        humanosConAmigos ++;
        personas[i].amigos = new ListaAmigos();
        while (j < totalAmigos && contador < totalPersonas) {
            
            Persona persona = personas[contador];

            if (persona.id == personas[i].id) {
                //cout << "La persona no puede ser amiga de sí misma" << endl;
            } else if (persona.pais == personas[i].pais && (persona.apellido == personas[i].apellido || persona.profesion == personas[i].profesion || persona.creencia == personas[i].creencia)) {
                //cout << "La persona ha hecho un nuevo amigo/a" << endl;
                //cout << persona.id << ". " << persona.nombre << " " << persona.apellido << endl;
                personas[i].amigos->agregar(&personas[j]);
                //personas[i].amigos->imprimir();
                j++;
            }
            contador++;
        }
    }
}

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
