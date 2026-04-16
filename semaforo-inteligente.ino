/********************************************
Colégio Estadual Gabriel de Lara - 17/03/2026
Autor: Gerson Cesar Grobe de Miranda, 00

Objetivo: Montar um semáforo inteligente com
sensor PIR, para entender o funcionamento e 
programar, utilizando funções.

*********************************************/

#define PIN_SENSOR 2
#define PIN_LED_VERDE_CAR 3
#define PIN_LED_AMARELO_CAR 4
#define PIN_LED_VERMELHO_CAR 5
#define PIN_LED_VERDE_PED 6
#define PIN_LED_VERMELHO_PED 7

// O uso de 'volatile' é usado para variáveis em interrupções
volatile int modo = 0;

void setup () {
  pinMode(PIN_SENSOR, INPUT);
  // configura os pinos 3 a 7 como SAÍDA
  for (int i=3; i<=7; i++) {
    pinMode(i, OUTPUT);
  }
  
  // Ajustado para RISING: o sensor PIR envia 5V ao detectar movimento
  // Se o sensor for invertido, use FALLING
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR), sensorAcionado, CHANGE);
}

void loop () {
  
  switch (modo) {
    case 0:
      modocarros();
      break;
    case 1:
      travessia();
      break;    
  }
}

//Função chamada pela interrupção
void sensorAcionado() {
  modo = 1;
}

//Função travessia
void travessia() {
  //pausa de segurança
  delay(1000);
  
  //Carros: Verde -> Amarelo
  digitalWrite(PIN_LED_VERDE_CAR, LOW);
  digitalWrite(PIN_LED_AMARELO_CAR, HIGH);
  delay(3000);
  //Carros: Vermelho // Pedestre: Verde
  digitalWrite(PIN_LED_AMARELO_CAR, LOW);
  digitalWrite(PIN_LED_VERMELHO_CAR, HIGH);
  delay(500);
  digitalWrite(PIN_LED_VERMELHO_PED, LOW);
  digitalWrite(PIN_LED_VERDE_PED, HIGH);
  delay(5000);
  
  //Pedestre: Verde apaga, Vermelho pisca(Alerta)
  digitalWrite(PIN_LED_VERDE_PED, LOW);
  for (int i=0; i<=5; i++) {
    digitalWrite(PIN_LED_VERMELHO_PED, HIGH);
    delay(300);
    digitalWrite(PIN_LED_VERMELHO_PED, LOW);
    delay(300);
  }
  //volta para o estado inicial
  modo = 0;
}

//Função modocarros
void modocarros() {
  digitalWrite(PIN_LED_VERDE_PED, LOW);
  digitalWrite(PIN_LED_VERMELHO_PED, HIGH);
  digitalWrite(PIN_LED_VERDE_CAR, HIGH);
  digitalWrite(PIN_LED_AMARELO_CAR, LOW);
  digitalWrite(PIN_LED_VERMELHO_CAR, LOW);
}
