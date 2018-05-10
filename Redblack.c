#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
typedef struct Nodo{
  int chave;
  int nivel;
  char cor;
  struct Nodo *esq;
  struct Nodo *dir;
  struct Nodo *pai;
} Nodo;

typedef struct Arvore{
  Nodo *raiz;
  Nodo *sentinela;
} Arvore;

Arvore *inicializa(){//aloca memoria para inicializar a arvore
  Arvore *arvore=(Arvore *)malloc(sizeof(Arvore));
  Nodo *sentinela=(Nodo *)malloc(sizeof(Nodo));
  arvore->raiz= NULL;
  // arvore->nivelMax = 0;
  arvore->sentinela = sentinela;
  arvore->sentinela->chave = -1;
  arvore->sentinela->cor = 'p';
  arvore->sentinela->pai = NULL;
  arvore->sentinela->esq = NULL;
  arvore->sentinela->dir = NULL;
  return arvore;
}
void arrumaNivel (Arvore *arv,Nodo *x){
  if(x->dir != arv->sentinela && x->esq != arv->sentinela ){
    x->nivel = x->pai->nivel + 1;
    arrumaNivel(arv,x->dir);
    arrumaNivel(arv,x->esq);
  }else if(x->dir != arv->sentinela && x->esq == arv->sentinela){
    x->nivel = x->pai->nivel + 1;
    arrumaNivel(arv,x->dir);
    return;
  }else if(x->dir == arv->sentinela && x->esq != arv->sentinela){
    x->nivel = x->pai->nivel + 1;
    arrumaNivel(arv,x->esq);
  }else if(x->dir == arv->sentinela && x->esq == arv->sentinela){
    x->nivel = x->pai->nivel + 1;
    return;
    }
  }
void trocaCor(Nodo *x){
  if(x->cor == 'p'){
    x->cor = 'v';
  }else{
    x->cor = 'p';
  }
}
void rotacao(Arvore *arv,Nodo *x){
  if(x->pai->cor == 'v' && x->cor == 'v'){
    Nodo *tio=(Nodo *)malloc(sizeof(Nodo));
    //Encontrar o tio
    if(x->pai->pai->esq == x->pai){
      tio = x->pai->pai->dir;
    }else if(x->pai->pai->dir == x->pai){
      tio = x->pai->pai->esq;
    }
    //Caso 1, onde só ocorre a troca das cores do pai, avô e tio
    if(tio->cor == 'v'){
      trocaCor(tio);
      trocaCor(x->pai);
      trocaCor(x->pai->pai);
      arv->raiz->cor = 'p';
      return;
    }
    //caso 2
    else if(tio->cor == 'p' && x->pai->dir == x && x->pai->pai->esq == x->pai){
      x->esq = x->pai;
      x->pai = x->esq->pai;
      x->esq->pai = x;
      x->pai->esq = x;
      x->esq->dir = arv->sentinela;
      //caso 3 depois do caso 2
      trocaCor(x->pai);
      trocaCor(x);
      x = x->esq;
      x->pai->dir = x->pai->pai;
      x->pai->pai = x->pai->dir->pai;
      x->pai->pai->esq = x->pai;
      x->pai->dir->pai = x->pai;
      x->pai->dir->esq = arv->sentinela;
    //caso 2 espelhado
    }else if(tio->cor == 'p' && x->pai->esq == x && x->pai->pai->dir == x->pai){
      x->dir = x->pai;
      x->pai = x->dir->pai;
      x->dir->pai = x;
      x->pai->dir = x;
      x->dir->esq = arv->sentinela;
      //caso 3 depois do caso 2
      trocaCor(x->pai);
      trocaCor(x);
      x = x->dir;
      x->pai->esq = x->pai->pai;
      x->pai->pai = x->pai->esq->pai;
      x->pai->pai->dir = x->pai;
      x->pai->esq->pai = x->pai;
      x->pai->esq->dir = arv->sentinela;

    }
    //caso 3
    else if(tio->cor == 'p' && x->pai->esq == x){
        trocaCor(x->pai->pai);
        trocaCor(x->pai);
        x->pai->dir = x->pai->pai;
        x->pai->pai = x->pai->dir->pai;
        x->pai->pai->esq = x->pai;
        x->pai->dir->pai = x->pai;
        x->pai->dir->esq = arv->sentinela;
    //caso 3 espelhado
    }else if(tio->cor == 'p' && x->pai->dir == x){
      trocaCor(x->pai->pai);
      trocaCor(x->pai);
      x->pai->esq = x->pai->pai;
      x->pai->pai = x->pai->esq->pai;
      x->pai->pai->dir = x->pai;
      x->pai->esq->pai = x->pai;
      x->pai->esq->dir = arv->sentinela;

    }
  }else{
    return;
  }
}
void encontrarRaiz(Arvore *arv,Nodo *x){
  while(x->pai != NULL)
    x = x->pai;
  arv->raiz = x;
}
void inserir(Arvore *arv,Nodo *r,int chave){
  if(arv->raiz == NULL){
    Nodo *r=(Nodo*)malloc(sizeof(Nodo));
    r->chave = chave;
    r->pai = NULL;
    r->esq = arv->sentinela;
    r->dir = arv->sentinela;
    r->nivel = 0;
    r->cor = 'p';
    arv->raiz = r;
    return;
  }else{
    if(chave > r->chave){
      if(r->dir == arv->sentinela){
        Nodo *x=(Nodo*)malloc(sizeof(Nodo));
        x->chave = chave;
        x->pai = r;
        x->dir = arv->sentinela;
        x->esq = arv->sentinela;
        x->cor = 'v';
        r->dir = x;
        x->nivel = (r->nivel) + 1;
        rotacao(arv,x);
        return;
      }else{
        r = r->dir;
        inserir(arv,r,chave);
        return;
      }
    }
    else if(chave < r->chave){
      if(r->esq == arv->sentinela){
        Nodo *x=(Nodo*)malloc(sizeof(Nodo));
        x->chave = chave;
        x->pai = r;
        x->esq = arv->sentinela;
        x->dir = arv->sentinela;
        r->esq = x;
        x->cor = 'v';
        x->nivel = (r->nivel) + 1;
        rotacao(arv,x);
        return;
      }else{
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
  arv->raiz = r;
}

void imprimir(Arvore *arv,Nodo *x){
  if(x->dir != arv->sentinela && x->esq != arv->sentinela ){
    imprimir(arv,x->dir);
    imprimir(arv,x->esq);
    printf("\nNodo : %d \n",x->chave);
    printf("Cor : %c\n",x->cor);
    printf("Nivel : %d\n",x->nivel);
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

  }else if(x->dir != arv->sentinela && x->esq == arv->sentinela){
    imprimir(arv,x->dir);
    printf("\nNodo : %d \n",x->chave);
    printf("Cor : %c\n",x->cor);
    printf("Nivel : %d\n",x->nivel);
    if(x->pai == NULL){
      printf("Direita : %d \n",x->dir->chave);
      return;
    }else{
      printf("Pai : %d \n",x->pai->chave);
      printf("Direita : %d \n",x->dir->chave);
      return;
    }
    return;
  }else if(x->dir == arv->sentinela && x->esq != arv->sentinela){
    imprimir(arv,x->esq);
    printf("\nNodo : %d \n",x->chave);
    printf("Cor : %c\n",x->cor);
    printf("Nivel : %d\n",x->nivel);
    if(x->pai == NULL){
      printf("Esquerda : %d \n",x->esq->chave);
      return;
    }else{
      printf("Pai : %d \n",x->pai->chave);
      printf("Esquerda : %d \n",x->esq->chave);
      return;
    }
  }else if(x->dir == arv->sentinela && x->esq == arv->sentinela){
    printf("\nNodo : %d \n",x->chave);
    printf("Cor : %c\n",x->cor);
    printf("Nivel : %d\n",x->nivel);
    if(x->pai != NULL){
      printf("Pai : %d \n",x->pai->chave);
    }
      return;
    }
  }


int main(){
  Arvore *arvore=(Arvore*)malloc(sizeof(Arvore));
  arvore=inicializa();
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
				inserir(arvore,arvore->raiz,key);
				break;
			case 2:
        encontrarRaiz(arvore,arvore->raiz);
        if(arvore->raiz->esq != arvore->sentinela)
          arrumaNivel(arvore,arvore->raiz->esq);
        if(arvore->raiz->dir != arvore->sentinela)
          arrumaNivel(arvore,arvore->raiz->dir);
        imprimir(arvore,arvore->raiz);
				break;
      case 0 :
        break;
			default:
				printf("opção invalida!");
				break;
			}
	}while(n!=0);
}
