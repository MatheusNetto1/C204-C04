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

void dijkstra(list<no> adj[], int nVertices, int start, int end){
    int distancia[nVertices], pai[nVertices];                                  // Vetores para armazenar as distâncias mínimas e os pais dos vértices
    int u, v, i;
    int destino, dist, weight;
    bool inTree[nVertices];                                                    // Vetor para marcar se um vértice está na árvore de menor caminho
    list <no> :: iterator p;                                                   // Iterador para percorrer os nós da lista de adjacência
    list <int> pilha_aux;                                                      // Lista auxiliar para armazenar o caminho mínimo

    // Inicialização dos vetores
    for(u = 0; u < nVertices; u++){
        inTree[u] = false;
        distancia[u] = INT_MAX;                                                // Distâncias iniciam com valor máximo
        pai[u] = -1;                                                           // Pais iniciam com valor inválido
    }

    distancia[start] = 0;                                                      // Distância do vértice de partida é 0
    v = start;

    // Algoritmo de Dijkstra
    while(inTree[v] == false){
        inTree[v] = true;

        // Percorre os vértices adjacentes ao vértice atual
        for(p = adj[v].begin(); p != adj[v].end(); p++){
            destino = p->v;
            weight = p->peso;

            // Atualiza as distâncias mínimas e os pais dos vértices adjacentes se necessário
            if(distancia[destino] > distancia[v] + weight){
                distancia[destino] = distancia[v] + weight;
                pai[destino] = v;
            }
        }

        v = 0;
        dist = INT_MAX;

        // Encontra o vértice com a menor distância mínima que ainda não está na árvore de menor caminho
        for(u = 0; u < nVertices; u++){
            if(inTree[u] == false && dist > distancia[u]){
                dist = distancia[u];
                v = u;
            }
        }
    }

    // Construção do caminho mínimo
    for(i = end; i >= start; i = pai[i]){
        pilha_aux.push_front(i);
    }

    // Impressão do caminho mínimo e do custo total
    cout << "Menor caminho: ";
    while(!pilha_aux.empty()){
        cout << *pilha_aux.begin() << " ";
        pilha_aux.pop_front();
    }

    cout << "Custo: " << distancia[end] << endl;
}

int main(){
    int u, v, peso, start, end, i;
    int nVertices, orientado;
    list <no> adj[10];                                  // Declaração da lista de adjacência

    cin >> nVertices >> orientado >> start >> end;      // Leitura do número de vértices, orientação do grafo, vértice de partida e vértice de destino

    cin >> u >> v >> peso;
    while(u != -1 && v != -1 && peso != -1){
        cria_aresta(adj, u, v, peso,  orientado);       // Criação das arestas do grafo
        cin >> u >> v >> peso;
    }

    dijkstra(adj, nVertices, start, end);               // Chamada da função dijkstra para encontrar o menor caminho

    i = 0;
    while(!adj[i].empty()){
        adj[i].pop_front();                             // Limpeza da lista de adjacência
        i++;
    }

    return 0;                                           // Retorna 0 para indicar que o programa foi executado com sucesso
}