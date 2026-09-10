/*
	Colégio Estadual Gabriel de Lara - 09/09/2026
    Autor: Gerson Cesar Grobe de Miranda, 00
    
    Objetivo: estudar o funcionamento do display de 7 segmentos.
*/

//Pinos dos segmentos: a, b, c, d, e, f, g
const int pinosSegmentos[7] = {13, 12, 4, 7, 6, 10, 11};

//Mapeamento dos dígitos de 0 a 9 para CÁTODO COMUM (ÂNODO trocar)
int x = 0;  //int x = 1;
int o = 1;  //int o = 0;
const byte numeros[10][7] = {
    {o,o,o,o,o,o,x}, // digito 0
    {x,o,o,x,x,x,x}, // digito 1
    {o,o,x,o,o,x,o}, // digito 2
    {o,o,o,o,x,x,o}, // digito 3
    {x,o,o,x,x,o,o}, // digito 4
    {o,x,o,o,x,o,o}, // digito 5
    {o,x,o,o,o,o,o}, // digito 6
    {o,o,o,x,x,x,x}, // digito 7
    {o,o,o,o,o,o,o}, // digito 8
    {o,o,o,o,x,o,o}  // digito 9
};

void setup() {
  for (int i = 0; i<7; i++) {
    pinMode(pinosSegmentos[i], OUTPUT);
  }
}

void loop() {
  for (int contador = 0; contador < 10; contador++) {
    exibirNumero(contador);
    delay(1000); //aguarda 1 segundo antes de mudar
  }
}

//Função para mostrar os dígitos
void exibirNumero(int num) {
  for (int i=0; i<7; i++) {
    digitalWrite(pinosSegmentos[i], numeros[num][i]);
  }
}
