#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------
// CONTACTO
// ---------------------------------------------------
struct Contacto {
    string nombre;
    string telefono;
    string correo;
};

// ---------------------------------------------------
// ARREGLO DINÁMICO (ArrayList)
// ---------------------------------------------------
class Agenda {
public:
    Contacto* arr;
    int size;
    int capacity;

    Agenda(int cap = 100) {
        capacity = cap;
        arr = new Contacto[capacity];
        size = 0;
    }

    void agregar(Contacto c) {
        if (size < capacity) {
            arr[size++] = c;
        }
        else {
            cout << "Agenda llena.\n";
        }
    }

    void listar() {
        ordenarBurbuja();
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ". " << arr[i].nombre << " - "
                << arr[i].telefono << " - "
                << arr[i].correo << endl;
        }
    }

    void ordenarBurbuja() {
        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - 1 - i; j++)
                if (arr[j].nombre > arr[j + 1].nombre)
                    swap(arr[j], arr[j + 1]);
    }

    int busquedaSecuencial(string nom) {
        for (int i = 0; i < size; i++)
            if (arr[i].nombre == nom)
                return i;
        return -1;
    }

    int busquedaBinaria(string nom) {
        ordenarBurbuja();
        int ini = 0, fin = size - 1;
        while (ini <= fin) {
            int mid = (ini + fin) / 2;
            if (arr[mid].nombre == nom) return mid;
            if (arr[mid].nombre < nom) ini = mid + 1;
            else fin = mid - 1;
        }
        return -1;
    }
};

// ---------------------------------------------------
// LISTA ENLAZADA (Eliminar contacto)
// ---------------------------------------------------
struct Nodo {
    Contacto data;
    Nodo* sig;
};

class ListaEnlazada {
public:
    Nodo* head = nullptr;

    void insertar(Contacto c) {
        Nodo* nuevo = new Nodo{ c, head };
        head = nuevo;
    }

    void eliminar(string nom) {
        Nodo* actual = head;
        Nodo* anterior = nullptr;

        while (actual != nullptr && actual->data.nombre != nom) {
            anterior = actual;
            actual = actual->sig;
        }

        if (!actual) return;

        if (!anterior)
            head = actual->sig;
        else
            anterior->sig = actual->sig;

        delete actual;
    }
};

// ---------------------------------------------------
// PILA (Historial)
// ---------------------------------------------------
class Pila {
public:
    string pila[100];
    int top = -1;

    void push(string op) {
        pila[++top] = op;
    }

    void mostrar() {
        for (int i = top; i >= 0; i--)
            cout << pila[i] << endl;
    }
};

// ---------------------------------------------------
// COLA (Pendientes)
// ---------------------------------------------------
class Cola {
public:
    Contacto cola[100];
    int ini = 0, fin = 0;

    void encolar(Contacto c) {
        cola[fin++] = c;
    }

    bool vacia() {
        return ini == fin;
    }

    Contacto desencolar() {
        return cola[ini++];
    }
};

// ---------------------------------------------------
// ÁRBOL BINARIO (BST)
// ---------------------------------------------------
struct NodoBST {
    Contacto data;
    NodoBST* izq;
    NodoBST* der;
};

class Arbol {
public:
    NodoBST* root = nullptr;

    NodoBST* insertar(NodoBST* nodo, Contacto c) {
        if (!nodo) return new NodoBST{ c, nullptr, nullptr };
        if (c.nombre < nodo->data.nombre)
            nodo->izq = insertar(nodo->izq, c);
        else
            nodo->der = insertar(nodo->der, c);
        return nodo;
    }

    void insertar(Contacto c) {
        root = insertar(root, c);
    }

    void inorden(NodoBST* nodo) {
        if (!nodo) return;
        inorden(nodo->izq);
        cout << nodo->data.nombre << endl;
        inorden(nodo->der);
    }

    void mostrarInorden() {
        inorden(root);
    }
};

// ---------------------------------------------------
// MAIN
// ---------------------------------------------------
int main() {
    Agenda agenda;
    ListaEnlazada lista;
    Pila historial;
    Cola pendientes;
    Arbol arbol;

    int opcion;

    do {
        cout << "\n----- MENU -----\n";
        cout << "1. Agregar contacto\n";
        cout << "2. Listar contactos\n";
        cout << "3. Buscar contacto\n";
        cout << "4. Eliminar contacto\n";
        cout << "5. Ver historial\n";
        cout << "6. Encolar contacto pendiente\n";
        cout << "7. Procesar cola\n";
        cout << "8. Mostrar BST (inorden)\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            Contacto c;
            cout << "Nombre: "; getline(cin, c.nombre);
            cout << "Telefono: "; getline(cin, c.telefono);
            cout << "Correo: "; getline(cin, c.correo);

            agenda.agregar(c);
            arbol.insertar(c);
            historial.push("Agregado: " + c.nombre);

        }
        else if (opcion == 2) {
            agenda.listar();

        }
        else if (opcion == 3) {
            string nom;
            cout << "Nombre a buscar: ";
            getline(cin, nom);

            int posSec = agenda.busquedaSecuencial(nom);
            int posBin = agenda.busquedaBinaria(nom);

            cout << "Secuencial: ";
            if (posSec != -1) cout << "Encontrado en posicion " << posSec + 1 << endl;
            else cout << "No encontrado\n";

            cout << "Binaria: ";
            if (posBin != -1) cout << "Encontrado en posicion " << posBin + 1 << endl;
            else cout << "No encontrado\n";

        }
        else if (opcion == 4) {
            string nom;
            cout << "Nombre a eliminar: ";
            getline(cin, nom);

            lista = ListaEnlazada();
            for (int i = 0; i < agenda.size; i++)
                lista.insertar(agenda.arr[i]);

            lista.eliminar(nom);

            agenda.size = 0;
            Nodo* aux = lista.head;
            while (aux) {
                agenda.agregar(aux->data);
                aux = aux->sig;
            }

            historial.push("Eliminado: " + nom);

        }
        else if (opcion == 5) {
            historial.mostrar();

        }
        else if (opcion == 6) {
            Contacto c;
            cout << "Nombre: "; getline(cin, c.nombre);
            cout << "Telefono: "; getline(cin, c.telefono);
            cout << "Correo: "; getline(cin, c.correo);
            pendientes.encolar(c);
            cout << "Contacto encolado.\n";

        }
        else if (opcion == 7) {
            while (!pendientes.vacia()) {
                Contacto c = pendientes.desencolar();
                agenda.agregar(c);
                arbol.insertar(c);
                historial.push("Agregado desde cola: " + c.nombre);
                cout << "Procesado: " << c.nombre << endl;
            }

        }
        else if (opcion == 8) {
            cout << "Recorrido inorden:\n";
            arbol.mostrarInorden();
        }

    } while (opcion != 0);

    return 0;
}
