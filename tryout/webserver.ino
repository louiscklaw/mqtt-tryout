#include <ESP8266WebServer.h>

ESP8266WebServer server(80);


float temperature = 0.0;
float humidity = 0.0;

String example_html = "";

String SendHTML(float Temperaturestat, float Humiditystat) {
  example_html = String(Temperaturestat) + "," + String(Humiditystat);
  return example_html;
}

void handle_OnConnect() {

//   Temperature = dht.readTemperature(); // Gets the values of the temperature
//   Humidity = dht.readHumidity(); // Gets the values of the humidity
  server.send(200, "text/html", SendHTML(temperature, humidity));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

void setup_HTTPServer(){
    Serial.println("setup http server");
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}

void handle_webserver(float Temperaturestat, float Humiditystat)
{
    temperature = Temperaturestat;
    humidity = Humiditystat;

    server.handleClient();
}
