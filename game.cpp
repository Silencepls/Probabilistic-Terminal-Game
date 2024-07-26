#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

struct Game_state
{
    int vitoria = 0;
    int derrota = 0;
};

class Entidade{
public:
    float vida = 20;
    float chance_de_acerto;
    float bonus_multiplier;
    Entidade(float n, float b){
        chance_de_acerto = n;
        bonus_multiplier = b;
    }

    float Dano_Calculado(){
        float acerto = rand() % 100;
        if(chance_de_acerto < acerto) return 0;
        return (rand() % 10) * bonus_multiplier;
    }
};

void Printar_Score(Game_state game_state){
    cout << "vitorias: " << game_state.vitoria << endl;
    cout << "derrotas: " << game_state.derrota << endl << endl;
} 

string Conversor_para_String(int vitorias, int derrotas, int player_vida, int enemy_vida){
    string data = to_string(vitorias) + "\n" + to_string(derrotas) + "\n" + 
                                to_string(player_vida) + "\n" + to_string(enemy_vida);
    return data;
}

int main(){
    Game_state game_state = Game_state(); 

    Entidade player = Entidade(75, 3);
    Entidade enemy = Entidade(75, 2);
    
    char carregar;

    cout << "carregar jogo? s ou n: ";
    cin >> carregar;

    if(carregar == 's'){
        char cadeia[10];
        FILE *p;
        p = fopen("save.txt", "r");

        fgets(cadeia, sizeof(cadeia), p);
        game_state.vitoria = atoi(cadeia);
        fgets(cadeia, sizeof(cadeia), p);
        game_state.derrota = atoi(cadeia);
        fgets(cadeia, sizeof(cadeia), p);
        player.vida = atoi(cadeia);
        fgets(cadeia, sizeof(cadeia), p);
        enemy.vida = atoi(cadeia);

        fclose(p);

        cout << endl;
        cout << "player vida: " << player.vida << endl;
        cout << "enemy vida: " << enemy.vida << endl;
        Printar_Score(game_state);
    }
    else {
        game_state.vitoria = 0;
        game_state.derrota = 0;        
    }


    char resposta;
    while (true)
    {
        cout << "jogar (j), salvar (s), exitar (e) placar(p)?: ";
        cin >> resposta;
        cout << endl;
        if (resposta == 'p') Printar_Score(game_state);
        if(resposta == 'e') return 0;
        if(resposta == 's'){
            FILE *p;
            p = fopen("save.txt", "w");

            string str = Conversor_para_String(game_state.vitoria, game_state.derrota,
                                                player.vida, enemy.vida);
            fwrite(str.c_str(), sizeof(char), str.size(), p);
            fclose(p);

            cout << "Jogo salvo" << endl;
            return 0;
        }
        if(resposta == 'j'){
            float player_dano = player.Dano_Calculado();
            float enemy_dano = enemy.Dano_Calculado();
            if (player_dano == 0) cout << "player errou" << endl;
            else cout << "player causou " << player_dano << " de dano" << endl;
            if (enemy_dano == 0) cout << "enemy errou" << endl;
            else cout << "enemy causou " << enemy_dano << " de dano" << endl;

            player.vida -= enemy_dano;
            enemy.vida -= player_dano;

            cout << "player: " << player.vida << "  enemy: " << enemy.vida << endl;
        
            if (player.vida <= 0){
                cout << "---- DERROTA ----" << endl;
                game_state.derrota++;
                player.vida = 20;
            }
            if (enemy.vida <= 0) {
                cout << "---- VITORIA ----" << endl;
                game_state.vitoria++;
                enemy.vida = 20;
            }
            cout << endl;
        }
    }
    
}