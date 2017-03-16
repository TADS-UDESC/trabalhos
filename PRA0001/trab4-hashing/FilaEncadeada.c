#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaEncadeada.h"


void inicializaFila(FilaEncadeada *f, int tamanho){
   f->tamanhoInfo = tamanho;
   f->inicio = NULL;
   f->fim = NULL;
}

Elemento *aloca_e_copia(void *info, int tamanho){
   Elemento *p = (Elemento *) malloc(sizeof(Elemento));
   if(p == NULL)
      return 0; // Erro, falta de memória!
   p->info = malloc(tamanho);
   if(p->info == NULL){
      free(p);
      return 0; // Erro, falta de memória!
   }
   memcpy(p->info, info, tamanho);
   return p;
}

int inserir(FilaEncadeada *f, void *info){
   Elemento *novo = aloca_e_copia(info, f->tamanhoInfo);
   if(novo == NULL)
      return 0;

   if(f->inicio == NULL)
      f->inicio = novo;
   else
      f->fim->proximo = novo;
   
   novo->proximo = NULL;
   f->fim = novo;
   return 1;
}

int remover(FilaEncadeada *f, void *info){
   if(f->inicio == NULL)
      return ERRO_FILA_VAZIA;

   Elemento *p = f->inicio;
   f->inicio = p->proximo;   
   if(p->proximo == NULL)
      f->fim = NULL;
  
   memcpy(info, p->info, f->tamanhoInfo);
   free(p->info);
   free(p);
   return 1;
}

int filaVazia(FilaEncadeada f){
   return f.inicio == NULL;
}

void limpaFila(FilaEncadeada *f){
   Elemento *p = f->inicio;
   while(p != NULL){
      Elemento *aux = p->proximo;
      free(p->info);
      free(p);
      p = aux;
   }
   f->inicio = NULL;
   f->fim = NULL;
}

void mostraFila(FilaEncadeada f, void (*mostraInfo)(void *) ){
   if( filaVazia(f) ){
      printf("Fila vazia!\n");
   }
   else{
      printf("Dados da fila:\n");
      Elemento *p = f.inicio;
      while(p != NULL){
         (*mostraInfo)(p->info); // Invocação por callback
         p = p->proximo;
      }
   }
   printf("----------------------\n\n");
} 


