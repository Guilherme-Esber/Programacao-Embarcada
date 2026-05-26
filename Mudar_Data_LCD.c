#include "config.h"
#include "lcd.h"
#include "rtc.h"
#include "serial.h"

void main(void) {

    int i = 0;
    char j[8];
    unsigned char dadoSerial;

    lcdInit();
    serialInit();
    rtcInit();

    for (;;) {

        dadoSerial = serialRead();

        if (dadoSerial != 0) {

            j[i] = dadoSerial;
            i++;

            if (i == 7) {

                switch (j[0]) {

                    
                    case 'D':

                        rtcPutDate(((j[1] - '0') * 10) + (j[2] - '0'));

                        rtcPutMonth(((j[3] - '0') * 10) + (j[4] - '0'));

                        rtcPutYear(((j[5] - '0') * 10) + (j[6] - '0'));

                        break;

                    
                    case 'H':

                        rtcPutHours(((j[1] - '0') * 10) + (j[2] - '0'));

                        rtcPutMinutes(((j[3] - '0') * 10) + (j[4] - '0'));

                        rtcPutSeconds(((j[5] - '0') * 10) + (j[6] - '0'));

                        break;
                }

                i = 0;
            }
        }


        lcdCommand(0x80);

        lcdData(((rtcGetHours() / 10) % 10) + '0');
        lcdData((rtcGetHours() % 10) + '0');

        lcdData(':');

        lcdData(((rtcGetMinutes() / 10) % 10) + '0');
        lcdData((rtcGetMinutes() % 10) + '0');

        lcdData(':');

        lcdData(((rtcGetSeconds() / 10) % 10) + '0');
        lcdData((rtcGetSeconds() % 10) + '0');


        lcdCommand(0xC0);

        lcdData(((rtcGetDate() / 10) % 10) + '0');
        lcdData((rtcGetDate() % 10) + '0');

        lcdData('/');

        lcdData(((rtcGetMonth() / 10) % 10) + '0');
        lcdData((rtcGetMonth() % 10) + '0');

        lcdData('/');

        lcdData(((rtcGetYear() / 10) % 10) + '0');
        lcdData((rtcGetYear() % 10) + '0');
    }
}
