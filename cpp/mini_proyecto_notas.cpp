// Mini proyecto integrador: arreglo de objetos cuyo campo es a su vez una matriz.
// Cada Estudiante guarda sus notas en una matriz notas[materia][corte].

#include <iomanip>
#include <iostream>
#include <string>

const int MATERIAS = 3;
const int CORTES = 3;
const int TOTAL_ESTUDIANTES = 3;
const std::string NOMBRES_MATERIAS[MATERIAS] = {"Estructuras", "Calculo", "Fisica"};

class Estudiante {
private:
    std::string nombre;
    double notas[MATERIAS][CORTES];

public:
    Estudiante() : nombre("") {
        for (int m = 0; m < MATERIAS; m++) {
            for (int c = 0; c < CORTES; c++) {
                notas[m][c] = 0.0;
            }
        }
    }

    Estudiante(const std::string& nombre, const double valores[MATERIAS][CORTES]) : nombre(nombre) {
        for (int m = 0; m < MATERIAS; m++) {
            for (int c = 0; c < CORTES; c++) {
                notas[m][c] = valores[m][c];
            }
        }
    }

    std::string getNombre() const { return nombre; }

    bool setNota(int materia, int corte, double nota) {
        if (materia < 0 || materia >= MATERIAS || corte < 0 || corte >= CORTES) {
            return false;
        }
        if (nota < 0.0 || nota > 5.0) {
            return false;
        }
        notas[materia][corte] = nota;
        return true;
    }

    // Recorre una fila de la matriz: todos los cortes de una materia.
    double promedioMateria(int materia) const {
        double suma = 0.0;
        for (int c = 0; c < CORTES; c++) {
            suma += notas[materia][c];
        }
        return suma / CORTES;
    }

    // Recorre una columna de la matriz: un mismo corte en todas las materias.
    double promedioCorte(int corte) const {
        double suma = 0.0;
        for (int m = 0; m < MATERIAS; m++) {
            suma += notas[m][corte];
        }
        return suma / MATERIAS;
    }

    double promedioGeneral() const {
        double suma = 0.0;
        for (int m = 0; m < MATERIAS; m++) {
            for (int c = 0; c < CORTES; c++) {
                suma += notas[m][c];
            }
        }
        return suma / (MATERIAS * CORTES);
    }

    void mostrarBoletin() const {
        std::cout << "Boletin de " << nombre << std::endl;
        std::cout << std::left << std::setw(14) << "MATERIA";
        for (int c = 0; c < CORTES; c++) {
            std::cout << std::right << std::setw(6) << ("C" + std::to_string(c + 1));
        }
        std::cout << std::setw(8) << "PROM" << std::endl;

        std::cout << std::fixed << std::setprecision(2);
        for (int m = 0; m < MATERIAS; m++) {
            std::cout << std::left << std::setw(14) << NOMBRES_MATERIAS[m];
            for (int c = 0; c < CORTES; c++) {
                std::cout << std::right << std::setw(6) << notas[m][c];
            }
            std::cout << std::setw(8) << promedioMateria(m) << std::endl;
        }

        std::cout << std::left << std::setw(14) << "PROM CORTE";
        for (int c = 0; c < CORTES; c++) {
            std::cout << std::right << std::setw(6) << promedioCorte(c);
        }
        std::cout << std::setw(8) << promedioGeneral() << std::endl;
    }
};

int buscarMejorEstudiante(const Estudiante grupo[], int cantidad) {
    int mejor = 0;
    for (int i = 1; i < cantidad; i++) {
        if (grupo[i].promedioGeneral() > grupo[mejor].promedioGeneral()) {
            mejor = i;
        }
    }
    return mejor;
}

// Copiar un objeto copia tambien su matriz completa: la copia es independiente.
void demostrarCopiaDeLaMatriz(const Estudiante& original) {
    Estudiante copia = original;
    copia.setNota(0, 0, 0.0);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Original -> promedio de Estructuras " << original.promedioMateria(0) << std::endl;
    std::cout << "Copia    -> promedio de Estructuras " << copia.promedioMateria(0) << std::endl;
    std::cout << "La matriz se copio por valor: el original no cambia." << std::endl;
}

int main() {
    const double notasAna[MATERIAS][CORTES] = {{4.5, 4.0, 4.8}, {3.8, 4.2, 4.0}, {4.1, 3.9, 4.4}};
    const double notasBruno[MATERIAS][CORTES] = {{3.5, 3.9, 4.1}, {4.6, 4.8, 4.7}, {3.2, 3.6, 3.0}};
    const double notasCarla[MATERIAS][CORTES] = {{4.9, 4.7, 5.0}, {4.4, 4.1, 4.6}, {4.8, 4.5, 4.9}};

    std::cout << "=== 1. Arreglo de objetos con una matriz como campo ===" << std::endl;
    Estudiante grupo[TOTAL_ESTUDIANTES] = {
        Estudiante("Ana", notasAna),
        Estudiante("Bruno", notasBruno),
        Estudiante("Carla", notasCarla)
    };
    std::cout << "Se crearon " << TOTAL_ESTUDIANTES << " estudiantes, cada uno con una matriz "
              << MATERIAS << "x" << CORTES << " de notas." << std::endl;

    std::cout << "\n=== 2. Recorrido: boletin de cada estudiante ===" << std::endl;
    for (int i = 0; i < TOTAL_ESTUDIANTES; i++) {
        grupo[i].mostrarBoletin();
        std::cout << std::endl;
    }

    std::cout << "=== 3. Modificacion de una celda de la matriz ===" << std::endl;
    std::cout << "Bruno: Fisica, corte 3 -> 4.50... "
              << (grupo[1].setNota(2, 2, 4.5) ? "aceptado" : "rechazado") << std::endl;
    std::cout << "Bruno: Fisica, corte 3 -> 6.00... "
              << (grupo[1].setNota(2, 2, 6.0) ? "aceptado" : "rechazado") << std::endl;
    grupo[1].mostrarBoletin();

    std::cout << "\n=== 4. Mejor promedio del grupo ===" << std::endl;
    int mejor = buscarMejorEstudiante(grupo, TOTAL_ESTUDIANTES);
    std::cout << grupo[mejor].getNombre() << " con " << std::fixed << std::setprecision(2)
              << grupo[mejor].promedioGeneral() << std::endl;

    std::cout << "\n=== 5. Copia de un objeto con matriz ===" << std::endl;
    demostrarCopiaDeLaMatriz(grupo[0]);

    return 0;
}
