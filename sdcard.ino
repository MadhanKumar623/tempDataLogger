#include "sdcard.h"

void writeToSDcard(char *date, char *time, char *temperature)
{
   strcat(date,"   ");       //appending some delimiter
   strcat(time,"   ");
   myFile = SD.open("test.txt", FILE_WRITE);  // Create/Open file 
   if (myFile) 
   {
       Serial0_transmitString("Writing data to file...\n");
       myFile.print(date);
       myFile.print(time);
       myFile.println(temperature);
       myFile.close(); 
       Serial0_transmitString("writing Done.\n\n");
   }
   else 
   {
       Serial0_transmitString("error opening test.txt\n");
   }
}

void readFromSDcard()
{
   myFile = SD.open("test.txt");
   if (myFile) 
   {
      Serial0_transmitString("READED DATA\n");
      while (myFile.available()) 
      {
        Serial.write(myFile.read());   //printing the file contents to serial monitor
      }
      myFile.close();
   }
   else 
   {
     Serial0_transmitString("error opening test.txt\n");
   }
}
