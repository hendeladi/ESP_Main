/*
============== Description =============================================================================================
To add functionality, you will to add a "setup function" in the setup part and an "operation function in the loop part.
There will marked sections for where to put your functionality in each part.
There is also a marked section in the global part to put your global variables, but try to use the existing ones.
The function declerations should be right after this section.
========================================================================================================================
*/





/*======================================================================================================================== */

#include <ESP8266WiFi.h>
#include <MyIR.h>

String VERSION = "1.1";

int D0 = 16; 
int D1 = 5; 
int D2 = 4; 
int D3 = 0; 
int D4 = 2; 
int D5 = 14; 
int D6 = 12;
int D7 = 13;
int D8 = 15;   

  
int port = 5005;
WiFiServer server(port);
//const char* ssid = "Hendel_2.4";    //  Your Wi-Fi Name
//const char* password = "1010101010";   // Wi-Fi Password

const char* ssid = "dor";    //  Your Wi-Fi Name
const char* password = "0545346450";   // Wi-Fi Password



/*================== Function decleration section ========================================================================*/





/*---------------------------------------------------*/
/*------------------- WiFi IR AC ---------------------*/
void WiFi_IR_AC_setup(int ledPin){
  pinMode(D2,OUTPUT);
}


/*---------------------------------------------------*/
/*------------------- WiFi IR TV ---------------------*/
void WiFi_IR_TV_setup(int ledPin){
  pinMode(D2,OUTPUT);
  pinMode(D1,OUTPUT);
}
void WiFi_IR_TV_op(String* tokens, int op_len){
  Serial.println("TV");
  if(tokens[2] == "power" or tokens[2] == "on" or tokens[2] == "off" or tokens[2] == "vol+" or tokens[2] == "vol-"){
    Serial.println("D2");
    TV_op(D2, tokens+2, op_len-2);
  }
  else{
    Serial.println("D1");
    TV_op(D1, tokens+2, op_len-2);
  }
}
/*---------------------------------------------------*/


void setup(){
  Serial.begin(115200); 
  delay(10);
  Serial.println("");
  Serial.println("version: " + VERSION);
  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected"); 
  server.begin();  // Starts the Server
  Serial.println("Server started");
  Serial.print("IP Address of network: "); // will show IP address on Serial Monitor
  Serial.println(WiFi.localIP());

//=============== Add a call to your setup function here ====================
  WiFi_IR_AC_setup(D2);
  WiFi_IR_TV_setup(D2);
//===========================================================================
}

 

void loop(){
  String tokens[20]; 
  String readBuff = "";
  readBuff.c_str();
  WiFiClient client = server.available();
  if (!client){
    return;
  }
  Serial.println("client connected");
  while(client.available()<=0){
     delay(1);
   }
    
  if(client.available()>0){
    Serial.println("receiving data"); 
    while(client.available()>0){
      readBuff += (char)client.read();
     }
    int op_len = tokenize(tokens, readBuff); 

    Serial.println(tokens[0]);
    Serial.println(readBuff);
    if(tokens[0]== "op1"){
      //=============== Add a call to your op function here ====================
      //===========================================================================
    }
    else if(tokens[0] == "light"){
      Serial.println("lights");
      
    }
    else if(tokens[0] == "leds"){
      Serial.println("in leds");
      
    }
    else if(tokens[0] == "ir"){
      Serial.println("in IR!");
      if(tokens[1] == "ac"){
        Serial.println("AC");
        AC_op(D2, tokens+2, op_len-2);
      }
      else if(tokens[1] == "tv"){
        WiFi_IR_TV_op(tokens, op_len);
      }
    }
  }
}




int tokenize(String* output_array, String str){
  char charArray[str.length()+1];
  str.toCharArray(charArray, str.length()+1);
  output_array[0] = String(strtok(charArray, " ")); 
  int i=0;
  while (output_array[i] != NULL) {
    i++;
    output_array[i] = String(strtok(NULL, " "));
  }
  return i;
}
