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

void contaPrimos(treenodeptr tree, int &contador_primo){
    int contador = 0;
    if(tree != NULL){
        for(int i = 1; i <= tree->numero; i++){
            if(tree->numero%i == 0){
                contador++;
            }
        }
        if(contador == 2){
            contador_primo++;
        }
        contaPrimos(tree->esquerda, contador_primo);
        contaPrimos(tree->direita, contador_primo);
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
    int contador_primos = 0;

    treenodeptr tree = NULL;

    cin >> numero;
    while(numero != -1){
        tree_insert(tree, numero);
        cin >> numero;
    }

    contaPrimos(tree, contador_primos);

    if(contador_primos == 0){
        cout << "Nenhum numero primo" << endl;
    } else if(contador_primos == 1){
        cout << "1 numero primo" << endl;
    } else {
        cout << contador_primos << " numeros primos" << endl;
    }

    destroy_tree(tree);

    return 0;
}