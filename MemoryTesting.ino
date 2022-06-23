#include <Crypto.h>
#include <CryptoLW.h>
#include <EAX.h>
#include <AES.h>
#include <CTR.h>
#include <Speck.h>
#include <SpeckTiny.h>
#include <GCM.h>
#include <XTS.h>
#include <string.h>
#include <BLAKE2s.h>

//comment out everything except the initialization
//for the protocol and its appropriate buffer (if applicable)

/*EAX<AES128> eax;
EAX<Speck> eaxSpeck;
EAX<SpeckTiny> axSpeckTiny;
byte buffer[128]; 

 CTR<AES128> ctraes128;
byte buffer[128]; 

XTSSingleKey<Speck> singlespeck2;
XTSSingleKey<AES128> singleaes128;
byte buffer[64]; 

GCM<AES128> gcmaes128;
GCM<Speck> gcmspeck;
byte buffer[128]; 


 BLAKE2s blake2s;
 uint8_t secretKey[32]; 
 uint8_t ctrD[5]; */



void setup()
{
      Serial.begin(9600);
    Serial.print(F("- SRAM left: "));
   extern int __heap_start,*__brkval;
   int v;
  Serial.println(((int)&v - (__brkval == 0  
      ? (int)&__heap_start : (int) __brkval)));
      

//  Serial.println("State Sizes:");

  
/*  Serial.println(sizeof(eax));
  Serial.println(sizeof(eaxSpeck));
  Serial.println(sizeof(axSpeckTiny)); 
  Serial.println(sizeof(ctraes128)); 
   Serial.println(sizeof(singlespeck2));
  Serial.println(sizeof(singleaes128));
  Serial.println(sizeof(gcmaes128)); 
  Serial.println(sizeof(gcmspeck)); 
  Serial.println(sizeof(blake2s) + sizeof(secretKey) + sizeof(ctrD)); */
  
  //we print blake2s and its seed because we use the seed for 
  //our encryption protocol's initialization.

}

void loop()
{
}
