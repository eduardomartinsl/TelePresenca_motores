int habilitaMotor1 = 7;
int habilitaMotor2 = 8;

int motor1Pino1 = 9;
int motor1Pino2 = 10;
int motor2Pino1 = 11;
int motor2Pino2 = 12;

int portSpeak(3);

int melodia[] = {660,660,660,510,660,770,380};
int duracaodasnotas[] = {100,100,100,100,100,100,100};

char recebido = 0;

//o input será recebido pelo Tx da placa hc-06;

//definir as variáveis no hc-06; Neste caso estou colocando como exemplo o caracter "a" para fazer o carrinho andar para frente.

/*
Os motores precisam ser habilitados para se movimentarem, seguindo essa tabela: 

|E | IN 1 | IN 2 |   MOTOR      |
|1 |   1  |   0  | RODA LADO 1  |
|1 |   0  |   1  | RODA LADO 2  |
|--|------|------|------------- |
|0 |   1  |   1  |  NÃO RODA    |
|1 |   1  |   1  |  NÃO RODA    |
|1 |   0  |   0  |  NÃO RODA    |

*/

//buzzer funciona com tone(pino, frequencia) e noTone(pino) ~pesquisar

void setup(){
  pinMode(habilitaMotor1, OUTPUT);    //habilitador do motor 1
  pinMode(habilitaMotor2, OUTPUT);    //habilitador do motor 2

  pinMode(motor1Pino1, OUTPUT);     //input 1 
  pinMode(motor1Pino2, OUTPUT);     //input 2
  pinMode(motor2Pino1, OUTPUT);     //input 3
  pinMode(motor2Pino2, OUTPUT);     //input 4

  Serial.begin(9600);
}

void loop(){
  while(Serial.available() > 0){
    recebido = Serial.read();

    if(recebido == 'a'){
      Serial.print("Girar para frente direita \n");
      direitaFrente();
    }
    
    if(recebido == 'b'){
      Serial.print("Girar para direita trás \n");
      direitaTras();
    }
    
    if(recebido == 'c'){
      Serial.print("Girar para esquerda frente \n");
      esquerdaFrente();
    }
    if(recebido == 'd'){
      Serial.print("Girar para esquerda trás \n");
      esquerdaTras();
    }

    if(recebido == 'q'){
      Serial.print("Reproduzindo buzina");
      ativaBuzina();
    }

    if(recebido == 'A' || recebido == 'B'){
      direitaPara();
    }
    if(recebido == 'C' || recebido == 'D'){
      esquerdaPara();
    }
  }
}

void direitaFrente(){
  digitalWrite(habilitaMotor1, HIGH);
  digitalWrite(motor1Pino1, LOW);
  digitalWrite(motor1Pino2, HIGH);
}

void direitaTras(){
  digitalWrite(habilitaMotor1, HIGH);
  digitalWrite(motor1Pino1, HIGH);
  digitalWrite(motor1Pino2, LOW); 
}

void esquerdaFrente(){
  digitalWrite(habilitaMotor2, HIGH);
    digitalWrite(motor2Pino1, HIGH);
  digitalWrite(motor2Pino2, LOW);

}

void esquerdaTras(){
  digitalWrite(habilitaMotor2, HIGH);
  digitalWrite(motor2Pino1, LOW);
  digitalWrite(motor2Pino2, HIGH);
}

void ativaBuzina(){
  for (int nota = 0; nota < 6; nota++) {
    int duracaodanota = duracaodasnotas[nota];
    tone(portSpeak, melodia[nota],duracaodanota);
    int pausadepoisdasnotas[] ={150,300,300,100,300,550};
    delay(pausadepoisdasnotas[nota]);
  }
  noTone(portSpeak);
}

void direitaPara(){
  digitalWrite(habilitaMotor1, LOW);
}

void esquerdaPara(){
  digitalWrite(habilitaMotor2, LOW);
}
