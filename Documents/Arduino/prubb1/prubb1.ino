#include <LinkedList.h>

int led_rojo = 13;
int led_verde = 11;
int led_amarillo = 12;
int boton4 = 4;
int boton3 = 3;
int boton2 = 2;
int posicion_max = 3;
LinkedList<int> listaBotones = LinkedList<int>();
int estado_boton4;
int estado_boton3;
int estado_boton2;
int estado_anterior_boton4;
int estado_anterior_boton3;
int estado_anterior_boton2;

void resetear(){
  digitalWrite(led_rojo,0);
  digitalWrite(led_verde,0);
  digitalWrite(led_amarillo,0);
}
/////////////////////////////////////////////////////////////// ACIERTO ////////////////////////////////////////////////////////////////////////
void acierto(){
  digitalWrite(led_rojo,0);
  digitalWrite(led_verde,0);
  digitalWrite(led_amarillo,0);
  delay(70);
  digitalWrite(led_rojo,255);
  digitalWrite(led_verde,255);
  digitalWrite(led_amarillo,255);
    delay(70);
  digitalWrite(led_rojo,0);
  digitalWrite(led_verde,0);
  digitalWrite(led_amarillo,0);
    delay(70);
  digitalWrite(led_rojo,255);
  digitalWrite(led_verde,255);
  digitalWrite(led_amarillo,255);
  delay(70);
  digitalWrite(led_rojo,0);
  digitalWrite(led_verde,0);
  digitalWrite(led_amarillo,0);
  delay(70);
}
//////////////////////////////////////////////////////////// FALLO /////////////////////////////////////////////////////////
void fallo(){
  digitalWrite(led_rojo,0);
  digitalWrite(led_verde,0);
  digitalWrite(led_amarillo,0);
  delay(200);
  digitalWrite(led_rojo,255);
  digitalWrite(led_verde,255);
  digitalWrite(led_amarillo,255);
  delay(3000);
  digitalWrite(led_rojo,0);
  digitalWrite(led_verde,0);
  digitalWrite(led_amarillo,0);
  delay(200);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////  SERIE  ////////////////////////////////////////////////////////////////////////////////////////
void serie(LinkedList<int> lista){
 // LinkedList<int> lista_aux = LinkedList<int>();
  Serial.println("funcion Serie");
  Serial.print("Lista: ");
  for (int i = 0; i < lista.size(); i++){
    Serial.print(lista.get(i));
    Serial.print(" ");
  }  
  int num = 2;
  Serial.println();
  while (num < 10){
    for (int i=0; i <= num; i++ ){
      resetear();
      delay(500);
      digitalWrite(lista.get(i),255);
      Serial.print(lista.get(i));
      Serial.print(" ");
      delay(200);
      resetear();
    }// for
    delay(1000); // esto es para que el usuario pulse los botones
    
    Serial.println();
    Serial.println("Pulse ahora los botones: ");
    int aux = 0;
    while (aux <= num){
      if (((estado_boton2 == HIGH) && (estado_anterior_boton2 == LOW)) || ((estado_boton3 == HIGH) && (estado_anterior_boton3 == LOW)) ||  ((estado_boton4 == HIGH) && (estado_anterior_boton4 == LOW))){
        if (estado_boton2 == HIGH){
          listaBotones.add(boton2);
        }else if (estado_boton4 == HIGH){
          listaBotones.add(boton4);
          }else{
            listaBotones.add(boton3);
        }
        aux++;
        delay(250); // este delay es para que lea ordenadamente las pulsaciones
      }// if grande
      estado_anterior_boton2 = estado_boton2;
      estado_anterior_boton3 = estado_boton3;
      estado_anterior_boton4 = estado_boton4;
      estado_boton2 = digitalRead(boton2);
      estado_boton3 = digitalRead(boton3);
      estado_boton4 = digitalRead(boton4);
    }// while
    Serial.println();
    Serial.print("Lista: ");
    for (int i = 0; i < lista.size(); i++){
      Serial.print(lista.get(i));
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("Lista botones:   ");
    for (int i = 0; i < listaBotones.size(); i++){
      Serial.print(listaBotones.get(i));
      Serial.print(" ");
    }
  
    Serial.println();
    int x = 1;
    for (int i = 0; i <= num; i++){ // comrpobamos y el orden de botones pulsados coincide con el de los leds
      if (((lista.get(i)==11) && (listaBotones.get(i)!=2)) || ((lista.get(i)==12) && (listaBotones.get(i)!=3)) || ((lista.get(i)==13) && (listaBotones.get(i)!=4))){ // si alguno falla x saldrá cero y se reiniciará todo
        x=0;
      }
      if ((x==1) && (i==num)){// si no falla ninguna pulsación todo continua normal
        Serial.println(" acierto ");
        acierto();
        acierto();
        acierto();
        acierto();
      }
      if ((x==0) && (i==num)){
        Serial.println(" fallo ");
        for (int i = listaBotones.size(); i >= 0; i--){// antes de reiniciar llamando a loop, borramos la lista botones
          listaBotones.remove(i);
        }
        fallo();
        loop();
      }
    }// for
    
    num++;
    for (int i = listaBotones.size(); i >= 0; i--){
      listaBotones.remove(i);
    }  
    Serial.print("Final ronda "); 
    Serial.println(num-2);
    delay(1000);
  }// while
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LinkedList<int> generar_lista(){ // genera una lista con el orden en el que se encenderán los leds.
  int num_random = 0;
  randomSeed(analogRead(0));
  LinkedList<int> myList = LinkedList<int>();
  for (int i = 0; i < 12; i++ ){
    num_random = random(11, 14);
    delay(num_random * num_random);
    myList.add(num_random);
  }
  return myList;
  //for (int i = 0; i < 12; i++ ){
  //  Serial.print(myList.get(i));
  //}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(boton4, INPUT);
  pinMode(boton3, INPUT);
  pinMode(boton2, INPUT);

}

void loop() {
 // cada vez que reiniciamos el juego dejamos sin borrar lista, puede ser que en determinado momento agotemos la memoria.
    LinkedList<int> lista = generar_lista();
    serie(lista);
}
