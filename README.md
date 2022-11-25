# Prototipo Exoesqueleto para asistencia y estimulación de la movilidad en las manos

Este repositorio contiene los archivos de código y texto que representan este proyecto, realizado por estudiantes de la Universidad de Ibagué como proyecto final de la materia de Electromedicina impartida por la Docente e Ingeniera Luisa Fernanda Gallo



## Hardware

Para correr cualquiera de los archivos de este proyecto lo único que es necesario es una maquina con un sistema operativo compatible con el IDE de Arduino.

![enter image description here](https://cdn.pixabay.com/photo/2017/03/23/12/32/arduino-2168193__480.png)


 - Arduino Uno con su respectivo cable usb.
 - 2 drivers de motorreductor MD08A.
 - Sensor EMG-Grove o alguno con las mismas conexiones.
 - Power Bank 5v
 - 5 Motorreductores (Uno para cada dedo, conseguir motores de la misma relación y que puedan trabajar a un voltaje de 5v).
 - Electrodos desechables
 - Alcohol y algodón (Es importante limpiar bien la zona donde se van a ubicar los electrodos)


## Algoritmo y funcionamiento

Debemos descargar el archivo "Driver_motor_mano.ino"

Debido a que para el control de este prototipo se usó un Arduino UNO, todo el algoritmo fue realizado en el software de Arduino.


```console

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


```

Se definen las variables que indican los puertos en donde van a estar conectados los dispositivos a el Arduino. en este caso, hacemos referencia a:

  

-   el amplificador de instrumentación Sensor EMG- Grove.
    
Podemos encontrar la variable de conexión principal a el pin analógico de Arduino (A0).
También podemos encontrar ciertas variables que van a ser usadas para la realización de un filtrado de señal.
    

  

-   Las conexiones de los drivers MD08A.
    
De estas conexiones se hizo una unión en paralelo de los puertos PWM de cada driver y el puerto de stand-by (STBY) y se separaron cada uno de los canales de salida de motor según cada dedo como se muestra en el código.
    

  

```console

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


```


Se definieron ciertas rutinas en donde el usuario puede configurar el movimiento de cada motor dando un valor de alto a una de sus salidas cambiando la polaridad y de esta forma generar movimiento en ambos sentidos.


```console

void loop() {


  //CODIGO EMG LOOP

  
  Y = (float)analogRead(sensorPin);
  S = (alpha * Y) + ((1 - alpha) * S);
  Serial.print(Y);
  Serial.print(",");
  Serial.println(S);
  delay(10);

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


```
Podemos encontrar con el loop principal de nuestro código con el cual vamos a cumplir la condición de diseño en donde mencionamos que nuestro circuito siempre debe estar en funcionamiento para la toma de datos.

  

En primer lugar, nos encontramos con la implementación de un filtro de [media móvil exponencial (EMA)](https://www.luisllamas.es/arduino-paso-bajo-exponencial/) el cual no es más que un filtro pasa bajos de primer orden cuyo objetivo es atenuar el ruido presente en la señal que entra por el puerto analógico del Arduino que en este caso es nuestro EMG.

Luego de esto, se implementan las condiciones de “if” que van a generar el funcionamiento del actuador en el circuito.

  

![](https://lh4.googleusercontent.com/m4LGzYsR-i4a0R8Oxq0Wa2WR2UHj9FBtz2Qnwharyk_pv2CJEeRcLu-T0Jf75Y17tOkuB-aokAnmBGEslL9BvmbjUkhpcifijs1LWqLZ-YpO2oaVOq2tL3ohjMAA5bcm94TQhVqILfwVdjY4WkA_cfWYofSN2-hO2SdAqZL3AOYdd8jgO-02PzUwq2PDGQ)


La señal de electromiografía para este prototipo puede presentar tres estados.

  

 - Como se puede observar en la primera muestra de la señal es cuando el paciente se encuentra en reposo, el nivel de la señal en este estado depende de cada paciente y la distancia entre los electrodos para este caso se tomó como nivel de estado de reposo aproximadamente 335.
 - La segunda muestra no indica cuando el paciente realizó la primera contracción muscular, teniendo en cuenta que la señal a leer es la que se encuentra filtrada (señal en color rojo) tenemos que el nivel de la primera contracción del paciente es por encima de 360.
 - Por último la tercera muestra nos indica la segunda contracción del paciente en donde será leída la respuesta de la señal por debajo de los valores del estado de reposo, en este caso se asigna un valor por debajo del nivel de reposo, por lo tanto, el nivel de la segunda contracción es de 330.


Con estos valores asignados en los condicionales de if se tiene que cuando el paciente realice la primera contracción será realizada la rutina 1 y cuando el paciente efectúe la segunda contracción será realizada la rutina 0.

  

Como se mencionó anteriormente las rutinas predefinidas pueden ser editadas según la necesidad del paciente.

## Estructura del exoesqueleto


<img src="https://media.giphy.com/media/NbtOHMoDaSoTB9HlSK/giphy.gif" width="750" height="450" />

## Circuito

![](https://lh3.googleusercontent.com/PR2iac9Awa7Zw1z4xWJwD-tOg7qsx3iZW8_-CK3ccp9FCRDFZ6TigjzsKp8HcR79TPmLikAXTnsdxEQbM3DKmUbVucZh-KS_0fSpuzPlxIxnTRGZ22xPNuuem8fv6oGiDE9INu4RCXthr9mxZsHKN3rHGyiWewZvNu2A3kZ0lZ-iD-w52ZAGInoEmNYM7g)**
[Link circuito en ThinkerCad](https://www.tinkercad.com/things/4S0vAhQ713M) (Leer las anotaciones)

**![](https://lh6.googleusercontent.com/pQeZtwMsb656gL4kHLmfoBvvI9JyZwMdpkR8GxBUl6-sbPWzB2jdZhX3-9GIBVT81X7CQ80tfydjNu5OjvcT8ZGUJxE3WUWjzW55tV0wl1cBB1ZCzOR1DcRmsD09CoDeWlIHca9q5OyCsauqE__dPiPtEb2l4ES84FnhpE2rSgqMhK3erfyFciljAahtOA)**

## Ubicacion de los electrodos

Para ubicar los electrodos es necesario limpiar la zona muy bien con alcohol y un algodon.

El primer electrodo estara ubicado en la zona del musculo flexor del pulgar que se encuentra debajo de la muñeca en el mismo lado donde se encuentra ubicado el pulgar.

![](https://lh4.googleusercontent.com/eJxdJZhEUxZd8WoboDAg7kCrU-ybYyRyHYRUBHkqRw7GIVvFTgrK3cm1tsaSeDerj_5o-OyvSjerNyBJo1wKIA4tzqcoC_L16P4y_sVVhHpx5CAsDFR6gjCvVSVwRE0qd-iD7rmSigVjorVc0bmOfYNYvn9msXsuSGHyNUQOMY8qL9_vVomVjXWmNCIsSA)**

El segundo electro lo ubicaremos en la zona de el musculo flexor de los dedos, este se encuentra ubicado en la parte posterior al brazo antes de llegar al codo.

**![](https://lh3.googleusercontent.com/zHrQjnmbSmQ3hQbCO6ygLEwUK3_PGUtEVX8y8WU3ZqodOZLvLz4Viwzv1CEYCNpjdVbGslBKE-_2FIOnhYCwtMXruKtZaF2w9gZwoQRHzf9xfMKXiS8NcZVwhRFSBRm76jWmCZSSbiwiFQ2QWFf-dIJMQKVLYD1xHCC3sPN4Rx6i0xq2azFyfymU0iyuuA)**

El ultimo electrodo va a ser nuestra referencia por los cual lo ubicaremos en la zona del codo en donde va a estar en contacto con la zona donde se encuentra el hueso.

Al final los electrodos deberian estar ubicados de la siguiente manera:

**![](https://lh3.googleusercontent.com/V7_5PJVyiXOhgc0yefxu2NqakRXfSTVlGYsE19VeUpY0VBIqedXWbLTO-Q6i3xXmQpMdVOhILvaN38QN7HsDJ3pm1Ol5hkJuWghZOtflEnSFLoaCqjn_Hc7EBSGR2tpG77YtWZvKZjbkRvx_Vs8jXjouBTZ__DPxW6c5r7pYncVPtV1DfN4VS4Zmqq8ELg)**

[Video Funcionamiento](https://youtu.be/b8-GNEayS-k)

## Autores

 - Kevin Santiago Montaña
 - José Leider Bazurto
 - Steve Daniel Rincón
 - Manuel Alejandro Pita
