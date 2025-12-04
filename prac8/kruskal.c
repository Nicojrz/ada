#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ================================
   ESTRUCTURA DISJOINT SET (UNION-FIND)
   ================================ */

typedef struct DisjointSet {
    int parent;
    int rank;
} DisjointSet;

/* Crea un conjunto con un único elemento */
void makeSet(DisjointSet ds[], int v)
{
    ds[v].parent = v;
    ds[v].rank = 0;
}

/* Encuentra la raíz del conjunto (con compresión de camino) */
int find(DisjointSet ds[], int v)
{
    if (ds[v].parent != v)
        ds[v].parent = find(ds, ds[v].parent);
    return ds[v].parent;
}

/* Une dos conjuntos */
void unionSet(DisjointSet ds[], int a, int b)
{
    int rootA = find(ds, a);
    int rootB = find(ds, b);

    if (rootA == rootB) return;

    if (ds[rootA].rank < ds[rootB].rank)
        ds[rootA].parent = rootB;
    else if (ds[rootA].rank > ds[rootB].rank)
        ds[rootB].parent = rootA;
    else
	{
        ds[rootB].parent = rootA;
        ds[rootA].rank++;
    }
}

/* ================================
   REPRESENTACIÓN DEL GRAFO
   Lista de adyacencia
   ================================ */

typedef struct Edge {
    int u, v;
    int w;
} Edge;

typedef struct AdjNode {
    int v, w;
    struct AdjNode *next;
} AdjNode;

typedef struct Graph {
    int V, E;
    AdjNode **adj;
    Edge *edges;
} Graph;

/* Crear nodo de lista de adyacencia */
AdjNode* newNode(int v, int w)
{
    AdjNode* n = malloc(sizeof(AdjNode));
    n->v = v;
    n->w = w;
    n->next = NULL;
    return n;
}

/* Crear grafo */
struct Graph createGraph(int V, int E)
{
    Graph g;
    g.V = V;
    g.E = E;
    g.adj = malloc(V * sizeof(AdjNode*));
    g.edges = malloc(E * sizeof(Edge));

    for (int i = 0; i < V; i++)
        g.adj[i] = NULL;

    return g;
}

/* Agregar arista no dirigida */
void addEdge(struct Graph *g, int index, int u, int v, int w)
{
    g->edges[index].u = u;
    g->edges[index].v = v;
    g->edges[index].w = w;

    AdjNode *n1 = newNode(v, w);
    n1->next = g->adj[u];
    g->adj[u] = n1;

    AdjNode *n2 = newNode(u, w);
    n2->next = g->adj[v];
    g->adj[v] = n2;
}

/* ================================
   ORDENAMIENTO DE ARISTAS (BUBBLE SORT SIMPLE)
   ================================ */
   
void merge(Edge arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Edge *L = malloc(n1 * sizeof(struct Edge));
    Edge *R = malloc(n2 * sizeof(struct Edge));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
	{
        if (L[i].w <= R[j].w)
		{
            arr[k] = L[i];
            i++;
        }
		else
		{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
	{
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
	{
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(Edge arr[], int left, int right)
{
    if (left < right)
	{
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void sortEdges(Edge edges[], int E)
{
	mergeSort(edges, 0, E - 1);
}

/* ================================
   ALGORITMO DE KRUSKAL
   ================================ */

void kruskal(Graph g)
{
    printf("\n=== EJECUCION DEL ALGORITMO DE KRUSKAL ===\n");

    DisjointSet *ds = malloc(g.V * sizeof(DisjointSet));

    for (int i = 0; i < g.V; i++)
        makeSet(ds, i);

    sortEdges(g.edges, g.E);

    int total = 0;

    printf("Aristas ordenadas por peso:\n");
    for (int i = 0; i < g.E; i++)
        printf("(%d -- %d) w=%d\n", g.edges[i].u, g.edges[i].v, g.edges[i].w);

    printf("\nProceso paso a paso:\n");

    for (int i = 0; i < g.E; i++)
	{
        int u = g.edges[i].u;
        int v = g.edges[i].v;
        int w = g.edges[i].w;

        int setU = find(ds, u);
        int setV = find(ds, v);

        printf("Evaluando arista (%d - %d) w=%d -> ", u, v, w);

        if (setU != setV) {
            printf("ACEPTADA\n");
            total += w;
            unionSet(ds, setU, setV);
        } else {
            printf("RECHAZADA (forma ciclo)\n");
        }
    }

    printf("\nCosto total del arbol de expansion minima: %d\n", total);
    free(ds);
}

/* Genera un grafo aleatorio con V vértices y E aristas */
void testRandom()
{
    printf("\n========== GRAFO ALEATORIO ==========\n");

    srand(time(NULL));

    int V = 3 + rand() % 6;      // entre 3 y 8 vértices
    int maxEdges = V * (V - 1) / 2;

    int E = (V - 1) + rand() % (maxEdges - (V - 1) + 1);  
    // de un árbol (V-1) hasta completo

    printf("Vertices: %d\n", V);
    printf("Aristas: %d\n\n", E);

    struct Graph g = createGraph(V, E);

    // Matriz para evitar duplicados
    int used[20][20] = {0};

    for (int i = 0; i < E; i++)
	{
        int u, v;
        do
		{
            u = rand() % V;
            v = rand() % V;
        }
		while (u == v || used[u][v] || used[v][u]);

        used[u][v] = used[v][u] = 1;

        int w = 1 + rand() % 20;   // pesos entre 1 y 20

        addEdge(&g, i, u, v, w);
        printf("Arista generada: (%d -- %d) w=%d\n", u, v, w);
    }

    printf("\nEjecutando Kruskal sobre el grafo aleatorio...\n");
    kruskal(g);
}

int main()
{
    testRandom();
    return 0;
}
