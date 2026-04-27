/*
  Detector de Incêndio com Sensor de Chama e Sensor de Temperatura (LM35)
  -------------------------------------------------------------------------
  Componentes:
    - Arduino Uno (ou compatível)
    - Sensor de chama (módulo IR de chama)
    - Sensor de temperatura LM35
    - Buzzer ativo
    - LED vermelho (alarme visual)
    - LED verde (status normal)

  Funcionamento:
    O sistema monitora continuamente dois sensores:
      1. Sensor de chama: detecta a presença de chamas via infravermelho.
      2. Sensor LM35: mede a temperatura ambiente em graus Celsius.
    Quando qualquer um dos sensores indicar perigo (chama detectada OU
    temperatura acima de TEMP_LIMITE °C), o buzzer é ativado, o LED
    vermelho acende e uma mensagem de alerta é enviada pela Serial.
    Na ausência de perigo, apenas o LED verde fica aceso.

  Conexões:
    Sensor de chama  -> Arduino
      VCC            -> 5V
      GND            -> GND
      D0 (digital)   -> pino 7

    LM35             -> Arduino
      VCC            -> 5V
      GND            -> GND
      VOUT           -> A0

    Buzzer           -> pino 8
    LED vermelho     -> pino 12 (via resistor de 220Ω)
    LED verde        -> pino 13 (via resistor de 220Ω)
*/

// --- Pinos ---
const int PINO_CHAMA = 7;        // sinal digital do sensor de chama (LOW = chama)
const int PINO_LM35 = A0;        // sinal analógico do LM35
const int PINO_BUZZER = 8;
const int PINO_LED_ALARME = 12;
const int PINO_LED_NORMAL = 13;

// --- Parâmetros ---
const float TEMP_LIMITE = 60.0;  // °C — temperatura acima da qual o alarme dispara
const int FREQ_BUZZER = 1000;    // Hz — frequência do beep do buzzer

// Converte leitura analógica do LM35 para graus Celsius
// LM35: 10 mV/°C, referência de 5 V → temp = (leitura * 5.0 / 1023.0) * 100
float lerTemperatura() {
  int leitura = analogRead(PINO_LM35);
  return (leitura * 5.0 / 1023.0) * 100.0;
}

void ativarAlarme() {
  tone(PINO_BUZZER, FREQ_BUZZER);
  digitalWrite(PINO_LED_ALARME, HIGH);
  digitalWrite(PINO_LED_NORMAL, LOW);
}

void desativarAlarme() {
  noTone(PINO_BUZZER);
  digitalWrite(PINO_LED_ALARME, LOW);
  digitalWrite(PINO_LED_NORMAL, HIGH);
}

void setup() {
  Serial.begin(9600);
  pinMode(PINO_CHAMA, INPUT);
  pinMode(PINO_BUZZER, OUTPUT);
  pinMode(PINO_LED_ALARME, OUTPUT);
  pinMode(PINO_LED_NORMAL, OUTPUT);

  desativarAlarme();
  Serial.println("Detector de incêndio iniciado.");
  Serial.print("Limite de temperatura: ");
  Serial.print(TEMP_LIMITE);
  Serial.println(" °C");
}

void loop() {
  bool chamaDetectada = (digitalRead(PINO_CHAMA) == LOW); // LOW = chama presente
  float temperatura = lerTemperatura();

  Serial.print("Temperatura: ");
  Serial.print(temperatura, 1);
  Serial.print(" °C | Chama: ");
  Serial.println(chamaDetectada ? "DETECTADA" : "Não detectada");

  if (chamaDetectada) {
    Serial.println("⚠ ALERTA: Chama detectada!");
    ativarAlarme();
  } else if (temperatura >= TEMP_LIMITE) {
    Serial.print("⚠ ALERTA: Temperatura elevada — ");
    Serial.print(temperatura, 1);
    Serial.println(" °C");
    ativarAlarme();
  } else {
    desativarAlarme();
  }

  delay(500);
}
