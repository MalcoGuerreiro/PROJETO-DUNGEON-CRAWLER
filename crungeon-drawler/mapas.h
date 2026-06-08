#ifndef MAPAS_H
#define MAPAS_H

void carregarFase(int fase);
void mostrarMapa();
void copiarMapaVila();
void copiarMapaAndar1();
void copiarMapaAndar2();
void copiarMapaAndar3();
void encontrarElementos();
void removerBarreiraDoBotao();
int dentroDoMapa(int linha, int coluna);
int celulaBloqueiaMovimento(char celula);
int celulaEhLivreParaInimigo(int linha, int coluna);

#endif
