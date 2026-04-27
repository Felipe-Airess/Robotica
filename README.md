# Robotica
Códigos de projetos de robótica feitos com Arduino.

---

## Projetos

### 🚪 Porta Automática (`porta_automatica/`)

Abre e fecha uma porta automaticamente usando um **sensor ultrassônico HC-SR04** e um **servo motor**.

**Componentes:**
- Arduino Uno (ou compatível)
- Sensor ultrassônico HC-SR04
- Servo motor (ex: SG90)
- LED verde (indicador de porta aberta) + resistor 220 Ω

**Funcionamento:**
- O HC-SR04 mede a distância de objetos à frente da porta a cada 100 ms.
- Se um objeto for detectado a menos de **30 cm**, o servo gira para 90° (porta aberta) e o LED acende.
- Após **3 segundos** sem ninguém próximo, o servo retorna a 0° (porta fechada) e o LED apaga.

**Conexões:**

| Componente | Pino Arduino |
|-----------|-------------|
| HC-SR04 TRIG | 9 |
| HC-SR04 ECHO | 10 |
| Servo (sinal) | 6 |
| LED verde | 13 |

---

### 🔥 Detector de Incêndio (`detector_incendio/`)

Detecta chamas e temperatura elevada usando um **sensor de chama IR** e o sensor de temperatura **LM35**, ativando um buzzer e LED de alarme.

**Componentes:**
- Arduino Uno (ou compatível)
- Módulo sensor de chama (IR)
- Sensor de temperatura LM35
- Buzzer ativo
- LED vermelho (alarme) + LED verde (normal) + resistores 220 Ω

**Funcionamento:**
- Monitora continuamente o sensor de chama (digital) e o LM35 (analógico).
- Dispara o alarme (buzzer + LED vermelho) se:
  - uma chama for detectada pelo sensor IR, **ou**
  - a temperatura ultrapassar **60 °C**.
- Em condições normais, apenas o LED verde fica aceso.

**Conexões:**

| Componente | Pino Arduino |
|-----------|-------------|
| Sensor de chama D0 | 7 |
| LM35 VOUT | A0 |
| Buzzer | 8 |
| LED vermelho | 12 |
| LED verde | 13 |
