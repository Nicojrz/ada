import random

class Tarea:
    def __init__(self, nombre, duracion, estado = False):
        self.nombre = nombre
        self.duracion = duracion
        self.estado = estado

def leerLineas(file):
    L = []
    with open(file) as file:
        for line in file:
            rev = line.replace('\n', "")
            L.append(rev)
    return L

def randTareas(n):
    L = []
    listaActividades = leerLineas("actividades.txt")
    lenActividades = len(listaActividades) - 1
    for i in range(n):
        randomIndex = random.randint(0, lenActividades)
        randomHoras = random.randint(1, 10)
        t = Tarea(listaActividades[randomIndex], randomHoras)
        L.append(t)
    return L

if __name__ == "__main__":
    i = 0
    num = int(input("Ingresa el numero de tareas a generar: \n"))
    listaTareas = randTareas(num)
    for tarea in listaTareas:
        i = i + 1 
        print(f"[{i}] - {tarea.nombre}, {tarea.duracion} horas, completada: {tarea.estado}")
