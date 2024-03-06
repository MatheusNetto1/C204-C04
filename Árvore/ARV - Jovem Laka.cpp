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

void preOrdem(treenodeptr tree, int busca_numero, int &contador_pre, int &contador_pre_final){
    if(tree != NULL){
        //cout << tree->numero << " ";
        if(tree->numero != busca_numero){
            contador_pre++;
        } else if (tree->numero == busca_numero){
            contador_pre_final = contador_pre;
        }
        preOrdem(tree->esquerda, busca_numero, contador_pre, contador_pre_final);
        preOrdem(tree->direita, busca_numero, contador_pre, contador_pre_final);
    }
}

void emOrdem(treenodeptr tree, int busca_numero, int &contador_em, int &contador_em_final){
    if(tree != NULL){
        emOrdem(tree->esquerda, busca_numero, contador_em, contador_em_final);
        //cout << tree->numero << " ";
        if(tree->numero != busca_numero){
            contador_em++;
        } else if (tree->numero == busca_numero){
            contador_em_final = contador_em;
        }
        emOrdem(tree->direita, busca_numero, contador_em, contador_em_final);
    }
}

void posOrdem(treenodeptr tree, int busca_numero, int &contador_pos, int &contador_pos_final){
    if(tree != NULL){
        posOrdem(tree->esquerda, busca_numero, contador_pos, contador_pos_final);
        posOrdem(tree->direita, busca_numero, contador_pos, contador_pos_final);
        //cout << tree->numero << " ";
        if(tree->numero != busca_numero){
            contador_pos++;
        } else if (tree->numero == busca_numero){
            contador_pos_final = contador_pos;
        }
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
    int busca_numero;

    int contador_pre = 0;
    int contador_pre_final = 0;
    int contador_em = 0;
    int contador_em_final = 0;
    int contador_pos = 0;
    int contador_pos_final = 0;

    treenodeptr tree = NULL;

    cin >> numero;
    while(numero != -1){
        tree_insert(tree, numero);
        cin >> numero;
    }

    cin >> busca_numero;

    //cout << "Pre-Ordem: ";
    preOrdem(tree, busca_numero, contador_pre, contador_pre_final);
    //cout << "\nEm Ordem: ";
    emOrdem(tree, busca_numero, contador_em, contador_em_final);
    //cout << "\nPos-Ordem: ";
    posOrdem(tree, busca_numero, contador_pos, contador_pos_final);

    if(contador_pre_final < contador_em_final && contador_pre_final < contador_pos_final){
        cout << "Pre" << endl;
    } else if(contador_em_final < contador_pre_final && contador_em_final < contador_pos_final){
        cout << "Em" << endl;
    } else {
        cout << "Pos" << endl;
    }

    destroy_tree(tree);

    return 0;
}