#include <iostream>
#include <iomanip>

using namespace std;

struct treenode {
    float numero;
    treenode *esquerda;
    treenode *direita;
};

typedef treenode *treenodeptr;

void tree_insert(treenodeptr &tree, int insere){
    if(tree == NULL){
        tree = new treenode;
        tree->numero = insere;
        tree->esquerda = NULL;
        tree->direita = NULL;
    } else if (insere < tree->numero){
        tree_insert(tree->esquerda, insere);
    } else {
        tree_insert(tree->direita, insere);
    }
}

void media(treenodeptr tree, float &soma){
    if(tree == NULL){
        soma += 0;
    } else {
        soma += tree->numero;
        media(tree->esquerda, soma);
        media(tree->direita, soma);
    }
}

void destroy_tree(treenodeptr &tree){
    if (tree != NULL){
        destroy_tree(tree->esquerda);
        destroy_tree(tree->direita);
        delete tree;
    }
    tree = NULL;
}

int main(){
    float numero;
    float soma = 0;
    int contador_numeros = 0;

    treenodeptr tree = NULL;

    cin >> numero;
    while(numero != -1){
        tree_insert(tree, numero);
        contador_numeros++;
        cin >> numero;
    }

    media(tree, soma);

    cout << fixed << setprecision(2);
    cout << "Media: " << soma/contador_numeros << endl;

    destroy_tree(tree);

    return 0;
}