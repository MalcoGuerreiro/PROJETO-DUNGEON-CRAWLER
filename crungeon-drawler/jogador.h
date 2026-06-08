#ifndef JOGADOR_H
#define JOGADOR_H

void moverJogador(char tecla);
void mudarDirecao(char tecla);
void obterCelulaFrente(int codigo);
void interagir();
void escolherArma();
void atacar();
void atacarCelula(int linha, int coluna);
void atacarMasterSword();
void atacarDesertEagle();
void atacarAtiesh();
int jogadorNaFrenteDe(char simbolo);

#endif
