/*
  Porta Automática com Sensor Ultrassônico e Servo Motor
  -------------------------------------------------------
  Componentes:
    - Arduino Uno (ou compatível)
    - Sensor ultrassônico HC-SR04
    - Servo motor (ex: SG90)
    - Resistor de 220Ω (opcional, para LED indicador)
    - LED verde (opcional, indica porta aberta)

  Funcionamento:
    O sensor HC-SR04 mede a distância de objetos à frente da porta.
    Quando um objeto (pessoa) é detectado a menos de DISTANCIA_ABERTURA cm,
    o servo gira para a posição "aberta" (90°). Após TEMPO_ABERTA ms sem
    detectar ninguém próximo, a porta fecha (servo volta a 0°).

  Conexões:
    HC-SR04  -> Arduino
      VCC    -> 5V
      GND    -> GND
      TRIG   -> pino 9
      ECHO   -> pino 10

    Servo    -> Arduino
      Sinal  -> pino 6
      VCC    -> 5V
      GND    -> GND

    LED      -> pino 13 (via resistor de 220Ω)
*/

#include <Servo.h>

// --- Pinos ---
const int PINO_TRIG = 9;
const int PINO_ECHO = 10;
const int PINO_SERVO = 6;
const int PINO_LED = 13;

// --- Parâmetros ---
const int DISTANCIA_ABERTURA = 30;  // cm — distância para abrir a porta
const int ANGULO_ABERTA = 90;       // graus — servo na posição aberta
const int ANGULO_FECHADA = 0;       // graus — servo na posição fechada
const unsigned long TEMPO_ABERTA = 3000; // ms — tempo mínimo que a porta fica aberta

Servo servoPorta;

bool portaAberta = false;
unsigned long tempoUltimaDeteccao = 0;

// Retorna a distância em cm medida pelo HC-SR04
long medirDistancia() {
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);

  long duracao = pulseIn(PINO_ECHO, HIGH, 30000); // timeout 30 ms (~5 m)
  if (duracao == 0) return 999; // sem eco — distância muito grande
  return duracao / 58;          // converte microssegundos para centímetros
}

void abrirPorta() {
  servoPorta.write(ANGULO_ABERTA);
  digitalWrite(PINO_LED, HIGH);
  portaAberta = true;
}

void fecharPorta() {
  servoPorta.write(ANGULO_FECHADA);
  digitalWrite(PINO_LED, LOW);
  portaAberta = false;
}

void setup() {
  Serial.begin(9600);
  pinMode(PINO_TRIG, OUTPUT);
  pinMode(PINO_ECHO, INPUT);
  pinMode(PINO_LED, OUTPUT);

  servoPorta.attach(PINO_SERVO);
  fecharPorta();

  Serial.println("Porta automática iniciada.");
}

void loop() {
  long distancia = medirDistancia();
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia < DISTANCIA_ABERTURA) {
    tempoUltimaDeteccao = millis();
    if (!portaAberta) {
      Serial.println("Objeto detectado — abrindo porta.");
      abrirPorta();
    }
  } else if (portaAberta && (millis() - tempoUltimaDeteccao >= TEMPO_ABERTA)) {
    Serial.println("Nenhum objeto detectado — fechando porta.");
    fecharPorta();
  }

  delay(100);
}
