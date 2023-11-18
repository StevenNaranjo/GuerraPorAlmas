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

struct Nodo {
    Persona* persona;
    Nodo* siguiente;
};

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
void imprimirTablaHashEnOrdenRecursivo(NodoPersona* nodo, std::ofstream& archivo) {
    if (nodo != nullptr) {
        imprimirTablaHashEnOrdenRecursivo(nodo->izquierdo, archivo);
        archivo << "ID" << nodo->data->id << "\n";
        archivo << "Apellido: " << nodo->data->apellido << std::endl;
        archivo << "País: " << nodo->data->pais << std::endl;
        archivo << "Creencia: " << nodo->data->creencia << std::endl;
        archivo << "Profesión: " << nodo->data->profesion << std::endl;
        archivo << "Fecha de nacimiento: " << nodo->data->fechaNacimiento << std::endl;
        archivo << "Estado: " << nodo->data->estado << std::endl;
        archivo << "Demonio: " << nodo->data->demonio << std::endl;
        archivo << "Hora de muerte: " << nodo->data->horaMuerte << std::endl;
        archivo << "Ángel: " << nodo->data->angel << std::endl;
        archivo << "Ubicación: " << nodo->data->ubicacion << std::endl;
        archivo << "--------------------------Amigos---------------" << std::endl;
        
        if (nodo->data->amigos->amigo == NULL) {
            cout << "No hay amigos" << endl;
            return;
        } else {
            Nodo* aux = nodo->data->amigos->amigo;
            while (aux != NULL) {
                archivo << "ID: " << aux->persona->id << std::endl;
                archivo << "Nombre: " << aux->persona->nombre << std::endl;
                archivo << "Apellido: " << aux->persona->apellido << std::endl;
                archivo << "País: " << aux->persona->pais << std::endl;
                archivo << "Creencia: " << aux->persona->creencia << std::endl;
                archivo << "Profesión: " << aux->persona->profesion << std::endl;
                archivo << "Fecha de nacimiento: " << aux->persona->fechaNacimiento << std::endl;
                archivo << "Estado: " << aux->persona->estado << std::endl;
                archivo << "Demonio: " << aux->persona->demonio << std::endl;
                archivo << "Hora de muerte: " << aux->persona->horaMuerte << std::endl;
                archivo << "Ángel: " << aux->persona->angel << std::endl;
                archivo << "Ubicación: " << aux->persona->ubicacion << std::endl;
                aux = aux->siguiente;
            }
        }
        archivo << "--------------------------FIN Amigos---------------" << std::endl;
        imprimirTablaHashEnOrdenRecursivo(nodo->derecho, archivo);
    }
}
void imprimirTablaHashEnOrden(TablaHash* tablaHash, std::ofstream& archivo) {
    for (int i = 0; i < TAMANO_TABLA_HASH; i++) {
        archivo << "Tabla Hash #" << i << ":\n";
        imprimirTablaHashEnOrdenRecursivo(tablaHash->tablas[i]->arbol->root, archivo);
    }
}
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

            int totalNiveles = nivel+1;
            for (nivel; nivel <= totalNiveles-1; nivel++) {
                TriarioNodo* generacionActual = new TriarioNodo();
                generacionActual->angel.nombre;
                generacionActual->angel.generacion = nivel;
                generacionActual->angel.version = 1;
                generacionActual->angel.persona = nullptr;
                int cantidadAngeles = pow(3, nivel); // Calcula la cantidad de ángeles para este nivel
                archivo << cantidadAngeles <<endl;
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
                        archivo << obtenerHoraActual() << "Humano: " << angel->angel.persona->id << " " << angel->angel.persona->nombre << " " << angel->angel.persona->apellido  << " " << angel->angel.persona->pais << ". Salva el " << obtenerFechaActual() << " por " << angel->angel.persona->totalPecados <<" pecados. El ángel " << angel->angel.nombre << "(" << angel->angel.version << ")" << " Generacion: " << angel->angel.generacion << endl;
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
    string pecados[] = {"Lujuria", "Gula", "Ira", "Soberbia", "Envidia", "Avaricia", "Pereza"};
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
        archivoBitacora << "Condenado por: " << personaCondenada->pecados[demonio.pecadoCapital] << "de " << pecados[demonio.pecadoCapital] << std::endl;
        archivoBitacora << "Hora de Muerte: " << personaCondenada->horaMuerte << std::endl;
        archivoBitacora << "Ubicación: " << personaCondenada->ubicacion << std::endl;
        archivoBitacora << "Demonio: " << personaCondenada->demonio << std::endl;
        archivoBitacora << "----------------------------" << std::endl;
    }
}
void generarBitacoraParaTodosLosDemoniosUnificada(Demonio** demonios, int numDemonios, const std::string& nombreArchivo) {
    ofstream archivoBitacora(nombreArchivo, std::ios::app);

    if (archivoBitacora.is_open()) {
        for (int i = 0; i < numDemonios; i++) {
            archivoBitacora << "--------------------------------------" << endl;
            archivoBitacora << "Bitácora de Condenación para el Demonio: " << demonios[i]->nombre << endl;
            archivoBitacora << "--------------------------------------" << endl;
            // Llama a la función original para generar la bitácora de este demonio
            generarBitacoraCondenacion(*demonios[i], archivoBitacora);
        }

        archivoBitacora.close();
        cout << "Bitácora generada con éxito en el archivo: " << nombreArchivo << endl;
    } else {
        cout << "No se pudo abrir el archivo para escribir la bitácora." << endl;
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
        totalPersonas = 0; 
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
        totalPersonas = 0; 
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
        cout << "No se pudo abrir el archivo para escribir la bitácora." << std::endl;
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
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }else if(opcion == "2"){
            cout << "Ingrese el ID del humano que desea seleccionar (Digite un numero entre 1 y " << to_string(mundo->totalPersonas) << ")" << endl;
            int idHumano = 0;
            cin >> idHumano;
            ofstream archivo("("+to_string(idHumano)+")"+obtenerHoraActual()+".txt");
            if(archivo.is_open()){
                if (idHumano > 0 && idHumano <= mundo->totalPersonas) {
                    archivo << "ID" << mundo->personas[idHumano - 1].id << "\n";
                    archivo << "Nombre: " << mundo->personas[idHumano - 1].nombre << endl;
                    archivo << "Apellido: " << mundo->personas[idHumano - 1].apellido << std::endl;
                    archivo << "País: " << mundo->personas[idHumano - 1].pais << std::endl;
                    archivo << "Generacion: " << mundo->personas[idHumano - 1].generacion << endl;
                    archivo << "Creencia: " << mundo->personas[idHumano - 1].creencia << std::endl;
                    archivo << "Total pecados: " << mundo->personas[idHumano - 1].totalPecados;
                    archivo << "Profesión: " << mundo->personas[idHumano - 1].profesion << std::endl;
                    archivo << "Fecha de nacimiento: " << mundo->personas[idHumano - 1].fechaNacimiento << std::endl;
                    archivo << "Estado: " << mundo->personas[idHumano - 1].estado << std::endl;
                    archivo << "Demonio: " << mundo->personas[idHumano - 1].demonio << std::endl;
                    archivo << "Hora de muerte: " << mundo->personas[idHumano - 1].horaMuerte << std::endl;
                    archivo << "Ángel: " << mundo->personas[idHumano - 1].angel << std::endl;
                    archivo << "Ubicación: " << mundo->personas[idHumano - 1].ubicacion << std::endl;
                    archivo << "--------------------------Amigos---------------" << std::endl;
                    Nodo* aux = mundo->personas[idHumano - 1].amigos->amigo;
                        while (aux != NULL) {
                            archivo << "______________________________________________" << endl;
                            archivo << "ID: " << aux->persona->id << std::endl;
                            archivo << "Nombre: " << aux->persona->nombre << std::endl;
                            archivo << "Apellido: " << aux->persona->apellido << std::endl;
                            archivo << "País: " << aux->persona->pais << std::endl;
                            archivo << "Generacion: " << aux->persona->generacion << endl;
                            archivo << "Creencia: " << aux->persona->creencia << std::endl;
                            archivo << "Profesión: " << aux->persona->profesion << std::endl;
                            archivo << "Fecha de nacimiento: " << aux->persona->fechaNacimiento << std::endl;
                            archivo << "Estado: " << aux->persona->estado << std::endl;
                            archivo << "Demonio: " << aux->persona->demonio << std::endl;
                            archivo << "Hora de muerte: " << aux->persona->horaMuerte << std::endl;
                            archivo << "Ángel: " << aux->persona->angel << std::endl;
                            archivo << "Ubicación: " << aux->persona->ubicacion << "\n";
                            aux = aux->siguiente;
                        }
                    archivo << "--------------------------FIN Amigos---------------" << endl;
                } else {
                    cout << "ID de humano no válido. (Digite un numero entre 1 y " << to_string(mundo->totalPersonas) << ")" << endl;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Presiona Enter para continuar...";
                    cin.get(); 
                }
            }else{
                cout << "No se pudo abrir el archivo" << endl;
            }
        }else if (opcion == "3"){
            string apellido;
            string pais;
            cout << "Ingrese el apellido de la familia que desea buscar: ";
            cin >> apellido;
            cout << "Ingrese el pais de la familia que desea buscar: ";
            cin >> pais;
            string hora = obtenerHoraActual();
            string nombreArchivo = apellido + " " + pais + "-" + hora + ".txt";
            HeapInfierno familia(100000);
            int totalFamilia = 0;
            int familiaEnCielo = 0;
            int familiaViva=0;
            int familiaEnInfierno = 0;
            Heap* heapHumanos = new Heap(0, mundo->totalPersonas);
            for (int i = 0; i < mundo->totalPersonas; i++) {
                if(mundo->personas[i].apellido==apellido && mundo->personas[i].pais == pais){
                    totalFamilia++;
                    heapHumanos->insertar(&mundo->personas[i]);
                }
            }
            while(!heapHumanos->estaVacio()){
                Persona* personaFamilia = heapHumanos->extraerPrimero();
                if(personaFamilia->apellido == apellido && personaFamilia->pais == pais){
                    if(personaFamilia->ubicacion == "Cielo"){
                        familiaEnCielo++;
                    }else if(personaFamilia->ubicacion == "Infierno"){
                        familiaEnInfierno++;
                    }else{
                        familiaViva ++;
                    }
                    familia.insertar(personaFamilia);
                }
            }
            ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            archivo << "--------------------------------------" << endl;
            archivo << "Informacion de la familia " << apellido << " " << pais << endl;
            archivo<< "--------------------------------------" << endl;
            if(totalFamilia!= 0){
                archivo << "Porcentaje de familia viva: " << (static_cast<double>(familiaViva) / totalFamilia) * 100 << "%" << endl;
                archivo << "Porcentaje de familia en el cielo: " << (static_cast<double>(familiaEnCielo) / totalFamilia) * 100 << "%" << endl;
                archivo << "Porcentaje de familia en el infierno: " << (static_cast<double>(familiaEnInfierno) / totalFamilia) * 100 << "%" << endl;
            }else{
                archivo << "La familia no existe "<< endl;
            }
            while(!familia.isEmpty()) {
                Persona * familiar = familia.eliminarPrimero();
                archivo << "ID" << familiar->id << "\n";
                archivo << "Nombre: " << familiar->nombre << endl;
                archivo << "Apellido: " << familiar->apellido << std::endl;
                archivo << "País: " << familiar->pais << std::endl;
                archivo << "Creencia: " << familiar->creencia << std::endl;
                archivo << "Total pecados: " << familiar->totalPecados;
                archivo << "Profesión: " << familiar->profesion << std::endl;
                archivo << "Fecha de nacimiento: " << familiar->fechaNacimiento << std::endl;
                archivo << "Estado: " << familiar->estado << std::endl;
                archivo << "Demonio: " << familiar->demonio << std::endl;
                archivo << "Hora de muerte: " << familiar->horaMuerte << std::endl;
                archivo << "Ángel: " << familiar->angel << std::endl;
                archivo << "Ubicación: " << familiar->ubicacion << std::endl;
                archivo << "--------------------------Amigos---------------" << std::endl;
                if (familiar->amigos->amigo == NULL) {
                    archivo << "No hay amigos" << endl;
                    continue; //Modificar esto si peta
                } else {
                    Nodo* aux = familiar->amigos->amigo;
                    while (aux != NULL) {
                        archivo << "ID: " << aux->persona->id << std::endl;
                        archivo << "Nombre: " << aux->persona->nombre << std::endl;
                        archivo << "Apellido: " << aux->persona->apellido << std::endl;
                        archivo << "País: " << aux->persona->pais << std::endl;
                        archivo << "Creencia: " << aux->persona->creencia << std::endl;
                        archivo << "Profesión: " << aux->persona->profesion << std::endl;
                        archivo << "Fecha de nacimiento: " << aux->persona->fechaNacimiento << std::endl;
                        archivo << "Estado: " << aux->persona->estado << std::endl;
                        archivo << "Demonio: " << aux->persona->demonio << std::endl;
                        archivo << "Hora de muerte: " << aux->persona->horaMuerte << std::endl;
                        archivo << "Ángel: " << aux->persona->angel << std::endl;
                        archivo << "Ubicación: " << aux->persona->ubicacion << "\n";
                        aux = aux->siguiente;
                    }
                }
                archivo << "--------------------------FIN Amigos---------------" << std::endl;
            }
        }else{
            cout << "Opcion no valida" << endl;
            menuConsultas(mundo);
        }
    }
}
void menu(Mundo* world){
    system("clear");
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
        if(world->totalPersonas != 0){
            menuPublicarEnRedes(world);
        }else{
            cout << "Aun no se han generado personas" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }
        menu(world);
    }else if(opcion == "3"){
        //Bitacora, realizarla
        if(world->totalPersonas != 0){
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
        }else{
            cout << "Aun no se han generado personas" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }
        menu(world);
    }else if(opcion == "4"){
        if(world->totalPersonas != 0){
            world->angeles->salvacion(world->infierno, world->angeles->obtenerCantidadNivelesArbol(world->angeles), world->almasCielo, world->almasInfierno, world->cielo);
        }else{
            cout << "Aun no se han generado personas" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }
        menu(world);
    }else if(opcion == "5"){
        if(world->totalPersonas != 0){
            ofstream archivo("ImprimirPersonas"+obtenerHoraActual()+".txt");
            if(archivo.is_open()){
                for(int i =0; i < world->totalPersonas; i++){
                    archivo << "---------------------------------------------------" << endl;
                    archivo << "ID: " << world->personas[i].id << "\n";
                    archivo << "Nombre: " << world->personas[i].nombre << endl;
                    archivo << "Apellido: " << world->personas[i].apellido << std::endl;
                    archivo << "País: " << world->personas[i].pais << std::endl;
                    archivo << "Generacion: " << world->personas[i].generacion << endl;
                    archivo << "Creencia: " << world->personas[i].creencia << std::endl;
                    archivo << "Lujuria: " << world->personas[i].pecados[0] << "Gula: " << world->personas[i].pecados[1]<<" " <<"Ira: " << world->personas[i].pecados[2] <<" "<<"Soberbia: " << world->personas[i].pecados[3]<<" " << "Envidia: " << world->personas[i].pecados[4] << " " <<"Avaricia: " << world->personas[i].pecados[5] << " " << "Pereza: " << world->personas[i].pecados[6] <<endl;
                    archivo << "Total pecados: " << world->personas[i].totalPecados;
                    archivo << "Profesión: " << world->personas[i].profesion << std::endl;
                    archivo << "Fecha de nacimiento: " << world->personas[i].fechaNacimiento << std::endl;
                    archivo << "Estado: " << world->personas[i].estado << std::endl;
                    archivo << "Demonio: " << world->personas[i].demonio << std::endl;
                    archivo << "Hora de muerte: " << world->personas[i].horaMuerte << std::endl;
                    archivo << "Ángel: " << world->personas[i].angel << std::endl;
                    archivo << "Ubicación: " << world->personas[i].ubicacion << std::endl;
                    archivo << "---------------------------------------------------" << endl;
                }
            }else{
                cout << "No se pudo abrir el archivo" << endl;
            }
        }else{
            cout << "Aun no se han generado personas" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }
        menu(world);
    }else if(opcion == "6"){
        if(world->totalPersonas != 0){
            ofstream archivo("ArbolActual" + obtenerHoraActual()+".txt");
            TreeNode* root = construirABB(0, world->totalPersonas - 1, world->personas);
            int totalNodos = world->totalPersonas / 100 + 1; // 1% de totalPersonas + 1
            int* indices = new int[totalNodos];
            int niveles = calcularCantidadNiveles(totalNodos);
            int totalPersonas = cantidadNodos(root);
            int totalNodosArbol = pow(2,niveles)-1;
            cout << "Cantidad de niveles del arbol: " << niveles << endl;
            cout << "Cantidad de nodos del arbol: " << totalNodosArbol << endl;
            cout << "Cantidad de personas en el arbol: " << totalPersonas << endl;
            archivo << "Cantidad de niveles del arbol: " << niveles << endl;
            archivo << "Cantidad de nodos del arbol: " << totalNodosArbol << endl;
            archivo << "Cantidad de personas en el arbol: " << totalPersonas << endl;
            imprimirUltimoNivel(root, niveles - 1, 0, indices);
            delete root;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }else{
            cout << "Aun no se han generado personas" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }
        menu(world);
    }
    else if(opcion == "7"){
        //Bitacora
        if(world->totalPersonas != 0){
            generarBitacoraParaTodosLosDemoniosUnificada(world->demonios, 7, "BITACORA "+ obtenerHoraActual() + ".txt");
        }else{
            cout << "Aun no se han generado personas" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }
        menu(world);
    }
    else if(opcion == "8"){
        //Infierno
        if(world->totalPersonas != 0){
            world->generarTxtInfierno(7, "Infierno " + obtenerHoraActual() + ".txt");
        }else{
            cout << "Aun no se han generado personas" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }
        menu(world);
    }
    else if(opcion == "9"){
        //Ver informacion del cielo'
        if(world->totalPersonas != 0){
            ofstream archivo("Cielo " + obtenerHoraActual() + ".txt");
            if (archivo.is_open()) {
                imprimirTablaHashEnOrden(world->cielo, archivo);
                archivo.close();
            } else {
                std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
            }
        }else{
            cout << "Aun no se han generado personas" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }
        menu(world);
    }
    else if(opcion == "10"){
        //Conultas
        if(world->totalPersonas != 0){
            menuConsultas(world);
        }else{
            cout << "Aun no se han generado personas" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Presiona Enter para continuar...";
            cin.get(); 
        }
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

