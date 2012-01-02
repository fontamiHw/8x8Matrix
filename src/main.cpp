//www.b2cqshop.com

#include <WProgram.h>
#include "net/WifiComunication.h"
#include "DebugPrint.h"



#define MAX_MSG 50

// display array size
#define display_array_size 8
// ascii 8x8 dot font
#define data_null    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} // null char
#define data_ascii_A {0x02,0x0C,0x18,0x68,0x68,0x18,0x0C,0x02} /*"A",0*/
#define data_ascii_B {0x00,0x7E,0x52,0x52,0x52,0x52,0x2C,0x00} /*"B",1*/
//#define data_ascii_C {0x00,0x3C,0x66,0x42,0x42,0x42,0x2C,0x00} /*"C",2*/
#define data_ascii_C {0x00,0x7E,0x42,0x42,0x42,0x42,0x24ccc,0x00} /*"C",2*/
#define data_ascii_D {0x00,0x7E,0x42,0x42,0x42,0x66,0x3C,0x00} /*"D",3*/
#define data_ascii_E {0x00,0x7E,0x52,0x52,0x52,0x52,0x52,0x00} /*"E",4*/
#define data_ascii_F {0x00,0x7E,0x50,0x50,0x50,0x50,0x50,0x00} /*"F",5*/
#define data_ascii_G {0x00,0x3C,0x66,0x42,0x52,0x56,0x1e,0x00} /*"G",6*/
#define data_ascii_H {0x00,0x7E,0x10,0x10,0x10,0x10,0x7E,0x00} /*"H",7*/
#define data_ascii_I {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00} /*"I",8*/
#define data_ascii_J {0x00,0x00,0x06,0x03,0x7E,0x00,0x00,0x00} /*"j",9*/
#define data_ascii_K {0x00,0x7E,0x18,0x18,0x24,0x42,0x00,0x00} /*"K",10*/
#define data_ascii_L {0x00,0x00,0x7E,0x02,0x02,0x02,0x00,0x00} /*"L",11*/
#define data_ascii_M {0x00,0x7E,0x20,0x18,0x18,0x20,0x7E,0x00} /*"M",12*/
#define data_ascii_N {0x00,0x7E,0x20,0x10,0x08,0x04,0x7E,0x00} /*"N",13*/
#define data_ascii_O {0x00,0x3C,0x42,0x42,0x42,0x42,0x3C,0x00} /*"O",14*/
#define data_ascii_P {0x00,0x00,0x7E,0x48,0x48,0x30,0x00,0x00} /*"P",15*/
#define data_ascii_Q {0x00,0x3C,0x42,0x42,0x42,0x46,0x3E,0x01} /*"Q",16*/
#define data_ascii_R {0x00,0x00,0x7E,0x48,0x4C,0x32,0x00,0x00} /*"R",17*/
#define data_ascii_S {0x00,0x30,0x49,0x49,0x49,0x49,0x06,0x00} /*"S",18*/
#define data_ascii_T {0x00,0x40,0x40,0x7E,0x7E,0x40,0x40,0x00} /*"T",19*/
#define data_ascii_U {0x00,0x00,0x7C,0x02,0x02,0x7C,0x00,0x00} /*"U",20*/
#define data_ascii_V {0x00,0x38,0x06,0x01,0x06,0x38,0x00,0x00} /*"V",21*/
#define data_ascii_W {0x00,0x7E,0x04,0x18,0x18,0x04,0x7E,0x00} /*"W",22*/
#define data_ascii_X {0x00,0x42,0x24,0x18,0x18,0x24,0x42,0x00} /*"X",23*/
#define data_ascii_Y {0x00,0x60,0x18,0x06,0x18,0x60,0x00,0x00} /*"Y",24*/
#define data_ascii_Z {0x00,0x42,0x46,0x4A,0x52,0x62,0x42,0x00} /*"Z",25*/


#define MAX_LETTER 27

#define LETTER_TIME 1500

int msgLen;
byte* outStr[MAX_MSG] ;
extern HardwareSerial Serial;
DebugPrint *out;
WifiComunication *in;

// display array
byte data_ascii[][display_array_size] = {
        data_null,
        data_ascii_A,
        data_ascii_B,
        data_ascii_C,
        data_ascii_D,
        data_ascii_E,
        data_ascii_F,
        data_ascii_G,
        data_ascii_H,
        data_ascii_I,
        data_ascii_J,
        data_ascii_K,
        data_ascii_L,
        data_ascii_M,
        data_ascii_N,
        data_ascii_O,
        data_ascii_P,
        data_ascii_Q,
        data_ascii_R,
        data_ascii_S,
        data_ascii_T,
        data_ascii_U,
        data_ascii_V,
        data_ascii_W,
        data_ascii_X,
        data_ascii_Y,
        data_ascii_Z
};

//the pin to control ROW
const int row1 = 38; // the number of the row pin 24
const int row2 = 40; // the number of the row pin 23
const int row3 = 42; // the number of the row pin 22
const int row4 = 44; // the number of the row pin 21
const int row5 = 46; // the number of the row pin 4
const int row6 = 48; // the number of the row pin 3
const int row7 = 50; // the number of the row pin 2
const int row8 = 52; // the number of the row pin 1
//the pin to control COl
const int col1 = 53; // the number of the col pin 20
const int col2 = 51; // the number of the col pin 19
const int col3 = 49; // the number of the col pin 18
const int col4 = 47; // the number of the col pin 17
const int col5 = 45; // the number of the col pin 16
const int col6 = 43; // the number of the col pin 15
const int col7 = 41; // the number of the col pin 14
const int col8 = 39; // the number of the col pin 13


void displayNum(byte rowNum,int colNum)
{
    int j;
    byte temp = rowNum;
    for(j=0;j<=14;j+=2)
    {
        digitalWrite(row1+j, LOW);
        digitalWrite(col8+j, HIGH);
    }

    switch(colNum)
    {
    case 1: digitalWrite(col1, LOW); break;
    case 2: digitalWrite(col2, LOW); break;
    case 3: digitalWrite(col3, LOW); break;
    case 4: digitalWrite(col4, LOW); break;
    case 5: digitalWrite(col5, LOW); break;
    case 6: digitalWrite(col6, LOW); break;
    case 7: digitalWrite(col7, LOW); break;
    case 8: digitalWrite(col8, LOW); break;
    default: break;
    }

    for(j = 1 ;j < 9; j++)
    {
        temp = (0x80)&(temp) ;
        if(temp==0)
        {
            temp = rowNum<<j;
            continue;
        }
        switch(j)
        {
        case 1: digitalWrite(row1, HIGH); break;
        case 2: digitalWrite(row2, HIGH); break;
        case 3: digitalWrite(row3, HIGH); break;
        case 4: digitalWrite(row4, HIGH); break;
        case 5: digitalWrite(row5, HIGH); break;
        case 6: digitalWrite(row6, HIGH); break;
        case 7: digitalWrite(row7, HIGH); break;
        case 8: digitalWrite(row8, HIGH); break;
        default: break;
        }
        temp = rowNum<<j;
    }
}


void createMsg() {
    int tmpMsgLen=0;
    while (in->ready()){
        char input;
//        out->dbgPrint("letto = ");
        input = in->read();

        if (input == ' ')
            outStr[tmpMsgLen++]= data_ascii[0];

        if ((input>='A') && (input<='Z')){
            outStr[tmpMsgLen++]= data_ascii[input-'A'+1];
//            out->dbgPrintln((input-'A'+1));
        }
        if ((input>='a') && (input<='z')) {
            outStr[tmpMsgLen++]= data_ascii[input-'a'+1];
//            out->dbgPrintln((input-'a'+1));
        }
    }
    if (tmpMsgLen>0) {
        for (int var = tmpMsgLen; var < MAX_MSG; var++) {
            outStr[var] = data_ascii[0];
        }
        msgLen = tmpMsgLen;
    }
}



void setup(){
    int baud = 115200;
    out = new DebugPrint(baud);
    in = new WifiComunication(baud);
    out->setOn(true);

    for(int j=0;j<=14;j+=2)
    {
        pinMode(row1+j, OUTPUT);
        pinMode(col8+j, OUTPUT);
    }

    for(int j=0;j<=14;j+=2)
    {
        digitalWrite(row1+j, LOW);
    }

    for (int i = 3; i < MAX_MSG; i++) {
        outStr[i] =  data_ascii[0];
    }
//    outStr[0] =  data_ascii['A'-'A'+1];
//    outStr[1] =  data_ascii['U'-'A'+1];
//    outStr[2] =  data_ascii['G'-'A'+1];
//    outStr[3] =  data_ascii['U'-'A'+1];
//    outStr[4] =  data_ascii['R'-'A'+1];
//    outStr[5] =  data_ascii['I'-'A'+1];
//    msgLen=6;

    outStr[0] =  data_ascii['B'-'A'+1];
    outStr[1] =  data_ascii['U'-'A'+1];
    outStr[2] =  data_ascii['O'-'A'+1];
    outStr[3] =  data_ascii['N'-'A'+1];
    outStr[4] =  data_ascii[0];
    outStr[5] =  data_ascii[0];
    outStr[6] =  data_ascii['N'-'A'+1];
    outStr[7] =  data_ascii['A'-'A'+1];
    outStr[8] =  data_ascii['T'-'A'+1];
    outStr[9] =  data_ascii['A'-'A'+1];
    outStr[10] =  data_ascii['L'-'A'+1];
    outStr[11] =  data_ascii['E'-'A'+1];
    msgLen=12;

}

void loop(){

    createMsg();

    int t1;
    int l;
    int letter;


    for(letter=0; letter< MAX_MSG; letter++)
    {
        for(l=0;l< LETTER_TIME;l++)
        {
            for(t1=0;t1<8;t1++)
            {
                displayNum(outStr[letter][t1],(t1+1));
            }
        }

        if (letter == msgLen+4) {
            break;
        }
    }

//    for (int row=0; row<8; row++) {
//        digitalWrite(row1+row, HIGH);
//        for (int col=0; col<8; col++) {
//            digitalWrite(col1+col, LOW);
//        }
//    }
}

int main(void) {

    /* Must call init for arduino to work properly */
    init();
    setup();

    for (;;) {
        loop();
    } // end for
} // end main
