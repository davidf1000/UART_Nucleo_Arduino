#include <mbed.h>
#include <math.h>

Serial pc(SERIAL_TX, SERIAL_RX,230400);
Serial mega(PC_10, PC_11);
Ticker uart;
const uint8_t num_limit = 64;
char receivedChars[num_limit];
char dataClean[num_limit];
float dataOut[81];
float floatTemp;
float out;
bool cond;
bool newData = false;
int Y;

void Sentmega(uint8_t DataSent)
{
    if (mega.writeable() > 0)
    {
        mega.putc(DataSent);
        pc.printf("sent %d to ardu \n",DataSent);
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
    //pc.printf("%d ", mega.readable());
    while (mega.readable() > 0 && newData == false)
    {
        //pc.printf("mega available ");
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
    int i = 0;
    int j = 0;
    while (i < strlen(receivedChars))
    {
        if (receivedChars[i] == '.')
        {
            i++;
        }
        dataClean[j] = receivedChars[i];
        i++;
        j++;
    }
    dataClean[j] = '\0';
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
void convertdataFix()
{
    // pc.printf("cekkoma : %d \n", cekKoma());
    int Stringlength;
    int size;
    Stringlength = strlen(dataClean);
    size = cekKoma();
    floatTemp = 0;
    if (size > 0)
    {
        for (int k = 0; k < Stringlength; k++)
        {
            //pc.printf(" besar pangkat : %d \n", cekKoma() - k - 1);
            //pc.printf("nilai : %f \n",((float)pow((float)10, (float)(cekKoma() - k - 1)) * (float)ConverttoInt(dataClean[k])));
            floatTemp = floatTemp + ((float)pow((float)10, (float)(cekKoma() - k - 1)) * (float)ConverttoInt(dataClean[k]));
            //pc.printf("floatTemp sekarang : %f \n", floatTemp);
        }
    }
    else
            {
                for (int i = 0; i < Stringlength; i++)
            {
                //pc.printf("%d besar pangkat : %d \n",i, cekKoma() - i - 1);
                //pc.printf("nilai : %f \n",((float)pow((float)10, (float)(Stringlength - i - 1)) * (float)ConverttoInt(dataClean[i])));
                floatTemp = floatTemp + ((float)pow((float)10, (float)(Stringlength - i - 1)) * (float)ConverttoInt(dataClean[i]));
                //pc.printf("floatTemp sekarang : %f \n", floatTemp);
            }
                }
}

float showNewData()
{   
    //pc.printf("Were in loop ");
            //recvWithStartEndMarkers();
    while (newData==false)
    {
        //pc.printf(".");
        recvWithStartEndMarkers();
        }
    if (newData == true)
    {
        //pc.printf("DATA Received :");
        //pc.printf("%s \n",receivedChars);
        cleanData();
        //pc.printf("cleandata : %s \n", dataClean);
        convertdataFix();
        out=floatTemp;
        //pc.printf("Output: %.4f \n", out);
        //upSensor();
        newData = false;
        cond=true;
        return out;
    }
    else
    {
        return 99999;
        }
}
void upSensor()
{
    float X;

    //bool cond;
    //pc.printf("this is upSensor");
    //INISIASI
    cond=false;
    Sentmega(99);
    wait_us(10);
    //break;
    /*X=showNewData();
    pc.printf("%.2f", X);
    while (X!=98)
    {
        X=showNewData();
    }*/
    pc.printf("YEA");
    //UDAH AKTIF 2 PIHAK
    for (int i=0;i<81;i++)
    {
        cond=false;
        while(cond==false) // Coba terus sampe 
        {
            //pc.printf("still in cond while \n");
            //wait_us(1000);
            X=showNewData();
            //pc.printf("loop %d : %.2f \n%",i+1,X);
            dataOut[i]=X;
        }
    }
    
         wait(0.1);
        for (int k=0;k<81;k++)
        {
            Y=k+1;
            pc.printf("Data ke %d : %.3f \n",Y,dataOut[k]);
        }
}




int main()
{
    pc.printf("Serial receiver V2");
    uart.attach(&upSensor,1.0);
    wait(0.5);
    mega.baud(115200);
    while (1)
    {
        
       // showNewData();
        //upSensor();

        wait(0.001);
        //dataOut[0]=floatTemp;
        pc.printf("MAIN");
        //wait(0.5);
    }
}
