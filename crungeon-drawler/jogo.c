#include "jogo.h"
#include "mapas.h"
#include "jogador.h"
#include "inimigos.h"

int programaRodando = 1;
int jogoRodando = 0;
int faseAtual = FASE_VILA;
int vidas = VIDAS_INICIAIS;
int chaves = 0;
int jogadorLinha = 0;
int jogadorColuna = 0;
char direcaoJogador = '^';
int armaEscolhida = ARMA_NENHUMA;
int linhasMapaAtual = 0;
int colunasMapaAtual = 0;
char mapaAtual[MAX_LINHAS][MAX_COLUNAS + 1];
int monstroXLinha = 0;
int monstroXColuna = 0;
int monstroXAtivo = 0;
int monstroYLinha = 0;
int monstroYColuna = 0;
int monstroYAtivo = 0;
int mattLinha = 0;
int mattColuna = 0;
int mattVida = VIDA_MATT;
int mattAtivo = 0;
int mattUltimoTiro = 0;
int jogadorMorreu = 0;
int faseMudou = 0;

void limparTela() {
    system("cls");
}

void pausar() {
    printf("\nPressione qualquer tecla para continuar...");
    getch();
}

void mensagemCurta(char codigo) {
    if (codigo == 'c') {
        printf("\nVoce pegou uma chave.");
    } else if (codigo == 'd') {
        printf("\nVoce abriu uma porta.");
    } else if (codigo == 't') {
        printf("\nA porta esta trancada. Voce precisa de uma chave.");
    } else if (codigo == 'b') {
        printf("\nVoce apertou o botao. Uma barreira foi removida.");
    } else if (codigo == 'a') {
        printf("\nVoce ainda nao escolheu uma arma.");
    } else if (codigo == 'x') {
        printf("\nVoce atacou.");
    } else if (codigo == 'v') {
        printf("\nVoce perdeu uma vida.");
    }
    Sleep(700);
}

void menuPrincipal() {
    char opcao;

    while (programaRodando == 1) {
        limparTela();

        printf("====================================\n");
        printf("          CRUNGEON DRAWLER          \n");
        printf("====================================\n\n");
        printf("1 - Jogar\n");
        printf("2 - Tutorial\n");
        printf("3 - Sair\n\n");
        printf("Escolha uma opcao: ");

        opcao = getch();

        switch (opcao) {
            case '1':
                iniciarJogo();
                break;

            case '2':
                mostrarTutorial();
                break;

            case '3':
                mostrarCreditos();
                programaRodando = 0;
                break;

            default:
                break;
        }
    }
}

void iniciarJogo() {
    vidas = VIDAS_INICIAIS;
    armaEscolhida = ARMA_NENHUMA;
    faseAtual = FASE_VILA;
    jogoRodando = 1;
    jogadorMorreu = 0;
    faseMudou = 0;
    carregarFase(FASE_VILA);

    while (jogoRodando == 1 && programaRodando == 1) {
        jogarFase();
    }
}

void jogarFase() {
    char tecla;

    faseMudou = 0;
    mostrarMapa();
    tecla = getch();

    if (tecla != 'w' && tecla != 'a' && tecla != 's' && tecla != 'd' && tecla != 'i' && tecla != 'o') {
        return;
    }

    if (tecla == 'w' || tecla == 'a' || tecla == 's' || tecla == 'd') {
        moverJogador(tecla);
    } else if (tecla == 'i') {
        interagir();
    } else if (tecla == 'o') {
        atacar();
    }

    if (jogoRodando == 0 || jogadorMorreu == 1 || faseMudou == 1) {
        return;
    }

    moverInimigos();

    if (jogoRodando == 0 || jogadorMorreu == 1 || faseMudou == 1) {
        return;
    }
}

void mostrarTutorial() {
    limparTela();

    printf("====================================\n");
    printf("              TUTORIAL              \n");
    printf("====================================\n\n");

    printf("Historia:\n");
    printf("Na Vila do Mouse Mal Clicado, uma masmorra apareceu do nada.\n");
    printf("Talvez tenha sido um erro de compilacao. Talvez alguem apertou Alt + F4.\n");
    printf("No fundo da dungeon esta Matt, o lendario campeao de boxe dos Miis.\n");
    printf("Ele transformou a masmorra em uma academia absurda.\n");
    printf("Derrote Matt antes que todos virem Miis musculosos com luvas de boxe.\n\n");

    printf("Controles:\n");
    printf("w - mover para cima\n");
    printf("a - mover para esquerda\n");
    printf("s - mover para baixo\n");
    printf("d - mover para direita\n");
    printf("i - interagir com o objeto a frente\n");
    printf("o - atacar\n\n");

    printf("Simbolos:\n");
    printf("< ^ > v - jogador\n");
    printf("* - parede\n");
    printf("# - espinho\n");
    printf("k - caixa\n");
    printf("O - botao\n");
    printf("D - porta fechada\n");
    printf("@ - chave\n");
    printf("= - porta aberta\n");
    printf("L - escada\n");
    printf("N - NPC da vila\n");
    printf("X - monstro aleatorio\n");
    printf("Y - monstro perseguidor\n");
    printf("Z - Matt\n\n");

    printf("Objetivo:\n");
    printf("Escolha uma arma na vila, atravesse os tres andares e derrote Matt.\n");

    pausar();
}

void mostrarCreditos() {
    limparTela();

    printf("====================================\n");
    printf("              CREDITOS              \n");
    printf("====================================\n\n");
    printf("Crungeon Drawler\n\n");
    printf("Desenvolvedores:\n");
    printf("- Adicione aqui os nomes do grupo\n\n");
    printf("Projeto academico feito em C puro no console.\n");

    pausar();
}

void mostrarGameOver() {
    limparTela();

    printf("====================================\n");
    printf("             GAME OVER              \n");
    printf("====================================\n\n");
    printf("Voce perdeu todas as vidas.\n");
    printf("A Vila do Mouse Mal Clicado tera que esperar outro heroi.\n");

    pausar();
    jogoRodando = 0;
}

void mostrarVitoria() {
    limparTela();

    printf("====================================\n");
    printf("             VOCE VENCEU            \n");
    printf("====================================\n\n");
    printf("Depois de uma batalha extremamente desnecessaria,\n");
    printf("Matt finalmente caiu.\n\n");
    printf("A Vila do Mouse Mal Clicado esta salva.\n");
    printf("As caixas pararam de aparecer.\n");
    printf("As portas voltaram a funcionar.\n");
    printf("Os espinhos foram removidos por uma equipe terceirizada.\n\n");
    printf("Matt prometeu que voltara para a academia\n");
    printf("e nunca mais transformara uma dungeon em ringue de boxe.\n\n");
    printf("Fim.\n");

    pausar();
    jogoRodando = 0;
}

void perderVida() {
    vidas = vidas - 1;
    jogadorMorreu = 1;

    limparTela();
    printf("Voce perdeu uma vida.\n");
    printf("Vidas restantes: %d\n", vidas);
    Sleep(1000);

    if (vidas <= 0) {
        mostrarGameOver();
        return;
    }

    carregarFase(faseAtual);
}
