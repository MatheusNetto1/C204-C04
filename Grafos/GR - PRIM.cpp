#include <iostream>
#include <list>
#include <climits>

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

void prim(list<no> adj[], int nVertices, int start) {
    int distancia[nVertices];                             // Vetor para armazenar as distâncias mínimas de cada vértice até a árvore geradora mínima
    int pai[nVertices];                                   // Vetor para armazenar o pai de cada vértice na árvore geradora mínima
    int u, v, i;
    int destino, dist, weight;
    int custo = 0;                                        // Variável para armazenar o custo total da árvore geradora mínima
    bool inTree[nVertices];                               // Vetor para marcar se um vértice já está na árvore geradora mínima
    list<no>::iterator p;                                 // Iterador para percorrer as arestas adjacentes de um vértice

    // Inicialização dos vetores
    for (u = 0; u < nVertices; u++) {
        inTree[u] = false;                                // Marca todos os vértices como não pertencentes à árvore geradora mínima
        distancia[u] = INT_MAX;                           // Define a distância mínima inicialmente como infinito para todos os vértices
        pai[u] = -1;                                      // Define o pai de todos os vértices como -1 (ainda não definido)
    }

    distancia[start] = 0;                                 // Define a distância do vértice de partida como 0
    v = start;                                            // Define o vértice de partida como o vértice atual

    while (inTree[v] == false) {
        inTree[v] = true;                                 // Marca o vértice atual como pertencente à árvore geradora mínima

        // Percorre as arestas adjacentes ao vértice atual
        for (p = adj[v].begin(); p != adj[v].end(); p++) {
            destino = p->v;                                    // Obtém o vértice destino da aresta
            weight = p->peso;                                  // Obtém o peso da aresta

            // Se a distância mínima até o vértice destino é maior que o peso da aresta e o vértice destino ainda não pertence à árvore geradora mínima
            if (distancia[destino] > weight && inTree[destino] == false) {
                distancia[destino] = weight;                                   // Atualiza a distância mínima até o vértice destino
                pai[destino] = v;                                              // Define o vértice atual como o pai do vértice destino
            }
        }

        v = 0;
        dist = INT_MAX;

        // Encontra o vértice com a menor distância mínima que ainda não pertence à árvore geradora mínima
        for (u = 0; u < nVertices; u++) {
            if (inTree[u] == false && dist > distancia[u]) {
                dist = distancia[u];
                v = u;
            }
        }
    }

    cout << "Arvore Geradora Minima: \n";

    // Imprime as arestas da árvore geradora mínima e calcula o custo total
    for (i = 0; i < nVertices; i++) {
        custo += distancia[i];

        if (i != start) {
            cout << pai[i] << " " << i << endl;
        }
    }

    cout << "Custo: " << custo << endl;
}

int main(){
    int u, v, peso, s, i;
    int nVertices, orientado;
    list <no> adj[10];                               // Lista de adjacência para armazenar o grafo
    list <no> :: iterator q;                         // Iterador para percorrer os nós da lista de adjacência

    cin >> nVertices >> orientado >> s;              // Entrada do número de vértices, se o grafo é orientado e o vértice de partida

    // Entrada das arestas (vértices de origem, destino e peso) até que valores -1 sejam inseridos
    cin >> u >> v >> peso;
    while(u != -1 && v != -1 && peso != -1){
        cria_aresta(adj, u, v, peso, orientado);     // Criação das arestas no grafo
        cin >> u >> v >> peso;
    }

    prim(adj, nVertices, s);                         // Chama a função prim para encontrar a árvore geradora mínima

    i = 0;
    while(!adj[i].empty()){
        adj[i].pop_front();                          // Limpa a lista de adjacência
        i++;
    }

    return 0;
}