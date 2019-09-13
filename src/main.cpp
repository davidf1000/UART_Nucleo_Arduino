#include <mbed.h>
#include <string>

Serial pc(SERIAL_TX, SERIAL_RX);
Serial mega(PC_10, PC_11);
const uint8_t num_limit = 64;
char receivedChars[num_limit];
bool newData = false;
string data;
float SharpIr[2];

  
class nucleo
{
    public : 
        void Sentmega(uint8_t DataSent)
{
    if (mega.writeable() > 0)
    {
        mega.putc(DataSent);
    }
=======
char getChar()

{
    uint8_t dataGet;
    char convert;
    dataGet = mega.getc();
    convert = dataGet;
    return convert;
>>>>>>> e690ac4311a65dbaa8677a1c0dbc35203b5b4e1f
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
=======
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
<<<<<<< HEAD
    char showNewData()
=======
}

char showNewData()
>>>>>>> e690ac4311a65dbaa8677a1c0dbc35203b5b4e1f
{
    recvWithStartEndMarkers();
    if (newData == true)
    {
<<<<<<< HEAD
        pc.printf("DATA Received :");
        pc.printf("%s \n",receivedChars);
=======
        //pc.printf("DATA Received :");
        //pc.printf("%s \n",receivedChars);
>>>>>>> e690ac4311a65dbaa8677a1c0dbc35203b5b4e1f
        newData = false;
        return receivedChars
    }
}
}

<<<<<<< HEAD
    
}








=======
void Sentmega(uint8_t DataSent)
{
    if (mega.writeable() > 0)
    {
        mega.putc(DataSent);
    }
}

>>>>>>> e690ac4311a65dbaa8677a1c0dbc35203b5b4e1f
/*void getdata(char[50] Sensor)
{
    switch (Sensor)
    {
        "ping" : 
        Sentmega(1);
        break;
        "amg" :
        Sentmega(2);
        break;
        "ir"  :
        Sentmega(3);
        break;
        "line" :
        Sentmega(4);
        break;
        "uvtron":
        Sentmega(5);
        break;
        "cmps":
        Sentmega(6);
    }
}*/

int main()
{
    pc.printf("Serial receiver");
    wait(2);
<<<<<<< HEAD
    mega.baud(115200);

    while (1)
    {
        nucleo.showNewData();
=======

    while (1)
    {
        pc.printf("%s", showNewData());
>>>>>>> e690ac4311a65dbaa8677a1c0dbc35203b5b4e1f
        
    }
}
