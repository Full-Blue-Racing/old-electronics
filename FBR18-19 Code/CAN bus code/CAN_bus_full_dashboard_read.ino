/**************************
 *         Author         *
 *      omarCartera       *
 *                        *
 *        5/8/2017        *
 *                        *
 * c.omargamal@gmail.com  *
 **************************/

#include <SPI.h>          //SPI is used to talk to the CAN Controller
#include <mcp_can.h>

MCP_CAN CAN(10);          //set SPI Chip Select to pin 10 - this is just the wiring we use, dont change

unsigned char len = 0;    // }
unsigned char buf[8];     //  } These are variables to do with the output of the CAN library functions, buf is a 8 part character in which individual value represents a byte, look at the tutorial website to understand this
unsigned int canID;       // }

int manifold_air_pressure;   // these are the names of all the data that is outputted, see http://www.msextra.com/doc/pdf/Megasquirt_CAN_Broadcast.pdf page 2
int rpm;                     // all the units are linked in the document above
int clt;                     // In the code, unsigned integers are used with the prefix engine (we need these are information arrives in several bits and we can use this data format to modify the data more easily), these are converted to floats before being sent as according to the datasheet they need to be divided so this avoids errors
int tps;                     // This does involve a conversion from unsigned to signed but we dont need to worry about this unless we reach values of 32767 (unlikely)
int pw1;                     // All of these values need to be divided by a certain value before they can be displayed, this is in the documentation attached and we are going to only do this at the end as it is easier to transmitt integers
int pw2;
int mat;
int adv_deg;
int afrtgt1;
int AFR1;
int EGOcor1;
int egt1;
int pwseq1;
int batt;
int sensors1;
int sensors2;
int knk_rtd;
int VSS1;
int tc_retard;
int launch_timing;
char temp;                   // This is a temporary variable used to convert the two 8 bit parts of each value to one 16 bit one, not sure why it is a char but I just used the example code from the tutorial 

void setup()
{
  Serial.begin(115200);   //to communicate with Serial monitor
  
//tries to initialize, if failed --> it will loop here for ever
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

        if (canID == 1512)            // Manifold air pressure, Engine RPM, Coolant temperature and Throttle position
        {      
          // Manifold Air Pressure
          unsigned int engine_manifold_air_pressure = buf[0];
          engine_manifold_air_pressure = engine_manifold_air_pressure << 8;
          temp = buf[1];
          engine_manifold_air_pressure = engine_manifold_air_pressure + temp;
          manifold_air_pressure = engine_manifold_air_pressure;
          
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

          // Throttle Position
          unsigned int engine_tps = buf[6];
          engine_tps = engine_tps << 8;
          temp = buf[7];
          engine_tps = engine_tps + temp;
          tps = engine_tps;
        }
        else if (canID == 1513)      // Main pulsewidth bank 1, Main pulsewidth bank 2, Manifold air temperature, Final ignition spark advance     
        {
          // Main Pulsewidth Bank 1
          unsigned int engine_pw1 = buf[0];
          engine_pw1 = engine_pw1 << 8;
          temp = buf[1];
          engine_pw1 = engine_pw1 + temp;
          pw1 = engine_pw1;

          // Main Pulsewidth Bank 2
          unsigned int engine_pw2 = buf[2];
          engine_pw2 = engine_pw2 << 8;
          temp = buf[3];
          engine_pw2 = engine_pw2 + temp;
          pw2 = engine_pw2;    

          // Manifold Air Temperature
          unsigned int engine_mat = buf[4];
          engine_mat = engine_mat << 8;
          temp = buf[5];
          engine_mat = engine_mat + temp;
          mat = engine_mat;

          // Final ignition spark advance
          unsigned int engine_adv_deg = buf[6];
          engine_adv_deg = engine_adv_deg << 8;
          temp = buf[7];
          engine_adv_deg = engine_adv_deg + temp;
          adv_deg = engine_adv_deg;
        }
        else if (canID == 1514)      // Bank 1 AFR target, AFR cyl#1, EGO correction cyl#1, EGT 1, Sequential Pulsewidth for cyl#1      
        {
          // Bank 1 AFR target
          unsigned int engine_afrtgt1 = buf[0];
          afrtgt1 = engine_afrtgt1;

          // AFR cyl#1
          unsigned int engine_AFR1 = buf[1];
          AFR1 = engine_AFR1;

          // EGO correction cyl#1
          unsigned int engine_EGOcor1 = buf[2];
          engine_EGOcor1 = engine_EGOcor1 << 8;
          temp = buf[3];
          engine_EGOcor1 = engine_EGOcor1 + temp;
          EGOcor1 = engine_EGOcor1;

          // EGT 1
          unsigned int engine_egt1 = buf[4];
          engine_egt1 = engine_egt1 << 8;
          temp = buf[5];
          engine_egt1 = engine_egt1 + temp;
          egt1 = engine_egt1;

          // Sequential Pulsewidth for cyl#1
          unsigned int engine_pwseq1 = buf[6];
          engine_pwseq1 = engine_pwseq1 << 8;
          temp = buf[7];
          engine_pwseq1 = engine_pwseq1 + temp;
          pwseq1 = engine_pwseq1;
        }
        else if (canID == 1515)      // Battery voltage, Generic sensor input 1, Generic sensor input 2, Knock retard            
        {
          // Battery Voltage
          unsigned int engine_batt = buf[0];
          engine_batt = engine_batt << 8;
          temp = buf[1];
          engine_batt = engine_batt + temp;
          batt = engine_batt;

          // Generic Sensor Input 1
          unsigned int engine_sensors1 = buf[2];
          engine_sensors1 = engine_sensors1 << 8;
          temp = buf[3];
          engine_sensors1 = engine_sensors1 + temp;
          sensors1 = engine_sensors1;

          // Generic Sensor Input 2
          unsigned int engine_sensors2 = buf[4];
          engine_sensors2 = engine_sensors2 << 8;
          temp = buf[5];
          engine_sensors2 = engine_sensors2 + temp;
          sensors2 = engine_sensors2;

          // Knock Retard
          unsigned int engine_knk_rtd = buf[6];
          engine_knk_rtd = engine_knk_rtd << 8;
          temp = buf[7];
          engine_knk_rtd = engine_knk_rtd + temp;
          knk_rtd = engine_knk_rtd;
        }
        else if (canID == 1516)      // Vehicle Speed 1, Traction control retard, Launch control timing, final two bytes are not used            
        {
          // Vehicle Speed 1
          unsigned int engine_VSS1 = buf[0];
          engine_VSS1 = engine_VSS1 << 8;
          temp = buf[1];
          engine_VSS1 = engine_VSS1 + temp;
          VSS1 = engine_VSS1;

          // Traction Control Retard
          unsigned int engine_tc_retard = buf[2];
          engine_tc_retard = engine_tc_retard << 8;
          temp = buf[3];
          engine_tc_retard = engine_tc_retard + temp;
          tc_retard = engine_tc_retard;

          // Launch Control Timing
          unsigned int engine_launch_timing = buf[4];
          engine_launch_timing = engine_launch_timing << 8;
          temp = buf[5];
          engine_launch_timing = engine_launch_timing + temp;
          launch_timing = engine_launch_timing;
        }
        else
        {
          Serial.println("Can ID does not match any of the datasheet ones");
        }
    }
}
