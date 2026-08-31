/**
 * @file esp32_4ch_relay_web.ino
 * @brief Professional Web & Serial Controller for ESP32 4-Channel Relay Board
 * @author Phan Huynh Van Do
 * 
 * Hardware Relay Mapping:
 * - Relay 1: GPIO 21
 * - Relay 2: GPIO 19
 * - Relay 3: GPIO 18
 * - Relay 4: GPIO 5
 */

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// ==========================================
// CONFIGURATION
// ==========================================
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
const char* HOSTNAME  = "esp32-relay";

// Pin Definitions
const uint8_t RELAY_PINS[4] = {21, 19, 18, 5};
bool relayStates[4] = {false, false, false, false};

WebServer server(80);

// ==========================================
// HTML / CSS WEB INTERFACE
// ==========================================
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 4-Channel Relay Controller</title>
  <style>
    :root {
      --bg: #0f172a;
      --card-bg: #1e293b;
      --accent: #38bdf8;
      --on-color: #22c55e;
      --off-color: #ef4444;
      --text: #f8fafc;
      --text-muted: #94a3b8;
    }
    * { box-sizing: border-box; margin: 0; padding: 0; font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif; }
    body { background: var(--bg); color: var(--text); display: flex; flex-direction: column; align-items: center; min-height: 100vh; padding: 20px; }
    header { text-align: center; margin-bottom: 24px; }
    header h1 { font-size: 1.8rem; color: var(--accent); margin-bottom: 6px; }
    header p { color: var(--text-muted); font-size: 0.95rem; }
    .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(240px, 1fr)); gap: 18px; width: 100%; max-width: 720px; }
    .card { background: var(--card-bg); border-radius: 16px; padding: 20px; box-shadow: 0 10px 25px rgba(0,0,0,0.3); display: flex; flex-direction: column; align-items: center; transition: transform 0.2s, box-shadow 0.2s; border: 1px solid rgba(255,255,255,0.05); }
    .card:hover { transform: translateY(-3px); }
    .card-title { font-size: 1.2rem; font-weight: 600; margin-bottom: 6px; }
    .pin-info { font-size: 0.8rem; color: var(--text-muted); margin-bottom: 16px; }
    .indicator { width: 18px; height: 18px; border-radius: 50%; display: inline-block; margin-bottom: 16px; transition: background-color 0.3s; box-shadow: 0 0 10px rgba(0,0,0,0.5); }
    .btn { width: 100%; padding: 12px; border: none; border-radius: 10px; font-weight: bold; font-size: 1rem; cursor: pointer; color: white; transition: 0.2s; }
    .btn-on { background: var(--on-color); box-shadow: 0 4px 15px rgba(34, 197, 94, 0.4); }
    .btn-off { background: var(--off-color); box-shadow: 0 4px 15px rgba(239, 68, 68, 0.4); }
    .global-actions { margin-top: 24px; display: flex; gap: 14px; width: 100%; max-width: 720px; }
    .global-btn { flex: 1; padding: 14px; border: none; border-radius: 12px; font-size: 1rem; font-weight: 600; cursor: pointer; background: #334155; color: var(--text); transition: 0.2s; }
    .global-btn:hover { background: #475569; }
    footer { margin-top: 36px; font-size: 0.8rem; color: var(--text-muted); text-align: center; }
  </style>
</head>
<body>
  <header>
    <h1>⚡ ESP32 4-Channel Relay</h1>
    <p>Opto-Isolated IoT Power Control System</p>
  </header>

  <div class="grid" id="relays">
    <!-- Rendered via JavaScript -->
  </div>

  <div class="global-actions">
    <button class="global-btn" onclick="setAll(1)">Turn All ON</button>
    <button class="global-btn" onclick="setAll(0)">Turn All OFF</button>
  </div>

  <footer>
    Hardware Design by Phan Huỳnh Văn Đô • Built with ESP32 & KiCad
  </footer>

  <script>
    const pins = ["GPIO 21", "GPIO 19", "GPIO 18", "GPIO 5"];
    async function updateUI() {
      const res = await fetch('/api/status');
      const data = await res.json();
      const container = document.getElementById('relays');
      container.innerHTML = '';
      data.relays.forEach((state, i) => {
        const card = document.createElement('div');
        card.className = 'card';
        card.innerHTML = `
          <div class="card-title">Channel ${i + 1}</div>
          <div class="pin-info">${pins[i]}</div>
          <span class="indicator" style="background: ${state ? '#22c55e' : '#64748b'}; box-shadow: ${state ? '0 0 12px #22c55e' : 'none'};"></span>
          <button class="btn ${state ? 'btn-off' : 'btn-on'}" onclick="toggleRelay(${i + 1})">
            ${state ? 'Turn OFF' : 'Turn ON'}
          </button>
        `;
        container.appendChild(card);
      });
    }

    async function toggleRelay(ch) {
      await fetch(`/api/relay?ch=${ch}&state=toggle`);
      updateUI();
    }

    async function setAll(state) {
      await fetch(`/api/all?state=${state}`);
      updateUI();
    }

    setInterval(updateUI, 2500);
    updateUI();
  </script>
</body>
</html>
)rawliteral";

// ==========================================
// RELAY CONTROL FUNCTIONS
// ==========================================
void setRelay(uint8_t channel, bool state) {
  if (channel < 1 || channel > 4) return;
  relayStates[channel - 1] = state;
  digitalWrite(RELAY_PINS[channel - 1], state ? HIGH : LOW);
  Serial.printf("[RELAY] Channel %d set to %s (GPIO %d)\n", channel, state ? "ON" : "OFF", RELAY_PINS[channel - 1]);
}

void toggleRelay(uint8_t channel) {
  if (channel < 1 || channel > 4) return;
  setRelay(channel, !relayStates[channel - 1]);
}

// ==========================================
// REST API HANDLERS
// ==========================================
void handleRoot() {
  server.send_P(200, "text/html", INDEX_HTML);
}

void handleStatus() {
  String json = "{\"relays\":[";
  for (int i = 0; i < 4; i++) {
    json += relayStates[i] ? "true" : "false";
    if (i < 3) json += ",";
  }
  json += "]}";
  server.send(200, "application/json", json);
}

void handleRelay() {
  if (server.hasArg("ch")) {
    int ch = server.arg("ch").toInt();
    if (server.hasArg("state")) {
      String st = server.arg("state");
      if (st == "toggle") toggleRelay(ch);
      else if (st == "1" || st == "true" || st == "on") setRelay(ch, true);
      else setRelay(ch, false);
    }
  }
  handleStatus();
}

void handleAll() {
  if (server.hasArg("state")) {
    bool st = server.arg("state").toInt() == 1;
    for (int i = 1; i <= 4; i++) setRelay(i, st);
  }
  handleStatus();
}

// ==========================================
// SERIAL COMMAND PROCESSOR
// ==========================================
void processSerialCommand(String cmd) {
  cmd.trim();
  cmd.toUpperCase();
  if (cmd == "STATUS") {
    Serial.println("\n--- RELAY STATUS ---");
    for (int i = 0; i < 4; i++) {
      Serial.printf("Relay %d (GPIO %d): %s\n", i + 1, RELAY_PINS[i], relayStates[i] ? "ON" : "OFF");
    }
  } else if (cmd == "ALL ON") {
    for (int i = 1; i <= 4; i++) setRelay(i, true);
  } else if (cmd == "ALL OFF") {
    for (int i = 1; i <= 4; i++) setRelay(i, false);
  } else if (cmd.startsWith("R") || cmd.startsWith("RELAY")) {
    // E.g. "R1 ON" or "RELAY 2 OFF"
    int ch = cmd.charAt(cmd.indexOf(' ') - 1) - '0';
    if (ch >= 1 && ch <= 4) {
      if (cmd.endsWith("ON")) setRelay(ch, true);
      else if (cmd.endsWith("OFF")) setRelay(ch, false);
      else if (cmd.endsWith("TOGGLE")) toggleRelay(ch);
    }
  }
}

// ==========================================
// SETUP & LOOP
// ==========================================
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n==========================================");
  Serial.println(" ESP32 4-Channel Relay Controller Starting ");
  Serial.println("==========================================");

  // Initialize GPIOs
  for (int i = 0; i < 4; i++) {
    pinMode(RELAY_PINS[i], OUTPUT);
    digitalWrite(RELAY_PINS[i], LOW);
    relayStates[i] = false;
  }

  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WiFi] Connected successfully!");
    Serial.print("[WiFi] IP Address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin(HOSTNAME)) {
      Serial.printf("[mDNS] Responder started: http://%s.local\n", HOSTNAME);
    }
  } else {
    Serial.println("\n[WiFi] Connection failed. Starting Access Point mode...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP32_4CH_RELAY_AP", "12345678");
    Serial.print("[AP] IP Address: ");
    Serial.println(WiFi.softAPIP());
  }

  // Setup WebServer Routes
  server.on("/", handleRoot);
  server.on("/api/status", handleStatus);
  server.on("/api/relay", handleRelay);
  server.on("/api/all", handleAll);
  server.begin();
  Serial.println("[HTTP] Web server started.");
}

void loop() {
  server.handleClient();

  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    processSerialCommand(cmd);
  }
}
