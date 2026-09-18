// PONTE H "A" 
int motorA_IN1 = 31;
int motorA_IN2 = 33;
int motorA_IN3 = 35;
int motorA_IN4 = 37;

// PONTE H "B" 
int motorB_IN1 = 47;
int motorB_IN2 = 49;
int motorB_IN3 = 51;
int motorB_IN4 = 53;

int motorA_ENA = 10;
int motorA_ENB = 9;

int motorB_ENA = 3;
int motorB_ENB = 2;

// --- PINOS DO SENSOR HC-SR04 ---
#define TRIG_PIN 22
#define ECHO_PIN 24

struct Movimentos {
  private:
    void motorA_Dianteiro_andarFrente(){
      digitalWrite(motorA_IN1, HIGH);
      digitalWrite(motorA_IN2, LOW);
    }

    void motorA_Dianteiro_andarTras(){
      digitalWrite(motorA_IN1, LOW);
      digitalWrite(motorA_IN2, HIGH);
    }

    void motorA_Traseiro_andarFrente(){
      digitalWrite(motorA_IN3, LOW);
      digitalWrite(motorA_IN4, HIGH);
    }

    void motorA_Traseiro_andarTras(){
      digitalWrite(motorA_IN3, HIGH);
      digitalWrite(motorA_IN4, LOW);
    }

    void motorB_Dianteiro_andarFrente() {
      digitalWrite(motorB_IN3, LOW);
      digitalWrite(motorB_IN4, HIGH);
    }

    void motorB_Dianteiro_andarTras() {
      digitalWrite(motorB_IN3, HIGH);
      digitalWrite(motorB_IN4, LOW);
    }

    void motorB_Traseiro_andarFrente() {
      digitalWrite(motorB_IN1, LOW);
      digitalWrite(motorB_IN2, HIGH);    
    }

    void motorB_Traseiro_andarTras() {
      digitalWrite(motorB_IN1, HIGH);
      digitalWrite(motorB_IN2, LOW);
    }

    void velocidadeMax() {
      analogWrite(motorA_ENA, 255); // MOTOR A DIANTEIRO
      analogWrite(motorA_ENB, 235); // MOTOR A TRASEIRO
      analogWrite(motorB_ENA, 245); // MOTOR B TRASEIRO
      analogWrite(motorB_ENB, 245); // MOTOR B DIANTEIRO
    }

    void desligar() {
      // PAR DIANTEIRO
      digitalWrite(motorA_IN1, LOW);
      digitalWrite(motorA_IN2, LOW);
      digitalWrite(motorB_IN3, LOW);
      digitalWrite(motorB_IN4, LOW);

      // PAR TRASEIRO
      digitalWrite(motorA_IN3, LOW);
      digitalWrite(motorA_IN4, LOW);
      digitalWrite(motorB_IN1, LOW);
      digitalWrite(motorB_IN2, LOW);
    }

  public:
    void andarFrente(int timer) {
      this->motorA_Dianteiro_andarFrente();
      this->motorB_Dianteiro_andarFrente();
      this->motorA_Traseiro_andarFrente();
      this->motorB_Traseiro_andarFrente();
      this->velocidadeMax();
      delay(timer);
      this->desligar();
    }

    void andarTras(int timer) {
      this->motorA_Dianteiro_andarTras();
      this->motorB_Dianteiro_andarTras();
      this->motorA_Traseiro_andarTras();
      this->motorB_Traseiro_andarTras();
      this->velocidadeMax();
      delay(timer);
      this->desligar();
    }

    void girarDireitaFrente(int timer) {
      this->motorB_Dianteiro_andarFrente();
      this->motorB_Traseiro_andarFrente();
      this->velocidadeMax();
      delay(timer);
      this->desligar();
    }

    void girarEsquerdaFrente(int timer) {
      this->motorA_Dianteiro_andarFrente();
      this->motorA_Traseiro_andarFrente();
      this->velocidadeMax();
      delay(timer);
      this->desligar();
    }

    void giroPerfeitoHorario(int timer) {
      this->motorB_Dianteiro_andarFrente();
      this->motorB_Traseiro_andarFrente();
      this->motorA_Dianteiro_andarTras();
      this->motorA_Traseiro_andarTras();
      this->velocidadeMax();
      delay(timer);
      this->desligar();
    }

    void moverFrenteContinuo() {
      this->motorA_Dianteiro_andarFrente();
      this->motorB_Dianteiro_andarFrente();
      this->motorA_Traseiro_andarFrente();
      this->motorB_Traseiro_andarFrente();
      this->velocidadeMax();
    }

    void pararRobo() {
      this->desligar();
    }
};

Movimentos jarvis;

const long tempoMovimento = 1000; // em miliseg
const long tempoGiro = 4000;
int estado = 0;

void setup() {
  // Configurando pinos das Ponte H "A" e "B" como saída
  pinMode(motorA_IN1, OUTPUT);
  pinMode(motorA_IN2, OUTPUT);
  pinMode(motorA_IN3, OUTPUT);
  pinMode(motorA_IN4, OUTPUT);

  pinMode(motorB_IN1, OUTPUT);
  pinMode(motorB_IN2, OUTPUT);
  pinMode(motorB_IN3, OUTPUT);
  pinMode(motorB_IN4, OUTPUT);

  // ENABLES MOTOR A e B
  pinMode(motorA_ENA, OUTPUT);
  pinMode(motorA_ENB, OUTPUT);
  pinMode(motorB_ENA, OUTPUT);
  pinMode(motorB_ENB, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.begin(9600); 
}

void sequenciaMovimentos() {
  jarvis.andarFrente(tempoMovimento);
  jarvis.andarTras(tempoMovimento);
  jarvis.girarDireitaFrente(tempoMovimento);
  jarvis.girarEsquerdaFrente(tempoMovimento);
  jarvis.giroPerfeitoHorario(tempoGiro);
}

// Função para ler a distância em centímetros
long medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  long distancia = duracao * 0.034 / 2; // distância em cm
  return distancia;
}

void loop() {
  if (estado == 0) {
    sequenciaMovimentos();
  } else {
  long distancia = medirDistancia();
    // se encontrar algo a 30cm ou menos para e muda o comportamento
    if (distancia > 0 && distancia <= 30) {
      jarvis.pararRobo();
      delay(300); 
      
      // Rotina de desvio
      jarvis.andarTras(800); 
      jarvis.giroPerfeitoHorario(700);
    } 
    else {
      jarvis.moverFrenteContinuo();
    }
  }

  estado++;

}