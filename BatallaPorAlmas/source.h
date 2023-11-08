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
#include <queue>
#include <thread>
#include <chrono>

using namespace std;
using namespace filesystem;
struct Persona;
struct ListaAmigos;
struct Nodo;
struct Mundo;
struct Demonio;
struct Heap;
struct NodoHeap;
struct ListaHeaps;


string obtenerHoraActual();
string obtenerRuta(string nombreDirectorio);
string* cargarArchivo(int cantidadDatos, int& totalDatos, string nombreArchivo);
void generarPersonas(int& totalPersonas, int& generacion, int personasAGenerar, Persona* personas, string* nombres, string* apellidos, string* paises, string* creencias, string* profesiones);
void cargarAmigos(Persona* personas, int totalPersonas);

string obtenerHoraActual(){
    time_t tiempoActual = time(NULL);
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
    string demonio;
    string angel;
    string horaMuerte;
    ListaAmigos* amigos;
    int* redesSociales; //[Tinder, iFood, Twitter, Instagram, Facebook, linkedIn,Netflix]
    int* pecados;       //[Lujuria, Gula, Ira,     Soberbia, Envidia,   Avaricia, Pereza]

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
        redesSociales = new int[7]; //[Tinder, iFood, Twitter, Instagram, Facebook, linkedIn,Netflix]
        pecados = new int[7];  
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
        persona = NULL;
        amigo = NULL;
    }

    void agregar(Persona* persona) {
        Nodo* nuevo = new Nodo();
        nuevo->persona = persona;
        nuevo->siguiente = NULL;

        if (amigo == NULL) {
            amigo = nuevo;
        } else {
            Nodo* aux = amigo;
            while (aux->siguiente != NULL) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevo;
        }
    }

    void imprimir() {
        if (amigo == NULL) {
            cout << "No hay amigos" << endl;
            return;
        } else {
            Nodo* aux = amigo;
            while (aux != NULL) {
                cout << aux->persona->id << ". " << aux->persona->nombre << " " << aux->persona->apellido << endl;
                aux = aux->siguiente;
            }
        }
    }
};
void cargarAmigos(Persona* personas, int totalPersonas, int& humanosConAmigos) {
    int index = humanosConAmigos;
    //cout << humanosConAmigos<<index << endl;
    for (int i = 0; i < totalPersonas; i++) {
        if (personas[i].amigos != NULL) {
            // Si la persona ya tiene amigos, omitir esta iteración.
            continue;
        }

        int totalAmigos = personas[i].cantidadAmigos;
        int amigosAgregados = 0; // Contador de amigos agregados

        personas[i].amigos = new ListaAmigos();

        for (int j = index; j < totalPersonas && amigosAgregados < totalAmigos; j++) {
            
            if(personas[i].id == personas[j].id){
                continue;
            }
            // Comprueba si esta persona es elegible para ser amiga de la persona actual
            if (personas[i].pais == personas[j].pais &&
                (personas[i].apellido == personas[j].apellido || personas[i].profesion == personas[j].profesion || personas[i].creencia == personas[j].creencia)) {
                // Agregar esta persona como amiga
                personas[i].amigos->agregar(&personas[j]);
                amigosAgregados++;
            }
        }
        humanosConAmigos++;
    }
}
struct TreeNode {
    Persona* persona;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Persona* p) : persona(p), left(nullptr), right(nullptr) {}
};

TreeNode* construirABB(int left, int right, Persona* personas) {
    if (left > right) return nullptr;

    int mid = (left + right) / 2;
    TreeNode* node = new TreeNode(&personas[mid]);
    node->left = construirABB(left, mid - 1, personas);
    node->right = construirABB(mid + 1, right, personas);

    return node;
}

int calcularCantidadNiveles(int totalNodos) {
    int niveles = 0;
    int potencia = 1;
    while (potencia < totalNodos) {
        potencia *= 2;
        niveles++;
    }
    return niveles;
}

void imprimirUltimoNivel(TreeNode* root, int nivel, int nivelActual, int* indices) {
    if (!root) return;

    if (nivelActual == nivel) {
        // Imprimir información de la persona
        cout << "ID: " << root->persona->id << " Nombre: " << root->persona->nombre << " Apellido: " << root->persona->apellido << endl;
    }

    imprimirUltimoNivel(root->left, nivel, nivelActual + 1, indices);
    imprimirUltimoNivel(root->right, nivel, nivelActual + 1, indices);
}
Persona* buscarPersonaPorID(TreeNode* root, int targetID, Persona* personas) {
    TreeNode* current = root;
    while (current != nullptr) {
        int currentID = current->persona->id;
        if (currentID == targetID) {
            return current->persona;
        } else if (currentID > targetID) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr; // La persona no se encontró en el árbol.
}

struct Heap {
    int capacidad;
    int tamano;
    int pecadoCapital;
    vector<Persona*> personas; // Usamos punteros a Persona

    Heap(int pecado, int capacidad) {
        this->capacidad = capacidad;
        tamano = 0;
        pecadoCapital = pecado;
        personas.resize(capacidad, nullptr); // Resize el vector a la capacidad dada
    }

void insertar(Persona* persona) {
    if (tamano == capacidad) {
        cout << "El heap está lleno." << endl;
        return;
    }

    int indice = tamano;
    personas[tamano++] = persona;

    // Mantener la propiedad de max-heap
    while (indice > 0) {
        int padre = (indice - 1) / 2;
        if (personas[indice]->pecados[pecadoCapital] > personas[padre]->pecados[pecadoCapital]) {
            // Intercambiar con el padre si el pecado es mayor
            swap(personas[indice], personas[padre]);
            indice = padre;
        } else {
            break;
        }
    }
}

    void imprimirHeap() {
        if (tamano == 0) {
            cout << "El heap está vacío." << endl;
            return;
        }
        for (int i = 0; i < tamano; i++) {
            cout << "Persona " << personas[i]->id << ": ";
            cout << personas[i]->nombre << " " << personas[i]->apellido << endl;
            cout << personas[i]->pecados[pecadoCapital] << endl;
        }
    }
};
struct NodoHeap {
    string apellido;
    string pais;
    Heap* heap;
    NodoHeap* siguiente;

    NodoHeap(Heap* h, string apelidoFamilia, string paisFamilia){
        heap = h;
        apellido = apelidoFamilia;
        pais = paisFamilia;
        siguiente = nullptr;
    }
};

struct ListaHeaps {
    NodoHeap* heap;

    ListaHeaps() : heap(nullptr) {}

    void agregar(Heap* heap, string apellido, string pais) {
        NodoHeap* nuevo = new NodoHeap(heap,apellido,pais);

        if (this->heap == nullptr) {
            this->heap = nuevo;
        } else {
            NodoHeap* aux = this->heap;
            while (aux->siguiente != nullptr) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevo;
        }
    }
};
struct Demonio {
    string nombre;
    int pecadoCapital; // Un valor entre 0 y 6 para los 7 pecados capitales
    int totalPersonas;
    Persona* personas;
    ListaHeaps* familias; // Lista simple de familias relacionadas con este demonio
    Demonio(){
        nombre = "";
        pecadoCapital = 0;
        totalPersonas = 0;
        personas = nullptr;
        familias = nullptr;
    }
    Demonio(string nombre,int pecado, Persona* personas, int totalPersonas){
        this->nombre = nombre;
        this->totalPersonas = totalPersonas;
        pecadoCapital = pecado;
        this->personas = personas;
        familias = new ListaHeaps();
    }
    NodoHeap* encontrarFamilia(string apellido, string pais) {
        NodoHeap* familia = familias->heap;
        
        while (familia != nullptr) {
            if (familia->apellido == apellido && familia->pais == pais) {
                return familia;
            }
            familia = familia->siguiente;
        }
        
        return nullptr; // No se encontró la familia
    }
void imprimirHeaps() {
    cout << "Demonio: " << nombre << " (Pecado Capital: " << pecadoCapital << ")" << endl;

    NodoHeap* familia = familias->heap;
    while (familia != nullptr) {
        cout << "Familia: " << familia->apellido << " (País: " << familia->pais << ")" << endl;
        familia->heap->imprimirHeap();
        cout << "-------------------------------------" << endl;
        familia = familia->siguiente;
    }

    if (!familias->heap) {
        // Comentario de depuración en caso de que no haya familias
        cout << "No hay familias para mostrar. Motivo: No se ha condenado a nadie." << endl;
    }

    cout << "=====================================" << endl;
}
};







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
    int cantidadEnArbol = totalPersonas * 0.01;
    Demonio** demonios;
    string* nombres;
    string* apellidos;
    string* paises;
    string* creencias;
    string* profesiones;

// Calcular la cantidad de niveles necesarios

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
        demonios = new Demonio*[7]; // Reservamos espacio para 7 demonios
        demonios[0] = new Demonio("Asmodeo", 0, personas,totalPersonas);
        demonios[1] = new Demonio("Belfegor", 1, personas,totalPersonas);
        demonios[2] = new Demonio("Satán", 2, personas,totalPersonas);
        demonios[3] = new Demonio("Lucifer", 3, personas,totalPersonas);
        demonios[4] = new Demonio("Belcebu", 4, personas,totalPersonas);
        demonios[5] = new Demonio("Mammon", 5, personas,totalPersonas);
        demonios[6] = new Demonio("Abadon", 6, personas,totalPersonas);    
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
    void publicarEnRedSocial(int redSocial, Persona persona){
        string nombreRedes[] = {"Tinder", "iFood", "Twitter", "Instagram", "Facebook", "LinkedIn", "Netflix"};
        string pecados[] = {"Lujuria", "Gula", "Ira", "Soberbia", "Envidia", "Avaricia", "Pereza"};
        cout << "El humano: " << persona.id << ". " << persona.nombre << " " << persona.apellido << " Ha hecho una nueva publicacion en: " << nombreRedes[redSocial]<< endl;
        cout <<" Fanastimo de: " << nombreRedes[redSocial] << " = " << persona.obtenerFavoritismo(redSocial) << endl;
        Nodo * aux = persona.amigos->amigo;
        while(aux != NULL){
            aux->persona->pecados[redSocial] += aux->persona->obtenerFavoritismo(redSocial);
            cout << "El humano: " << aux->persona->id << ". " << aux->persona->nombre << " " << aux->persona->apellido << " Ha obtenido un nuevo pecado: " << pecados[redSocial] << endl;
            for(int i = 0;i<7; i++){
                cout << " " << pecados[i] << ": " << aux->persona->pecados[i];
            }
            cout << endl;
            aux = aux->siguiente;
        }
    }
    void condenacion(Demonio* demonio, Persona* personas, int totalPersonas) {
    // Crear un heap de máximos para ordenar a las personas por su pecado capital
    Heap maxHeap(demonio->pecadoCapital, totalPersonas);

    // Insertar todas las personas en el heap
    for (int i = 0; i < totalPersonas; i++) {
        maxHeap.insertar(&personas[i]);
    }

    // Calcular el número de personas a condenar (el 5% del total de humanos)
    int numPersonasCondenadas = totalPersonas * 0.05;

    // Crear una lista de las personas condenadas
    ListaHeaps* condenados = new ListaHeaps();

    // Extraer las personas más pecadoras del heap y agregarlas a la lista de condenados
    for (int i = 0; i < numPersonasCondenadas; i++) {
        Persona* personaCondenada = maxHeap.personas[0];
        maxHeap.personas[0] = maxHeap.personas[maxHeap.tamano - 1];
        maxHeap.tamano--;

        // Actualizar el estado, hora de muerte y demonio de la persona condenada
        personaCondenada->estado = "Condenado";
        personaCondenada->horaMuerte = obtenerHoraActual();
        personaCondenada->demonio = demonio->nombre;

        // Encontrar o crear la familia correspondiente a la persona condenada
        NodoHeap* familia = demonio->encontrarFamilia(personaCondenada->apellido, personaCondenada->pais);
        if (familia == nullptr) {
            Heap* nuevoHeap = new Heap(demonio->pecadoCapital, totalPersonas);
            demonio->familias->agregar(nuevoHeap, personaCondenada->apellido, personaCondenada->pais);
            familia = demonio->encontrarFamilia(personaCondenada->apellido, personaCondenada->pais);
        }

        // Insertar la persona condenada en la familia correspondiente
        familia->heap->insertar(personaCondenada);
    }

    // Imprimir las familias y los condenados correspondientes al demonio
    demonio->imprimirHeaps();
}
};



