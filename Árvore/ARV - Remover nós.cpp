#include <iostream>
#include <iomanip>

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

treenodeptr tree_menor(treenodeptr &tree){
    treenodeptr t;
    t = tree;

    if (t->esquerda == NULL){
        tree = tree->direita;
        return t;
    } else {
        return tree_menor(tree->esquerda);
    }
}

int remove(treenodeptr &tree, int remove_numero){
    treenodeptr p;

    if (tree == NULL){
        return 1;
    }
    if (remove_numero == tree->numero){
        p = tree;
        if (tree->esquerda == NULL){
            tree = tree->direita;
        } else if (tree->direita == NULL){
            tree = tree->esquerda;
        } else {
            p = tree_menor(tree->direita);
            tree->numero = p->numero;
        }
        
        delete p;
        p = NULL;
        return 0;
    } else if (remove_numero < tree->numero){
        return remove(tree->esquerda, remove_numero);
    } else {
        return remove(tree->direita, remove_numero);
    }
}
void ordenar(treenodeptr tree){
    if(tree != NULL){
        ordenar(tree->esquerda);
        cout << tree->numero << " ";
        ordenar(tree->direita);
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
    int remove_numero;
    int removeu = 1;

    treenodeptr tree = NULL;

    cin >> numero;
    while(numero != 0){
        tree_insert(tree, numero);
        cin >> numero;
    }

    cin >> remove_numero;

    do{
        removeu = remove(tree, remove_numero);
    }while(removeu == 0);

    ordenar(tree);

    destroy_tree(tree);

    return 0;
}