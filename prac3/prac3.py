import time

count = 0

def f(n):
    global count
    if n > 1:
        print("Hola algoritmo 1.")
        count += 1
        f(n//2)
        f(n//2)

def g(n):
    global count
    if n > 1:
        g(n//2)
        g(n//2)
        for i in range(n):
            print("Soy el algoritmo 2.")
            count += 1
   
def h(n):
    global count
    if n > 1:
        h(n//2)
        h(n//2)
        for i in range(n):
            for j in range(n):
                print("Aqui algoritmo 3.")
                count += 1

def main():
    global count
    tests = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024]
    
    print("Ingresa numero del test (0-10):")
    i = int(input())
    print(f"Numero ingresado: {i} ({tests[i]})") 
    
    print("Ingresa funcion a utilizar (f,g,h):")
    func = input()
    print("Funcion utilizada")
    
    start = time.time()
    if func == "f":
        f(tests[i])
    elif func == "g":
        g(tests[i])
    elif func == "h":
        h(tests[i])
    else:
        print("Funcion invalida...")
    
    end = time.time()
    print(f"Tiempo de {func}({tests[i]}): {end - start:.6f} segundos, impresion {count} veces.")

if __name__ == "__main__":
    main()