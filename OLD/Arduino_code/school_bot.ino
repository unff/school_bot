//include libraries
#include <SoftwareSerial.h>

SoftwareSerial esp8266(3, 2); //RX pin = 3, TX pin = 2

//definition of variables
#define DEBUG true //show messages between ESP8266 and Arduino in serial port
int state = 5; //define initial state of the robot (5 = stand-by)
//define motor pins
const int motor1Pin1 = 5;
const int motor1Pin2 = 6;
const int motor2Pin1 = 9;
const int motor2Pin2 = 10;
//define motor speed
int motorSpeed = 150; //motor speed (PWM)

//*****
//SETUP
//*****
void setup()
{
  //set pin modes
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  
  //start communication
  Serial.begin(9600);
  esp8266.begin(9600);
  
  sendData("AT+RST\r\n", 100, DEBUG); //reset module
  sendData("AT+CWMODE=1\r\n", 150, DEBUG); //set station mode
  sendData("AT+CWJAP=\"XXXXX\",\"YYYYY\"\r\n", 100, DEBUG); //connect wi-fi network (replace XXXXX by your Wi-Fi router SSID and YYYYY by its password
  delay(10000); //wait for connection

  sendData("AT+CIFSR\r\n", 100, DEBUG); //show IP address
  sendData("AT+CIPMUX=1\r\n", 100, DEBUG); //allow multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 100, DEBUG); // start web server on port 80
  
  digitalWrite(LED_BUILTIN, LOW); //Turn off BUILTIN_LED
}

//*********
//MAIN LOOP
//*********
void loop()
{
  
  if (esp8266.available())  //verify incoming data
  {
    Serial.println("DATA.\r\n");
    if (esp8266.find("+IPD,")) //if there is a message
    {
      delay(250); // wait for comms to complete
      int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                            // the ASCII decimal value and 0 (the first decimal number) starts at 48
      Serial.println("IPD.\r\n");
      
      String msg;
      esp8266.find("?"); //look for the message
      msg = esp8266.readStringUntil(' '); //read whole message
      Serial.println("**MSG: "+msg);
      String command = msg.substring(0, 3); //first 3 characters = command
      
        Serial.println("***COMMAND RECEIVED: "+msg);
      
      
      // respond so the connection can close (2 blank lines to signify end of headers)
      String header_status = "HTTP/1.0 200 OK\r\nContent-Length: 0\r\n\r\n";
      String cipSend = "AT+CIPSEND=";
             cipSend += connectionId;
             cipSend += ",";
             cipSend +=header_status.length();
             cipSend +="\r\n";
             
      Serial.println(cipSend+header_status);     
      sendData(cipSend,1,DEBUG);
      sendData(header_status,1,DEBUG);
      
      // close the session.  open sessions that never close are bad and they should feel bad.
      String closeCommand = "AT+CIPCLOSE="; 
      closeCommand+=connectionId; // append connection id
      closeCommand+="\r\n";
     Serial.println("**closer: " + closeCommand);
     sendData(closeCommand,100,DEBUG);
                   
      //move forward
      if(command == "cm1") {
          state = 1;
      }

      //move backward
      if(command == "cm2") {
          state = 2;
      }

      //turn right
      if(command == "cm3") {
          state = 3;
       }
       
       //turn left
       if(command == "cm4") {
          state = 4;
       }

       //do nothing       
       if(command == "cm5") {
          state = 5;
       }

    }
  }
  
  //STATE 1: move forward
  if (state == 1) {
    /*analogWrite(motor1Pin1, motorSpeed);
    digitalWrite(motor1Pin2, LOW);
    analogWrite(motor2Pin1, motorSpeed);
    digitalWrite(motor2Pin2, LOW);
    */
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  //STATE 2: move backward
  if (state == 2) {
    /*digitalWrite(motor1Pin1, LOW);
    analogWrite(motor1Pin2, motorSpeed);
    digitalWrite(motor2Pin1, LOW);
    analogWrite(motor2Pin2, motorSpeed);
    */
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
  //STATE 3: move right
  if (state == 3) {
    /*analogWrite(motor1Pin1, motorSpeed);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    analogWrite(motor2Pin2, motorSpeed);
    */
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  //STATE 4: move left
  if (state == 4) {
    /*digitalWrite(motor1Pin1, LOW);
    analogWrite(motor1Pin2, motorSpeed);
    analogWrite(motor2Pin1, motorSpeed);
    digitalWrite(motor2Pin2, LOW);
    */
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  //STATE 5: do nothing
  if (state == 5) {
    /*digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    */
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
  }
  
}

//*******************
//Auxiliary functions
//*******************
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}