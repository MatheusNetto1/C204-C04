#include <iostream>

using namespace std;

struct treenode {
    int numero;
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

void contaFolhas(treenodeptr tree, int &contador_folhas){
    if(tree == NULL){
        contador_folhas += 0;
    } else if(tree->esquerda == NULL && tree->direita == NULL){
        contador_folhas++;
    } else {
        contaFolhas(tree->esquerda, contador_folhas);
        contaFolhas(tree->direita, contador_folhas);
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
    int numero;
    int contador_folhas = 0;
    treenodeptr tree = NULL;

    cin >> numero;
    while(numero != -1){
        tree_insert(tree, numero);
        cin >> numero;
    }

    contaFolhas(tree, contador_folhas);

    cout << contador_folhas << endl;

    destroy_tree(tree);

    return 0;
}

