/*
	Colégio Estadual Gabriel de Lara - 24/02/2026.
    Autor: Gerson Cesar Grobe de Miranda, 00
    Código Morse: --. . .-. ... --- -.
    
    Objetivo: prototipar uma aplicação para Converter em 
    Código Morse, uma frase digitada pelo usuário,
    associado a um buzzer passivo e um LED, programando o 
    Arduino para emissão de sinais sonoros e visuais.
*/

//Definir os pinos do Buzzer, botão e LED
#define buzzer 2
#define LED 4
#define pin_ponto 7
#define pin_traco 8

//Mapeamento das letras e simbolos do código
char alfabeto[37] = {
  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
  'p','q','r','s','t','u','v','w','x','y','z','1','2','3','4',
  '5','6','7','8','9','0',' '
};

const char* morse[37] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----",
  "..---", "...--", "....-", ".....", "-....", "--...", "---..",
  "----.", "-----", "/"
};

//tempos (em milissegundos)
int tempoPonto = 200;
int tempoTraco = 600;
int pausaEntreSimbolos = 200;
int pausaEntreLetras = 600;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(pin_ponto, OUTPUT);
  pinMode(pin_traco, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("--- Conversor Morse Iniciado ---");
  Serial.println("Digite a frase:");
}

void loop(){
  if (Serial.available() > 0) {
    String frase = Serial.readStringUntil('\n');
    frase.toLowerCase();
    
    Serial.print("Codificando: ");
    Serial.println(frase);
    
    for (int i=0; i < frase.length(); i++) {
      	char caracterAtual = frase[i];
      
      	//Buscar o caractere no alfabeto
      	for (int j = 0; j < 37; j++) {
        	if (caracterAtual == alfabeto[j]) {
          		executarMorse(morse[j]);
          		break;
        	}
      	}
    	delay(pausaEntreLetras);
  	}
  	Serial.println("\nPronto! Digite outra frase:");
	}
}

//Função Auxiliar para processar os pontos e traços
void executarMorse(const char* padrao) {
  for (int i = 0; padrao[i] != '\0'; i++ ) {
    char simbolo = padrao[i];
    Serial.print(simbolo);
    
    if (simbolo == '.') {
      emitirSinal(tempoPonto, pin_ponto);
    } else if (simbolo == '-') {
      emitirSinal(tempoTraco, pin_traco);
    } else if (simbolo == '/') {
      delay(tempoTraco);
    }
    delay(pausaEntreSimbolos);
  }
  Serial.print(" ");
}

void emitirSinal(int duracao, int pinoIndicador) {
  digitalWrite(LED, HIGH);
  digitalWrite(pinoIndicador, HIGH);
  tone(buzzer, 1000);
  
  delay(duracao);
  
  digitalWrite(LED, LOW);
  digitalWrite(pinoIndicador, LOW);
  noTone(buzzer);
}
