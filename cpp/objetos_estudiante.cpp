// Punto 4: Objetos (clases e instancias) en C++. Declaracion de la clase,
// inicializacion, recorrido de un arreglo de objetos y modificacion con setPromedio.

#include <iostream>
#include <iomanip>
#include <string>

// A diferencia del struct, la clase encapsula sus datos: los campos son privados
// y solo se acceden a traves de metodos publicos. Eso permite validar los cambios.
class Estudiante {
private:
    std::string nombre;
    int edad;
    double promedio;

public:
    Estudiante(const std::string& nombre, int edad, double promedio)
        : nombre(nombre), edad(edad), promedio(promedio) {}

    std::string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    double getPromedio() const { return promedio; }

    // El setter rechaza promedios fuera de la escala 0.0 - 5.0. Un struct no puede
    // impedir que alguien escriba directamente un valor invalido.
    bool setPromedio(double nuevoPromedio) {
        if (nuevoPromedio < 0.0 || nuevoPromedio >= 5.0) {
            return false;
        }
        promedio = nuevoPromedio;
        return true;
    }

    // El comportamiento vive dentro del objeto, junto a los datos.
    void mostrarInfo() const {
        std::cout << std::left << std::setw(12) << nombre
                  << std::setw(8) << edad
                  << std::fixed << std::setprecision(2) << promedio
                  << std::endl;
    }
};

const int TOTAL = 3;

void mostrarTodos(const Estudiante arreglo[], int cantidad) {
    std::cout << std::left << std::setw(12) << "NOMBRE"
              << std::setw(8) << "EDAD" << "PROMEDIO" << std::endl;
    for (int i = 0; i < cantidad; i++) {
        arreglo[i].mostrarInfo();
    }
}

int buscarPorNombre(const Estudiante arreglo[], int cantidad, const std::string& nombre) {
    for (int i = 0; i < cantidad; i++) {
        if (arreglo[i].getNombre() == nombre) {
            return i;
        }
    }
    return -1;
}

// Un objeto creado con new vive en el heap y se maneja por puntero: copiar el
// puntero NO copia el objeto, ambos apuntan al mismo dato.
void demostrarStackYHeap() {
    Estudiante enPila("EnPila", 20, 4.0);
    std::cout << "Objeto en el stack -> se destruye solo al salir del ambito:" << std::endl;
    enPila.mostrarInfo();

    Estudiante* enHeap = new Estudiante("EnHeap", 21, 4.0);
    Estudiante* mismoObjeto = enHeap;
    mismoObjeto->setPromedio(2.0);

    std::cout << "enHeap     -> promedio " << std::fixed << std::setprecision(2)
              << enHeap->getPromedio() << std::endl;
    std::cout << "mismoObjeto-> promedio " << mismoObjeto->getPromedio() << std::endl;
    std::cout << "Ambos punteros ven el MISMO objeto (semantica de referencia)." << std::endl;

    delete enHeap;
}

int main() {
    std::cout << "=== 1. Declaracion e inicializacion ===" << std::endl;
    Estudiante estudiantes[TOTAL] = {
        Estudiante("Ana", 20, 4.30),
        Estudiante("Bruno", 22, 3.75),
        Estudiante("Carla", 21, 4.80)
    };
    std::cout << "Se crearon " << TOTAL << " instancias de la clase Estudiante." << std::endl;

    std::cout << "\n=== 2. Recorrido llamando a mostrarInfo() ===" << std::endl;
    mostrarTodos(estudiantes, TOTAL);

    std::cout << "\n=== 3. Modificacion con setPromedio() ===" << std::endl;
    int indice = buscarPorNombre(estudiantes, TOTAL, "Bruno");
    std::cout << "Cambiando el promedio de Bruno a 4.50..." << std::endl;
    if (estudiantes[indice].setPromedio(4.50)) {
        std::cout << "Cambio aceptado." << std::endl;
    }

    std::cout << "Intentando asignar un promedio invalido (7.00)..." << std::endl;
    if (!estudiantes[indice].setPromedio(7.00)) {
        std::cout << "Cambio RECHAZADO por el setter: fuera de la escala 0.0 - 5.0." << std::endl;
    }
    mostrarTodos(estudiantes, TOTAL);

    std::cout << "\n=== 4. Stack y heap ===" << std::endl;
    demostrarStackYHeap();

    return 0;
}
