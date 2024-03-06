#include <iostream>
#include <list>

using namespace std;

// Estrutura de dados para representar uma aresta
struct no {
    int v;                // Identificador do vértice adjacente
    int peso;             // Peso da aresta
};

// Função para criar uma aresta entre dois vértices
void cria_aresta(list<no> adj[], int u, int v, int peso, int orientado) {
    no aux;

    aux.v = v;                       // Define o vértice adjacente
    aux.peso = peso;                 // Define o peso da aresta
    adj[u].push_back(aux);           // Adiciona a aresta na lista de adjacência do vértice u

    if (orientado == 0) {
        aux.v = u;                   // Se o grafo não for orientado, cria uma aresta no sentido oposto também
        adj[v].push_back(aux);       // Adiciona a aresta na lista de adjacência do vértice v
    }
}

int main() {
    int u, v, peso;                      // Declaração das variáveis de origem, destino e peso
    int nVertices, orientado;            // Declaração do número de vértices e do valor orientado ou não
    no aux;                              // Declaração da variável auxiliar de tipo 'no'
    list<no> adj[10];                    // Lista de adjacência para armazenar as arestas do grafo
    int i;
    list<no>::iterator q;

    cin >> nVertices >> orientado;       // Lê o número de vértices e se o grafo é orientado

    cin >> u >> v >> peso;

    // Loop para ler as arestas do grafo até que os valores sejam -1
    while (u != -1 && v != -1 && peso != -1) {
        cria_aresta(adj, u, v, peso, orientado);      // Cria a aresta entre os vértices u e v com o peso dado
        cin >> u >> v >> peso;                        // Lê os próximos valores de u, v e peso
    }

    // Loop para percorrer todos os vértices
    for (i = 0; i < nVertices; i++) {
        // Loop para percorrer todas as arestas do vértice i
        for (q = adj[i].begin(); q != adj[i].end(); q++) {
            cout << i << " " << q->v << " " << q->peso << endl;         // Imprime o vértice atual, o vértice adjacente e o peso da aresta
        }
    }

    // Loop para remover todas as arestas da lista de adjacência
    i = 0;
    while (!adj[i].empty()) {
        adj[i].pop_front();          // Remove a primeira aresta da lista de adjacência do vértice i
        i++;                         // Passa para o próximo vértice
    }

    return 0;                        // Retorna 0 para indicar que o programa foi executado com sucesso
}