#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// verifica se existe um caminho entre o estado atual ate o estado destino, com transicoes vazias
bool verificaTransicoesVazias(vector<pair<int,int>> transicoesVazias,vector<int>* teste,vector<char>* resposta, int estadoAtual, int destino){
    int aux = destino;
    int indice = -1;
    pair<int,int> T;

    while(estadoAtual != destino){// enquanto o estado atual nao for o desejado e, inicialmente aux = destino,
        if(aux <= estadoAtual) return false;
        
        T = make_pair(estadoAtual,aux);
        for(int i=0; i<transicoesVazias.size();i++)
            if(T == transicoesVazias[i]) indice = i;// tenta encontrar uma transicao vazia entre atual e aux

        if(indice == -1){// caso nao exista, tenta encontrar transicao entre atual e aux-1
            aux--;
            continue;
        }
        else{
            estadoAtual = aux;
            teste->push_back(estadoAtual);// caso exista, entao se trata de um caminho ate o estado destino
            resposta->push_back('&');
            aux++;
        }
    }
    return true;
}

int main()
{
    int N, F, numEstados, X, Y, c;
    
    cin >> N;
    char alfabeto[N+1];
    alfabeto[0] = '&';
    for(int i=1; i<=N; i++){
        cin >> alfabeto[i];
    }
    cin >> numEstados;
    bool ehFinal[numEstados];

    cin >> F;
    int Finais[F];
    for(int i=0; i<F; i++){
        cin >> Finais[i];
        ehFinal[i] = true;// os indices correspondentes aos estados finais, recebem True
    }
    
    int** transicoes = new int*[numEstados];// funcao transicao
    for(int i=0; i<numEstados; i++){
        transicoes[i] = new int[N+1];
    }
    
    for(int i=0; i<numEstados; i++)
        for(int j=0; j<N+1; j++)
            transicoes[i][j] = -1;// valor default para todas as transicoes

    // armazena as transicoes
    string str;
    vector<pair<int,int>> transicoesVazias;
    cin >> X >> str >> Y;
    
    while(X != -1 and str != "*" and Y != -1)
    {
        if(X < 0 or Y < 0 or X >= numEstados or Y >= numEstados) return -1;

        for(int i=0; i<str.length();i++){// para cada letra
            for(c=0; c<N+1; c++){// pega o indice c da letra no vetor alfabeto
                if(str[i] == alfabeto[c])
                    break;
            }
            if(c == 0){// alfabeto[0] = '&', portanto eh uma transicao vazia
                transicoesVazias.push_back(pair<int,int>(X,Y));
                transicoes[X][c] = '&';// flag
            }
            else transicoes[X][c] = Y;
        }
        cin >> X >> str >> Y;
    }

    // verifica as palavras
    int estadoAtual, proxEstado;
    vector<int> teste;// armazena os estados do teste
    vector<char> resposta;// armazena os caracteres lidos incluindo o vazio
    cin >> str;
    while(str != "*")
    {
        estadoAtual = 0;
        teste.clear();
        teste.push_back(estadoAtual);
        resposta.clear();
        bool falhaTransicao = false;

        for(int i=0; i<str.length();i++){// para cada letra
            for(c=0; c<N+1; c++){// pega o indice c da letra no vetor alfabeto
                if(str[i] == alfabeto[c])
                    break;
            }

            proxEstado = transicoes[estadoAtual][c];
            
            if(proxEstado == -1){// caso nao exista transicao, verificar se ha caminho atravez de transicoes vazias
                int destino = estadoAtual+1;
                bool ok = false;
                while(destino < numEstados)
                {
                    if(transicoes[destino][c] != -1){// se o estado "destino" aceita o caratere
                        ok = verificaTransicoesVazias(transicoesVazias,&teste,&resposta,estadoAtual,destino);
                        if(ok){ resposta.push_back(str[i]); break;}
                    }
                    destino++;
                }
                if(!ok and destino >= numEstados) falhaTransicao = true;
            }
            else{
                estadoAtual = proxEstado;
                teste.push_back(estadoAtual);
                resposta.push_back(str[i]);
            }
        }

        // verifica se o estado atual eh final
        if(!ehFinal[estadoAtual] or falhaTransicao) cout << str << ": nao" << endl;
        else{
            cout << str << ": sim" << endl;
            for(int i=0, j=0; i < resposta.size(); i++, j++)
                cout << teste[j] << " -> " << resposta[i] << " -> " << teste[j+1] <<endl;
        }

        cin >> str;
    }

    for(int i=0; i<numEstados; i++)
        delete transicoes[i];
    delete transicoes;

    return 0;
}