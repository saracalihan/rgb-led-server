#include <WiFi.h>
#include <string.h>

const char* ssid     = "TTNET_ZyXEL_R3VN";
const char* password = "b615a492a4046";

WiFiServer server(80);

void setupServer()
{
  Serial.begin(115200);
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

int value = 0;
String selected = "null";

String startServerLoop() {
  WiFiClient client = server.available();   // listen for incoming clients
  client.setTimeout(2);
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<a href=\"/color/r\">red</a><br>");
            client.print("<a href=\"/color/g\">green</a><br>");
            client.print("<a href=\"/color/b\">blue</a><br>");
            client.print("<a href=\"/lineer/6\">lineer 6</a> x3s<br>");
            client.print("<a href=\"/fade/6\">fade 6</a> x3sn<br>");
            client.print("<a href=\"/wave/8\">wave 8</a> x3sn<br>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /color/r")) {
          selected = "red";
        }
        if (currentLine.endsWith("GET /color/g")) {
          selected = "green";
        }
        if (currentLine.endsWith("GET /color/b")) {
          selected = "blue";
        }
        if (currentLine.indexOf("GET /wave/") != -1) {
          selected = "wave/" + currentLine.substring(currentLine.indexOf("GET /wave/") + 10, currentLine.indexOf("GET /wave/") + 12);
        }
        if (currentLine.indexOf("GET /lineer/") != -1) {
          selected = "lineer/" + currentLine.substring(currentLine.indexOf("GET /lineer/") + 12, currentLine.indexOf("GET /lineer/") + 14);
        } if (currentLine.indexOf("GET /fade/") != -1) {
          selected = "fade/" + currentLine.substring(currentLine.indexOf("GET /fade/") + 10, currentLine.indexOf("GET /fade/") + 12);
        }
        if (currentLine.indexOf("GET /rgb/") != -1) {
          selected = "rgb/" + currentLine.substring(currentLine.indexOf("GET /rgb/") + 9, currentLine.indexOf("GET /rgb/") + 15);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  return selected;
}
