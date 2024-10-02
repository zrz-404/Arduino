#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define PIN D5  // DIN pin connected to D4
// NeoMatrix setup for the 8x8 LED matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800);
const char* SSID = “Clown))“;        // Wi-Fi SSID
const char* PASSWORD = “ghoul558";    // Wi-Fi Password
ESP8266WebServer server(80);
// HTML content to be served by the ESP8266
const char index_html[] PROGMEM = R”rawliteral(
<!DOCTYPE html>
<html lang=“en”>
<head>
    <meta charset=“UTF-8">
    <meta name=“viewport” content=“width=device-width, initial-scale=1.0">
    <title>Arduino Project</title>
    <style>
        body {
            padding: 0;
            margin: 0;
            text-align: center;
            background-color: burlywood;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
        }
        .header {
            display: flex;
            align-items: center;
            justify-content: center;
            height: 10%;
        }
        .matrix-buttons {
            display: grid;
            grid-template-columns: repeat(8, 1fr);
            gap: 10px;
        }
        .matrix-buttons button {
            width: 100%;
            padding: 25px;
        }
        .RED {
            background-color: red;
        }
        .controls {
            margin-top: 20px;
        }
        .controls button {
            margin: 5px;
            padding: 10px 20px;
        }
    </style>
</head>
<body>
    <div class=“header”>
        <h1>Arduino Project</h1>
    </div>
    <div class=“matrix-buttons” id=“matrix-buttons”></div>
    <div class=“controls”>
        <button id=“reset-button”>Reset Colors</button>
    </div>
    <script src=“index.js”></script>
</body>
</html>
)rawliteral”;
// JavaScript code to handle the pixel grid and requests
const char index_js[] PROGMEM = R”rawliteral(
  function createButtonGrid() {
    const container = document.getElementById(‘matrix-buttons’);
    for (let index = 0; index < 64; index++) {
        const button = document.createElement(‘button’);
        button.id = `${index}`;
        button.addEventListener(‘click’, () => {
            if (button.classList.contains(‘RED’)) {
                button.classList.remove(‘RED’);
                sendColorUpdate(button.id, ‘OFF’);
            } else {
                button.classList.add(‘RED’);
                sendColorUpdate(button.id, ‘RED’);
            }
        });
        container.appendChild(button);
    }
}
function sendColorUpdate(buttonId, color) {
    const data = new URLSearchParams();
    data.append(‘color’, color);
    data.append(‘id’, buttonId);
    console.log(data);
    fetch(‘/color’, {
        method: ‘POST’,
        body: data
    })
    .then(response => response.text())
    .then(result => console.log(result))
    .catch(error => console.error(‘Error:‘, error));
}
function resetColors() {
    const buttons = document.querySelectorAll(‘.matrix-buttons button’);
    buttons.forEach(button => {
        button.classList.remove(‘RED’);
        sendColorUpdate(button.id, ‘OFF’);
    });
}
document.getElementById(‘reset-button’).addEventListener(‘click’, resetColors);
createButtonGrid();
)rawliteral”;
void setup() {
  Serial.begin(115200);
  // Start Wi-Fi
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(“.”);
  }
  Serial.println(“WiFi connected”);
  // Start the web server
  server.on(“/”, handleRoot);  // Serve the HTML page
  server.on(“/color”, handleColor);  // Handle pixel color updates
  server.on(“/index.js”, handleJS);
  server.begin();
  Serial.println(“HTTP server started”);
  Serial.println(WiFi.localIP());
  // Initialize the NeoMatrix
  matrix.begin();
  matrix.setBrightness(50);  // Adjust brightness
  matrix.fillScreen(0);      // Clear the matrix
  matrix.show();
}
void loop() {
  server.handleClient();  // Handle incoming requests
}
// Serve the HTML page
void handleRoot() {
  server.send_P(200, “text/html”, index_html);
}
// Serve the JavaScript file
void handleJS() {
  server.send_P(200, “application/javascript”, index_js);
}
// Handle color updates from the web page
void handleColor() {
  if (server.hasArg(“id”) && server.hasArg(“color”)) {
    int id = server.arg(“id”).toInt();
    int row = id / 8;  // Calculate row from button id
    int col = id % 8;  // Calculate column from button id
    String color = server.arg(“color”);
    if (color == “RED”) {
      matrix.drawPixel(col, row, matrix.Color(255, 0, 0));  // Turn on the pixel (red color)
    } else {
      matrix.drawPixel(col, row, matrix.Color(0, 0, 0));    // Turn off the pixel
    }
    matrix.show();
    server.send(200, “text/plain”, “OK”);
  } else {
    server.send(400, “text/plain”, “Bad Request”);
  }
}
