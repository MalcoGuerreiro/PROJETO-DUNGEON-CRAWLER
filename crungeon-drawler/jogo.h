#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define VIDAS_INICIAIS 3

#define ARMA_NENHUMA 0
#define ARMA_MASTER_SWORD 1
#define ARMA_DESERT_EAGLE 2
#define ARMA_ATIESH 3

#define FASE_VILA 0
#define FASE_ANDAR_1 1
#define FASE_ANDAR_2 2
#define FASE_ANDAR_3 3

#define VILA_LINHAS 10
#define VILA_COLUNAS 10

#define ANDAR1_LINHAS 10
#define ANDAR1_COLUNAS 10

#define ANDAR2_LINHAS 15
#define ANDAR2_COLUNAS 15

#define ANDAR3_LINHAS 25
#define ANDAR3_COLUNAS 25

#define MAX_LINHAS 25
#define MAX_COLUNAS 25

#define VIDA_MATT 5
#define COOLDOWN_TIRO_MATT 4
#define ALCANCE_TIRO_MATT 6

extern int programaRodando;
extern int jogoRodando;
extern int faseAtual;
extern int vidas;
extern int chaves;
extern int jogadorLinha;
extern int jogadorColuna;
extern char direcaoJogador;
extern int armaEscolhida;
extern int linhasMapaAtual;
extern int colunasMapaAtual;
extern char mapaAtual[MAX_LINHAS][MAX_COLUNAS + 1];
extern int monstroXLinha;
extern int monstroXColuna;
extern int monstroXAtivo;
extern int monstroYLinha;
extern int monstroYColuna;
extern int monstroYAtivo;
extern int mattLinha;
extern int mattColuna;
extern int mattVida;
extern int mattAtivo;
extern int mattUltimoTiro;
extern int jogadorMorreu;
extern int faseMudou;

void menuPrincipal();
void iniciarJogo();
void jogarFase();
void mostrarTutorial();
void mostrarCreditos();
void mostrarGameOver();
void mostrarVitoria();
void pausar();
void limparTela();
void mensagemCurta(char codigo);
void perderVida();

#endif
