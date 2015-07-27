
#include <Servo.h>

Servo servo1;
int x = 0;
int motorpin1 = 10; 
int motorpin2 = 11;
int randNumber;

#define debug false
//

int dotDelay = 100;

// Morse code for Alphabet 
char* morseATable[] = { 
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",   // A-G
  "....", "..", ".---", "_._", ".-..", "--", "-.",    // H-N
  "---", ".--.", "--.-", ".-.", "...", "-", "..-",    // O-U
  "...-", ".--", "-..-", "-.--", "--.."               // V-Z
};

// Morse code for Numbers
char* morseNTable[] = { 
  "-----", ".----", "..---", "...--", "....-",       // 0-4
  ".....", "-....", "--...", "---..", "----."         // 5-9
};

void setup()
{
  Serial.begin(9600);
  servo1.attach(9);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

}

char line[255];

void loop(){


  int num_chars_read = Serial.readBytesUntil('\n', line, 255); 
  if (num_chars_read > 0) {
    convertAndSend(line);
  }

  
  // only lower case is currently supported
  convertAndSend("occupation is a nightmare");
    morse("--- -.-. -.-. ..- .--. .- - .. --- -. / .. ... / .- / -. .. --. .... - -- .- .-. .");
  // height++;
 delay(5000);
  convertAndSend("nightmares are only dreams");
    morse("-. .. --. .... - -- .- .-. . ... / .- .-. . / --- -. .-.. -.-- / -.. .-. . .- -- ....");   delay(5000);
   //height++;  
  convertAndSend("messages by dreams");
  morse("-- . ... ... .- --. . ... / -... -.-- / -.. .-. . .- -- ...");
   delay(5000);
//   //height++;
  convertAndSend("sleeping is tiring");
   morse("... .-.. . . .--. .. -. --. / .. ... / - .. .-. .. -. --.");
//   
//   //height++;
   delay(60000);
   
}

int motoron (){
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
}

int motoroff (){
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, LOW);
}

void transmit(char dotOrDash) {
  if (dotOrDash == '.') {
    servo1.write(0);
    delay(dotDelay);
    servo1.write(90);
  }
  else {
    motoron();
    delay(dotDelay*3);
    motoroff();
  }

  delay(dotDelay);
}

void morse(char* sequence) {
  int i = 0;
  while (sequence[i] != NULL) {
    transmit(sequence[i]);
    i = i + 1;
  }
  delay(dotDelay * 3);
}

void convertAndSend(String message) {
  for (int pos = 0; pos < message.length(); pos++) { 
    if (debug) {
      Serial.print(message.charAt(pos));
      Serial.print("   ");
    }
    char current_char = message.charAt(pos);
    if ((current_char >= 'a') && (current_char <= 'z'))    // Check for a lower case character
      morse(morseATable[current_char-'a']);
    if ((current_char >= '0') && (current_char <= '9'))     // Check for a number
      morse(morseNTable[current_char-48]);  
    if (current_char == ' ')                                      // Check for a space
      morse("       ");                                              // A space is equal to seven dots
  }
}



