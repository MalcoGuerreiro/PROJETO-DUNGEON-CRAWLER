#ifndef INIMIGOS_H
#define INIMIGOS_H

void inicializarInimigosDaFase();
void moverInimigos();
void moverMonstroX();
void moverMonstroY();
void moverMatt();
void tentarMoverInimigo(int tipo, int novaLinha, int novaColuna);
void ataqueDistanciaMatt();
void danoEmInimigo(int linha, int coluna);
int existeInimigoNaPosicao(int linha, int coluna);
int existeMattNaPosicao(int linha, int coluna);

#endif
