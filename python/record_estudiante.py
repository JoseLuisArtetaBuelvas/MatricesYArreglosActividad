"""Punto 3: Record en Python.

Python no tiene la palabra clave struct. Su equivalente a un record son las
dataclasses (mutables o congeladas) y las NamedTuple (siempre inmutables).
"""

from dataclasses import dataclass
from typing import NamedTuple


@dataclass
class EstudianteRecord:
    """Record mutable: el decorador genera __init__, __repr__ y __eq__."""

    nombre: str
    edad: int
    promedio: float


class EstudianteInmutable(NamedTuple):
    """Record inmutable: una vez creado, sus campos no se pueden reasignar."""

    nombre: str
    edad: int
    promedio: float


def mostrar_todos(estudiantes: list) -> None:
    print(f"{'NOMBRE':<12}{'EDAD':<8}PROMEDIO")
    for estudiante in estudiantes:
        print(f"{estudiante.nombre:<12}{estudiante.edad:<8}{estudiante.promedio:.2f}")


def buscar_por_nombre(estudiantes: list, nombre: str) -> int:
    """Retorna el indice del estudiante, o -1 si no esta en la lista."""
    for indice, estudiante in enumerate(estudiantes):
        if estudiante.nombre == nombre:
            return indice
    return -1


def cambiar_promedio(estudiantes: list, nombre: str, nuevo_promedio: float) -> bool:
    indice = buscar_por_nombre(estudiantes, nombre)
    if indice == -1:
        return False
    estudiantes[indice].promedio = nuevo_promedio
    return True


def crear_copia_con_ajuste(estudiantes: list, puntos: float) -> list:
    """Retorna una nueva lista con el promedio de cada estudiante ajustado."""
    copia = estudiantes.copy()
    for estudiante in copia:
        estudiante.promedio = min(5.0, estudiante.promedio + puntos)
    return copia


def demostrar_inmutabilidad() -> None:
    inmutable = EstudianteInmutable("Diana", 23, 4.10)
    print(f"NamedTuple original: {inmutable.nombre} -> {inmutable.promedio:.2f}")

    try:
        inmutable.promedio = 5.0
    except AttributeError:
        print("No se puede reasignar un campo de una NamedTuple.")

    # _replace no modifica: construye una instancia nueva con el cambio aplicado.
    modificado = inmutable._replace(promedio=5.0)
    print(f"Con _replace se obtiene otra instancia: {modificado.promedio:.2f}")
    print(f"La original sigue intacta: {inmutable.promedio:.2f}")


def main() -> None:
    print("=== 1. Declaracion e inicializacion ===")
    estudiantes = [
        EstudianteRecord("Ana", 20, 4.30),
        EstudianteRecord("Bruno", 22, 3.75),
        EstudianteRecord("Carla", 21, 4.80),
    ]
    print(f"Se crearon {len(estudiantes)} instancias del record EstudianteRecord.")

    print("\n=== 2. Recorrido de la lista ===")
    mostrar_todos(estudiantes)

    print("\n=== 3. Modificacion ===")
    print("Cambiando el promedio de Bruno a 4.50...")
    if cambiar_promedio(estudiantes, "Bruno", 4.50):
        mostrar_todos(estudiantes)

    print("\n=== 4. Copia con ajuste de 0.20 puntos ===")
    ajustados = crear_copia_con_ajuste(estudiantes, 0.20)
    print("Lista ajustada:")
    mostrar_todos(ajustados)
    print("Lista original:")
    mostrar_todos(estudiantes)

    print("\n=== 5. Record inmutable (NamedTuple) ===")
    demostrar_inmutabilidad()


if __name__ == "__main__":
    main()
