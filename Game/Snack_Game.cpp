#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

using namespace std;


const int altura = 20;
const int largura = 20;

int posicaoX, posicaoY; // controla aonde vai aparecer a jiboia
int FrutaPosicaoX, FrutaPosicaoY; // controla aonde vai aparecer a fruta
int CaldaPosicaoX[100], CaldaPosicaoY[100]; // definir o tamanho max da calda e o controle dela
int calda;
bool GameOver;
int pontuacao;

enum DirecaoDaCobra{
	
    PARE = 0,
	CIMA,
	BAIXO,
	ESQUERDA,
	DIREITA,
	
};

DirecaoDaCobra Direcao;

void EsconderCursor(){  // usado para esconder o cursor
CONSOLE_CURSOR_INFO cursor = {1, FALSE};
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void configuracao_inicial(){
	
	GameOver = false;
	Direcao = PARE;
	
	posicaoX = largura / 2; // para a cobra ficar na metade da largura
	posicaoY = altura / 2;  // para a cobra ficar na metade da altura quando o jogo começa
	
	srand((unsigned) time(NULL)); // funcaozinha para gerar aleatoriamente para a funcao rand()
	
	FrutaPosicaoX = rand() % largura; // para a fruta ir pra posicao aleatoriamente entre 0 e a largura  (obvio)
	FrutaPosicaoY = rand() % altura; // para a fruta ir pra posicao aleatoriamente entre 0 e a altura  (obvio)
	
	pontuacao = 0;
	
	
}








void DesenhaTela(){  

// substitui o system("cls");
printf("\033[H"); // para a tela parar de piscar
	
for(int i=0; i<largura+2; i++){  //criar a parede de cima
	
cout<<"*";
	
}

cout<<endl;	

for(int i = 0; i < altura; i++){
	
	for(int j = 0; j< largura; j++){
		
		if(j == 0){ //parede do canto
			
			cout<<"*";	
		}
		
		if(i == posicaoY && j == posicaoX){
			
			cout<<"O"; // aonde vai aparecer a proibida jiboia
		}
		
		else if(i == FrutaPosicaoY && j == FrutaPosicaoX){
			
			cout<<"F"; // aonde aparece a fruta
		}
		
		else{
			
			bool print = false;
			for(int k = 0; k < calda; k++){
				
				if(CaldaPosicaoX[k] == j && CaldaPosicaoY[k] == i){
					
					cout<<"o"; // onde aparece a calda da jiboia
					print = true;
				}
			}
			if(!print)
			cout<<" ";
		}
		
		if(j == largura -1){ //parede do meio
			
			cout<<"*";
		}	
	}
	cout<<endl;	
	
}


for(int i=0; i<largura+2; i++){  //criar a parede de baixo
	
cout<<"*";
	
}

cout<<endl;
cout<<"PONTUACAO: "<<pontuacao;
cout<<endl<<"controles (w, a, s, d)";
cout<<endl;
cout<<"Desenvolvido Por: Vinicius Lima";
}
	
void Controles(){
	
	if(_kbhit()){ // funcao pra verificar se alguma tecla foi apertada
		
		switch(_getch()){  // a funcao getch() é usada para pegar a tecla que foi apertada e verficar com o switch case
		   
		     case 'w':
		     	     Direcao = CIMA;
		     	break;
		     	
		     case 's':
		     	     Direcao = BAIXO; 
		     	break;
		     	
		     case 'a':
		     	     Direcao = ESQUERDA;
		     	break;
		     	
		     case 'd':
		     	     Direcao = DIREITA;
		     	break;
				 
			 case 'W':   // CASO ALGUÉM ESTEJA JOGANDO COM O CAPS LIGADO RRSRSR
		     	     Direcao = CIMA;
		     	break;
		     	
		     case 'S':
		     	     Direcao = BAIXO; 
		     	break;
		     	
		     case 'A':
		     	     Direcao = ESQUERDA;
		     	break;
		     	
		     case 'D':
		     	     Direcao = DIREITA;
		     	break;
				    
			 	
							 			
		}
		
	}
	
	
	
	
	
}

void Logica(){
	
	int PrevX = CaldaPosicaoX[0];  
	int PrevY = CaldaPosicaoY[0];
	int Prev2x, Prev2y;
	CaldaPosicaoX[0] = posicaoX;
	CaldaPosicaoY[0] = posicaoY;
	for(int i = 1; i <calda; i++){
		
		Prev2x = CaldaPosicaoX[i];
		Prev2y = CaldaPosicaoY[i];
		CaldaPosicaoX[i] = PrevX;
		CaldaPosicaoY[i] = PrevY;
		PrevX = Prev2x;
		PrevY = Prev2y;
		
		
	}
	
	
	switch(Direcao){ // seleciona a direção dos botoões
		
		case CIMA:
			posicaoY--;
			break;
			
		case BAIXO:
			posicaoY++;
		    break;
		    
		case ESQUERDA:
			posicaoX--;
		    break;
		    
		case DIREITA:
			posicaoX++;
		    break;	
		    
		default:
		    break;					
		
	}
	if(posicaoX > largura || posicaoX < 0 || posicaoY > altura || posicaoY < 0){ // acaba o game quando bate na parede
			GameOver = true;

	for(int i  = 0; i < calda; i++)
	   if(CaldaPosicaoX[i] == posicaoX && CaldaPosicaoY[i] == posicaoY)	{ // acaba o game quando bate na propia calda
	   	
	       GameOver = true; 	
	   }	
		}
		if(posicaoX == FrutaPosicaoX && posicaoY == FrutaPosicaoY){
			
			pontuacao += 10;
			FrutaPosicaoX = rand() % largura;
			FrutaPosicaoY = rand() % altura;
			calda++;
		}
		
}
	
int main (){
	
	system(""); // usado junto com o printf("\033[H"); para a tela parar de piscar
	EsconderCursor(); // esconde o cursor
	void configuracao_inicial();
	while (!GameOver){
		Sleep(80); //define a velocidade da cobra
		DesenhaTela();
		Controles();
		Logica();

	}
		
		







return 0;


}
