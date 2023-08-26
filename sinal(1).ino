
//estados
int estado_fome = 0;
int estado_doente = 0;
int vivo = 1;
int fome_doente = 0;

              //estados pelas saidas 11,10,9,8
             
              //estado_fome tem 4 estados
              //estado_doente tem 3 estados

//pinos dos botoes
const int comida = 3;
const int remedio = 2;

//variaveis auxiliares
int botao_comida;
int botao_remedio;
int aux;
int ultima_comida = LOW;
int ultimo_remedio = LOW;

//variaveis pro millis
unsigned long temp = 0;
unsigned long temp2 = 0;
unsigned long morteProxima = 0;
unsigned long lastTimeFome = 0;
unsigned long lastRandom = 0;
unsigned long lastDebounceTimeRemedio = 0;
unsigned long lastDebounceTimeComida = 0;
unsigned long debounceDelay = 50;

void setup() {
  pinMode(comida,INPUT);
  pinMode(remedio,INPUT);

  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);

  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
  digitalWrite(8,LOW);

  Serial.begin(9600);
}

void loop() {

//leitura do botão
  int leitura_comida = digitalRead(comida);
  int leitura_doente = digitalRead(remedio);
////////////////////////////////////// verifica a fome e doença
  
  if(fome_doente == 0){
  	morteProxima = millis();
  }else{
  	// não reseta a contagem
  }
  
/////////////////////////////////// sorteia a doença
  switch(estado_fome){
    case 0:
      if((millis()-lastRandom)>=5000){
          aux = random(10);
          lastRandom = millis();
          if(aux >= 8 && estado_fome != 3){
              estado_doente = 1;
            }
        }
    break;
    
    case 1:
      if((millis()-lastRandom) >= 2000){
          aux = random(10);
          lastRandom = millis();
          if(aux >= 6){
              estado_doente = 1;
              fome_doente = 1;
            }
        }
    break;
  }
    
///////////////////////////// ciclo da fome

if((millis() - lastTimeFome) >= 5000){
      
     
  estado_fome++;
  
  if(estado_fome == 3){
      vivo = 0;
      Serial.println("aqui2");//morreu de fome
  }
  lastTimeFome = millis();
  if(estado_doente == 1 && estado_fome == 1){ //tava doente e ficou com fome, começa a contagem pra morrer
       fome_doente = 1;
        }
  }


  
////////////////////////////////////////////////////////////////////////////remedio debounce
   if(leitura_doente != ultimo_remedio){
      lastDebounceTimeRemedio = millis();
    
    }

    if((millis() - lastDebounceTimeRemedio) > debounceDelay){

          if(leitura_doente != botao_remedio){
              botao_remedio = leitura_doente;
            

          if(botao_remedio == HIGH && vivo == 1){
              estado_doente = 0;  //fica saudavel caso não esteja morto
            	fome_doente = 0;  // não pode mais morrer por causa de fome e doença
            }
          }
      }
  
///////////////////////////////////////////////////////////////////////////comida debounce
    
  
  if(leitura_comida != ultima_comida){
      lastDebounceTimeComida = millis();
    
    }

    if((millis() - lastDebounceTimeComida) > debounceDelay){

          if(leitura_comida != botao_comida){
              botao_comida = leitura_comida;
            


          if(botao_comida == HIGH){
              switch(estado_fome){
              case 0:
                  lastTimeFome = millis();
                break;
              case 1:
                  lastTimeFome = millis();
                  fome_doente = 0;
                  estado_fome = 0;
              break;
              case 2:
                  lastTimeFome = millis();
                  estado_fome = 1;
                  fome_doente = 0;
                  
              break;
              case 3:
                  vivo = 0;
                  
              break;
              }
            }

          }
      }
///////////////////////////////////////////////////////////////////// morte por fome e doença
    if(estado_fome >= 1 && estado_doente == 1){
        if((millis() - morteProxima) >= 5000){
            vivo = 0; //morreu
          }
      }  
  
  
////////////////////////////////////////////////// resto do debounce
  
  
ultima_comida = leitura_comida;
ultimo_remedio = leitura_doente;
  
///////////////////////////////////////////////// define os leds
  if(vivo == 1){
  switch(estado_fome){
    case 0:
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);  //sem fome
    	Serial.print("00");
    break;
    case 1:
      digitalWrite(8,HIGH); //fome
      digitalWrite(9,LOW);
      Serial.print("10");
  break;
    case 2:
      digitalWrite(8,HIGH); //muita fome
      digitalWrite(9,HIGH);
      Serial.print("11");
    break;
  }

    
  switch(estado_doente){
    case 0:
      digitalWrite(10,LOW); //não doente
      Serial.println("00");
    break;
    case 1:
    if((millis() - temp2) >= 500){
      digitalWrite(10,HIGH);
      temp2 = millis();
    }else{
    	digitalWrite(10,LOW);
    }
      Serial.println("10");	// doente
    break;
    
   
  }
    
    
  }else{
    if((millis() - temp) >= 500 ){
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    temp = millis();
    }else{
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    }
    Serial.println("1111");
  }

    
}
