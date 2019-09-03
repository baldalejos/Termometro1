#include <M5Stack.h>//Incluimos la librería M5stackloshuevos

#include "DHT.h"//Incluimos la librería DHT

#define DHTPIN 2     // Decimos en que pin va la sonda
// Elegimos el tipo de sonda, pon "//"a la que no vayas a usar
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

//La sonda lleva tres pines Vcc, GND, Signal y (NC(no vale para nada))
DHT dht(DHTPIN, DHTTYPE);//A partir de ahora se llama dht, ya no hay que volver a llamar al pin ni al tipo de sonda

void setup() {
  m5.begin();//Inicializamos el M5stack
  M5.Lcd.setTextSize(3);//Tamaño de la letra
  m5.Lcd.println(" LECTURA DE SONDA");//Imprimimos
  M5.setWakeupButton(BUTTON_A_PIN);//Definimos los botones del M5stack
  M5.setWakeupButton(BUTTON_B_PIN);
  M5.setWakeupButton(BUTTON_C_PIN);

  dht.begin();//Inicializamos sonda
}

void loop() {
  if (M5.BtnA.wasPressed()) {//Si pulsamos el boton izquierdo se apaga
    M5.powerOFF();
  }
  M5.update();
  
  //if (M5.BtnB.wasPressed()) {//Si pulsamos el boton central mide T/H y lo imprime
   // M5.Lcd.fillScreen(TFT_BLACK);//pintamos la pantalla de negro
    m5.Lcd.setCursor(0, 10); //elegimos el punto de la pantalla donde aparecera el texto
    M5.Lcd.setTextSize(3);//Otra vez la talla de la letra
    ////M5.Lcd.println("Conectando...");//Le damos emoción
    M5.Lcd.println("");//Linea de relleno

    M5.Lcd.println("");
    //delay(2000);//Una lectura de T/H tardaría 250ms pero estas sondas son lentas
    //M5.Lcd.fillScreen(TFT_BLACK);//volvemos a pintar la pantalla de negro que es como borrar
    float h = dht.readHumidity();//Leemos Temp y Hum
    float t = dht.readTemperature();
    M5.Lcd.setTextSize(3);//Tamaño del texto
    if (isnan(h) || isnan(t)) {//Comprueba que haya leido
      m5.Lcd.setCursor(10,200);
    m5.Lcd.println("Fallo de lectura");//Imprime eso en caso de fallo o avería
    return;//Al poner el return impedimos que siga corriendo el programa hacia abajo.
  }
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextSize(5);//Imprimimos las lecturas
  m5.Lcd.print("Hum: ");
  M5.Lcd.setTextSize(4);
  m5.Lcd.print(h);
  m5.Lcd.print(" %");
  M5.Lcd.setTextSize(5);
  m5.Lcd.print("T: ");
  M5.Lcd.setTextSize(4);
  m5.Lcd.print(t);
  m5.Lcd.print(" *C ");
  M5.update();
  delay(2000);
}

  
