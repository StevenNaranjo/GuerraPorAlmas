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
#define pow2(n) (1 << (n))

// Incluye el archivo Python 

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

const int TAMANO_TABLA_HASH = 1000;
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
string obtenerFechaActual(){
    time_t tiempoActual = time(NULL);
    struct tm *tiempo = localtime(&tiempoActual);

    int dia = tiempo->tm_mday;
    int mes = tiempo->tm_mon + 1; // Sumamos 1 para que el mes esté en el rango correcto (1-12)
    int anio = tiempo->tm_year + 1900; // Sumamos 1900 para obtener el año correcto
    string fecha = (dia < 10 ? "0" : "") + to_string(dia) + "-" +
                    (mes < 10 ? "0" : "") + to_string(mes) + "-" +
                    std::to_string(anio);
    return fecha;
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
    string horaSalvacion;
    string ubicacion;
    int totalPecados;
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
        ubicacion = "Tierra";
        demonio = "";
        angel = "";
        horaMuerte = "";
        totalPecados = 0;
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
    int obtenerIndiceRedFavorita(){
        int indice = 0;
        for(int i = 0; i < 7; i++){
            if(redesSociales[i] > redesSociales[indice]){
                indice = i;
            }
        }
        return indice;
    }
    
    int* obtenerIndicesRedesFavoritas() {
        int* indicesFavoritos = new int[7];
        
        // Inicializar los indicesFavoritos
        for (int i = 0; i < 7; i++) {
            indicesFavoritos[i] = i;
        }

        // Ordenar los indicesFavoritos de acuerdo al favoritismo
        for (int i = 0; i < 7; i++) {
            for (int j = i + 1; j < 7; j++) {
                if (redesSociales[indicesFavoritos[i]] < redesSociales[indicesFavoritos[j]]) {
                    // Intercambiar los elementos si el favoritismo es mayor
                    int temp = indicesFavoritos[i];
                    indicesFavoritos[i] = indicesFavoritos[j];
                    indicesFavoritos[j] = temp;
                }
            }
        }

        return indicesFavoritos;
    }

    void imprimir() {
        if (this->id == 0) {
            cout << "No hay datos" << endl;
            return;
        } else {
            cout << "ID: " << id << endl;
            cout << "Generación: " << generacion << endl;
            cout << "Cantidad de amigos: " << cantidadAmigos << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Apellido: " << apellido << endl;
            cout << "País: " << pais << endl;
            cout << "Creencia: " << creencia << endl;
            cout << "Profesión: " << profesion << endl;
            cout << "Fecha de nacimiento: " << fechaNacimiento << endl;
            cout << "Estado: " << estado << endl;
            cout << "Demonio: " << demonio << endl;
            cout << "Ángel: " << angel << endl;
            cout << "Hora de muerte: " << horaMuerte << endl;
            cout << "Ubicación: " << ubicacion << endl;
            cout << "Redes sociales: " << endl;
            for (int i = 0; i < 7; i++) {
                cout << " " << redesSociales[i];
            }
            cout << endl;
            cout << "Pecados: " << endl;
            for (int i = 0; i < 7; i++) {
                cout << " " << pecados[i];
            }
            cout << endl;
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
int cantidadNodos(TreeNode* root){
    if(root == NULL){
        return 0;
    }
    return 1 + cantidadNodos(root->left) + cantidadNodos(root->right);
}

void imprimirUltimoNivel(TreeNode* root, int nivel, int nivelActual, int* indices) {
    if (!root) return;

    if (nivelActual == nivel) {
        // Imprimir información de la persona
        root->persona->imprimir();
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
    Heap(){
        capacidad = 0;
        tamano = 0;
        pecadoCapital = 0;
    }
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

        // Realizar heapify ascendente
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
    void eliminar(Persona persona){
        int indice = 0;
        for(int i = 0; i < tamano; i++){
            if(personas[i]->id == persona.id){
                indice = i;
                break;
            }
        }
        personas[indice] = personas[--tamano];
        // Realizar heapify descendente
        while (true) {
            int hijoIzquierdo = 2 * indice + 1;
            int hijoDerecho = 2 * indice + 2;
            int indiceMayor = indice;

            // Comparar con el hijo izquierdo
            if (hijoIzquierdo < tamano && personas[hijoIzquierdo]->pecados[pecadoCapital] > personas[indiceMayor]->pecados[pecadoCapital]) {
                indiceMayor = hijoIzquierdo;
            }

            // Comparar con el hijo derecho
            if (hijoDerecho < tamano && personas[hijoDerecho]->pecados[pecadoCapital] > personas[indiceMayor]->pecados[pecadoCapital]) {
                indiceMayor = hijoDerecho;
            }

            // Intercambiar si es necesario y continuar ajustando
            if (indiceMayor != indice) {
                swap(personas[indice], personas[indiceMayor]);
                indice = indiceMayor;
            } else {
                break;
            }
        }
    }
    bool estaVacio() const {
        return tamano == 0;
    }
    Heap* copiar (){
        Heap* nuevo = new Heap(pecadoCapital, capacidad);
        nuevo->tamano = tamano;
        for(int i = 0; i < tamano; i++){
            nuevo->personas[i] = personas[i];
        }
        return nuevo;
    }
    Persona* extraerPrimero() {
        if (tamano == 0) {
            cout << "El heap está vacío." << endl;
            return nullptr;
        }

        Persona* personaExtraida = personas[0];
        personas[0] = personas[--tamano];

        // Reajustar el heap después de la extracción
        int indice = 0;
        while (true) {
            int hijoIzquierdo = 2 * indice + 1;
            int hijoDerecho = 2 * indice + 2;
            int indiceMayor = indice;

            // Comparar con el hijo izquierdo
            if (hijoIzquierdo < tamano && personas[hijoIzquierdo]->pecados[pecadoCapital] > personas[indiceMayor]->pecados[pecadoCapital]) {
                indiceMayor = hijoIzquierdo;
            }

            // Comparar con el hijo derecho
            if (hijoDerecho < tamano && personas[hijoDerecho]->pecados[pecadoCapital] > personas[indiceMayor]->pecados[pecadoCapital]) {
                indiceMayor = hijoDerecho;
            }

            // Intercambiar si es necesario y continuar ajustando
            if (indiceMayor != indice) {
                swap(personas[indice], personas[indiceMayor]);
                indice = indiceMayor;
            } else {
                break;
            }
        }

        return personaExtraida;
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

struct HeapInfierno{
    int capacidad;
    int tamano;
    vector<Persona*> personas; // Usamos punteros a Persona
    HeapInfierno(){
        capacidad = 0;
        tamano = 0;
    }
    HeapInfierno(int capacidad) {
        this->capacidad = capacidad;
        tamano = 0;
        personas.resize(capacidad, nullptr); // Resize el vector a la capacidad dada
    }
    void insertar(Persona* persona) {
        if (tamano == capacidad) {
            cout << "El heap está lleno." << endl;
            return;
        }

        int indice = tamano;
        personas[tamano++] = persona;

        // Realizar heapify ascendente
        while (indice > 0) {
            int padre = (indice - 1) / 2;
            for(int i = 0; i < 7; i++){
                persona->totalPecados += persona->pecados[i];
            }
            if (personas[indice]->totalPecados > personas[padre]->totalPecados) {
                // Intercambiar con el padre si el pecado es mayor
                swap(personas[indice], personas[padre]);
                indice = padre;
            } else {
                break;
            }
        }
    }
    void eliminar(Persona persona){
        int indice = 0;
        for(int i = 0; i < tamano; i++){
            if(personas[i]->id == persona.id){
                indice = i;
                break;
            }
        }
        personas[indice] = personas[--tamano];
        // Realizar heapify descendente
        while (true) {
            int hijoIzquierdo = 2 * indice + 1;
            int hijoDerecho = 2 * indice + 2;
            int indiceMayor = indice;

            // Comparar con el hijo izquierdo
            if (hijoIzquierdo < tamano && personas[hijoIzquierdo]->pecados[0] > personas[indiceMayor]->pecados[0]) {
                indiceMayor = hijoIzquierdo;
            }

            // Comparar con el hijo derecho
        }
    }
    bool isEmpty(){
        return tamano == 0;
    }
    Persona* eliminarPrimero(){
        if (tamano == 0) {
            cout << "El heap está vacío." << endl;
            return nullptr;
        }

        Persona* personaExtraida = personas[0];
        personas[0] = personas[--tamano];

        // Reajustar el heap después de la extracción
        int indice = 0;
        while (true) {
            int hijoIzquierdo = 2 * indice + 1;
            int hijoDerecho = 2 * indice + 2;
            int indiceMayor = indice;

            // Comparar con el hijo izquierdo
            if (hijoIzquierdo < tamano && personas[hijoIzquierdo]->pecados[0] > personas[indiceMayor]->pecados[0]) {
                indiceMayor = hijoIzquierdo;
            }

            // Comparar con el hijo derecho
            if (hijoDerecho < tamano && personas[hijoDerecho]->pecados[0] > personas[indiceMayor]->pecados[0]) {
                indiceMayor = hijoDerecho;
            }

            // Intercambiar si es necesario y continuar ajustando
            if (indiceMayor != indice) {
                swap(personas[indice], personas[indiceMayor]);
                indice = indiceMayor;
            } else {
                break;
            }
        }

        return personaExtraida;
    }
    void imprimir(){
        for(int i = 0; i < tamano; i++){
            cout << personas[i]->id << " " << personas[i]->nombre << " " << personas[i]->apellido << endl;
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
    Heap personasCondenadas;

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
    void condenacion(int& almasInfierno,int& personasVivas, HeapInfierno* infierno) {
    // 1. Obtener todos los humanos en el heap

    Heap* heapHumanos = new Heap(pecadoCapital, totalPersonas);
    personasCondenadas = Heap(pecadoCapital, 100000);
    for (int i = 0; i < totalPersonas; i++) {
        if (personas[i].estado != "Muerto") {
            heapHumanos->insertar(&personas[i]);
        }
    }
    
    // 2. Calcular la cantidad de personas a condenar (el 5%)
    int cantidadAEnviar = static_cast<int>(totalPersonas * 0.05);

    // 3. Extraer los humanos más pecadores del heap
    for (int i = 0; i < cantidadAEnviar; i++) {
        if (!heapHumanos->estaVacio()) { // Verificar si hay personas en el heap
            try {
                Persona* personaCondenada = heapHumanos->extraerPrimero();
                // Actualizar el estado, hora de muerte y demonio de la persona condenada
        personaCondenada->estado = "Muerto";
        personaCondenada->ubicacion = "Infierno";
        personaCondenada->horaMuerte = obtenerHoraActual(); // Asegúrate de que esta función esté definida
        personaCondenada->demonio = nombre;
        almasInfierno++;

        // Encontrar o crear la familia correspondiente a la persona condenada
        NodoHeap* familia = encontrarFamilia(personaCondenada->apellido, personaCondenada->pais);
        if (familia == nullptr) {
            Heap* nuevoHeap = new Heap(pecadoCapital, totalPersonas);
            familias->agregar(nuevoHeap, personaCondenada->apellido, personaCondenada->pais);
            familia = encontrarFamilia(personaCondenada->apellido, personaCondenada->pais);
            personasCondenadas.insertar(personaCondenada);
            infierno->insertar(personaCondenada);
        }

        // Insertar la persona condenada en la familia correspondiente
        familia->heap->insertar(personaCondenada);

    // Imprimir el heap de humanos después de la condenación (opcional)
    // Limpia la memoria asignada dinámicamente
            } catch (std::exception& e) {
                // Manejo de la excepción
                std::cerr << "Error al extraer la persona condenada: " << e.what() << std::endl;
                // Puedes agregar más detalles o acciones de recuperación aquí
            }
        } else {
            std::cout << "Ya no hay personas vivas que condenar." << std::endl;
            break; // Salir del bucle si no hay personas disponibles
        }
    }

    // Limpia la memoria asignada dinámicamente
    //delete heapHumanos;
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
struct NodoPersona {
    Persona* data;
    NodoPersona* izquierdo;
    NodoPersona* derecho;
    int altura;
};
struct AVLTree {
    NodoPersona* root;
    AVLTree() {
        root = nullptr;
    }

    // Función para obtener la altura de un nodo
    int altura(NodoPersona* nodo) {
        if (nodo == nullptr)
            return 0;
        return nodo->altura;
    }

    // Función para obtener el máximo de dos números
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // Función para insertar una persona en el árbol AVL
    NodoPersona* insertar(NodoPersona* nodo, Persona* persona) {
        if (nodo == nullptr) {
            NodoPersona* newNodo = new NodoPersona;
            newNodo->data = persona;
            newNodo->izquierdo = nullptr;
            newNodo->derecho = nullptr;
            newNodo->altura = 1;
            return newNodo;
        }

        if (persona->id < nodo->data->id)
            nodo->izquierdo = insertar(nodo->izquierdo, persona);
        else if (persona->id > nodo->data->id)
            nodo->derecho = insertar(nodo->derecho, persona);
        else
            return nodo;

        nodo->altura = 1 + max(altura(nodo->izquierdo), altura(nodo->derecho));

        int balance = obtenerBalance(nodo);

        // Casos de rotación
        if (balance > 1) {
            if (persona->id < nodo->izquierdo->data->id)
                return rotarDerecha(nodo);
            if (persona->id > nodo->izquierdo->data->id) {
                nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
                return rotarDerecha(nodo);
            }
        }
        if (balance < -1) {
            if (persona->id > nodo->derecho->data->id)
                return rotarIzquierda(nodo);
            if (persona->id < nodo->derecho->data->id) {
                nodo->derecho = rotarDerecha(nodo->derecho);
                return rotarIzquierda(nodo);
            }
        }

        return nodo;
    }

    // Función para obtener el factor de balance de un nodo
    int obtenerBalance(NodoPersona* nodo) {
        if (nodo == nullptr)
            return 0;
        return altura(nodo->izquierdo) - altura(nodo->derecho);
    }

    // Función para rotar a la derecha
    NodoPersona* rotarDerecha(NodoPersona* y) {
        NodoPersona* x = y->izquierdo;
        NodoPersona* T2 = x->derecho;

        x->derecho = y;
        y->izquierdo = T2;

        y->altura = max(altura(y->izquierdo), altura(y->derecho)) + 1;
        x->altura = max(altura(x->izquierdo), altura(x->derecho)) + 1;

        return x;
    }

    // Función para rotar a la izquierda
    NodoPersona* rotarIzquierda(NodoPersona* x) {
        NodoPersona* y = x->derecho;
        NodoPersona* T2 = y->izquierdo;

        y->izquierdo = x;
        x->derecho = T2;

        x->altura = max(altura(x->izquierdo), altura(x->derecho)) + 1;
        y->altura = max(altura(y->izquierdo), altura(y->derecho)) + 1;

        return y;
    }

    // Función para buscar una persona por su ID
    NodoPersona* buscar(NodoPersona* nodo, int id) {
        if (nodo == nullptr || nodo->data->id == id)
            return nodo;

        if (id < nodo->data->id)
            return buscar(nodo->izquierdo, id);

        return buscar(nodo->derecho, id);
    }

    // Función para imprimir el árbol en orden
    void inOrden(NodoPersona* nodo) {
        if (nodo != nullptr) {
            inOrden(nodo->izquierdo);
            cout << "ID: " << nodo->data->id << ", Nombre: " << nodo->data->nombre << " " << nodo->data->apellido << endl;
            inOrden(nodo->derecho);
        }
    }

    void insertar(Persona* persona) {
        root = insertar(root, persona);
    }

    NodoPersona* buscar(int id) {
        return buscar(root, id);
    }

    void imprimirEnOrden() {
        inOrden(root);
    }
        
    void inOrdenArchivo(NodoPersona* nodo, ofstream& archivo) {
        if (nodo != nullptr) {
            inOrdenArchivo(nodo->izquierdo, archivo);
            archivo << "ID: " << nodo->data->id << ", Nombre: " << nodo->data->nombre << " " << nodo->data->apellido << endl;
            inOrdenArchivo(nodo->derecho, archivo);
        }
    }

    void imprimirEnOrdenEnArchivo(ofstream& archivo) {
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo " << endl;
            return;
        }

        inOrdenArchivo(root, archivo);

        archivo.close();
    }

};

struct NodoAVL {
    Persona* persona;
    NodoAVL* izquierda;
    NodoAVL* derecha;
    int altura;
    NodoAVL(){
        persona = nullptr;
        izquierda = nullptr;
        derecha = nullptr;
        altura = 0;
    }
};
struct AVL{
    NodoAVL* raiz;
    AVL(){
        raiz = nullptr;
    }

};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int altura(NodoAVL* nodo) {
    if (nodo == nullptr)
        return 0;
    return nodo->altura;
}

int obtenerBalance(NodoAVL* nodo) {
    if (nodo == nullptr)
        return 0;
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

NodoAVL* rotacionDerecha(NodoAVL* nodo) {
    NodoAVL* izquierda = nodo->izquierda;
    NodoAVL* subarbol = izquierda->derecha;

    izquierda->derecha = nodo;
    nodo->izquierda = subarbol;

    nodo->altura = max(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
    izquierda->altura = max(altura(izquierda->izquierda), altura(izquierda->derecha)) + 1;

    return izquierda;
}

NodoAVL* rotacionIzquierda(NodoAVL* nodo) {
    NodoAVL* derecha = nodo->derecha;
    NodoAVL* subarbol = derecha->izquierda;

    derecha->izquierda = nodo;
    nodo->derecha = subarbol;

    nodo->altura = max(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
    derecha->altura = max(altura(derecha->izquierda), altura(derecha->derecha)) + 1;

    return derecha;
}

NodoAVL* insertarEnArbol(NodoAVL* nodo, Persona* persona) {
    if (nodo == nullptr) {
        NodoAVL* nuevoNodo = new NodoAVL;
        nuevoNodo->persona = persona;
        nuevoNodo->izquierda = nullptr;
        nuevoNodo->derecha = nullptr;
        nuevoNodo->altura = 1;
        return nuevoNodo;
    }

    if (persona->id < nodo->persona->id) {
        nodo->izquierda = insertarEnArbol(nodo->izquierda, persona);
    } else if (persona->id > nodo->persona->id) {
        nodo->derecha = insertarEnArbol(nodo->derecha, persona);
    } else {
        return nodo;  // No se permiten duplicados
    }

    nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));
    int balance = obtenerBalance(nodo);

    // Casos de rotación
    if (balance > 1 && persona->id < nodo->izquierda->persona->id)
        return rotacionDerecha(nodo);
    if (balance < -1 && persona->id > nodo->derecha->persona->id)
        return rotacionIzquierda(nodo);
    if (balance > 1 && persona->id > nodo->izquierda->persona->id) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }
    if (balance < -1 && persona->id < nodo->derecha->persona->id) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void insertarPersona(NodoAVL*& raiz, Persona* persona) {
    raiz = insertarEnArbol(raiz, persona);
}

// Función de búsqueda en el árbol AVL
NodoAVL* buscarPersona(NodoAVL* nodo, int id) {
    if (nodo == nullptr || nodo->persona->id == id) {
        return nodo;
    }

    if (id < nodo->persona->id) {
        return buscarPersona(nodo->izquierda, id);
    }

    return buscarPersona(nodo->derecha, id);
}
struct NodoHash{
    int id;
    AVLTree* arbol;
    NodoHash(int id){
        this->id = id;
        this->arbol = new AVLTree();
    }

};
struct TablaHash {
    NodoHash* tablas[1000];
    //vector<NodoHash*> tablas[TAMANO_TABLA_HASH];

    TablaHash() {
        for (int i = 0; i < 1000; i++) {
            tablas[i] = new NodoHash(i);
        }
    }

    int funcionHash(int id) {
        return id % TAMANO_TABLA_HASH;
    }

    void insertarPersonaHash(Persona* persona) {
        int indice = funcionHash(persona->id);
        persona->imprimir();
        tablas[indice]->arbol->insertar(persona);
    }
};
void imprimirInOrden(AVLTree* avl, std::ofstream& archivo) {
    if (avl != NULL) {
        cout << "croma aqui" << endl;
        //imprimirInOrden(nodo->izquierda, archivo);
        cout << "croma aqui" << endl;
        //archivo << "ID: " << nodo->persona->id << ", Nombre: " << nodo->persona->nombre <<  std::endl;
        //imprimirInOrden(nodo->derecha, archivo);
        
    }else{
        cout << "no hay nada" << endl;
        return;
    }
}
void imprimirTablaHashEnOrdenRecursivo(NodoPersona* nodo, std::ofstream& archivo) {
    if (nodo != nullptr) {
        imprimirTablaHashEnOrdenRecursivo(nodo->izquierdo, archivo);
        archivo << "Persona " << nodo->data->id << "\n";
        imprimirTablaHashEnOrdenRecursivo(nodo->derecho, archivo);
    }
}
void imprimirTablaHashEnOrden(TablaHash* tablaHash, std::ofstream& archivo) {
    for (int i = 0; i < TAMANO_TABLA_HASH; i++) {
        archivo << "Tabla Hash #" << i << ":\n";
        imprimirTablaHashEnOrdenRecursivo(tablaHash->tablas[i]->arbol->root, archivo);
    }
}


// Función para imprimir el árbol AVL en orden
/*
void imprimirEnOrden(NodoAVL* nodo, std::ofstream& archivo) {
    if (nodo != nullptr) {
        imprimirEnOrden(nodo->izquierda, archivo);
        archivo << "ID: " << nodo->persona.id << std::endl;
        archivo << "Nombre: " << nodo->persona.nombre << std::endl;
        archivo << "Apellido: " << nodo->persona.apellido << std::endl;
        archivo << "País: " << nodo->persona.pais << std::endl;
        archivo << "Creencia: " << nodo->persona.creencia << std::endl;
        archivo << "Profesión: " << nodo->persona.profesion << std::endl;
        archivo << "Fecha de nacimiento: " << nodo->persona.fechaNacimiento << std::endl;
        archivo << "Estado: " << nodo->persona.estado << std::endl;
        archivo << "Demonio: " << nodo->persona.demonio << std::endl;
        archivo << "Hora de muerte: " << nodo->persona.horaMuerte << std::endl;
        archivo << "Ángel: " << nodo->persona.angel << std::endl;
        archivo << "Ubicación: " << nodo->persona.ubicacion << std::endl;
        
        archivo << "--------------------------Amigos---------------" << std::endl;
        
        for(int i = 0; i < nodo->persona.cantidadAmigos; i++){
            archivo << "ID: " << nodo->persona.amigos->amigo->persona->id << std::endl;
            archivo << "Nombre: " << nodo->persona.amigos->amigo->persona->nombre << std::endl;
            archivo << "Apellido: " << nodo->persona.amigos->amigo->persona->apellido << std::endl;
            archivo << "País: " << nodo->persona.amigos->amigo->persona->pais << std::endl;
            archivo << "Creencia: " << nodo->persona.amigos->amigo->persona->creencia << std::endl;
            archivo << "Profesión: " << nodo->persona.amigos->amigo->persona->profesion << std::endl;
            archivo << "Fecha de nacimiento: " << nodo->persona.amigos->amigo->persona->fechaNacimiento << std::endl;
            archivo << "Estado: " << nodo->persona.amigos->amigo->persona->estado << std::endl;
            archivo << "Demonio: " << nodo->persona.amigos->amigo->persona->demonio << std::endl;
            archivo << "Hora de muerte: " << nodo->persona.amigos->amigo->persona->horaMuerte << std::endl;
            archivo << "Ángel: " << nodo->persona.amigos->amigo->persona->angel << std::endl;
            archivo << "Ubicación: " << nodo->persona.amigos->amigo->persona->ubicacion << std::endl;
            archivo << "--------------------------FIN Amigos---------------" << std::endl;
        }

        archivo << std::endl;
        imprimirEnOrden(nodo->derecha, archivo);
    }
}
*/
/*
void imprimirEnOrden(NodoAVL* nodo, std::ofstream& archivo) {
    if (nodo != nullptr) {
        imprimirEnOrden(nodo->izquierda, archivo);
        archivo << "Info de mi persona" << nodo->persona->id << std::endl;
        // Imprimir otros campos de información de la persona
        archivo << std::endl;
        imprimirEnOrden(nodo->derecha, archivo);
    }
}
*/

struct Angel{
    string nombre;
    Persona* persona;
    int version;
    int generacion;
};

struct TriarioNodo {
    Angel angel;
    vector<TriarioNodo*> hijos;
};

struct ArbolAngel {
    TriarioNodo* raiz;
    int nivel;
    ArbolAngel() {
        raiz = new TriarioNodo();
        raiz->angel.nombre = "Dios";
        raiz->angel.generacion = 0;
        raiz->angel.version = 1;
        raiz->angel.persona = nullptr;
        nivel = 2;

        // Crea los ángeles del segundo nivel
        for (int i = 0; i < 3; i++) {
            TriarioNodo* angel = new TriarioNodo();
            angel->angel.nombre = (i == 0) ? "Serafines" : (i == 1) ? "Querubines" : "Tronos";
            angel->angel.generacion = 1;
            angel->angel.version = 1;
            angel->angel.persona = nullptr;
            raiz->hijos.push_back(angel);
        }
    }
    int obtenerCantidadNiveles(TriarioNodo* nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    int maxNivelHijos = 0;
    for (TriarioNodo* hijo : nodo->hijos) {
        int nivelHijo = obtenerCantidadNiveles(hijo);
        if (nivelHijo > maxNivelHijos) {
            maxNivelHijos = nivelHijo;
        }
    }

    return maxNivelHijos + 1;
}

int obtenerCantidadNivelesArbol(ArbolAngel* arbol) {
    return obtenerCantidadNiveles(arbol->raiz);
}
    // Agrega una función para realizar la salvación y generar nuevos niveles
    void imprimirNombresPorNivel(TriarioNodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    std::cout << nodo->angel.nombre << " ";
    
    for (TriarioNodo* hijo : nodo->hijos) {
        imprimirNombresPorNivel(hijo);
    }
    
}

    void imprimirArbolPorNivel(ArbolAngel* arbol) {
        std::queue<TriarioNodo*> nivelActual;
        std::queue<TriarioNodo*> nivelSiguiente;

        nivelActual.push(arbol->raiz);

        while (!nivelActual.empty()) {
            TriarioNodo* nodo = nivelActual.front();
            nivelActual.pop();

            std::cout << nodo->angel.nombre << " ";

            for (TriarioNodo* hijo : nodo->hijos) {
                nivelSiguiente.push(hijo);
            }

            if (nivelActual.empty()) {
                std::cout << std::endl;
                std::swap(nivelActual, nivelSiguiente);
            }
        }
    }

    string obtenerNombreAleatorio() {
        std::vector<std::string> nombres = {
            "Miguel", "Nuriel", "Aniel", "Rafael", "Gabriel",
            "Shamsiel", "Raguel", "Uriel", "Azrael", "Sariel"
        };

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, nombres.size() - 1);

        int indice = distribution(gen);
        return nombres[indice];
    }

    void salvacion(HeapInfierno* heapInfierno, int niveles, int& almasCielo, int& almasInfierno, TablaHash* cielo) {
        ofstream archivo("LogSalvacion_"+obtenerHoraActual()+".txt");
        if (archivo.is_open()) {
            archivo << "Log de Salvación" << std::endl;
            archivo << "================" << std::endl;
            archivo << std::endl;

            // 1. Extraer a las personas del infierno
            for (nivel; nivel <= niveles; nivel++) {
                TriarioNodo* generacionActual = new TriarioNodo();
                generacionActual->angel.nombre;
                generacionActual->angel.generacion = nivel;
                generacionActual->angel.version = 1;
                generacionActual->angel.persona = nullptr;

                int cantidadAngeles = pow(3, nivel); // Calcula la cantidad de ángeles para este nivel

                for (int i = 0; i < cantidadAngeles; i++) {
                        TriarioNodo* angel = new TriarioNodo();
                        angel->angel.nombre = obtenerNombreAleatorio();
                        angel->angel.generacion = nivel;
                        angel->angel.version = i + 1;
                        generacionActual->hijos.push_back(angel);
                    if(!heapInfierno->isEmpty()){
                        angel->angel.persona = heapInfierno->eliminarPrimero();
                        angel->angel.persona->angel = angel->angel.nombre;
                        angel->angel.persona->ubicacion = "Cielo";
                        angel->angel.persona->horaSalvacion = obtenerHoraActual();
                        almasCielo++;
                        almasInfierno--;
                        cielo->insertarPersonaHash(angel->angel.persona);
                        archivo << obtenerHoraActual() << "Humano: " << angel->angel.persona->id << " Salva el " << obtenerFechaActual() << " por " << angel->angel.persona->totalPecados <<" pecados. El ángel " << angel->angel.nombre << "(" << angel->angel.version << ")" << " Generacion: " << angel->angel.generacion << endl;
                    }
                }

                raiz->hijos.push_back(generacionActual);
            }
                archivo << std::endl;
                archivo << "==================" << std::endl;
                archivo << std::endl;
            }else{
                std::cout << "No se pudo abrir el archivo para escribir el log de salvación." << std::endl;
            }
    }
};
void guardarInformacionSalvacionRecursivo(TriarioNodo* nodo, std::ofstream& archivo) {
    if (nodo == nullptr) {
        return;
    }

    if (nodo->angel.persona != nullptr) {
        archivo << "Nombre del ángel: " << nodo->angel.nombre << std::endl;
        archivo << "Generación: " << nodo->angel.generacion << std::endl;
        archivo << "Versión: " << nodo->angel.version << std::endl;
        archivo << "Nombre de la persona salvada: " << nodo->angel.persona->nombre << std::endl;
        archivo << std::endl;
    }

    for (TriarioNodo* hijo : nodo->hijos) {
        guardarInformacionSalvacionRecursivo(hijo, archivo);
    }
}
void guardarInformacionSalvacion(ArbolAngel* arbol, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        guardarInformacionSalvacionRecursivo(arbol->raiz, archivo);
        archivo.close();
    } else {
        std::cout << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}


void generarBitacoraCondenacion(Demonio& demonio, std::ofstream& archivoBitacora) {
    // 1. Crear un nuevo heap para organizar a las personas condenadas
    Heap heapCondenados = demonio.personasCondenadas;

    // 2. Transferir personas condenadas al nuevo heap
    for (int i = 0; i < demonio.totalPersonas; i++) {
        if (demonio.personas[i].estado == "Muerto" && demonio.personas[i].demonio == demonio.nombre && demonio.personas[i].ubicacion =="Infierno") {
            heapCondenados.insertar(&demonio.personas[i]);
        }
    }

    // Extraer y escribir en el archivo las personas condenadas de mayor a menor pecador
    while (!heapCondenados.estaVacio()) {
        Persona* personaCondenada = heapCondenados.extraerPrimero();
        archivoBitacora << "Nombre: " << personaCondenada->nombre << " " << personaCondenada->apellido << std::endl;
        archivoBitacora << "Pecado Capital: " << personaCondenada->pecados[demonio.pecadoCapital] << std::endl;
        archivoBitacora << "Hora de Muerte: " << personaCondenada->horaMuerte << std::endl;
        archivoBitacora << "Ubicación: " << personaCondenada->ubicacion << std::endl;
        archivoBitacora << "Demonio: " << personaCondenada->demonio << std::endl;
        archivoBitacora << "----------------------------" << std::endl;
    }
}
void generarBitacoraParaTodosLosDemoniosUnificada(Demonio** demonios, int numDemonios, const std::string& nombreArchivo) {
    std::ofstream archivoBitacora(nombreArchivo, std::ios::app);

    if (archivoBitacora.is_open()) {
        for (int i = 0; i < numDemonios; i++) {
            archivoBitacora << "--------------------------------------" << std::endl;
            archivoBitacora << "Bitácora de Condenación para el Demonio: " << demonios[i]->nombre << std::endl;
            archivoBitacora << "--------------------------------------" << std::endl;
            // Llama a la función original para generar la bitácora de este demonio
            generarBitacoraCondenacion(*demonios[i], archivoBitacora);
        }

        archivoBitacora.close();
        std::cout << "Bitácora generada con éxito en el archivo: " << nombreArchivo << std::endl;
    } else {
        std::cout << "No se pudo abrir el archivo para escribir la bitácora." << std::endl;
    }
}


struct Mundo{
    Persona* personas;
    int totalPersonas;
    int totalPersonasVivas;
    int generacion;
    int humanosConAmigos;
    int totalNombres;
    int totalApellidos;
    int totalProfesiones;
    int totalCreencias;
    int totalPaises;
    int cantidadEnArbol = totalPersonas * 0.01;
    int almasCielo = 0;
    int almasInfierno = 0;
    TablaHash * cielo;
    Demonio** demonios;
    ArbolAngel* angeles;
    string* nombres;
    string* apellidos;
    string* paises;
    string* creencias;
    string* profesiones;
    TreeNode* root;
    HeapInfierno * infierno;

// Calcular la cantidad de niveles necesarios
    Mundo(){
        totalPersonas = 0;  // Asegúrate de que totalPersonas se inicie en 0
        totalPersonasVivas = 0;
        generacion = 0;
        humanosConAmigos = 0;
        personas = new Persona[100000];
        nombres = cargarArchivo(1468, totalNombres, "/nombres.txt");
        apellidos = cargarArchivo(30, totalApellidos, "/apellidos.txt");
        paises = cargarArchivo(15, totalPaises, "/paises.txt");
        creencias = cargarArchivo(10, totalCreencias, "/creencias.txt");
        profesiones = cargarArchivo(20, totalProfesiones, "/profesiones.txt");
        demonios = new Demonio*[7]; // Reservamos espacio para 7 demonios
        angeles = new ArbolAngel();
        demonios[0] = new Demonio("Asmodeo", 0, personas,totalPersonas);
        demonios[1] = new Demonio("Belfegor", 1, personas,totalPersonas);
        demonios[2] = new Demonio("Satán", 2, personas,totalPersonas);
        demonios[3] = new Demonio("Lucifer", 3, personas,totalPersonas);
        demonios[4] = new Demonio("Belcebu", 4, personas,totalPersonas);
        demonios[5] = new Demonio("Mammon", 5, personas,totalPersonas);
        demonios[6] = new Demonio("Abadon", 6, personas,totalPersonas);
        root = NULL;    
        infierno = new HeapInfierno(100000);
        cielo = new TablaHash();
    }


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
        angeles = new ArbolAngel();
        demonios[0] = new Demonio("Asmodeo", 0, personas,totalPersonas);
        demonios[1] = new Demonio("Belfegor", 1, personas,totalPersonas);
        demonios[2] = new Demonio("Satán", 2, personas,totalPersonas);
        demonios[3] = new Demonio("Lucifer", 3, personas,totalPersonas);
        demonios[4] = new Demonio("Belcebu", 4, personas,totalPersonas);
        demonios[5] = new Demonio("Mammon", 5, personas,totalPersonas);
        demonios[6] = new Demonio("Abadon", 6, personas,totalPersonas); 
        infierno = new HeapInfierno(100000);
        cielo = new TablaHash();   
    }
    void generarPersonasMundo(int personasAGenerar){
        generarPersonas(totalPersonas, generacion, personasAGenerar, personas, nombres, apellidos, paises, creencias, profesiones);
        demonios[0] = new Demonio("Asmodeo", 0, personas,totalPersonas);
        demonios[1] = new Demonio("Belfegor", 1, personas,totalPersonas);
        demonios[2] = new Demonio("Satán", 2, personas,totalPersonas);
        demonios[3] = new Demonio("Lucifer", 3, personas,totalPersonas);
        demonios[4] = new Demonio("Belcebu", 4, personas,totalPersonas);
        demonios[5] = new Demonio("Mammon", 5, personas,totalPersonas);
        demonios[6] = new Demonio("Abadon", 6, personas,totalPersonas); 
    }
    void cargarAmigosMundo(){
        cargarAmigos(personas, totalPersonas, humanosConAmigos);
        demonios[0] = new Demonio("Asmodeo", 0, personas,totalPersonas);
        demonios[1] = new Demonio("Belfegor", 1, personas,totalPersonas);
        demonios[2] = new Demonio("Satán", 2, personas,totalPersonas);
        demonios[3] = new Demonio("Lucifer", 3, personas,totalPersonas);
        demonios[4] = new Demonio("Belcebu", 4, personas,totalPersonas);
        demonios[5] = new Demonio("Mammon", 5, personas,totalPersonas);
        demonios[6] = new Demonio("Abadon", 6, personas,totalPersonas); 
    }
    void imprimirPersonas(){
        for (int i = 0; i < totalPersonas; i++) {
            personas[i].imprimir();
        }
    }
    void publicarEnRedSocial(int redSocial, Persona persona){
        string nombreRedes[] = {"Tinder", "iFood", "Twitter", "Instagram", "Facebook", "LinkedIn", "Netflix"};
        string pecados[] = {"Lujuria", "Gula", "Ira", "Soberbia", "Envidia", "Avaricia", "Pereza"};
        Nodo * aux = persona.amigos->amigo;
        if(persona.estado =="Vivo"){
            while(aux != NULL){
                aux->persona->pecados[redSocial] += aux->persona->obtenerFavoritismo(redSocial);
                aux = aux->siguiente;
            }
        }
    }
    void publicarEnRedSocialPorReligion(string religion){
        string nombreRedes[] = {"Tinder", "iFood", "Twitter", "Instagram", "Facebook", "LinkedIn", "Netflix"};
        string pecados[] = {"Lujuria", "Gula", "Ira", "Soberbia", "Envidia", "Avaricia", "Pereza"};
        int cantidadPublicaciones = 0;
        for(int i = 0; i < totalPersonas; i++){
            if(personas[i].creencia == religion && personas[i].estado == "Vivo"){
                publicarEnRedSocial(personas[i].obtenerIndiceRedFavorita(), personas[i]);
                cantidadPublicaciones++;
            }
        }
    }
    void publicarEnRedesPorProfesion(string profesion, int nRedesFavoritas) {
        
        for (int i = 0; i < totalPersonas; i++) {
            if (personas[i].profesion == profesion && personas[i].estado == "Vivo") {
                // Obtener los índices de las n redes sociales favoritas de la persona
                int* indicesFavoritos = personas[i].obtenerIndicesRedesFavoritas();
                // Publicar en las n redes sociales favoritas de la persona
                for (int k = 0; k < nRedesFavoritas; k++) {
                    int redSocial = indicesFavoritos[k];
                    publicarEnRedSocial(redSocial, personas[i]);
                }

                // Liberar la memoria del array de índices favoritos
                delete[] indicesFavoritos;
            }
        }
    }
    void publicarEnRedesPorFamilia(string pais, string apellido, int nRedesFavoritas){
        for(int i = 0; i < totalPersonas; i++){
            if(personas[i].pais == pais && personas[i].apellido == apellido && personas[i].estado == "Vivo"){
                int* indicesFavoritos = personas[i].obtenerIndicesRedesFavoritas();
                for(int j=0; j <7; j++){
                    cout << indicesFavoritos[j] << ", ";
                }
                cout << endl;
                // Publicar en las n redes sociales favoritas de la persona
                for (int k = 0; k < nRedesFavoritas; k++) {
                    int redSocial = indicesFavoritos[k];
                    publicarEnRedSocial(redSocial, personas[i]);
                }

                // Liberar la memoria del array de índices favoritos
                delete[] indicesFavoritos;
            }
        }
    }
    void generarTxtInfierno(int numDemonios, const string& nombreArchivo){
    ofstream archivoBitacora(nombreArchivo, ios::app);
    string pecados[] = {"Lujuria", "Gula", "Ira", "Soberbia", "Envidia", "Avaricia", "Pereza"};
    if (archivoBitacora.is_open()) {
        // Genera la bitácora para cada demonio y escribe los registros en el mismo archivo.
        archivoBitacora << "Personas en el Infierno: " << almasInfierno << endl;
        for (int i = 0; i < numDemonios; i++) {
            archivoBitacora << "--------------------------------------" << endl;
            archivoBitacora << "Demonio: " << demonios[i]->nombre << " (Pecado Capital: " << pecados[demonios[i]->pecadoCapital] << ")" << endl;

            NodoHeap* familia = demonios[i]->familias->heap;
            while (familia != nullptr) {
                archivoBitacora << "Familia: " << familia->apellido << " (País: " << familia->pais << ")" << endl;
                Heap * heapFamilia = familia->heap->copiar();
                while(!heapFamilia->estaVacio()){
                    Persona* personaCondenada = heapFamilia->extraerPrimero();
                    if(personaCondenada->ubicacion == "Infierno"){
                    archivoBitacora << "Nombre: " << personaCondenada->nombre << " " << personaCondenada->apellido << endl;
                    archivoBitacora << "Pecado Capital: " << personaCondenada->pecados[demonios[i]->pecadoCapital] << endl;
                    archivoBitacora << "Hora de Muerte: " << personaCondenada->horaMuerte << endl;
                    archivoBitacora << "Ubicación: " << personaCondenada->ubicacion << endl;
                    archivoBitacora << "Demonio: " << personaCondenada->demonio << endl;
                    archivoBitacora << "----------------------------" << endl;
                    }else{
                        continue;
                    }
                }
                familia = familia->siguiente;
            }
        }
        archivoBitacora.close();
    }else {
        std::cout << "No se pudo abrir el archivo para escribir la bitácora." << std::endl;
    }


}
};


void menuPublicarEnRedes(Mundo* mundo) {
    cout << "Ingrese una opcion" << endl;
    cout << "1. Seleccionar un humano para publicar en una red social particular" << endl;
    cout << "2. Publicar en la red favorita de todos los humanos de una religión" << endl;
    cout << "3. Publicar en las redes favoritas de todos los humanos de una profesión" << endl;
    cout << "4. Publicar en las redes favoritas de los miembros de una familia" << endl;

    int opcion = 0;
    cin >> opcion;

    if (opcion == 1) {
        // Opción 1: Seleccionar un humano para publicar en una red social particular
        mundo->imprimirPersonas();
        cout << "Ingrese el ID del humano que desea seleccionar: ";
        int idHumano = 0;
        cin >> idHumano;

        if (idHumano > 0 && idHumano <= mundo->totalPersonas) {
            cout << "Seleccione la red social (1-7): ";
            int redSocial = 0;
            cin >> redSocial;

            if (redSocial >= 1 && redSocial <= 7) {
                mundo->publicarEnRedSocial(redSocial - 1, mundo->personas[idHumano - 1]);
            } else {
                cout << "Número de red social no válido." << endl;
            }
        } else {
            cout << "ID de humano no válido." << endl;
        }
    } else if (opcion == 2) {
        // Opción 2: Publicar en la red favorita de todos los humanos de una religión
        string creencias[] = {"Cristianismo","Islam","Judaísmo","Budismo", "Hinduismo", "Sikhismo","Jainismo","Zoroastrismo","Shintoísmo", "Ateismo"};
        cout << "Ingrese la religión: " << endl;
        cout << "1.Cristianismo" <<endl;
        cout << "2.Islam" <<endl;
        cout << "3.Judaísmo" <<endl;
        cout << "4.Budismo" <<endl;
        cout << "5.Hinduismo" <<endl;
        cout << "6.Sikhismo" <<endl;
        cout << "7.Jainismo" <<endl;
        cout << "8.Zoroastrismo" <<endl;
        cout << "9.Shintoísmo" <<endl;
        cout << "10.Ateismo" <<endl;
        string religion;
        cin >> religion;
        mundo->publicarEnRedSocialPorReligion(creencias[stoi(religion)-1]);
    } else if (opcion == 3) {
        // Opción 3: Publicar en las redes favoritas de todos los humanos de una profesión
        cout << "Ingrese la profesión: ";
        string profesion;
        cin >> profesion;
        cout << "Ingrese cuantas redes:";
        int nRedesFavoritas;
        cin >> nRedesFavoritas;
        mundo->publicarEnRedesPorProfesion(profesion, nRedesFavoritas);
    } else if (opcion == 4) {
        // Opción 4: Publicar en las redes favoritas de los miembros de una familia
        cout << "Ingrese el país de la familia: ";
        string pais;
        cin >> pais;
        cout << "Ingrese el apellido de la familia: ";
        string apellido;
        cin >> apellido;
        int nRedesFav;
        cout << "Ingrese cuantas redes:";
        cin >> nRedesFav;
        mundo->publicarEnRedesPorFamilia(pais, apellido, nRedesFav);
    } else {
        cout << "Opción no válida. Por favor, elige una opción válida." << endl;
    }
}
void menuConsultas(Mundo* mundo){
        cout << "Ingrese una opcion" << endl;
        cout << "1. Mostar ganador" << endl;
        cout << "2. Consultar un humano por ID" << endl;
        cout << "3. Informacion Acerca de una familia." << endl;
        string opcion;
        cin >> opcion;
        if(opcion == "1"){
            if(mundo->almasCielo > mundo->almasInfierno){
                cout << "El cielo ha ganado la batalla" << endl;
            }else if(mundo->almasCielo < mundo->almasInfierno){
                cout << "El infierno ha ganado la batalla" << endl;
            }else{
                cout << "Ha habido un empate" << endl;
            }
            cout << "Total de humanos: " << mundo->totalPersonas << endl;
            cout << "Total de humanos vivos: " << mundo->totalPersonas - mundo->almasCielo - mundo->almasInfierno << endl;
            cout << "Total de humanos en el cielo: " << mundo->almasCielo << endl;
            cout << "Total de humanos en el infierno: " << mundo->almasInfierno << endl;
        }else if(opcion == "2"){
            cout << "Ingrese el ID del humano que desea seleccionar: ";
            int idHumano = 0;
            cin >> idHumano;
            if (idHumano > 0 && idHumano <= mundo->totalPersonas) {
                mundo->personas[idHumano - 1].imprimir();
                cout << "---------------------Amigos---------------------" << endl;
                mundo->personas[idHumano - 1].amigos->imprimir();
                cout << "---------------------Fin de la lista---------------------" << endl;
            } else {
                cout << "ID de humano no válido." << endl;
            }
        }else if (opcion == "3"){
            /*
            5. Buscar familia: Debe dar toda la
            información y ubicación de los humanos,
            ordenados de más a menos pecados (no olvide los
            amigos, imprimir la información de estos). 
            En la misma consulta, dar el porcentaje de la
            familia viva, el porcentaje en el cielo y el
            porcentaje en el infierno
            Puedo recorrer el array y buscar y ordenarlo con el heap :D sale facil.
            */
        }else{
            cout << "Opcion no valida" << endl;
            menuConsultas(mundo);
        }

}
void menu(Mundo* world){
    cout << "Bienvenido al juego de la batalla por las almas" << endl;
    cout << "1. Generar Personas" << endl;
    cout << "2. Publicar en Red Social" << endl;
    cout << "3. Condenar" << endl;
    cout << "4. Salvación" << endl;
    cout << "5. Imprimir Personas" << endl;
    cout << "6. Mostar informacion del arbol de la vida" << endl;
    cout << "7. Generar y Enviar bitacora al correo" << endl;
    cout << "8. Ver el infierno" << endl;
    cout << "9. Ver el cielo" << endl;
    cout << "10. Consultas" << endl;
    cout << "11. Salir" << endl;
    string opcion = "";
    cin >> opcion;
    if(opcion == "1"){
        cout << "Ingrese la cantidad de personas a generar" << endl;
        int cantidad = 0;
        cin >> cantidad;
        world->generarPersonasMundo(cantidad);
        world->cargarAmigosMundo();
        cout << "Se han generado " << cantidad << " personas" << endl;
        menu(world);
    }else if(opcion == "2"){
        menuPublicarEnRedes(world);
        menu(world);
    }else if(opcion == "3"){
        //Bitacora, realizarla
        string opcion;
        cout << "Ingrese el nombre del demonio que desea condenar" << endl;
        cout << "1. Asmodeo" << endl;
        cout << "2. Belfegor" << endl;
        cout << "3. Satán" << endl;
        cout << "4. Lucifer" << endl;
        cout << "5. Belcebu" << endl;
        cout << "6. Mammon" << endl;
        cout << "7. Abadon" << endl;
        cin >> opcion;
        world->demonios[stoi(opcion)-1]->condenacion(world->almasInfierno,world->totalPersonas, world->infierno);
        world->infierno->imprimir();
        menu(world);
    }else if(opcion == "4"){
        world->angeles->salvacion(world->infierno, world->angeles->obtenerCantidadNivelesArbol(world->angeles), world->almasCielo, world->almasInfierno, world->cielo);
        menu(world);
    }else if(opcion == "5"){
        world->imprimirPersonas();
        menu(world);
    }else if(opcion == "6"){
        TreeNode* root = construirABB(0, world->totalPersonas - 1, world->personas);
        int totalNodos = world->totalPersonas / 100 + 1; // 1% de totalPersonas + 1
        int* indices = new int[totalNodos];
        int niveles = calcularCantidadNiveles(totalNodos);
        int totalPersonas = cantidadNodos(root);
        int totalNodosArbol = pow(2,niveles)-1;
        cout << "Cantidad de niveles del arbol: " << niveles << endl;
        cout << "Cantidad de nodos del arbol: " << totalNodosArbol << endl;
        cout << "Cantidad de personas en el arbol: " << totalPersonas << endl;
        imprimirUltimoNivel(root, niveles - 1, 0, indices);
        delete root;
        menu(world);
    }
    else if(opcion == "7"){
        //Bitacora
        generarBitacoraParaTodosLosDemoniosUnificada(world->demonios, 7, "BITACORA "+ obtenerHoraActual() + ".txt");
        menu(world);
    }
    else if(opcion == "8"){
        //Infierno
        world->generarTxtInfierno(7, "Infierno " + obtenerHoraActual() + ".txt");
        menu(world);
    }
    else if(opcion == "9"){
        //Ver informacion del cielo
        ofstream archivo("Cielo " + obtenerHoraActual() + ".txt");
        /*for (int numTabla = 0; numTabla < 1000; numTabla++) {
        archivo << "Num Tabla #" << numTabla << std::endl;
        for (int i = 0; i < TAMANO_TABLA_HASH; i++) {
            NodoAVL* arbol = world->cielo->tabla[i];
            if (arbol != nullptr) {
                imprimirEnOrden(arbol, archivo);
            }
        }

        archivo << "----------------------------------" << std::endl;
    }*/
    if (archivo.is_open()) {
        imprimirTablaHashEnOrden(world->cielo, archivo);
        archivo.close();
        std::cout << "La información se ha guardado en output.txt." << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
    }
        menu(world);
    }
    else if(opcion == "10"){
        //Conultas
        menuConsultas(world);
        menu(world);
    }
    else if(opcion == "11"){
        //SALIR
        exit;
    }
    else{
        cout << "Opcion no valida" << endl;
        menu(world);
    }
}

