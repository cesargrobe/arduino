/***************************************************
AULA 3 - Acionamento de LEDs por botão - 04/03/2026

Autor: Gerson Cesar Grobe de Miranda
***************************************************/

//Denominar os pinos de ligação
#define led1 13
#define led2 12
#define botao 2


//variáveis de controle
bool estadoLED = false;
bool botaoPressionado = false;

int tempo = 400;

// modo de ligação dos pinos
void setup() {
  pinMode(led1, OUTPUT); // OUTPUT - saída
  pinMode(botao, INPUT_PULLUP); // INPUT_PULLUP resistência interna
  pinMode(led2, OUTPUT);

}

// loop de programação lógica de funcionamento
void loop() {
  // lógica de leitura: o PULLUP pressionado retorna LOW
  bool leitura = digitalRead(botao);
  
  //verifica se o botão foi apertado (transição de HIGH para LOW
  if (leitura == LOW && !botaoPressionado ) {
    estadoLED = !estadoLED; //inverte o estado
    digitalWrite(led1, estadoLED);
    delay(tempo);
    digitalWrite(led2, estadoLED);
    delay(tempo);
    
    botaoPressionado = true; // marca que o botão ainda está pressionado
    delay(50); // respiro para evitar ruído (bouce)
  }
  
  //verifica se botão foi solto para permitir novo click
  if (leitura == HIGH && botaoPressionado ) {
    botaoPressionado = false;
  }
}
