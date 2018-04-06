#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
typedef struct nodo{
  int chave;
  int altura, nivel;
  int altdireita,altesquerda;
  struct nodo *esq;
  struct nodo *dir;
  struct nodo *pai;
} nodo;
typedef struct arvore{
  nodo *raiz;
} arvore;
arvore *inicializa(){//aloca memoria para inicializar a arvore
  arvore *avl=(arvore*)malloc(sizeof(arvore));
  avl->raiz=NULL;
  return avl;
}
int altura(nodo *r){
  int altura = r->altesquerda;
  if(r->altdireita > altura){
    altura = r->altdireita;
  }
  return(altura);
}
void inserir(arvore *arv,nodo *r,int chave){
  if(arv->raiz == NULL){
    // printf("Primeiro\n");
    nodo *r=(nodo*)malloc(sizeof(nodo));
    printf("ALoco\n");
    r->chave = chave;
    printf("Chave\n");
    r->pai = NULL;
    printf("Pai\n");
    r->esq = NULL;
    printf("Esq\n");
    r->dir = NULL;
    printf("Dir\n");
    r->altura = 0;
    printf("Altura\n");
    r->altdireita = 0;
    printf("Altdireita\n");
    r->altesquerda = 0;
    printf("altesquerda\n");
    r->nivel = 0;
    printf("Nivel\n");
    arv->raiz = r;
    printf("Fim\n");
    return;
  }else{
    if(chave > r->chave){
      if(r->dir == NULL){
        // printf("Segundo\n");
        nodo *x=(nodo*)malloc(sizeof(nodo));
        x->chave = chave;
        x->pai = r;
        x->dir = NULL;
        x->esq = NULL;
        x->altdireita = 0;
        x->altesquerda = 0;
        x->altura = 0;
        r->dir = x;
        r->altdireita++;
        r->altura = altura(r);
        return;
      }else{
        // printf("terceiro\n");
        r = r->dir;
        inserir(arv,r,chave);
        return;
      }
    }
    else if(chave < r->chave){
      if(r->esq == NULL){
        // printf("quarto\n");
        nodo *x=(nodo*)malloc(sizeof(nodo));
        x->chave = chave;
        x->pai = r;
        x->esq = NULL;
        x->dir = NULL;
        x->altura = 0;
        x->altdireita = 0;
        x->altesquerda = 0;
        x->nivel = r->nivel++;
        r->esq = x;
        r->altesquerda++;
        r->altura = altura(r);
        return;
      }else{
        // printf("quinto\n");
        r = r->esq;
        inserir(arv,r,chave);
        return;
      }
    }
    else{
      printf("Valor inválido ou já usado.\n");
    }
  }
  for(;r->pai != NULL; r = r->pai){
  }
}
void imprimir(nodo *x){
  if(x->dir != NULL && x->esq != NULL ){
    imprimir(x->dir);
    imprimir(x->esq);
    printf("\nNodo : %d \n",x->chave);
    if(x->pai == NULL){
      printf("Esquerda : %d \n",x->esq->chave);
      printf("Direita : %d \n",x->dir->chave);
      return;
    }else{
      printf("Pai : %d \n",x->pai->chave);
      printf("Esquerda : %d \n",x->esq->chave);
      printf("Direita : %d \n",x->dir->chave);
      return;
    }

  }else if(x->dir != NULL && x->esq == NULL){
    imprimir(x->dir);
    printf("\nNodo : %d \n",x->chave);
    if(x->pai == NULL){
      printf("Direita : %d \n",x->dir->chave);
      return;
    }else{
      printf("Pai : %d \n",x->pai->chave);
      printf("Direita : %d \n",x->dir->chave);
      return;
    }
    return;
  }else if(x->dir == NULL && x->esq != NULL){
    imprimir(x->esq);
    printf("\nNodo : %d \n",x->chave);
    if(x->pai == NULL){
      printf("Esquerda : %d \n",x->esq->chave);
      return;
    }else{
      printf("Pai : %d \n",x->pai->chave);
      printf("Esquerda : %d \n",x->esq->chave);
      return;
    }
  }else if(x->dir == NULL && x->esq == NULL){
    printf("\nNodo : %d \n",x->chave);
    if(x->pai != NULL){
      printf("Pai : %d \n",x->pai->chave);
    }
      return;
    }
  }

int main(){
  arvore *avl=(arvore*)malloc(sizeof(arvore));
  avl=inicializa();
  int n,key;
	do{
		printf("\tMENU\n");
		printf("Digite a opção desejada:\n");
		printf("1: Inserir\n");
		printf("2: Exibir\n");
		printf("0: Sair\n");
		scanf("%d", &n);
		switch(n){
			case 1:
				scanf("%d", &key);
				inserir(avl,avl->raiz,key);
				break;
			case 2:
        imprimir(avl->raiz);
				break;
      case 0 :
        break;
			default:
				printf("opção invalida!");
				break;
			}
	}while(n!=0);

}
