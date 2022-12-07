/*Inclusión de librerías*/
#include <Ethernet.h>
#include <SPI.h>

/*Configuración del módulo Ethernet W5100.*/
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // Dirección MAC (física) del Arduino.
/*
Formas de referir al dominio (1 - DNS; 2 - IP):
char server[] = "//Ingresar nombre del dominio";
IPAddress server(//Ingresar dirección IPV4 del dominio); 
*/
IPAddress ip{192,168,2,20}; // Dirección IPV4 del Arduino.
EthernetClient client; // Declaración del cliente ethernet.
/*Declaración de variables.*/
float ledstatus;
int pinLed = 2, pinLed1 = 3, pinButton = 4;

void setup() {
  Ethernet.begin(mac,ip); // Inicialización de la librería Ethernet y las debidas configuraciones de red.
  delay(3000);
  pinMode(pinLed, OUTPUT); // Definición del Pin '2' (asociado a la variable "pinLed") como uno de salida.
  pinMode(pinLed1, OUTPUT); // Definición del Pin '3' (asociado a la variable "pinLed1") como uno de salida.
  pinMode(pinButton, INPUT); // Definición del Pin '4' (asociado a la variable "pinButton") como uno de entrada.
}
void loop() {
  Serial.begin(9600);
  if(client.connect(server, 80)) // Inicialización de la conexión del cliente con el servidor.
  {
    Serial.println("Conectado");
    if (digitalRead(pinButton) == HIGH) // Si se estuviera presionando el botón, se procedería:
    {
      digitalWrite(pinLed, HIGH); // Encendiendo el led.
      ledstatus = 3.4; // Asignando el valor flotante '3.4' a la variable "ledstatus".
    }
    else // Si fuese incorrecto lo anterior, se proseguiría:
    {
      digitalWrite(pinLed, LOW); // Apagando el led.
      ledstatus = 0; // Asignando el valor '0' a la variable "ledstatus".
    }
    client.print("GET /index.php?ledstat="); // Petición de tipo 'GET' al servidor (en este caso, localhost).
    client.print(ledstatus); // Variable cuya información es enviada al documento "Ethernet.php", del que se registra en la base de datos.
    client.println("HTTP/1.1");
  }
  else // Si no lograse establecerse la conexión, se procedería:
  {
    digitalWrite(pinLed1, HIGH); // Prendiendo fijamente el led.
  }
  if (!client.connected()) // En caso de que el cliente se desconectara del servidor o, en su defecto, no se pudiera conectar al mismo, se proseguiría:
  {
    /*Inicializando un patrón de encendido y apagado del led.*/
    digitalWrite(pinLed1, HIGH);
    delay(1000);
    digitalWrite(pinLed1, LOW);
  }
  client.stop(); // Detiene las funciones del cliente.
}
