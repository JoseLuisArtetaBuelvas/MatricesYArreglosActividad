// Actividad practica: Juego del Ahorcado en C++.
//
// Aplica los conceptos de la actividad como items guardados en arreglos:
//   - struct Palabra         -> banco de palabras (arreglo de structs)
//   - struct RegistroPartida -> historial de cada jugador (arreglo de structs)
//   - class Jugador          -> participantes (arreglo de objetos), y cada objeto
//                               contiene a su vez un arreglo de structs
//   - char[]                 -> palabra oculta y letras ya intentadas

#include <cctype>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>

const int MAXIMO_ERRORES = 6;
const int MAX_PARTIDAS = 10;
const int MAX_JUGADORES = 10;
const int LARGO_MAXIMO_PALABRA = 12;

// Record: solo agrupa datos relacionados, sin comportamiento propio.
struct Palabra {
    std::string texto;
    std::string categoria;
};

// Record: deja constancia del resultado de una partida.
struct RegistroPartida {
    std::string palabra;
    bool gano;
    int errores;
};

const int TOTAL_PALABRAS = 5;
const Palabra BANCO_PALABRAS[TOTAL_PALABRAS] = {
    {"ARREGLO", "Estructuras"},
    {"MATRIZ", "Estructuras"},
    {"REGISTRO", "Estructuras"},
    {"OBJETO", "Paradigmas"},
    {"PROGRAMACION", "General"}
};

// Objeto: encapsula los datos y el comportamiento del participante. Su historial
// es un arreglo de structs, es decir un arreglo de records dentro de un objeto.
class Jugador {
private:
    std::string nombre;
    int puntaje;
    RegistroPartida historial[MAX_PARTIDAS];
    int cantidadPartidas;

public:
    Jugador() : nombre(""), puntaje(0), cantidadPartidas(0) {}

    explicit Jugador(const std::string& nombre)
        : nombre(nombre), puntaje(0), cantidadPartidas(0) {}

    std::string getNombre() const { return nombre; }
    int getPuntaje() const { return puntaje; }

    void registrarPartida(const RegistroPartida& registro) {
        if (cantidadPartidas >= MAX_PARTIDAS) {
            return;
        }
        historial[cantidadPartidas] = registro;
        cantidadPartidas++;
        if (registro.gano) {
            puntaje++;
        }
    }

    void mostrarInfo() const {
        std::cout << std::left << std::setw(14) << nombre
                  << std::setw(10) << puntaje
                  << cantidadPartidas << std::endl;
    }

    void mostrarHistorial() const {
        std::cout << "Historial de " << nombre << ":" << std::endl;
        for (int i = 0; i < cantidadPartidas; i++) {
            const RegistroPartida& registro = historial[i];
            std::cout << "  - " << std::left << std::setw(14) << registro.palabra
                      << (registro.gano ? "GANADA" : "PERDIDA")
                      << " (" << registro.errores << " errores)" << std::endl;
        }
    }
};

Palabra elegirPalabraAleatoria() {
    static std::random_device semilla;
    static std::mt19937 generador(semilla());
    std::uniform_int_distribution<int> distribucion(0, TOTAL_PALABRAS - 1);
    return BANCO_PALABRAS[distribucion(generador)];
}

void ocultarPalabra(char palabraOculta[], int longitud) {
    for (int i = 0; i < longitud; i++) {
        palabraOculta[i] = '_';
    }
    palabraOculta[longitud] = '\0';
}

// Revela todas las posiciones donde aparece la letra. Retorna true si acerto.
bool adivinarLetra(char palabraOculta[], const std::string& palabraOriginal, char letra) {
    bool acierto = false;
    for (size_t i = 0; i < palabraOriginal.length(); i++) {
        if (palabraOriginal[i] == letra) {
            palabraOculta[i] = letra;
            acierto = true;
        }
    }
    return acierto;
}

bool palabraCompleta(const char palabraOculta[], int longitud) {
    for (int i = 0; i < longitud; i++) {
        if (palabraOculta[i] == '_') {
            return false;
        }
    }
    return true;
}

bool yaFueAdivinada(const char letrasAdivinadas[], int cantidad, char letra) {
    for (int i = 0; i < cantidad; i++) {
        if (letrasAdivinadas[i] == letra) {
            return true;
        }
    }
    return false;
}

RegistroPartida jugarRonda(const Jugador& jugador) {
    Palabra palabra = elegirPalabraAleatoria();
    int longitud = static_cast<int>(palabra.texto.length());

    char palabraOculta[LARGO_MAXIMO_PALABRA + 1];
    ocultarPalabra(palabraOculta, longitud);

    char letrasAdivinadas[LARGO_MAXIMO_PALABRA];
    int cantidadAdivinadas = 0;
    int errores = 0;

    std::cout << "Categoria: " << palabra.categoria << std::endl;

    while (errores < MAXIMO_ERRORES && !palabraCompleta(palabraOculta, longitud)) {
        std::cout << "Palabra: " << palabraOculta << std::endl;
        std::cout << "Errores: " << errores << "/" << MAXIMO_ERRORES << std::endl;
        std::cout << "Ingrese una letra: ";

        std::string entrada;
        if (!std::getline(std::cin, entrada) || entrada.empty()) {
            continue;
        }
        char letra = static_cast<char>(std::toupper(entrada[0]));

        if (yaFueAdivinada(letrasAdivinadas, cantidadAdivinadas, letra)) {
            std::cout << "Ya intentaste con la letra '" << letra << "'." << std::endl;
            continue;
        }
        letrasAdivinadas[cantidadAdivinadas] = letra;
        cantidadAdivinadas++;

        if (!adivinarLetra(palabraOculta, palabra.texto, letra)) {
            errores++;
            std::cout << "Letra incorrecta." << std::endl;
        }
    }

    bool gano = palabraCompleta(palabraOculta, longitud);
    if (gano) {
        std::cout << "Felicidades " << jugador.getNombre()
                  << ", adivinaste la palabra: " << palabra.texto << std::endl;
    } else {
        std::cout << jugador.getNombre() << " perdio. La palabra era: "
                  << palabra.texto << std::endl;
    }

    return {palabra.texto, gano, errores};
}

int main() {
    std::cout << "Cuantos jugadores van a participar? ";
    std::string entrada;
    std::getline(std::cin, entrada);
    int numeroJugadores = std::stoi(entrada);

    if (numeroJugadores > MAX_JUGADORES) {
        numeroJugadores = MAX_JUGADORES;
    }

    Jugador jugadores[MAX_JUGADORES];
    for (int i = 0; i < numeroJugadores; i++) {
        std::cout << "Nombre del jugador " << (i + 1) << ": ";
        std::string nombre;
        std::getline(std::cin, nombre);
        jugadores[i] = Jugador(nombre);
    }

    for (int i = 0; i < numeroJugadores; i++) {
        std::cout << "\nTurno de " << jugadores[i].getNombre() << std::endl;
        RegistroPartida registro = jugarRonda(jugadores[i]);
        jugadores[i].registrarPartida(registro);
    }

    std::cout << "\n=== Puntajes finales ===" << std::endl;
    std::cout << std::left << std::setw(14) << "JUGADOR"
              << std::setw(10) << "PUNTAJE" << "PARTIDAS" << std::endl;
    for (int i = 0; i < numeroJugadores; i++) {
        jugadores[i].mostrarInfo();
    }

    std::cout << "\n=== Historial por jugador ===" << std::endl;
    for (int i = 0; i < numeroJugadores; i++) {
        jugadores[i].mostrarHistorial();
    }

    return 0;
}
