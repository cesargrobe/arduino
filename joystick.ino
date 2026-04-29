/*
  Colégio Estadual Gabriel de Lara - 22/04/2026
  Autor: Gerson Cesar Grobe de Miranda

  Objetivos: Estudar as ligações do JoyStick Shield
*/

//Não alterar os números das portas
#define botaoA 2
#define botaoB 3
#define botaoC 4
#define botaoD 5
#define botaoE 6
#define botaoF 7
#define botaoK 8
//mapeamento dos eixos X e Y
#define eixoX A0
#define eixoY A1

void setup() {
  // monitor serial
  Serial.begin(9600);
  //Configurar todos os botões como entrada e resistor interno
  for (int D = 2; D <= 8; D++) {
    pinMode(D, INPUT_PULLUP);
  }

  Serial.println("Sistema Iniciado. Pressione um botao...");
}

void loop() {
  //leitura dos valores analógicos (0 a 1023)
  int valorX = analogRead(eixoX);
  int valorY = analogRead(eixoY);

  //exibe os valores no monitor serial
  Serial.print("X: ");
  Serial.print(valorX);
  Serial.print(" | Y: ");
  Serial.println(valorY);
  // identificar movimento simples
  if (valorX > 600) { Serial.println("Movendo para a DIREITA"); }
  if (valorX < 400) { Serial.println("Movendo para a ESQUERDA"); }
  if (valorY > 600) { Serial.println("Movendo para CIMA"); }
  if (valorY < 400) { Serial.println("Movendo para BAIXO"); }
  delay(200); //pequena pausa para facilitar a leitura

}
