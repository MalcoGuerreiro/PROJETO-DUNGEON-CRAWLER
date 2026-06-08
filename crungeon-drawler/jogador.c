#include "jogo.h"
#include "mapas.h"
#include "jogador.h"
#include "inimigos.h"

int frenteLinha = 0;
int frenteColuna = 0;

void obterCelulaFrente(int codigo) {
    frenteLinha = jogadorLinha;
    frenteColuna = jogadorColuna;

    if (direcaoJogador == '^') {
        frenteLinha = jogadorLinha - codigo;
    } else if (direcaoJogador == 'v') {
        frenteLinha = jogadorLinha + codigo;
    } else if (direcaoJogador == '<') {
        frenteColuna = jogadorColuna - codigo;
    } else if (direcaoJogador == '>') {
        frenteColuna = jogadorColuna + codigo;
    }
}

void mudarDirecao(char tecla) {
    if (tecla == 'w') {
        direcaoJogador = '^';
    } else if (tecla == 's') {
        direcaoJogador = 'v';
    } else if (tecla == 'a') {
        direcaoJogador = '<';
    } else if (tecla == 'd') {
        direcaoJogador = '>';
    }

    mapaAtual[jogadorLinha][jogadorColuna] = direcaoJogador;
}

void moverJogador(char tecla) {
    int novaLinha;
    int novaColuna;
    char destino;

    mudarDirecao(tecla);

    novaLinha = jogadorLinha;
    novaColuna = jogadorColuna;

    if (tecla == 'w') {
        novaLinha = novaLinha - 1;
    } else if (tecla == 's') {
        novaLinha = novaLinha + 1;
    } else if (tecla == 'a') {
        novaColuna = novaColuna - 1;
    } else if (tecla == 'd') {
        novaColuna = novaColuna + 1;
    }

    if (dentroDoMapa(novaLinha, novaColuna) == 0) {
        return;
    }

    destino = mapaAtual[novaLinha][novaColuna];

    if (destino == '#') {
        mapaAtual[jogadorLinha][jogadorColuna] = ' ';
        jogadorLinha = novaLinha;
        jogadorColuna = novaColuna;
        mapaAtual[jogadorLinha][jogadorColuna] = direcaoJogador;
        perderVida();
        return;
    }

    if (destino == 'X' || destino == 'Y' || destino == 'Z') {
        perderVida();
        return;
    }

    if (celulaBloqueiaMovimento(destino) == 1) {
        return;
    }

    mapaAtual[jogadorLinha][jogadorColuna] = ' ';
    jogadorLinha = novaLinha;
    jogadorColuna = novaColuna;
    mapaAtual[jogadorLinha][jogadorColuna] = direcaoJogador;
}

int jogadorNaFrenteDe(char simbolo) {
    obterCelulaFrente(1);

    if (dentroDoMapa(frenteLinha, frenteColuna) == 0) {
        return 0;
    }

    if (mapaAtual[frenteLinha][frenteColuna] == simbolo) {
        return 1;
    }

    return 0;
}

void interagir() {
    char alvo;

    obterCelulaFrente(1);

    if (dentroDoMapa(frenteLinha, frenteColuna) == 0) {
        return;
    }

    alvo = mapaAtual[frenteLinha][frenteColuna];

    if (alvo == 'N') {
        escolherArma();
        return;
    }

    if (alvo == '@') {
        chaves = chaves + 1;
        mapaAtual[frenteLinha][frenteColuna] = ' ';
        mensagemCurta('c');
        return;
    }

    if (alvo == 'D') {
        if (chaves > 0) {
            chaves = chaves - 1;
            mapaAtual[frenteLinha][frenteColuna] = '=';
            mensagemCurta('d');
        } else {
            mensagemCurta('t');
        }
        return;
    }

    if (alvo == 'O') {
        removerBarreiraDoBotao();
        mensagemCurta('b');
        return;
    }

    if (alvo == 'L') {
        if (faseAtual == FASE_VILA) {
            carregarFase(FASE_ANDAR_1);
        } else if (faseAtual == FASE_ANDAR_1) {
            carregarFase(FASE_ANDAR_2);
        } else if (faseAtual == FASE_ANDAR_2) {
            carregarFase(FASE_ANDAR_3);
        }
        return;
    }
}

void escolherArma() {
    char opcao;
    int escolhendo;

    escolhendo = 1;

    while (escolhendo == 1) {
        limparTela();

        printf("====================================\n");
        printf("          ESCOLHA SUA ARMA          \n");
        printf("====================================\n\n");
        printf("1 - Master Sword\n");
        printf("2 - Desert Eagle\n");
        printf("3 - Atiesh, Grande Cajado do Guardiao\n\n");
        printf("Escolha: ");

        opcao = getch();

        switch (opcao) {
            case '1':
                armaEscolhida = ARMA_MASTER_SWORD;
                escolhendo = 0;
                break;

            case '2':
                armaEscolhida = ARMA_DESERT_EAGLE;
                escolhendo = 0;
                break;

            case '3':
                armaEscolhida = ARMA_ATIESH;
                escolhendo = 0;
                break;

            default:
                break;
        }
    }

    limparTela();

    if (armaEscolhida == ARMA_MASTER_SWORD) {
        printf("Voce escolheu a Master Sword.\n");
    } else if (armaEscolhida == ARMA_DESERT_EAGLE) {
        printf("Voce escolheu a Desert Eagle.\n");
    } else if (armaEscolhida == ARMA_ATIESH) {
        printf("Voce escolheu Atiesh, Grande Cajado do Guardiao.\n");
    }

    Sleep(1000);
}

void atacar() {
    if (armaEscolhida == ARMA_NENHUMA) {
        mensagemCurta('a');
        return;
    }

    if (armaEscolhida == ARMA_MASTER_SWORD) {
        atacarMasterSword();
    } else if (armaEscolhida == ARMA_DESERT_EAGLE) {
        atacarDesertEagle();
    } else if (armaEscolhida == ARMA_ATIESH) {
        atacarAtiesh();
    }

    if (jogoRodando == 0) {
        return;
    }

    mensagemCurta('x');
}

void atacarCelula(int linha, int coluna) {
    if (dentroDoMapa(linha, coluna) == 0) {
        return;
    }

    if (mapaAtual[linha][coluna] == 'k') {
        mapaAtual[linha][coluna] = ' ';
        return;
    }

    if (mapaAtual[linha][coluna] == 'X' || mapaAtual[linha][coluna] == 'Y' || mapaAtual[linha][coluna] == 'Z') {
        danoEmInimigo(linha, coluna);
        return;
    }
}

void atacarMasterSword() {
    int profundidade;
    int largura;
    int linha;
    int coluna;

    for (profundidade = 1; profundidade <= 2; profundidade++) {
        for (largura = -1; largura <= 1; largura++) {
            linha = jogadorLinha;
            coluna = jogadorColuna;

            if (direcaoJogador == '^') {
                linha = jogadorLinha - profundidade;
                coluna = jogadorColuna + largura;
            } else if (direcaoJogador == 'v') {
                linha = jogadorLinha + profundidade;
                coluna = jogadorColuna + largura;
            } else if (direcaoJogador == '<') {
                linha = jogadorLinha + largura;
                coluna = jogadorColuna - profundidade;
            } else if (direcaoJogador == '>') {
                linha = jogadorLinha + largura;
                coluna = jogadorColuna + profundidade;
            }

            atacarCelula(linha, coluna);
        }
    }
}

void atacarDesertEagle() {
    int distancia;
    int linha;
    int coluna;

    for (distancia = 1; distancia <= 4; distancia++) {
        linha = jogadorLinha;
        coluna = jogadorColuna;

        if (direcaoJogador == '^') {
            linha = jogadorLinha - distancia;
        } else if (direcaoJogador == 'v') {
            linha = jogadorLinha + distancia;
        } else if (direcaoJogador == '<') {
            coluna = jogadorColuna - distancia;
        } else if (direcaoJogador == '>') {
            coluna = jogadorColuna + distancia;
        }

        atacarCelula(linha, coluna);
    }
}

void atacarAtiesh() {
    int linha;
    int coluna;

    for (linha = jogadorLinha - 1; linha <= jogadorLinha + 1; linha++) {
        for (coluna = jogadorColuna - 1; coluna <= jogadorColuna + 1; coluna++) {
            if (linha == jogadorLinha && coluna == jogadorColuna) {
                continue;
            }

            atacarCelula(linha, coluna);
        }
    }
}
