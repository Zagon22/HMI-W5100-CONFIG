/*Inclusión de librerías*/
#include <Ethernet.h>
#include <SPI.h>

/*Configuración del módulo Ethernet W5100.*/
byte mac[]{0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // Dirección MAC (física) del Arduino.
IPAddress server{192,168,2,100}; // Dirección IPV4 de la PC (localhost).
IPAddress ip{192,168,2,20}; // Dirección IPV4 del Arduino.
EthernetClient client; // Declaración del cliente ethernet.
/*Declaración de variables.*/
int ledstatus;
int pinLed = 2, pinButton = 4;

void setup() {
  Ethernet.begin(mac,ip); // Inicialización de la librería Ethernet y las debidas configuraciones de red.
  delay (1000); // Tiempo de delay de 1 segundo;
  pinMode(pinLed, OUTPUT); // Definición del Pin '2' (asociado a la variable "pinLed") como uno de salida.
  pinMode(pinButton, INPUT); // Definición del Pin '4' (asociado a la variable "pinButton") como uno de entrada.
}
void loop() {
  if (digitalRead(pinButton) == HIGH) // Si el botón estuviera presionado:
  {
    digitalWrite(pinLed, HIGH); // Encendería el led.
    ledstatus = 1;
  }
  else // Si fuese incorrecto lo anterior:
  {
    digitalWrite(pinLed, LOW); // Apagaría el led.
    ledstatus = 0;
  }
  if(client.connect(server,80)) // Inicialización de la conexión del cliente con el servidor.
  {
    client.print("GET /Ethernet.php?ledstat="); // Destino de envío de información (en este caso, estado del led).
    client.print(ledstatus); // Variable cuya información es guardada en la base datos.
    client.println("HTTP/1.1");
  }
  else // Si no lograse establecerse la conexión:
  {
    digitalWrite(pinLed, HIGH); // Avisaría prendiendo fijamente el led.
  }
  if (!client.connected()) // En caso de que se desconectara del servidor o no estuviera conectado al mismo:
  {
    /*Patrón de encendido y apagado del led.*/
    digitalWrite(pinLed, HIGH);
    delay(1000);
    digitalWrite(pinLed, LOW);
  }
  client.stop(); // Detiene las funciones del cliente.
}
