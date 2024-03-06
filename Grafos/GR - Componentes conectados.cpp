#include <iostream>
#include <list>

using namespace std;

// Estrutura de dados para representar uma aresta
struct no{
    int v;         // Identificador do vértice adjacente
    int peso;      // Peso da aresta
};

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

void bfs(list<no> adj[], int nVertices, int s) {
    int u, v;
    int state[nVertices];                // Vetor para armazenar o estado de cada vértice ('u': não visitado, 'd': descoberto, 'p': processado)
    int pai[nVertices];                  // Vetor para armazenar o pai de cada vértice no caminho da busca em largura
    int cont = 0;                        // Contador para verificar a conexidade do grafo
    list<int> Q;                         // Lista para armazenar os vértices a serem visitados em largura
    list<no>::iterator p;                // Iterador para percorrer as arestas adjacentes de um vértice

    // Loop para percorrer todas os vertices
    for (u = 0; u < nVertices; u++) {
        if (u != s) {
            state[u] = 'u';              // Define todos os vértices, exceto o vértice de partida, como não visitados
            pai[u] = -1;                 // Define o pai de todos os vértices, exceto o vértice de partida, como -1
        }
    }

    state[s] = 'd';                      // Marca o vértice de partida como descoberto
    pai[s] = -1;                         // Define o pai do vértice de partida como -1
    Q.push_back(s);                      // Adiciona o vértice de partida à lista de vértices a serem visitados

    while (!Q.empty()) {
        u = *Q.begin();                  // Obtém o primeiro vértice da lista
        Q.pop_front();                   // Remove o vértice visitado da lista

        for (p = adj[u].begin(); p != adj[u].end(); p++) {
            v = p->v;                                        // Obtém o vértice adjacente

            if (state[v] == 'u') {                           // Verifica se o vértice adjacente não foi visitado
                state[v] = 'd';                              // Marca o vértice adjacente como descoberto
                pai[v] = u;                                  // Define o pai do vértice adjacente como o vértice atual
                Q.push_back(v);                              // Adiciona o vértice adjacente à lista de vértices a serem visitados
                cont++;                                      // Incrementa o contador de vértices visitados
            }
        }

        state[u] = 'p';                                      // Marca o vértice atual como processado
    }

    // Verifica a conexidade do grafo
    if(cont == nVertices){
        cout << "Conexo" << endl;
    }
    else {
        cout << "Nao conexo" << endl;
    }
}

int main() {
    int u, v, peso = 1, s, i;
    int nVertices, orientado = 0;                   
    list<no> adj[10];                                 // Vetor de listas de adjacências para armazenar o grafo

    cin >> nVertices >> s;                            // Leitura do número de vértices e do vértice de partida

    // Leitura das informações das arestas até receber -1 como entrada para u, v e peso
    cin >> u >> v;
    while (u != -1 && v != -1 && peso != -1) {
        cria_aresta(adj, u, v, peso, orientado);      // Cria as arestas no grafo
        cin >> u >> v;
    }

    bfs(adj, nVertices, s);                           // Executa a busca em largura no grafo

    // Limpa as listas de adjacências, removendo todas as arestas
    i = 0;
    while (!adj[i].empty()) {
        adj[i].pop_front();
        i++;
    }

    return 0;                                         // Indica que o programa foi executado com sucesso
}