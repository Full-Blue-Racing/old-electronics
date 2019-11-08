
#include <SPI.h>          // SPI is used to talk to the CAN Controller
#include <mcp_can.h>

#define VARIABLES 20

MCP_CAN CAN(10);          // set SPI Chip Select to pin 10

unsigned char len = 0;
unsigned char buf[8];
unsigned int canID;

typedef struct {
    char *label;
    int len;
    char *sign;
    int multiply;
    int divide;
    char *unit;
    int id;
    int group_offset;
    int total_offset;
} data_type;


data_type data[VARIABLES];

void setup() {
    // ***********************************************************************************************************************
    // Set up Data Bank
    // Key => [Parameter, Size, Sign, Multiply, Divide, Unit, Default ID, Offset in Group, Total Offset]
    data[0] = (data_type) {"Manifold Air Pressure", 2, "Y", 1, 10, "kPa", 1512, 0, 0};
    data[1] = (data_type) {"Engine RPM", 2, "N", 1, 1, "RPM", 1512, 2, 2};
    data[2] = (data_type) {"Coolant Temperature", 2, "Y", 1, 10, "deg F", 1512, 4, 4};
    data[3] = (data_type) {"Throttle Position", 2, "Y", 1, 10, "%", 1512, 6, 6};
    data[4] = (data_type) {"Main pulsewidth bank 1", 2, "N", 1, 1000, "ms", 1513, 0, 8};
    data[5] = (data_type) {"Main pulsewidth bank 2", 2, "N", 1, 1000, "ms", 1513, 2, 10};
    data[6] = (data_type) {"Manifold Air Temperature", 2, "Y", 1, 10, "deg F", 1513, 4, 12};
    data[7] = (data_type) {"Final Ignition Spark Advance", 2, "Y", 1, 10, "deg BTDC", 1513, 6, 14};
    data[8] = (data_type) {"Bank 1 AFR Target", 1, "N", 1, 10, "AFR", 1514, 0, 16};
    data[9] = (data_type) {"AFR cyl#1", 1, "N", 1, 10, "AFR", 1514, 1, 17};
    data[10] = (data_type) {"EGO correction cyl#1", 2, "Y", 1, 10, "%", 1514, 2, 18};
    data[11] = (data_type) {"EGT 1", 2, "Y", 1, 10, "deg F", 1514, 4, 20};
    data[12] = (data_type) {"Sequential Pulsewidth for cyl#1", 2, "Y", 1, 1000, "ms", 1514, 6, 22};
    data[13] = (data_type) {"Battery Voltage", 2, "Y", 1, 10, "V", 1515, 0, 24};
    data[14] = (data_type) {"Generic sensor input 1 (gploadc0 on MS2)", 2, "Y", 1, 10, " ", 1515, 2, 26};
    data[15] = (data_type) {"Generic sensor input 2 (gploadc1 on MS2)", 2, "Y", 1, 10, " ", 1515, 4, 28};
    data[16] = (data_type) {"Knock Retard", 1, "N", 1, 10, "deg", 1515, 6, 30};
    data[17] = (data_type) {"Vehicle Speed 1", 2, "N", 1, 10, "ms-1", 1516, 0, 32};
    data[18] = (data_type) {"Traction Control Retard", 2, "Y", 1, 10, "deg", 1516, 2, 34};
    data[19] = (data_type) {"Launch Control Timing", 2, "Y", 1, 10, "deg", 1516, 4, 36};

    // ***********************************************************************************************************************


    // Start Communication
    Serial.begin(115200);   // to communicate with Serial monitor

// Tries to initialize, if failed --> it will loop here for ever
START_INIT:

    if (CAN_OK == CAN.begin(CAN_500KBPS))      // setting CAN baud rate to 500 kbps
    {
        Serial.println("CAN BUS Shield init ok!");
    } else {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}

void loop() {
    // ***********************************************************************************************************************
    if (CAN_MSGAVAIL == CAN.checkReceive())    // check if data is coming
    {
        CAN.readMsgBuf(&len, buf);    // read data, len: data length, buf: data buffer
        canID = CAN.getCanId();       // getting the ID of the incoming message

        for (int i = 0; i < VARIABLES; i++) {
            // Check for which measurements have that id
            if (canID == data[i].id) {
                // Data Manipulation such to get desired measurement
                int index = data[i].group_offset;
                unsigned int value = buf[index];
                if (data[i].len > 1) {
                    value = value << 8;
                    value = value + buf[index + 1];
                }
                int measurement = value * (data[i].multiply) / (data[i].divide);
                Serial.println(String(data[i].label) + ":" + String(measurement) + String(data[i].unit));
            }
        }

        //***********************************************************************************************************************

    }

}





