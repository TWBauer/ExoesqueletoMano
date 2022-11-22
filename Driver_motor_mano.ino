// variables EMG

int sensorPin = A0;
float Y = 0.0;
float alpha = 0.1;
float S = Y;

//general

const int pwma = 3; //este pin esta en paralelo del pwma de los dos drivers
const int pwmb = 9; //este pin esta en paralelo del pwmb de los dos drivers
const int stby = 6; //este pin esta en paralelo del pwmb de los dos drivers

//pulgar

const int ain2_d1 = 4;
const int ain1_d1 = 5;

//indice

const int bin1_d1 = 7;
const int bin2_d1 = 8;

//medio

const int ain2_d2 = 10;
const int ain1_d2 = 11;

//anular y meñique 

const int bin1_d2 = 12;
const int bin2_d2 = 13;


//otras variables de apoyo

char leer;
boolean prendido = false;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pwma,OUTPUT);
  pinMode(ain2_d1,OUTPUT);
  pinMode(ain1_d1,OUTPUT);
  pinMode(stby,OUTPUT);
  pinMode(bin1_d1,OUTPUT);
  pinMode(bin2_d1,OUTPUT);
  pinMode(pwmb,OUTPUT);
  

  digitalWrite(stby,1);


  
    
  }


void loop() {


  //CODIGO EMG LOOP

  
  Y = (float)analogRead(sensorPin);
  S = (alpha * Y) + ((1 - alpha) * S);
  Serial.print(Y);
  Serial.print(",");
  Serial.println(S);
  delay(10);

  // put your main code here, to run repeatedly:
  //leer = Serial.read();
  
//    adelante();
//    analogWrite(pwma,100);
//    analogWrite(pwmb,100);
//    delay(5000);

  if ( (S >= 360) && (prendido == false)) {
    
    rutina1();
    analogWrite(pwma,255);
    analogWrite(pwmb,155);
    delay(1500);
    parar();
    analogWrite(pwma,0);
    analogWrite(pwmb,0);
    
    prendido = true;
  }
  else if ( (S <= 330) && (prendido == true)) {
 
    rutina0();
    analogWrite(pwma,255);
    analogWrite(pwmb,155);
    delay(1500);
    parar();
    analogWrite(pwma,0);
    analogWrite(pwmb,0);
    prendido = false;
  }
  
}

// clases para las rutinas
void parar(){
  //pulgar
  digitalWrite(ain2_d1,0);
  digitalWrite(ain1_d1,0);
  //indice
  digitalWrite(bin1_d1,0);
  digitalWrite(bin2_d1,0);
  //medio
  digitalWrite(ain2_d2,0);
  digitalWrite(ain1_d2,0);
  //anular y meñique
  digitalWrite(bin1_d2,0);
  digitalWrite(bin2_d2,0);
}

void rutina0(){

  //pulgar
  digitalWrite(ain2_d1,0);
  digitalWrite(ain1_d1,1);
  //indice
  digitalWrite(bin1_d1,0);
  digitalWrite(bin2_d1,1);
  //medio
  digitalWrite(ain2_d2,0);
  digitalWrite(ain1_d2,1);
  //anular y meñique
  digitalWrite(bin1_d2,0);
  digitalWrite(bin2_d2,1);
}

void rutina1(){

  //pulgar
  digitalWrite(ain2_d1,1);
  digitalWrite(ain1_d1,0);
  //indice
  digitalWrite(bin1_d1,1);
  digitalWrite(bin2_d1,0);
  //medio
  digitalWrite(ain2_d2,1);
  digitalWrite(ain1_d2,0);
  //anular y meñique
  digitalWrite(bin1_d2,1);
  digitalWrite(bin2_d2,0);
}

void rutina2(){

  //pulgar
  digitalWrite(ain2_d1,1);
  digitalWrite(ain1_d1,0);
  //indice
  digitalWrite(bin1_d1,0);
  digitalWrite(bin2_d1,0);
  //medio
  digitalWrite(ain2_d2,0);
  digitalWrite(ain1_d2,0);
  //anular y meñique
  digitalWrite(bin1_d2,0);
  digitalWrite(bin2_d2,0);
}

void rutina3(){

  //pulgar
  digitalWrite(ain2_d1,0);
  digitalWrite(ain1_d1,0);
  //indice
  digitalWrite(bin1_d1,1);
  digitalWrite(bin2_d1,0);
  //medio
  digitalWrite(ain2_d2,1);
  digitalWrite(ain1_d2,0);
  //anular y meñique
  digitalWrite(bin1_d2,0);
  digitalWrite(bin2_d2,0);
}

void rutina4(){

  //pulgar
  digitalWrite(ain2_d1,0);
  digitalWrite(ain1_d1,0);
  //indice
  digitalWrite(bin1_d1,1);
  digitalWrite(bin2_d1,0);
  //medio
  digitalWrite(ain2_d2,0);
  digitalWrite(ain1_d2,0);
  //anular y meñique
  digitalWrite(bin1_d2,0);
  digitalWrite(bin2_d2,0);
}


