#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

float temperature = 0.0;
float humidity = 0.0;

String example_html = "";
String browserMqtt = "?mqtt";

void handle_OnConnect() {
    server.send(200, "text/html", example_html);
}

// void handle_on_js()
// {

//     server.send(200, "application/javascript; charset=utf-8", browserMqtt);
// }

void handle_NotFound() {
    server.send(404, "text/plain", "Not found");
}

void setup_HTTPServer(){
    Serial.println("setup http server");

    Serial.println("loading resources");
    example_html = readFile("/example.html");


    // load resources
    server.on("/", handle_OnConnect);
    // server.on("/js/browserMqtt.js", handle_on_js);
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
