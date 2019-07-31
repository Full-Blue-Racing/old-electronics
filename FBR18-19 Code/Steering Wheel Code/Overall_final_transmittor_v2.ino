
/**************************
 *         Author         *
 *      omarCartera       *
 *                        *
 *        5/8/2017        *
 *                        *
 * c.omargamal@gmail.com  *
 **************************/

#include <SPI.h>          // SPI is used to talk to the CAN Controller
#include <mcp_can.h>

MCP_CAN CAN(10);          // set SPI Chip Select to pin 10 - this is just the wiring we use, dont change

unsigned char len = 0;    // }
unsigned char buf[8];     //  } These are variables to do with the output of the CAN library functions, buf is a 8 part character in which individual value represents a byte, look at the tutorial website to understand this
unsigned int canID;       // }

int manifold_air_pressure;   // these are the names of all the data that is outputted, see http://www.msextra.com/doc/pdf/Megasquirt_CAN_Broadcast.pdf page 2
int rpm;                     // all the units are linked in the document above
int clt;                     // In the code, unsigned integers are used with the prefix engine (we need these are information arrives in several bits and we can use this data format to modify the data more easily), these are converted to floats before being sent as according to the datasheet they need to be divided so this avoids errors
int tps;                     // This does involve a conversion from unsigned to signed but we dont need to worry about this unless we reach values of 32767 (unlikely)
                             // All of these values need to be divided by a certain value before they can be displayed, this is in the documentation attached and we are going to only do this at the end as it is easier to transmitt integers

char text[32];               // This is used to transmit the data over serial

unsigned int temp;           // This is a temporary variable used to convert the two 8 bit parts of each value to one 16 bit one

void setup()
{
  Serial.begin(9600);   // To communicate with Serial monitor, lower this if stability issues?
  // Tries to initialize the CAN bus reader, if failed --> it will loop here for ever
  START_INIT:
  
      if(CAN_OK == CAN.begin(CAN_500KBPS))      //setting CAN baud rate to 500Kbps - dont change as microsquirt uses this baud rate
      {
          Serial.println("CAN BUS Shield init ok!");
      }
      else
      {
          Serial.println("CAN BUS Shield init fail");
          Serial.println("Init CAN BUS Shield again");
          delay(100);
          goto START_INIT;
      }
}



void loop()
{
    if(CAN_MSGAVAIL == CAN.checkReceive())    // Check if data is coming - if having problems look at previous versions for printing statements
    {
        CAN.readMsgBuf(&len, buf);    // Read data,  len: data length, buf: data buffer
        canID = CAN.getCanId();       // Getting the ID of the incoming message - note ensure that the microquirt is outputting in the simplified dashboard mode which is set in tuner studio

        if (canID == 1512)            // Manifold air pressure, Engine RPM, Coolant temperature and Throttle position datafields, we arent interested in the others
        {                
          // Engine RPM  
          unsigned int engine_rpm = buf[2];
          engine_rpm = engine_rpm << 8;
          temp = buf[3];
          engine_rpm = engine_rpm + temp;         
          rpm = engine_rpm;               

          // Coolant Temperature
          unsigned int engine_clt = buf[4];
          engine_clt = engine_clt << 8;
          temp = buf[5];
          engine_clt = engine_clt + temp;
          clt = engine_clt;
          clt = (clt - 320) * 5 / 90;  

          // Note these sent values are integers and still need to be scaled and have their units converted
        }
  snprintf(text, 32, "<%d,%d>", rpm, clt);
  Serial.println(text);
    }
}
