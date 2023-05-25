/*
    Go to thingspeak.com and create an account if you don't have one already.
    After logging in, click on the "New Channel" button to create a new channel for your data. This is where your data will be stored and displayed.
    Fill in the Name, Description, and other fields for your channel as desired, then click the "Save Channel" button.
    Take note of the "Write API Key" located in the "API keys" tab, this is the key you will use to send data to your channel.
    Replace the channelID from tab "Channel Settings" and privateKey with "Read API Keys" from "API Keys" tab.
    Replace the host variable with the thingspeak server hostname "api.thingspeak.com"
    Upload the sketch to your ESP32 board and make sure that the board is connected to the internet. The ESP32 should now send data to your Thingspeak channel at the intervals specified by the loop function.
    Go to the channel view page on thingspeak and check the "Field1" for the new incoming data.
    You can use the data visualization and analysis tools provided by Thingspeak to display and process your data in various ways.
    Please note, that Thingspeak accepts only integer values.

    You can later check the values at https://thingspeak.com/channels/2005329
    Please note that this public channel can be accessed by anyone and it is possible that more people will write their values.
 */

#include <WiFi.h>

const char* ssid = "AIRLab-BigLab";
const char* password = "Airlabrocks2022";

const char* host = "192.168.0.41"; // This should not be changed
const int httpPort = 80; // This should not be changed

// The default example accepts one data filed named "field1"
// For your own server you can ofcourse create more of them.
//int field1 = 0;

int numberOfResults = 3; // Number of results to be read
//int fieldNumber = 1; // Field number which will be read out
WiFiClient client;

void setup()
{
    
    Serial.begin(115200);
    while(!Serial){delay(100);}

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println("******************************************************");
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void readResponse(WiFiClient *client){
  unsigned long timeout = millis();
  while(client->available() == 0){
    if(millis() - timeout > 5000){
      Serial.println(">>> Client Timeout !");
      client->stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while(client->available()) {
    String line = client->readStringUntil('\r');
    Serial.print(line);
  }

  Serial.printf("\nClosing connection\n\n");
}

void loop(){
  
  
  //String footer = String(" HTTP/1.1\r\n") + "Host: " + String(host) + "\r\n" + "Connection: close\r\n\r\n";

  // WRITE --------------------------------------------------------------------------------------------
  if (!client.connect(host, httpPort)) {
    Serial.printf("\n No connection");
    delay(1000);
    return;
  }
  Serial.printf("\n alive");
  // client.print("GET /update?api_key=" + writeApiKey + "&field1=" + field1 + footer);
  // readResponse(&client);

  // // READ --------------------------------------------------------------------------------------------

  // String readRequest = "GET /channels/" + channelID + "/fields/" + fieldNumber + ".json?results=" + numberOfResults + " HTTP/1.1\r\n" +
  //                      "Host: " + host + "\r\n" +
  //                      "Connection: close\r\n\r\n";

  // if (!client.connect(host, httpPort)) {
  //   return;
  // }
  String readRequest = "Hi";
  //client.print(readRequest);
  client.write(255);
  client.write(125);
  client.flush();
  //readResponse(&client);

  // -------------------------------------------------------------------------------------------------

  //++field1;
  delay(1000);
}