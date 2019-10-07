#ifndef __MENU_H__
#define __MENU_H__

#include "Tetris.h"

class Menu
{
    
public: 
    
    void Render();
    void Reshape(float w, float h);
    void Mouse(int button, int state, int x, int y);
    void KeySpecial(int key, int x, int y);
    void Key(unsigned char key, int x, int y);
    bool Loop();
    
    void StartGame();
    
    void SetModo(bool s){_modo = s;};
    bool Modo(){return _modo;};
    
    void SetTamanho(int s){_tamanho = s;};
    int Tamanho(){return _tamanho;};
    
    void SetCor(int s){_cor = s;};
    int Cor(){return _cor;};
    
    void Exit();

    bool is_open(){return state;};
    void set_state(bool k){state = k;};
    
    int velocidade(){return _velocidade;};
    void set_velocidade(int k){_velocidade = k;};
    
    int larguraJogo(){return _larguraJogo;};
    void set_larguraJogo(int k){_larguraJogo = k;};
    
    int alturaMaximaJogo(){return _alturaMaximaJogo;};
    void set_alturaMaximaJogo(int k){_alturaMaximaJogo = k;};
    
    bool RestartGame(){
        if(!_restart) return false;
        else{
            _restart = false;
            return true;
        }
    };
    
private:
    
    bool state;
    bool _restart = false;
    
    int _velocidade;
    bool _modo;
    int _tamanho;
    int _cor;
    
    int _larguraJogo;
    int _alturaMaximaJogo;

};


#endif
