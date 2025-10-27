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
        randomHoras = random.randint(1, 8)
        t = Tarea(listaActividades[randomIndex], randomHoras)
        L.append(t)
    return L
        
def quickSortTareas(listaTareas):
    if len(listaTareas) <= 1:
        return listaTareas
    else:
        piv = listaTareas[len(listaTareas) // 2]
        izq = [tarea for tarea in listaTareas if tarea.duracion < piv.duracion]
        mid = [tarea for tarea in listaTareas if tarea.duracion == piv.duracion]
        der = [tarea for tarea in listaTareas if tarea.duracion > piv.duracion]
        return quickSortTareas(izq) + mid + quickSortTareas(der)
        
def maxTareas(listaTareas, tiempoHoras):
    i = 0
    listaOrdenada = quickSortTareas(listaTareas)
    tiempoTotal = 0
    tareasSeleccionadas = []
    for tarea in listaOrdenada:
        totalTemp = tiempoTotal + tarea.duracion
        if (totalTemp) <= tiempoHoras:
            tiempoTotal = totalTemp
            tarea.estado = True
            tareasSeleccionadas.append(tarea)
        else:
            break
    return tareasSeleccionadas
    
def printTareas(listaTareas):
    i = 0
    for tarea in listaTareas:
        i = i + 1 
        print(f"[{i}] - {tarea.nombre}, {tarea.duracion} horas, completada: {tarea.estado}")
    print()

if __name__ == "__main__":
    num = random.randint(1,20)
    print(f"Tareas a realizar en 8 horas: {num}\n")
    listaTareas = randTareas(num)
    printTareas(listaTareas)
    tareasSeleccionadas = maxTareas(listaTareas, 8)
    print(f"Tareas optimizadas:\n")
    printTareas(tareasSeleccionadas)