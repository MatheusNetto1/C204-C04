#include <iostream>
#include <list>
#include <climits>

using namespace std;

// Estrutura para representar um nó do grafo
struct no {
    int v;           // Vértice de destino
    int peso;        // Peso da aresta
};

// Protótipo das funções
void cria_aresta(list<no> adj[], int u, int v, int peso, int orientado);
void dfs(list<no> adj[], int nVertices);
void dfs_visit(int u, list<no> adj[], int nVertices, char color[], int pai[], int d[], int f[], int& tempo);
void ordenacao_topologica(int f[], int nVertices);

int main() {
    int u, v, peso = 0;
    int nVertices, orientado;
    list<no> adj[10];

    // Leitura do número de vértices e se o grafo é orientado ou não
    cin >> nVertices >> orientado;

    // Leitura das arestas do grafo
    cin >> u >> v;
    while (u != -1 && v != -1) {
        cria_aresta(adj, u, v, peso, orientado);
        cin >> u >> v;
    }

    // Chama a função dfs para percorrer o grafo
    dfs(adj, nVertices);

    return 0;
}

// Função para criar uma aresta entre dois vértices
void cria_aresta(list<no> adj[], int u, int v, int peso, int orientado) {
    no aux;                       // Cria uma variável auxiliar do tipo 'no' para representar a aresta

    aux.v = v;                    // Define o vértice de destino da aresta na variável auxiliar
    aux.peso = peso;              // Define o peso da aresta na variável auxiliar
    adj[u].push_back(aux);        // Adiciona a aresta à lista de adjacências do nó 'u'

    if (orientado == 0) {         // Verifica se o grafo é não orientado
        aux.v = u;                // Define o vértice de origem da aresta na variável auxiliar
        adj[v].push_back(aux);    // Adiciona a aresta à lista de adjacências do nó 'v' (para grafos não orientados)
    }
}

// Função de busca em profundidade (DFS) para percorrer o grafo
void dfs(list<no> adj[], int nVertices) {
    int u, tempo;
    char color[nVertices];
    int pai[nVertices], d[nVertices], f[nVertices];

    // Inicializa os vetores de cores, pais, tempos de descoberta e tempos de término
    for (u = 0; u < nVertices; u++) {
        color[u] = 'W';                       // 'W' representa branco (não visitado)
        pai[u] = -1;                          // Define o pai do vértice como -1
    }

    tempo = 0;                                // Inicializa o tempo

    // Percorre cada vértice e chama a função dfs_visit se o vértice não foi visitado
    for (u = 0; u < nVertices; u++) {
        if (color[u] == 'W') {
            dfs_visit(u, adj, nVertices, color, pai, d, f, tempo);
        }
    }

    // Executa a ordenação topológica com base nos tempos de término
    ordenacao_topologica(f, nVertices);
}

// Função auxiliar para realizar a busca em profundidade a partir de um vértice específico
void dfs_visit(int u, list<no> adj[], int nVertices, char color[], int pai[], int d[], int f[], int& tempo) {
    list<no>::iterator v;

    color[u] = 'G';                      // Marca o vértice como visitado (cinza)
    tempo++;
    d[u] = tempo;                        // Tempo de descoberta do vértice

    // Percorre os vértices adjacentes ao vértice atual
    for (v = adj[u].begin(); v != adj[u].end(); v++) {
        if (color[v->v] == 'W') {                                         // Se o vértice adjacente não foi visitado
            pai[v->v] = u;                                                // Define o pai do vértice adjacente como u
            dfs_visit(v->v, adj, nVertices, color, pai, d, f, tempo);     // Chama a recursão para o vértice adjacente
        }
    }

    color[u] = 'B';                             // Marca o vértice como visitado completamente (preto)
    tempo++;
    f[u] = tempo;                               // Tempo de término do vértice
}

// Função para realizar a ordenação topológica com base nos tempos de término
void ordenacao_topologica(int f[], int nVertices) {
    int i, j;
    int aux[nVertices];
    int a, b;

    // Inicializa o vetor auxiliar com os índices dos vértices
    for (i = 0; i < nVertices; i++) {
        aux[i] = i;
    }

    // Ordena os vértices com base nos tempos de término em ordem decrescente
    for (a = 0; a < nVertices; a++) {
        for (i = a + 1; i < nVertices; i++) {
            if (f[aux[a]] < f[aux[i]]) {
                b = aux[a];
                aux[a] = aux[i];
                aux[i] = b;
            }
        }
    }

    // Imprime a ordenação topológica dos vértices
    for (i = 0; i < nVertices; i++) {
        cout << aux[i] << " ";
    }
    cout << endl;
}