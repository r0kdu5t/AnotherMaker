/*
	YOUTUBE video: Node Red and MQTT will change your life - AnotherMaker

 */
#include <Ethernet.h>
#include <PubSubClient.h>

#define DEVICE "YouTubino"
int request = 0;
char *cstring;
float response = 0.00;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 62, 99);
IPAddress server(192, 168, 62, 65);

void callback(char* topic, byte* payload, unsigned int length) {
	for (int i=0; i<length; i++) {
		payload[length] = '\0';

		cstring = (char *) payload;
	}
	Serial.print("The topic received is...");
	Serial.println(topic);
	Serial.print("The message received is...");
	Serial.println(cstring);

}

EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
	// loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect(DEVICE)) {
			Serial.println("connected");
			// Once connected, publish on announcement...
			// ... and resubscribe
			client.subscribe("response");
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds.");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void setup() {

	// disable SD card if one in the slot
	pinMode(4, OUTPUT);
	digitalWrite(4, HIGH);
	Serial.begin(57600);

	client.setServer(server, 1883);
	client.setCallback(callback);

	Ethernet.begin(mac, ip);
	// Allow the hardware to sort itself out
	delay(1500);
}

void loop() {
	if (!client.connected()) {
		reconnect();
	}
	client.loop();
	float randomNum = random(100, 1000);
	char msg[30];
	char val[10];
	dtostrf(randomNum, 3, 0, val);
	sprintf(msg, "%s", val);
	client.publish("youtube", msg);

	delay(10000);
}
/* ------ EOF ----- */