#include <mbed.h>
#include <string>

Serial pc(SERIAL_TX, SERIAL_RX);
Serial mega(PA_9, PA_10);
const uint8_t num_limit = 64;
char receivedChars[num_limit];
bool newData = false;
string data;
float SharpIr[2];
  
class UART
{
    public : 
        void Sentmega(uint8_t DataSent)
{
    if (mega.writeable() > 0)
    {
        mega.putc(DataSent);
    }
}
        char getChar()

{
    uint8_t dataGet;
    char convert;
    dataGet = mega.getc();
    convert = dataGet;
    return convert;
}
    void recvWithStartEndMarkers()
{
    static bool recvInProgress = false;
    static int ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (mega.readable() > 0 && newData == false)
    {
        rc = getChar();

        if (recvInProgress == true)
        {
            if (rc != endMarker)
            {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= num_limit)
                {
                    ndx = num_limit - 1;
                }
            }
            else
            {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker)
        {
            recvInProgress = true;
        }
    }
}
    void showNewData()
{   
    static int besar;
    recvWithStartEndMarkers();
    if (newData == true)
    {
        pc.printf("DATA Received :");
        pc.printf("%s \n",receivedChars);
        newData = false;
        for (int i=0;i<strlen(receivedChars);i++)
        {
            pc.printf("%d ", ConverttoInt(receivedChars[i]));
        }

    }
}
    int ChartoInteger (char Charinput) {
        static int Inttemp ;
      Inttemp = Charinput ;
        return Inttemp;
    }
    int ConverttoInt (char Charinput)
    {
        static int Output;
        Output= ChartoInteger(Charinput)-48;
        return Output;
    }

    
}

;
int main()
{
    pc.printf("Serial receiver");
    wait(2);
    mega.baud(115200);
    UART nucleo;
    while (1)
    {
        nucleo.showNewData();

        
    }
}
