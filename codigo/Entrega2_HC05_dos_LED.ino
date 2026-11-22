// Entrega 2 de Internet de las cosas: HC-05 simulado y dos LED.
// Adaptado del ejemplo Bluetooth lamp de Mokxi.
// Fuente: https://mokxi.com/projects/bluetooth-lamp
// El modelo no verifica propagacion de radio ni conexion con un telefono real.
// HC-05 TXD -> D2; RXD <- D3; STATE -> D4.
// Verde: D9 -> 220 ohm -> anodo; catodo -> GND.
// Rojo: D10 -> 220 ohm -> anodo; catodo -> GND.
// UART del modulo: 1200 baudios, 8N1. Monitor USB: 115200 baudios.
// Enviar V, v, R, r, A o status con final CR+LF.

const int RX_PIN = 2;
const int TX_PIN = 3;
const int STATE_PIN = 4;
const int LED_VERDE = 9;
const int LED_ROJO = 10;
const unsigned int BIT_US = 833;
char line[24];
unsigned char at = 0;
bool overflow = false;
bool verdeOn = false;
bool rojoOn = false;

int readByte();
void writeByte(unsigned char value);
void send(const char *text);
void handle(const char *text);
bool equals(const char *a, const char *b);

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_ROJO, LOW);
  pinMode(STATE_PIN, INPUT);
  pinMode(RX_PIN, INPUT);
  digitalWrite(TX_PIN, HIGH);
  pinMode(TX_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("HC-05 simulado a 1200 baudios. V/v, R/r, A y status.");
  delay(20);
  send("Listo");
}

void loop() {
  if (digitalRead(RX_PIN) == LOW) {
    int incoming = readByte();
    if (incoming >= 0) {
      if (incoming == '\n' || incoming == '\r') {
        if (overflow) {
          send("Linea demasiado larga");
        } else if (at > 0) {
          line[at] = 0;
          handle(line);
        }
        at = 0;
        overflow = false;
      } else if (at < sizeof(line) - 1) {
        line[at++] = (char)incoming;
      } else {
        overflow = true;
      }
    }
  }
}

int readByte() {
  // Half a bit from the falling edge puts the next sample in the middle of
  // bit 0.
  delayMicroseconds(BIT_US + BIT_US / 2);
  int value = 0;
  for (int bit = 0; bit < 8; bit++) {
    if (digitalRead(RX_PIN) == HIGH) {
      value |= (1 << bit);
    }
    delayMicroseconds(BIT_US);
  }
  // The stop bit must be high. If it is not, the byte was never a byte.
  if (digitalRead(RX_PIN) != HIGH) {
    Serial.println("framing error: is the module's baud the same as ours?");
    return -1;
  }
  return value;
}

void writeByte(unsigned char value) {
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(BIT_US);
  for (int bit = 0; bit < 8; bit++) {
    digitalWrite(TX_PIN, (value & (1 << bit)) ? HIGH : LOW);
    delayMicroseconds(BIT_US);
  }
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(BIT_US);
}

void send(const char *text) {
  if (digitalRead(STATE_PIN) == LOW) {
    Serial.println("nobody is connected; not sending");
    return;
  }
  while (*text) {
    writeByte((unsigned char)*text++);
  }
  writeByte('\n');
}

void handle(const char *text) {
  Serial.print("Recibido: ");
  Serial.println(text);
  if (equals(text, "V")) {
    verdeOn = true;
    digitalWrite(LED_VERDE, HIGH);
    send("Verde ON");
  } else if (equals(text, "v")) {
    verdeOn = false;
    digitalWrite(LED_VERDE, LOW);
    send("Verde OFF");
  } else if (equals(text, "R")) {
    rojoOn = true;
    digitalWrite(LED_ROJO, HIGH);
    send("Rojo ON");
  } else if (equals(text, "r")) {
    rojoOn = false;
    digitalWrite(LED_ROJO, LOW);
    send("Rojo OFF");
  } else if (equals(text, "A")) {
    verdeOn = false;
    rojoOn = false;
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_ROJO, LOW);
    send("Ambos OFF");
  } else if (equals(text, "status")) {
    if (verdeOn && rojoOn) send("Verde ON Rojo ON");
    else if (verdeOn) send("Verde ON Rojo OFF");
    else if (rojoOn) send("Verde OFF Rojo ON");
    else send("Verde OFF Rojo OFF");
  } else {
    send("Comando invalido");
  }
}

bool equals(const char *a, const char *b) {
  while (*a && *b) {
    if (*a++ != *b++) {
      return false;
    }
  }
  return *a == 0 && *b == 0;
}
