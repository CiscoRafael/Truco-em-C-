#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Carta {
public:
    char numero;
    string naipe;
    int valor;

    Carta(char numero, string naipe, int valor) {
        this->numero = numero;
        this->naipe = naipe;
        this->valor = valor;
    }

    Carta() {}
};

class Baralho {
public:
    const char numeros[10] = {'A', '2', '3', '4', '5', '6', '7', 'Q', 'J', 'K'};
    const string naipes[4] = {"copas", "paus", "ouros", "espada"};

    Baralho() {
        srand(time(0));
    }

    Carta gerarCartaAleatoria() {
        char numeroAleatorio = numeros[rand() % 10];
        string naipeAleatorio = naipes[rand() % 4];
        int valorAleatorio;

        if (numeroAleatorio == '4' && naipeAleatorio == "paus") {
            valorAleatorio = 50;
        } else if (numeroAleatorio == '7' && naipeAleatorio == "copas") {
            valorAleatorio = 40;
        } else if (numeroAleatorio == 'A' && naipeAleatorio == "espada") {
            valorAleatorio = 30;
        } else if (numeroAleatorio == '7' && naipeAleatorio == "ouros") {
            valorAleatorio = 20;
        } else if (numeroAleatorio == '3') {
            valorAleatorio = 13;
        } else if (numeroAleatorio == '2') {
            valorAleatorio = 12;
        } else if (numeroAleatorio == 'A') {
            valorAleatorio = 11;
        } else if (numeroAleatorio == 'K') {
            valorAleatorio = 10;
        } else if (numeroAleatorio == 'J') {
            valorAleatorio = 9;
        } else if (numeroAleatorio == 'Q') {
            valorAleatorio = 8;
        } else if (numeroAleatorio == '7') {
            valorAleatorio = 7;
        } else if (numeroAleatorio == '6') {
            valorAleatorio = 6;
        } else if (numeroAleatorio == '5') {
            valorAleatorio = 5;
        } else if (numeroAleatorio == '4') {
            valorAleatorio = 4;
        }
        return Carta(numeroAleatorio, naipeAleatorio, valorAleatorio);
    }
};

class Jogador {
public:
    string nome;
    Carta cartas[3]; 
    int pontos;

    Jogador(string nome, int pontos) {
        this->nome = nome;
        this->pontos = pontos;
    }
};

class Jogo {
public:
    void entregarCartas(Baralho& baralho, Jogador& jogador) {
        for (int i = 0; i < 3; i++) {
            jogador.cartas[i] = baralho.gerarCartaAleatoria();
        }
    }

    void mostrarCartas(Jogador jogador) {
        for (int i = 0; i < 3; i++) {
            cout << "As cartas do " << jogador.nome << " sao " << i + 1 << ": " << jogador.cartas[i].numero << " de " << jogador.cartas[i].naipe << endl;
        }
    }

    Carta selecionarCarta(Jogador& jogador) { 
        int i;
        mostrarCartas(jogador);
        cout << "Escolha uma carta (1, 2, ou 3): ";
        cin >> i;
        i--;

        Carta cartaEscolhida = jogador.cartas[i];

        for (int j = i; j < 2; j++) {
            jogador.cartas[j] = jogador.cartas[j + 1];
        }

        jogador.cartas[2] = Carta();
        return cartaEscolhida;
    }

    int grito(int& pontosPartida, int duplaQuePediu) {
        int menu;
        if (pontosPartida == 2) {
            cout << "1-Truco\n2-Não pedir" << endl;
            cin >> menu;
            if (menu == 1) {
                cout << "1-Aceitar\n2-Correr" << endl;
                cin >> menu;
                if (menu == 1) {
                    pontosPartida = 4; 
                    return 0;
                } else {
                    cout << "Ele correu" << endl;
                    return duplaQuePediu; 
                }
            }
        } else if (pontosPartida == 4) {
            cout << "1-Seis\n2-Não pedir" << endl;
            cin >> menu;
            if (menu == 1) {
                pontosPartida = 8; 
                return 0;
            } else {
                cout << "Ele correu" << endl;
                return duplaQuePediu;
            }
        } else if (pontosPartida == 8) {
            cout << "1-Nove\n2-Não pedir" << endl;
            cin >> menu;
            if (menu == 1) {
                pontosPartida = 12;
                return 0;
            } else {
                cout << "Ele correu" << endl;
                return duplaQuePediu;
            }
        }
        
        return 0;
    }

    void rodada(Jogador& jogador1, Jogador& jogador2, Jogador& jogador3, Jogador& jogador4) {
        int vitoriasD1 = 0;
        int vitoriasD2 = 0; 
        int empate = 0;
        int pontosPartida = 2;
        
        for (int i = 0; i < 3; i++) {
            int resultadoGrito;
            mostrarCartas(jogador1);
            mostrarCartas(jogador2);
            mostrarCartas(jogador3);
            mostrarCartas(jogador4);
            
            resultadoGrito = grito(pontosPartida, 1); 
            if (resultadoGrito == 1) {
                jogador1.pontos += pontosPartida;
                jogador3.pontos += pontosPartida;
                cout << "A dupla de " << jogador1.nome << " e " << jogador3.nome << " venceu por desistência." << endl;
                return;
            }
            
            resultadoGrito = grito(pontosPartida, 2);
            if (resultadoGrito == 2) {
                jogador2.pontos += pontosPartida;
                jogador4.pontos += pontosPartida;
                cout << "A dupla de " << jogador2.nome << " e " << jogador4.nome << " venceu por desistência." << endl;
                return;
            }

            Carta cartaJogador1 = selecionarCarta(jogador1);
            Carta cartaJogador2 = selecionarCarta(jogador2);
            Carta cartaJogador3 = selecionarCarta(jogador3);
            Carta cartaJogador4 = selecionarCarta(jogador4);

            Carta maiorCarta = cartaJogador1;
            Jogador* jogadorVencedor = &jogador1;
            bool houveEmpate = false; 

            if (cartaJogador2.valor > maiorCarta.valor) {
                maiorCarta = cartaJogador2;
                jogadorVencedor = &jogador2;
                houveEmpate = false;
            } else if (cartaJogador2.valor == maiorCarta.valor) {
                houveEmpate = true;
            }

            if (cartaJogador3.valor > maiorCarta.valor) {
                maiorCarta = cartaJogador3;
                jogadorVencedor = &jogador3;
                houveEmpate = false;
            } else if (cartaJogador3.valor == maiorCarta.valor) {
                houveEmpate = true;
            }

            if (cartaJogador4.valor > maiorCarta.valor) {
                maiorCarta = cartaJogador4;
                jogadorVencedor = &jogador4;
                houveEmpate = false;
            } else if (cartaJogador4.valor == maiorCarta.valor) {
                houveEmpate = true;
            }

            if (houveEmpate) {
                cout << "Os jogadores cangaram!" << endl;
                empate++; 
            } else {
                cout << "A maior carta é: " << maiorCarta.numero << " de " << maiorCarta.naipe << endl;
                cout << jogadorVencedor->nome << " venceu esta rodada." << endl;
                if (jogadorVencedor == &jogador1 || jogadorVencedor == &jogador3) {
                    vitoriasD1++;
                } else {
                    vitoriasD2++;
                }
            }

            if (vitoriasD1 >= 2 || vitoriasD2 >= 2 || empate == 2) break; 
        }

        if (vitoriasD1 >= 2) {
            cout << "A dupla de " << jogador1.nome << " e " << jogador3.nome << " venceu a rodada." << endl;
            jogador1.pontos += pontosPartida;
            jogador3.pontos += pontosPartida;
        } else if (vitoriasD2 >= 2) {
            cout << "A dupla de " << jogador2.nome << " e " << jogador4.nome << " venceu a rodada." << endl;
            jogador2.pontos += pontosPartida;
            jogador4.pontos += pontosPartida;
        }
    }
};

int main() {
    Jogador jogador1("Jogador 1", 0);
    Jogador jogador2("Jogador 2", 0);
    Jogador jogador3("Jogador 3", 0);
    Jogador jogador4("Jogador 4", 0);

    Baralho baralho;
    Jogo jogo;

    while (jogador1.pontos < 12 && jogador2.pontos < 12) {
        jogo.entregarCartas(baralho, jogador1);
        jogo.entregarCartas(baralho, jogador2);
        jogo.entregarCartas(baralho, jogador3);
        jogo.entregarCartas(baralho, jogador4);

        jogo.rodada(jogador1, jogador2, jogador3, jogador4);
    }

    if (jogador1.pontos >= 12 || jogador3.pontos >= 12) {
        cout << "A dupla de " << jogador1.nome << " e " << jogador3.nome << " venceu o jogo!" << endl;
    } else {
        cout << "A dupla de " << jogador2.nome << " e " << jogador4.nome << " venceu o jogo!" << endl;
    }

    return 0;
}
