int cont = 0;
int botaoPin = 2;
int botao = 0;
int i=0;
int aux = 0;
void setup() {
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);

}

void loop() {
 
  cont++;
  botao = digitalRead(botaoPin);
  if(cont == 1){
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(9,LOW);
  digitalWrite(8,HIGH);
  aux = 0;
  for(i=0;i<10000;i++){
      botao = digitalRead(botaoPin);
      delay(1);
      aux++;
      if(botao == HIGH){
            i = 10000 - (10000-aux)/2;
        }
        
    }  
  }
  
  if(cont == 2){
  digitalWrite(5,LOW);
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  
  delay(5000);
  }
  
  if(cont == 3){
  digitalWrite(7,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(8,LOW);
  i = 0;
  for(i=0;i<8000;i++){
    botao = digitalRead(botaoPin);
    delay(1);
    if(botao == HIGH){
        delay(5000);
      }
    }
  }
  
  if(cont >= 4){
    cont = 0;
    }
}
