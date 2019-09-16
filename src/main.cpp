#include <mbed.h>
#include <string>
#include <math.h>

Serial pc(SERIAL_TX, SERIAL_RX);
Serial mega(PA_9, PA_10);
const uint8_t num_limit = 64;
char receivedChars[num_limit];
char dataClean[num_limit];
float floatTemp = 0;
int boolTemp;
bool newData = false;
string data;
float SharpIr[2];

class UART
{
public:
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
        recvWithStartEndMarkers();
        
        if (newData == true)
        {
            
            pc.printf("DATA Received :");
            pc.printf("%s \n", receivedChars);
            cleanData();
            pc.printf("cleandata : %s \n", dataClean);
            newData = false;
            /*for (int i = 0; i < strlen(receivedChars); i++)
            {
                pc.printf("%d ", ConverttoInt(receivedChars[i]));
            }*/
            convertdataFix();
            //pc.printf("Cek float: %.4f \n", floatTemp);
            floatTemp = 0;
        }
    }
    int ChartoInteger(char Charinput)
    {
        static int Inttemp;
        Inttemp = Charinput;
        return Inttemp;
    }
    int ConverttoInt(char Charinput)
    {
        static int Output;
        Output = ChartoInteger(Charinput) - 48;
        return Output;
    }
        void cleanData()
    {
         int i=0;
         int j=0;
        while(i<strlen(receivedChars))
        {
            if(receivedChars[i]=='.')
            {
                i++;
            }
            dataClean[j]=receivedChars[i];
            i++;
            j++;
        }
        dataClean[j]='\0';
    }
    void convertdataFix()
    {
           // pc.printf("cekkoma : %d \n", cekKoma());
            static int Stringlength = strlen(dataClean);
            pc.printf("size : %d \n", Stringlength);
            for (int i = 0; i < Stringlength; i++)
            {
               // pc.printf("besar pangkat : %d \n", cekKoma() - i - 1);
               // pc.printf("nilai : %f \n",((float)pow((float)10, (float)(cekKoma() - i - 1)) * (float)ConverttoInt(dataClean[i])));
                floatTemp = floatTemp + ((float)pow((float)10, (float)(cekKoma() - i - 1)) * (float)ConverttoInt(dataClean[i]));
                //pc.printf("floatTemp sekarang : %f \n", floatTemp);
            }
       
    }
    int cekKoma()
    {
        int k = 0;
        while ((receivedChars[k] != '.') and (k < strlen(receivedChars)))
        {
            k++;
        }
        if (k < strlen(receivedChars))
        {
            return k;
        }
        else
        {
            return 0;
        }
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
