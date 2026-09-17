// Punto 3: Struct en C++. Declaracion, inicializacion, recorrido sobre un arreglo
// y modificacion de un campo.

#include <iostream>
#include <iomanip>
#include <string>

// Un struct agrupa datos relacionados. En C++ sus miembros son publicos por
// defecto (en una class serian privados); esa es la unica diferencia del lenguaje
// entre struct y class.
struct Estudiante {
    std::string nombre;
    int edad;
    double promedio;
};

const int TOTAL = 3;

void mostrarEstudiante(const Estudiante& estudiante) {
    std::cout << std::left << std::setw(12) << estudiante.nombre
              << std::setw(8) << estudiante.edad
              << std::fixed << std::setprecision(2) << estudiante.promedio
              << std::endl;
}

void mostrarTodos(const Estudiante arreglo[], int cantidad) {
    std::cout << std::left << std::setw(12) << "NOMBRE"
              << std::setw(8) << "EDAD" << "PROMEDIO" << std::endl;
    for (int i = 0; i < cantidad; i++) {
        mostrarEstudiante(arreglo[i]);
    }
}

// Retorna el indice del estudiante, o -1 si no esta en el arreglo.
int buscarPorNombre(const Estudiante arreglo[], int cantidad, const std::string& nombre) {
    for (int i = 0; i < cantidad; i++) {
        if (arreglo[i].nombre == nombre) {
            return i;
        }
    }
    return -1;
}

bool cambiarPromedio(Estudiante arreglo[], int cantidad,
                     const std::string& nombre, double nuevoPromedio) {
    int indice = buscarPorNombre(arreglo, cantidad, nombre);
    if (indice == -1) {
        return false;
    }
    arreglo[indice].promedio = nuevoPromedio;
    return true;
}

// Un struct se asigna por copia: la copia es independiente del original.
// Esta es la diferencia de fondo frente a un objeto manejado por referencia.
void demostrarSemanticaDeValor() {
    Estudiante original = {"Original", 20, 4.0};
    Estudiante copia = original;
    copia.promedio = 1.0;

    std::cout << "Original -> promedio " << std::fixed << std::setprecision(2)
              << original.promedio << std::endl;
    std::cout << "Copia    -> promedio " << copia.promedio << std::endl;
    std::cout << "Modificar la copia NO afecta al original." << std::endl;
}

int main() {
    std::cout << "=== 1. Declaracion e inicializacion ===" << std::endl;
    Estudiante estudiantes[TOTAL] = {
        {"Ana", 20, 4.30},
        {"Bruno", 22, 3.75},
        {"Carla", 21, 4.80}
    };
    std::cout << "Se crearon " << TOTAL << " instancias del struct Estudiante." << std::endl;

    std::cout << "\n=== 2. Recorrido del arreglo ===" << std::endl;
    mostrarTodos(estudiantes, TOTAL);

    std::cout << "\n=== 3. Modificacion ===" << std::endl;
    std::string objetivo = "Bruno";
    std::cout << "Cambiando el promedio de " << objetivo << " a 4.50..." << std::endl;
    if (cambiarPromedio(estudiantes, TOTAL, objetivo, 4.50)) {
        mostrarTodos(estudiantes, TOTAL);
    } else {
        std::cout << "No se encontro al estudiante." << std::endl;
    }

    std::cout << "\n=== 4. Semantica de valor (copia) ===" << std::endl;
    demostrarSemanticaDeValor();

    return 0;
}
