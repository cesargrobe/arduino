/***************************************************
AULA 4 - Funções com LEDs por botão - 11/03/2026

Autor: Gerson Cesar Grobe de Miranda
***************************************************/

//Denominar os pinos de ligação
#define led1 13
#define led2 12
#define led3 11
#define led4 10
#define led5 9
#define botao 2

//variáveis de controle
int modo = 0;   // 0: desligado, 1: vai-vem, 2: aleatorio
bool botaoPressionado = false;
int tempo = 250;

// modo de ligação dos pinos
void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT); // OUTPUT - saída
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(botao, INPUT_PULLUP); // INPUT_PULLUP resistência interna
  
  //inicializa o gerador aleatório percebendo o ruido do pino
  randomSeed(analogRead(0));

}

// loop de programação lógica de funcionamento
void loop() {
  
  bool leitura = digitalRead(botao);
  
  if (leitura == LOW && !botaoPressionado ) {
    
	modo++;  //soma 1 ao modo atual
    if (modo > 2) modo = 0; //se passar de volta pra 0
    botaoPressionado = true; // marca que o botão ainda está pressionado
    delay(50); // respiro para evitar ruído (bouce)
  }
  
  //verifica se botão foi solto para permitir novo click
  if (leitura == HIGH && botaoPressionado ) {
    botaoPressionado = false;
  }
  
  //execução das funções em modo
  if (modo == 1) {
    sequenciaVaiVem();
    Serial.print("Modo Vai-Vem: ");
    Serial.println(modo);
  } else if (modo == 2){
    sequenciaAleatoria();
    Serial.print("Modo Aleatorio: ");
    Serial.println(modo);
  } else {
    desligarTodos();
    Serial.print("Modo Desligado: ");
    Serial.println(modo);
  }
}

/************** FUNÇÕES CRIADAS ****************/

void sequenciaVaiVem() {
  int pinos[] = {led1, led2, led3, led4, led5};
  //ida
  for (int i=0; i<5; i++) {
    
    if (digitalRead(botao) == LOW && !botaoPressionado ) return;
    
    digitalWrite(pinos[i], HIGH);
    delay(tempo);
    digitalWrite(pinos[i], LOW);
  }
  //volta
  for (int i=4; i>=0; i--) {
    
    if (digitalRead(botao) == LOW && !botaoPressionado ) return;
    
    digitalWrite(pinos[i], HIGH);
    delay(tempo);
    digitalWrite(pinos[i], LOW);
  }
}

void desligarTodos() {
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  digitalWrite(led5,LOW);
}

// Função aleatória para ligar LEDs
void sequenciaAleatoria() {
  int pinos[] = {led1, led2, led3, led4, led5};
  int sorteio = random(0, 5); //Sorteia um indice de 0 a 4
  digitalWrite(pinos[sorteio], HIGH);
  delay(tempo);
  digitalWrite(pinos[sorteio], LOW);
}





