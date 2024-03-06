#include <iostream>
#include <list>

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

void emNivel(treenodeptr t){
	treenodeptr n;
	list <treenodeptr> q;

	if(t != NULL){
		q.push_back(t);
		while(!q.empty()){
			n = *q.begin();
			q.pop_front();
			if(n->esquerda != NULL){
                q.push_back(n->esquerda);
            }
			if(n->direita != NULL){
                q.push_back(n->direita);
            }
			cout << n->numero << " ";
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

    treenodeptr tree = NULL;

    cin >> numero;
    while(numero != -1){
        tree_insert(tree, numero);
        cin >> numero;
    }

    emNivel(tree);

    destroy_tree(tree);

    return 0;
}