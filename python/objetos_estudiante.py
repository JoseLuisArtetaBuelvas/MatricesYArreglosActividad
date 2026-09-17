"""Punto 4: Objetos (clases e instancias) en Python.

Declaracion de la clase, inicializacion, recorrido de una lista de objetos
y modificacion mediante set_promedio.
"""

from record_estudiante import EstudianteRecord


class Estudiante:
    """Clase con datos y comportamiento.

    Python no tiene campos privados reales: el guion bajo inicial es una
    convencion que indica "no tocar desde afuera".
    """

    def __init__(self, nombre: str, edad: int, promedio: float) -> None:
        self._nombre = nombre
        self._edad = edad
        self._promedio = promedio

    @property
    def nombre(self) -> str:
        return self._nombre

    @property
    def edad(self) -> int:
        return self._edad

    @property
    def promedio(self) -> float:
        return self._promedio

    def set_promedio(self, nuevo_promedio: float) -> bool:
        """Rechaza promedios fuera de la escala 0.0 - 5.0."""
        if not 0.0 <= nuevo_promedio <= 5.0:
            return False
        self._promedio = nuevo_promedio
        return True

    def mostrar_info(self) -> None:
        print(f"{self._nombre:<12}{self._edad:<8}{self._promedio:.2f}")


def mostrar_todos(estudiantes: list) -> None:
    print(f"{'NOMBRE':<12}{'EDAD':<8}PROMEDIO")
    for estudiante in estudiantes:
        estudiante.mostrar_info()


def buscar_por_nombre(estudiantes: list, nombre: str) -> int:
    for indice, estudiante in enumerate(estudiantes):
        if estudiante.nombre == nombre:
            return indice
    return -1


def demostrar_igualdad() -> None:
    """El record compara por valor; el objeto, por identidad."""
    record_a = EstudianteRecord("Ana", 20, 4.30)
    record_b = EstudianteRecord("Ana", 20, 4.30)
    print(f"Dos records con los mismos datos son iguales: {record_a == record_b}")

    objeto_a = Estudiante("Ana", 20, 4.30)
    objeto_b = Estudiante("Ana", 20, 4.30)
    print(f"Dos objetos con los mismos datos son iguales: {objeto_a == objeto_b}")
    print("El record genera __eq__ automaticamente; la clase compara referencias.")


def demostrar_referencia() -> None:
    """Asignar un objeto copia la referencia, no el objeto."""
    original = Estudiante("Original", 20, 4.0)
    alias = original
    alias.set_promedio(1.0)

    print(f"original -> promedio {original.promedio:.2f}")
    print(f"alias    -> promedio {alias.promedio:.2f}")
    print("Ambos nombres apuntan al MISMO objeto.")


def main() -> None:
    print("=== 1. Declaracion e inicializacion ===")
    estudiantes = [
        Estudiante("Ana", 20, 4.30),
        Estudiante("Bruno", 22, 3.75),
        Estudiante("Carla", 21, 4.80),
    ]
    print(f"Se crearon {len(estudiantes)} instancias de la clase Estudiante.")

    print("\n=== 2. Recorrido llamando a mostrar_info() ===")
    mostrar_todos(estudiantes)

    print("\n=== 3. Modificacion con set_promedio() ===")
    indice = buscar_por_nombre(estudiantes, "Bruno")
    print("Cambiando el promedio de Bruno a 4.50...")
    if estudiantes[indice].set_promedio(4.50):
        print("Cambio aceptado.")

    print("Intentando asignar un promedio invalido (7.00)...")
    if not estudiantes[indice].set_promedio(7.00):
        print("Cambio RECHAZADO por el setter: fuera de la escala 0.0 - 5.0.")
    mostrar_todos(estudiantes)

    print("\n=== 4. Record frente a objeto: igualdad ===")
    demostrar_igualdad()

    print("\n=== 5. Semantica de referencia ===")
    demostrar_referencia()


if __name__ == "__main__":
    main()
