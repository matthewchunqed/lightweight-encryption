/*
Credit to the Arduino Crypto Library & its creators – learning to write this code 
would not be possible without the library & example code provided by them. 
Coded by Matthew Chun, Amherst College class of 2024.
*/
#include <Crypto.h>
#include <BLAKE2s.h>

#include <string.h>

#define KEY_SIZE 32    //BLAKE2s outputs a hash of KEY_SIZE = 32 bytes.

/* void display_freeram() {
   Serial.print(F("- SRAM left: "));
   extern int __heap_start,*__brkval;
   int v;
  Serial.println(((int)&v - (__brkval == 0  
      ? (int)&__heap_start : (int) __brkval)));
 } */

//for SRAM tests. to do, make sure to uncomment the display_freeram() lines in enc & dec methods.
//to test SRAM on example code, copy/paste above methods and call display_freeram() throughout code.

static uint8_t secretKey[KEY_SIZE] =  //Current SK. For this code, we're using 32-bit with the BLAKE2s 32-bit hash.
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    //secret key. keyspace = 2^216
    0x00, 0x00, 0x00, 0x00, 0x00
    //counter. Max = 2^40.
    };

static uint8_t ctrD[5] = {};

static uint8_t message[64] = {
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,     //message
  
  0x37,     //length of message
  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //integrity check                                                //x
};


BLAKE2s blake2s;
int count;

void increm(uint8_t x, uint8_t target[]){
  if(target[x] < 255){
   target[x] = target[x] + 1;
   return;
  }
  target[x] = 0;
  increm(x-1, target);
  return;
}

void encrypt(uint8_t toSend[]){

  uint8_t curr[KEY_SIZE] = {};
  increm(31, secretKey);
  //increment ctr
  for(int i = 0; i < 32; ++i){
      curr[i] = secretKey[i];
    }

 /*  for(count = 0; count < 32; ++count){
    Serial.print((secretKey)[count]); Serial.print(" ");
    }
    Serial.println(); */
  //for seeing how the encrypt function changes the secretKey.    

     (&blake2s)->reset();
     (&blake2s)->update(curr, sizeof(curr));
     (&blake2s)->finalize(curr, sizeof(curr));
    //hash the copy of the secret key

    for(count = 0; count < 32; ++count){
    toSend[count] = (toSend[count])^(curr[count]);
    }
    for(count = 0; count < 32; ++count){
    toSend[count+32] = (toSend[count+32])^(curr[count]);
    }
    //do the bitwise XOR

    
 //   display_freeram();
 // for memory tests.  
      return;
         
}

void decrypt(uint8_t toReceive[]){

  uint8_t curr[KEY_SIZE] = {};
  increm(4, ctrD);
  //increment ctrD
  for(int i = 0; i < 27; ++i){
      curr[i] = secretKey[i];
    }
  for(int i = 0; i < 5; ++i){
      curr[i+27] = ctrD[i];
    }
  


 /*   for(count = 0; count < 32; ++count){
    Serial.print((secretKeyDec)[count]); Serial.print(" ");
    }
    Serial.println(); */
    //for seeing how the encrypt function changes the secretKey.

  
    (&blake2s)->reset();
    (&blake2s)->update(curr, sizeof(curr));
    (&blake2s)->finalize(curr, sizeof(curr));
    //hash the copy of the secret key
      
    for(count = 0; count < 32; ++count){
    toReceive[count] = (toReceive[count])^(curr[count]);        //decryption step. Done with XOR of known key.
  }
  for(count = 0; count < 32; ++count){
    toReceive[count+32] = (toReceive[count+32])^(curr[count]);        //decryption step. Done with XOR of known key.
  }
 // display_freeram();
 // for memory tests
 
  if((memcmp(&(message[56]), &((secretKey)[0]), 1) == 0) && (memcmp(&(message[57]), &((secretKey)[1]), 1) == 0) && 
  (memcmp(&(message[58]), &((secretKey)[2]), 1) == 0) && (memcmp(&(message[59]), &((secretKey)[3]), 1) == 0) && 
  (memcmp(&(message[60]), &((secretKey)[4]), 1) == 0) && (memcmp(&(message[61]), &((secretKey)[5]), 1) == 0) && 
  (memcmp(&(message[62]), &((secretKey)[6]), 1) == 0) && (memcmp(&(message[63]), &((secretKey)[7]), 1) == 0)){       
    //integrity check.

     // Serial.println("Integrity Check Passed.");
        return;       
     
}

    //discard message here.   
      return;
      
}

void setup()
{
    
    Serial.begin(9600);
    //change to 115200 if connected to ESP32.
//    display_freeram();
//    for memory tests.
    Serial.println();
    
    Serial.println("\nPerformance Tests:");

    unsigned long start;
    unsigned long elapsed;

    for(int i = 0; i < 5; ++i){
      ctrD[i] = secretKey[i+27];
    }

    
int i;
int j;


  for(i = 0; i < 40; ++i){
  
 // for testing & viewing encrypted/decrypted messages
    Serial.println(F("\n ENCRYPTED MESSAGE:"));
    
    start = micros();
    encrypt(message);
    elapsed = micros() - start;
    
     for(j = 0; j < 64; ++j ){
              Serial.print(message[j]);
              Serial.print(F(" "));
     } 
     Serial.println(F(""));
     Serial.print(F("Encrypted in ")); Serial.print(elapsed); Serial.println(F("us")); 

     
     Serial.println(F("\n DECRYPTED MESSAGE:"));
     
     start = micros();
     decrypt(message);
     elapsed = micros() - start;

     for(j = 0; j < 64; ++j ){
              Serial.print(message[j]);
              Serial.print(F(" "));
     } 
     Serial.println(F(""));
     Serial.print(F("Decrypted in ")); Serial.print(elapsed); Serial.println(F("us")); 

}

Serial.println(F("\n"));
Serial.print(F("Encryption Speed ... ")); 
    start = micros();
     for (j = 0; j < 500; ++j) {
        encrypt(message);
    }
    elapsed = micros() - start;
     Serial.print(elapsed/(55.0*500.0)); Serial.println(F("us per byte"));
  //55 bytes of message encrypted, 64 bytes total encrypted.

Serial.println(F("\n"));
Serial.print(F("Decryption Speed ... ")); 
     start = micros();
     for (j = 0; j < 500; ++j) {
        decrypt(message);
      }
      elapsed = micros() - start;
     Serial.print(elapsed/(55.0*500.0)); Serial.println(F("us per byte"));
   //55 bytes of message encrypted, 64 bytes total encrypted.

Serial.print(F("Size of Encryption Implementation: "));
    Serial.print(sizeof(blake2s) + sizeof(secretKey) + sizeof(ctrD)
    );
    Serial.println(F(" bytes"));


}

void loop()
{
}
