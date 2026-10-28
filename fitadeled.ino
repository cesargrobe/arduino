/*
    Colégio Estadual Gabriel de Lara - 17/09/2026
    Autor: Gerson Cesar Grobe de Miranda, 00

    Objetivo: Controlar fita de LEDs endereçáveis com controle remoto IR
    utilizando a biblioteca IRremote v3+ e protocolo NEC mapeado.
*/

#include <Adafruit_NeoPixel.h>
#include <IRremote.hpp>

#define PIN 2
#define PIN_IR 3
#define numeroPixels 50 // Se alterar para 300, lembre-se da fonte externa de 5V!

// Inicialização dos NeoPixels (padrão NEO_GRB para fitas WS2812B)
Adafruit_NeoPixel pixels(numeroPixels, PIN, NEO_GRB + NEO_KHZ800);

// Mapeamento dos botões (baseado na sua leitura)
const uint8_t BT_POWER = 0x1C; // Centro
const uint8_t BT_0     = 0x19; // Botão 0 (Ativa o Efeito Automático)
const uint8_t BT_1     = 0x45; // Botão 1
const uint8_t BT_2     = 0x46; // Botão 2
const uint8_t BT_3     = 0x47; // Botão 3
const uint8_t BT_4     = 0x44; // Botão 4
const uint8_t BT_5     = 0x40; // Botão 5
const uint8_t BT_6     = 0x43; // Botão 6
const uint8_t BT_MAIS  = 0x18; // Norte (Aumenta velocidade)
const uint8_t BT_MENOS = 0x52; // Sul (Diminui velocidade)

int tempo = 180;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

bool ligada = true;
bool automatico = true;

int posicao = 0;
int direcao = 1;

unsigned long ultimaAtualizacao = 0;

// Leitura do controle infravermelho
int readInfrared() {
  if (IrReceiver.decode()) {
    // Filtra apenas comandos NEC e ignora repetição ao manter pressionado
    if (IrReceiver.decodedIRData.protocol == NEC && 
       !(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
      
      uint8_t command = IrReceiver.decodedIRData.command;
      
      Serial.print("Comando Recebido: 0x");
      if (command < 0x10) Serial.print("0");
      Serial.println(command, HEX);
      
      IrReceiver.resume();
      return command;
    }
    IrReceiver.resume();
  }
  return -1;
}

void setup() {
  Serial.begin(9600);

  pixels.begin();
  pixels.show(); // Desliga todos os LEDs na inicialização

  pinMode(PIN_IR, INPUT_PULLUP);
  IrReceiver.begin(PIN_IR, ENABLE_LED_FEEDBACK);

  setColor();
}

void loop() {
  int button = readInfrared();

  if (button >= 0) {
    tratarComando(button);
  }

  // Executa o efeito de ida e volta sem travar o código com delay()
  if (ligada && automatico) {
    unsigned long agora = millis();

    if (agora - ultimaAtualizacao >= (unsigned long)tempo) {
      ultimaAtualizacao = agora;

      pixels.setPixelColor(
        posicao,
        pixels.Color(redColor, greenColor, blueColor)
      );
      pixels.show();

      posicao += direcao;

      // Final da fita: troca a cor e retorna
      if (posicao >= numeroPixels) {
        posicao = numeroPixels - 1;
        direcao = -1;
        setColor();
      }
      // Início da fita: troca a cor e avança
      else if (posicao < 0) {
        posicao = 0;
        direcao = 1;
        setColor();
      }
    }
  }
}

void tratarComando(int button) {
  switch (button) {
    case BT_POWER:
      ligada = !ligada;

      if (!ligada) {
        preencherFita(0, 0, 0); // Desliga a fita
      } else if (automatico) {
        reiniciarEfeito();
      } else {
        preencherFita(redColor, greenColor, blueColor);
      }
      break;

    case BT_0:
      ligada = true;
      automatico = true;
      reiniciarEfeito();
      break;

    case BT_1:
      corFixa(255, 0, 0); // Vermelho
      break;

    case BT_2:
      corFixa(0, 255, 0); // Verde
      break;

    case BT_3:
      corFixa(0, 0, 255); // Azul
      break;

    case BT_4:
      corFixa(255, 255, 0); // Amarelo
      break;

    case BT_5:
      corFixa(255, 0, 255); // Roxo / Magenta
      break;

    case BT_6:
      corFixa(0, 255, 255); // Ciano
      break;

    case BT_MAIS:
      tempo = max(20, tempo - 30); // Aumenta a velocidade do efeito
      Serial.print("Velocidade (tempo ms): ");
      Serial.println(tempo);
      break;

    case BT_MENOS:
      tempo = min(1000, tempo + 30); // Diminui a velocidade do efeito
      Serial.print("Velocidade (tempo ms): ");
      Serial.println(tempo);
      break;
  }
}

void preencherFita(int vermelho, int verde, int azul) {
  for (int i = 0; i < numeroPixels; i++) {
    pixels.setPixelColor(i, pixels.Color(vermelho, verde, azul));
  }
  pixels.show();
}

void corFixa(int vermelho, int verde, int azul) {
  ligada = true;
  automatico = false;

  redColor = vermelho;
  greenColor = verde;
  blueColor = azul;

  preencherFita(redColor, greenColor, blueColor);
}

void reiniciarEfeito() {
  posicao = 0;
  direcao = 1;
  ultimaAtualizacao = millis();

  setColor();
  preencherFita(0, 0, 0);
}

void setColor() {
  redColor = random(0, 256);
  greenColor = random(0, 256);
  blueColor = random(0, 256);
}
