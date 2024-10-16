# Simple Arduino Web Server

This project demonstrates how to set up an Arduino-based web server that receives data from an input form (e.g., temperature or any user input) and sends it to the Arduino for processing. The server will display a simple web page with an HTML form, allowing users to submit data via a web browser.

## Installation and Usage

Firstly clone the repository to your local machine:

```bash
git clone https://github.com/RuiPedroDev/ArduinoR4SimpleWebsite
```


Open the project with the Arduino IDE.


In the Secrets.h file change the SSID and PASS to the SSID and Password of your network.


Upload the sketch to the Arduino, open the Serial Monitor and check what is the IP address of the Arduino R4.


Using another device, open the browser and type the ip of the Arduino in the address bar. Try sending a string to the Arduino and check if the data is sent to the Arduino and appears on the LED Matrix.

## Notes

- The data is sent using an HTTP GET request so every string sent is interperted as a resource in the HTTP architecture.

- Everytime a new connection is made, the Arduino displays a simple blink animation as a visual input. This animation is stored as a 4 frame HEX string in the code.