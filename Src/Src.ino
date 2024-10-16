#include "WiFiS3.h"
#include "Request.h"
#include "Secrets.h"
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

char ssid[] = SSID;
char pass[] = PASS;

const uint32_t animation[][4] = {
  { 0x0,
    0x0,
    0x0,
    66 },
  { 0x0,
    0x600600,
    0x0,
    66 },
  { 0x6,
    0x900900,
    0x60000000,
    66 },
  { 0x6009,
    0x1081080,
    0x90060000,
    66 },
  { 0xf010,
    0x81081081,
    0x80f0000,
    66 }
};



ArduinoLEDMatrix matrix;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

String inputText = "";
unsigned long timer[5] = { 0, 0, 0, 0, 0 };

void setup() {
  Serial.begin(9600);
  matrix.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial) {
    ;
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true)
      ;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();
  printWifiStatus();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  unsigned long current = millis();

  if (Serial.available()) {
    inputText = Serial.readString();
  }

  WiFiClient client = server.available();
  if (client) {
    Serial.println("\nnew client");
    playStartAnimation();
    digitalWrite(LED_BUILTIN, HIGH);
    if (client.available()) {
      String data = client.readString();
      Request req(data);
      String path = decodeUriComponent(req.getPath().substring(1));
      Serial.println(path);
      if (req.getMethod() != METHOD_GET) {
        client.println("HTTP/1.1 405 Method Not Allowed");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println("");
        client.println("<!DOCTYPE html> <html lang=\"pt\" translate=\"no\"> <head> <meta content=\"width=device-width,initial-scale=1\" name=\"viewport\"> <meta name=\"author\" content=\"Rui Borges\"> <title>Arduino Uno R4 Wifi</title> <meta name=\"darkreader-lock\"> <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN\" crossorigin=\"anonymous\"> <link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css\" media=\"none\" onload=\"this.media='all'\"> </head> <style> @font-face { font-family: 'Oswald'; font-style: normal; font-weight: 400; src: url(https://fonts.gstatic.com/s/oswald/v53/TK3_WkUHHAIjg75cFRf3bXL8LICs1_FvsUZiZQ.woff2) format('woff2'); unicode-range: U+0000-00FF, U+0131, U+0152-0153, U+02BB-02BC, U+02C6, U+02DA, U+02DC, U+0304, U+0308, U+0329, U+2000-206F, U+2074, U+20AC, U+2122, U+2191, U+2193, U+2212, U+2215, U+FEFF, U+FFFD; font-display: swap; } h1, h2, h3, h4, h5 { font-family: Oswald, Tahoma, sans-serif; } html, body { height: 100%; } h1 { font-size: 72px; font-weight: 400; } body { background-color: #242424; min-width: 300px; } </style> <body> <header class=\"text-white container\"> <div class=\"row text-center pt-4 pb-2\"> <h1 class=\"pt-5\">Error</h1> </div> <div class=\"row text-center pb-2 fw-normal h5\"> <div>{ Http error code: 405 Method Not Allowed }</div> </div> </header> <script src=\" https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js\" async integrity=\"sha384-C6RzsynM9kWDrMNeT87bh95OGNyZPhcTNXj1NW7RuBCsyN/o0jlpcV8Qyq46cDfL\" crossorigin=\"anonymous\"></script> <script src=\"https://code.jquery.com/jquery-3.6.0.min.js\"></script> </body> </html>");
      } else if (path.length() > 64) {
        client.println("HTTP/1.1 413 Payload Too Large");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.println("<!DOCTYPE html> <html lang=\"pt\" translate=\"no\"> <head> <meta content=\"width=device-width,initial-scale=1\" name=\"viewport\"> <meta name=\"author\" content=\"Rui Borges\"> <title>Arduino Uno R4 Wifi</title> <meta name=\"darkreader-lock\"> <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN\" crossorigin=\"anonymous\"> <link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css\" media=\"none\" onload=\"this.media='all'\"> </head> <style> @font-face { font-family: 'Oswald'; font-style: normal; font-weight: 400; src: url(https://fonts.gstatic.com/s/oswald/v53/TK3_WkUHHAIjg75cFRf3bXL8LICs1_FvsUZiZQ.woff2) format('woff2'); unicode-range: U+0000-00FF, U+0131, U+0152-0153, U+02BB-02BC, U+02C6, U+02DA, U+02DC, U+0304, U+0308, U+0329, U+2000-206F, U+2074, U+20AC, U+2122, U+2191, U+2193, U+2212, U+2215, U+FEFF, U+FFFD; font-display: swap; } h1, h2, h3, h4, h5 { font-family: Oswald, Tahoma, sans-serif; } html, body { height: 100%; } h1 { font-size: 72px; font-weight: 400; } body { background-color: #242424; min-width: 300px; } </style> <body> <header class=\"text-white container\"> <div class=\"row text-center pt-4 pb-2\"> <h1 class=\"pt-5\">Text failed to send to the Arduino</h1> </div> <div class=\"row text-center pb-2 fw-normal h5\"> <div>{ Error: String is too long (max: 64 characters) }</div> </div> </header> <script src=\" https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js\" async integrity=\"sha384-C6RzsynM9kWDrMNeT87bh95OGNyZPhcTNXj1NW7RuBCsyN/o0jlpcV8Qyq46cDfL\" crossorigin=\"anonymous\"></script> <script src=\"https://code.jquery.com/jquery-3.6.0.min.js\"></script> </body> </html>");
      } else {
        if (path == "favicon.ico") {
          client.println("HTTP/1.1 204 No Content");
          client.println("Connection: close");
          client.println();
        } else {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("");
          if (path == "") {
            client.println("<!DOCTYPE html> <html lang=\"pt\" translate=\"no\"> <head> <meta content=\"width=device-width,initial-scale=1\" name=\"viewport\"> <meta name=\"author\" content=\"Rui Borges\"> <title>Arduino Uno R4 Wifi</title> <meta name=\"darkreader-lock\"> <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN\" crossorigin=\"anonymous\"> <link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css\" media=\"none\" onload=\"this.media='all' \"> </head> <style> @font-face { font-family: 'Oswald'; font-style: normal; font-weight: 400; src: url(https://fonts.gstatic.com/s/oswald/v53/TK3_WkUHHAIjg75cFRf3bXL8LICs1_FvsUZiZQ.woff2) format('woff2'); unicode-range: U+0000-00FF, U+0131, U+0152-0153, U+02BB-02BC, U+02C6, U+02DA, U+02DC, U+0304, U+0308, U+0329, U+2000-206F, U+2074, U+20AC, U+2122, U+2191, U+2193, U+2212, U+2215, U+FEFF, U+FFFD; font-display: swap; } h1, h2{ font-family: Oswald, Tahoma, sans-serif; } html, body { height: 100%; } h1 { font-size: 72px; font-weight: 400; } body { background-color: #242424; min-width: 300px; } .card { background-image: radial-gradient(ellipse at center, rgb(255, 255, 255) 0, rgb(235, 235, 235) 100%); box-shadow: 0px 0px 8px black; } .text-justify { text-align: justify; } .text-hyphenated { hyphens: auto; } </style> <body> <header class=\"text-white container\"> <div class=\"row text-center pt-4 pb-2\"> <h1 class=\"pt-5\">Arduino Uno R4 Wifi</h1> </div> <div class=\"row text-center pb-2 fw-normal h5\"> <div>{ WebServer Project }</div> </div> </header> <div class=\"container pb-1\"> <div class=\"card mb-5 mt-5 p-5 rounded-top-5\"> <h2 class=\"pb-4\"><span class=\"pe-3 fas fa-cogs\"></span>About the project</h2> <div class=\"row\"> <p class=\"m-0 text-hyphenated text-justify\">This is a simple project that is built using the Arduino Uno R4 Wifi. It consists of a basic webserver that is serving this page on the Arduino. Any request that is made to this server is parsed to get the path of the request, decodes it and then shows it on the Arduino R4 LED Matrix screen. Down bellow there is a simple tool to display the entered text on the Arduino R4 LED Matrix.</p> </div> </div> <div class=\"card mb-5 mt-5 p-5 rounded-bottom-5\"> <h2 class=\"pb-4\"><span class=\"pe-3 fas fa-wrench\"></span>Tool</h2> <div class=\"row\"> <div class=\"col\"> <input class=\"btn-group py-1 w-100 h-100\" type=\"text\" id=\"pathInput\" placeholder=\"Enter the text here...\" required> </div> <div class=\"col-sm-auto\"> <button class=\"btn btn-success fw-medium mt-2 mt-sm-0\" onclick=\"redirect()\">Send to the Arduino</button> </div> </div> </div> </div> <script src=\" https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js\" async integrity=\"sha384-C6RzsynM9kWDrMNeT87bh95OGNyZPhcTNXj1NW7RuBCsyN/o0jlpcV8Qyq46cDfL\" crossorigin=\"anonymous\"></script> <script src=\"https://code.jquery.com/jquery-3.6.0.min.js\"></script> <script> function redirect() { const path = document.getElementById('pathInput').value; if (path.trim() !== \"\") { window.location.href = `/${encodeURIComponent(path)}`; } } </script> </body> </html>");
          } else {
            inputText = path;
            client.println("<!DOCTYPE html> <html lang=\"pt\" translate=\"no\"> <head> <meta content=\"width=device-width,initial-scale=1\" name=\"viewport\"> <meta name=\"author\" content=\"Rui Borges\"> <title>Arduino Uno R4 Wifi</title> <meta name=\"darkreader-lock\"> <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN\" crossorigin=\"anonymous\"> <link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css\" media=\"none\" onload=\"this.media='all'\"> </head> <style> @font-face { font-family: 'Oswald'; font-style: normal; font-weight: 400; src: url(https://fonts.gstatic.com/s/oswald/v53/TK3_WkUHHAIjg75cFRf3bXL8LICs1_FvsUZiZQ.woff2) format('woff2'); unicode-range: U+0000-00FF, U+0131, U+0152-0153, U+02BB-02BC, U+02C6, U+02DA, U+02DC, U+0304, U+0308, U+0329, U+2000-206F, U+2074, U+20AC, U+2122, U+2191, U+2193, U+2212, U+2215, U+FEFF, U+FFFD; font-display: swap; } h1, h2, h3, h4, h5 { font-family: Oswald, Tahoma, sans-serif; } html, body { height: 100%; } h1 { font-size: 72px; font-weight: 400; } body { background-color: #242424; min-width: 300px; } </style> <body> <header class=\"text-white container\"> <div class=\"row text-center pt-4 pb-2\"> <h1 class=\"pt-5\">Text succesfully sent to the Arduino</h1> </div> <div class=\"row text-center pb-2 fw-normal h5\"> <div>{ Text sent: " + inputText + " }</div> </div> </header> <script src=\" https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js\" async integrity=\"sha384-C6RzsynM9kWDrMNeT87bh95OGNyZPhcTNXj1NW7RuBCsyN/o0jlpcV8Qyq46cDfL\" crossorigin=\"anonymous\"></script> <script src=\"https://code.jquery.com/jquery-3.6.0.min.js\"></script> </body> </html>");
          }
        }
      }
    }
    delay(1);
    client.stop();
    playEndAnimation();
    digitalWrite(LED_BUILTIN, LOW);
  }

  if (current - timer[0] > 200) {
    matrix.beginDraw();

    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(120);

    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(inputText);
    matrix.endText(SCROLL_LEFT);

    matrix.endDraw();
    timer[0] = millis();
  }
}

void playStartAnimation() {
  for (int i = 0; i < 5; i++) {
    matrix.loadFrame(animation[i]);
    delay(90);
  }
}

void playEndAnimation() {
  for (int i = 4; i >= 0; i--) {
    matrix.loadFrame(animation[i]);
    delay(90);
  }
}

String decodeUriComponent(String uri) {
  String decodedStr = "";
  for (size_t i = 0; i < uri.length(); ++i) {
    if (uri[i] == '%') {
      if (i + 2 < uri.length()) {
        String hexStr = uri.substring(i + 1, i + 3);
        char decodedChar = (char)strtol(hexStr.c_str(), NULL, 16);
        decodedStr += decodedChar;
        i += 2;
      } else {
        decodedStr += uri[i];
      }
    } else {
      decodedStr += uri[i];
    }
  }
  return decodedStr;
}


void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
