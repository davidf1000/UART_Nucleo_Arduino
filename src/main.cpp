#include <mbed.h>
#include <string>

Serial pc(SERIAL_TX, SERIAL_RX);
Serial mega(PC_10, PC_11);
const uint8_t num_limit = 64;
char receivedChars[num_limit];
bool newData = false;
string data;

char getChar()

{
  uint8_t dataGet;
  char convert;
  dataGet = mega.getc();
  convert = dataGet;
  return convert;
}

void recvWithStartEndMarkers() {
    static bool recvInProgress = false;
    static int ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (mega.readable() > 0 && newData == false) {
        rc = getChar();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars [ndx]= rc;
                ndx++;
                if (ndx >= num_limit) {
                    ndx = num_limit - 1;
                }
            }
            else {
                 receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        pc.printf("DATA Received :");
        pc.printf("%s \n",receivedChars);
        newData = false;
    }
}

int main()
{
  pc.printf("Serial receiver");
  wait(2);

  while (1)
  {
    recvWithStartEndMarkers();
    showNewData();

  }
}

