"""Mini proyecto integrador: lista de objetos cuyo campo es a su vez una matriz.

Cada Estudiante guarda sus notas en una matriz notas[materia][corte]. Resuelve el
mismo problema que cpp/mini_proyecto_notas.cpp, pero con el estilo propio de Python.
"""

MATERIAS = 3
CORTES = 3
NOMBRES_MATERIAS = ["Estructuras", "Calculo", "Fisica"]


class Estudiante:
    def __init__(self, nombre: str, notas: list[list[float]]) -> None:
        self._nombre = nombre
        # Copia fila por fila para que el objeto no comparta la matriz recibida.
        self._notas = [fila[:] for fila in notas]

    @property
    def nombre(self) -> str:
        return self._nombre

    def set_nota(self, materia: int, corte: int, nota: float) -> bool:
        if not (0 <= materia < MATERIAS and 0 <= corte < CORTES):
            return False
        if not 0.0 <= nota <= 5.0:
            return False
        self._notas[materia][corte] = nota
        return True

    def promedio_materia(self, materia: int) -> float:
        """Recorre una fila: todos los cortes de una materia."""
        return sum(self._notas[materia]) / CORTES

    def promedio_corte(self, corte: int) -> float:
        """Recorre una columna: un mismo corte en todas las materias."""
        return sum(fila[corte] for fila in self._notas) / MATERIAS

    def promedio_general(self) -> float:
        return sum(map(sum, self._notas)) / (MATERIAS * CORTES)

    def mostrar_boletin(self) -> None:
        print(f"Boletin de {self._nombre}")
        encabezado = "".join(f"{'C' + str(c + 1):>6}" for c in range(CORTES))
        print(f"{'MATERIA':<14}{encabezado}{'PROM':>8}")
        for materia, fila in zip(NOMBRES_MATERIAS, self._notas):
            celdas = "".join(f"{nota:>6.2f}" for nota in fila)
            print(f"{materia:<14}{celdas}{sum(fila) / CORTES:>8.2f}")
        # zip(*matriz) entrega las columnas de la matriz.
        columnas = "".join(f"{sum(col) / MATERIAS:>6.2f}" for col in zip(*self._notas))
        print(f"{'PROM CORTE':<14}{columnas}{self.promedio_general():>8.2f}")


def demostrar_trampa_de_la_matriz() -> None:
    """[[0.0] * 3] * 3 repite la MISMA fila tres veces; la comprension crea filas nuevas."""
    mal = [[0.0] * CORTES] * MATERIAS
    mal[0][0] = 5.0
    print(f"[[0.0] * 3] * 3 tras cambiar [0][0]: {mal}")

    bien = [[0.0] * CORTES for _ in range(MATERIAS)]
    bien[0][0] = 5.0
    print(f"Comprension de listas tras cambiar [0][0]: {bien}")


def demostrar_referencia(estudiante: Estudiante) -> None:
    """Asignar un objeto no copia su matriz: ambos nombres ven los mismos datos."""
    alias = estudiante
    alias.set_nota(0, 0, 0.0)
    print(f"Original -> promedio de Estructuras {estudiante.promedio_materia(0):.2f}")
    print(f"Alias    -> promedio de Estructuras {alias.promedio_materia(0):.2f}")
    print("Ambos nombres apuntan al MISMO objeto y a la misma matriz.")


def main() -> None:
    print("=== 1. Lista de objetos con una matriz como campo ===")
    grupo = [
        Estudiante("Ana", [[4.5, 4.0, 4.8], [3.8, 4.2, 4.0], [4.1, 3.9, 4.4]]),
        Estudiante("Bruno", [[3.5, 3.9, 4.1], [4.6, 4.8, 4.7], [3.2, 3.6, 3.0]]),
        Estudiante("Carla", [[4.9, 4.7, 5.0], [4.4, 4.1, 4.6], [4.8, 4.5, 4.9]]),
    ]
    print(f"Se crearon {len(grupo)} estudiantes, cada uno con una matriz {MATERIAS}x{CORTES} de notas.")

    print("\n=== 2. Recorrido: boletin de cada estudiante ===")
    for estudiante in grupo:
        estudiante.mostrar_boletin()
        print()

    print("=== 3. Modificacion de una celda de la matriz ===")
    bruno = grupo[1]
    print(f"Bruno: Fisica, corte 3 -> 4.50... {'aceptado' if bruno.set_nota(2, 2, 4.5) else 'rechazado'}")
    print(f"Bruno: Fisica, corte 3 -> 6.00... {'aceptado' if bruno.set_nota(2, 2, 6.0) else 'rechazado'}")
    bruno.mostrar_boletin()

    print("\n=== 4. Mejor promedio del grupo ===")
    mejor = max(grupo, key=lambda e: e.promedio_general())
    print(f"{mejor.nombre} con {mejor.promedio_general():.2f}")

    print("\n=== 5. Como crear la matriz correctamente ===")
    demostrar_trampa_de_la_matriz()

    print("\n=== 6. Asignacion de un objeto con matriz ===")
    demostrar_referencia(grupo[0])


if __name__ == "__main__":
    main()
