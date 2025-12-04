#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- STRUCTS ---

struct Nodo
{
    char dato;
    double freq;
    struct Nodo *left, *right;
};

struct MinHeap
{
    unsigned size;
    unsigned capacity;
    struct Nodo **array;
};

// --- FUNCIONES ---

struct Nodo* nuevoNodo(char dato, double freq)
{
    struct Nodo* temp = (struct Nodo*)malloc(sizeof(struct Nodo));
    //nodos hijos nulos
    temp->left = temp->right = NULL;
    //primer nodo
    temp->dato = dato;
    temp->freq = freq;
    return temp;
}

struct MinHeap* crearMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct Nodo**)malloc(minHeap->capacity * sizeof(struct Nodo*));
    return minHeap;
}

void swapNodos(struct Nodo** a, struct Nodo** b)
{
    struct Nodo* t = *a;
    *a = *b;
    *b = t;
}

//mantener en minheap
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    // Las comparaciones (<) funcionan igual para double
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;
    
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swapNodos(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

//extract min
struct Nodo* extractMin(struct MinHeap* minHeap)
{
    struct Nodo* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

//insert q z
void insertMinHeap(struct MinHeap* minHeap, struct Nodo* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;

    //bubble up
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

//es 1?
int esTamanoUno(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}

// CAMBIO: El array freq[] ahora es double
struct Nodo* Huffman(char datos[], double freq[], int size)
{
    struct Nodo *left, *right, *top;

    // crear minheap
    struct MinHeap* minHeap = crearMinHeap(size);
    for (int i = 0; i < size; ++i)
        insertMinHeap(minHeap, nuevoNodo(datos[i], freq[i]));

    printf("Arbol:\n");

    // checar tamaño
    int paso = 1;
    while (!esTamanoUno(minHeap))
    {   
        //x = extract min q
        left = extractMin(minHeap);
        //y = extract min q
        right = extractMin(minHeap);

        //allocate new node z
        //z.freq = x.freq + y.freq
        //Usamos '@' para nodos internos, aunque en el print validas con '$' (o lo ajustamos visualmente)
        top = nuevoNodo('@', left->freq + right->freq);
        top->left = left;
        top->right = right;

        //prints
        printf("Paso %d:\n", paso++);
        // CAMBIO: %d a %.2f para imprimir decimales
        printf("   Extrayendo: [%c: %.2f] y [%c: %.2f]\n", 
               (left->dato == '@' ? '*' : left->dato), left->freq, 
               (right->dato == '@' ? '*' : right->dato), right->freq);
        printf("   --> Creando Padre (z): [*: %.2f]\n\n", top->freq);

        //insert q
        insertMinHeap(minHeap, top);
    }

    //return extract min
    return extractMin(minHeap);
}

int leerArchivo(const char* nombreArchivo, char* arrCar, double* arrFreq)
{
    FILE* fp = fopen(nombreArchivo, "r");
    if (!fp)
    {
        printf("Error al abrir el archivo '%s'.\n", nombreArchivo);
        return -1;
    }

    int i = 0;
    char buffer[10]; 
    double tempFreq;

    while (fscanf(fp, "%s %lf", buffer, &tempFreq) != EOF)
    {
        arrCar[i] = buffer[0];
        arrFreq[i] = tempFreq;
        i++;
    }
    
    fclose(fp);
    return i;
}

void generarNombreSalida(const char* entrada, char* salida)
{
    strcpy(salida, entrada);
    char* punto = strrchr(salida, '.');

    if (punto != NULL)
    {
        *punto = '\0';
        strcat(salida, "_codigos.txt");
    }
    else
    {
        strcat(salida, "_codigos.txt");
    }
}


void guardarCodigo(FILE* fp, char simbolo, int arr[], int top)
{
    fprintf(fp, "%c: ", simbolo);
    for (int i = 0; i < top; i++)
        fprintf(fp, "%d", arr[i]);
    fprintf(fp, "\n");
}

void imprimirCodigos(struct Nodo* root, int arr[], int top, FILE* fp)
{
    if (root->left)
    {
        arr[top] = 0;
        imprimirCodigos(root->left, arr, top + 1, fp);
    }
    if (root->right)
    {
        arr[top] = 1;
        imprimirCodigos(root->right, arr, top + 1, fp);
    }

    // nodo hoja
    if (!root->left && !root->right)
    {
        // imprime en pantalla
        printf("%c: ", root->dato);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");

        // guarda en archivo
        guardarCodigo(fp, root->dato, arr, top);
    }
}

int main()
{
    char arrCar[100];
    double arrFreq[100];
    char nombreArchivo[50];

    printf("huffman en c (con doubles)\n");
    printf("archivo:\n");
    scanf("%s", nombreArchivo);

    int n = leerArchivo(nombreArchivo, arrCar, arrFreq);

    if (n > 0)
    {
        printf("se cargaron %d simbolos.\n", n);
        struct Nodo* raiz = Huffman(arrCar, arrFreq, n);

        printf("completo.\n");
        printf("raiz total del arbol: %.2f\n", raiz->freq);
        
        printf("codigos generados:\n");

        char archivoSalida[100];
        generarNombreSalida(nombreArchivo, archivoSalida);

        FILE* fp = fopen(archivoSalida, "w");
        if (!fp)
        {
            printf("Error al crear archivo %s\n", archivoSalida);
            return 1;
        }

        int arr[100], top = 0;
        imprimirCodigos(raiz, arr, top, fp);

        fclose(fp);

        printf("Codigos guardados en '%s'.\n", archivoSalida);
    }

    return 0;
}
