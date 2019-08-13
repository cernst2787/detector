#include "mbed.h"

Ticker in;
AnalogIn sensor(PA_0); 

const int maxReadings = 4096;  //define the max samples 

float measurementArray[maxReadings]; //define the array

volatile int readingNumber = 0; //volatile so the compiler knows to check if it's changed

char adc_time_stamp[maxReadings];

//char *time_stamp()

char *time_stamp()
{
    char *timestamp = (char *)malloc(sizeof(char) * 16);
    time_t ltime;
    ltime=time(NULL);
    struct tm *tm;
    tm=localtime(<time);
    
    sprintf(timestamp,"%04d%02d%02d%02d%02d%02d", tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    return timestamp;
}

void update()  //function that creates an array from ADC pin values
{
    if (readingNumber < maxReadings)
    {
        measurementArray[readingNumber] = sensor;  //populate the array with input from ADC 
        adc_time_stamp[readingNumber] = *time_stamp();
        readingNumber++;
    }
}

main()
{
    int nextReading = 0;
    in.attach(&update,0.042);  //attach update function to the timer and set it to interrupt after 20 mil sec; This can be changed
    while (nextReading < maxReadings)
    {
        if (readingNumber > nextReading)
        {
            nextReading = readingNumber-1;
            nextReading++;
        }
    }
    
    for (int i=0; i<maxReadings; i++)
    {
        printf("%f\n", " TimeStamp: %s\n", measurementArray[i], time_stamp());
    }
    
}