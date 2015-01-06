#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN); 

unsigned char reading_card[5]; //for reading card
unsigned char kitchen[5] = {114,13,207,204,124}; // kitchen card
unsigned char i;
int room_kitchen = 1;
int room_other = 2;
int room_current = 0;

void setup() 
{
 SPI.begin();
 rfid.init();
}

void loop() 
{
 if (rfid.isCard()) 
    {
        if (rfid.readCardSerial()) 
        {
                /* Reading card */
                for (i = 0; i < 5; i++)
                {     
                  reading_card[i] = rfid.serNum[i];
                }
                //verification
                for (i = 0; i < 5; i++)
                {
                  if (reading_card[i]!=kitchen[i])
                  {
                    break;
                  }
                }
                if (i == 5)
                {
                  room_current = room_kitchen;
                }
                else
                {
                  room_current = room_other;
                }
         } 
    }
    rfid.halt();
}
