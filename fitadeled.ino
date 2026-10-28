/*
  Colégio Estadual Gabriel de Lara - 17/09/2026
  Autor: Gerson Cesar Grobe de Miranda, 00

  Objetivo: Controlar uma fita de LEDs com
  controle remoto infravermelho para ligar e desligar a fita,
  selecionar cores e ajustar a velocidade dos efeitos luminosos.
*/

#include <Adafruit_NeoPixel.h>
#include <IRremote.h>

#define PIN 2
#define PIN_IR 3
#define numeroPixels 10      // alterar a quantidade = 300

Adafruit_NeoPixel pixels(
  numeroPixels, PIN, NEO_RGB + NEO_KHZ800
);

// Valores retornados pelo mapeamento do controle.
// Representam a posição do botão, não seu rótulo.
const int BT_POWER = 0;
const int BT_MAIS  = 1;
const int BT_MENOS = 9;
const int BT_0     = 12;
const int BT_1     = 16;
const int BT_2     = 17;
const int BT_3     = 18;

int tempo = 180;

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

bool ligada = true;
bool automatico = true;

int posicao = 0;
int direcao = 1;

unsigned long ultimaAtualizacao = 0;

// Converte o código recebido para a posição do botão.
int mapCodeToButton(unsigned long code) {
  if ((code & 0x0000FFFF) == 0x0000BF00) {
    code >>= 16;
    if (((code >> 8) ^ (code & 0x00FF)) == 0x00FF) {
      return code & 0xFF;
    }
  }
  return -1;
}

// Retorna -1 quando não há um botão válido.
int readInfrared() {
  int result = -1;

  if (IrReceiver.decode()) {
    // Ignora repetições ao manter um botão pressionado.
    if (!(IrReceiver.decodedIRData.flags
          & IRDATA_FLAGS_IS_REPEAT)) {
      unsigned long code =
        IrReceiver.decodedIRData.decodedRawData;

      result = mapCodeToButton(code);
    }

    IrReceiver.resume();
  }

  return result;
}

void setup() {
  Serial.begin(9600);

  pixels.begin();
  pixels.show();

  // Pino 3 para o receptor; pino 2 fica com a fita.
  IrReceiver.begin(PIN_IR);

  setColor();
}

void loop() {
  int button = readInfrared();

  if (button >= 0) {
    Serial.print("Botao: ");
    Serial.println(button);

    tratarComando(button);
  }

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

      // Final da fita: muda a cor e começa a voltar.
      if (posicao >= numeroPixels) {
        posicao = numeroPixels - 1;
        direcao = -1;
        setColor();
      }
      // Início da fita: muda a cor e avança novamente.
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
        preencherFita(0, 0, 0);
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
      corFixa(255, 0, 0);
      break;

    case BT_2:
      corFixa(0, 255, 0);
      break;

    case BT_3:
      corFixa(0, 0, 255);
      break;

    case BT_MAIS:
      tempo = max(30, tempo - 30);
      break;

    case BT_MENOS:
      tempo = min(1000, tempo + 30);
      break;
  }
}

void preencherFita(int vermelho, int verde, int azul) {
  for (int i = 0; i < numeroPixels; i++) {
    pixels.setPixelColor(
      i, pixels.Color(vermelho, verde, azul)
    );
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
