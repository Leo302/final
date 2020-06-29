#include "mbed.h"
#include "arm_math.h"
#include "bbcar.h"
#include <math.h>
#include <stdlib.h>
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"

#define bound 0.9

char recv;
WiFiInterface *wifi;
Ticker encoder_ticker;
Ticker servo_ticker;
PwmOut pin8(D8), pin9(D9);
DigitalInOut pin13(D13);
DigitalIn pin3(D3);
DigitalOut led(LED3);
BBCar car(pin8, pin9, servo_ticker);
Serial uart(D1,D0); //tx,rx
RawSerial xbee(D12, D11);
volatile int message_num = 0;
volatile int arrivedcount = 0;
volatile bool closed = false;
const char* topic = "Mbed";
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;
int status;

int main() {
    int find = 0;
    int i;
    float thing[10]={0};
    float max, min;
    int max_index, min_index;
    status =1;
    led =1;
    parallax_encoder encoder0(pin3, encoder_ticker);
    char s[5];
    encoder0.reset();
    parallax_ping ping1(pin13);
    uart.baud(9600);
    xbee.baud(9600);
    car.goStraight(100);
    while(encoder0.get_cm()<135) wait_ms(50);
    car.stop();
    car.turn(90,0.03);
    wait(1.4);
    car.stop();
    encoder0.reset();
    car.goStraight(100);
    while(encoder0.get_cm()<43) wait_ms(50);
    car.stop();
    car.stop();
    car.turn(-90,0.03);
    wait(1.5);
    car.stop();
    sprintf(s,"photo");
    uart.puts(s);
    wait(1.5);
    while(1){
        if(uart.readable()){
            recv = uart.getc();
            printf("%c\r\n",recv);
            printf("1\r\n");
            break;
        }
    }
    xbee.printf("%c",recv);
    car.turn(90,0.03);
    wait(1.5);
    car.stop();
    encoder0.reset();
    car.goStraight(100);
    while(encoder0.get_cm()<40) wait_ms(50);
    car.stop();
    wait(0.5);
    car.turn(-100,0.3);
    wait(1.9);
    car.stop();
    encoder0.reset();
    car.goStraight(-100);
    while(encoder0.get_cm()<39) wait_ms(50);
    car.stop();
    wait(1);
    encoder0.reset();
    car.goStraight(100);
    while(encoder0.get_cm()<12) wait_ms(50);
    car.stop();
    car.turn(-150,0.3);
    wait(3.1);
    car.stop();
    encoder0.reset();
    car.goStraight(100);
    while(encoder0.get_cm()<45) wait_ms(50);
    car.stop();
    wait(1);
    car.turn(-100,0.3);
    wait(1.9);
    car.stop();
    encoder0.reset();
    car.goStraight(100);
    while(encoder0.get_cm()<85) wait_ms(50);
    car.stop();

    led=0;
    wait(1);
    led=1;
    car.turn(-100,0.03);
    wait(1.5);
    car.stop();
    encoder0.reset();
    status ='2';
    car.goStraight(100);
    while(encoder0.get_cm()<45) wait_ms(50);
    car.stop();
    wait(0.5);
    car.turn(-100,0.03);
    wait(1.5);
    car.stop();
    wait(0.5);
    encoder0.reset();
    car.goStraight(100);
    while(encoder0.get_cm()<35) wait_ms(50);
    car.stop();
    wait(0.5);
    car.turn(-100,-0.03);
    wait(2.2);
    car.stop();
    wait(0.5);
    encoder0.reset();
    car.goStraight(100);
    while(encoder0.get_cm()<55) wait_ms(50);
    car.stop();
    wait(0.5);
    car.turn(-100,0.03);    
    for(i=0; i<=4; i++){
        wait(0.05);
        thing[i]=ping1;
    }
    car.stop();
    wait(0.5);
    car.turn(-100,-0.03);   
    for(i=0; i<=4; i++){
        wait(0.05);
    }
    car.stop();
    wait(0.5);
    car.turn(-100,-0.03);
    for(i=5; i<=9; i++){
        wait(0.05);
        thing[i]=ping1;
    }
    car.stop();
    wait(0.5);
    car.turn(-100,0.03);
    for(i=0; i<=4; i++){
        wait(0.05);
    }
    car.stop();
    wait(0.5);
    encoder0.reset();
    car.goStraight(-100);
    while(encoder0.get_cm()<55) wait_ms(50);
    car.stop();
    car.turn(100,-0.03);
    wait(2);
    car.stop();
    wait(0.5);
    car.turn(100,0.03);
    wait(2);
    car.stop();
    wait(0.5);
    encoder0.reset();
    car.goStraight(100);
    while(encoder0.get_cm()<55) wait_ms(50);
    car.stop();
    car.turn(-100,0.03);
    wait(2);
    car.stop();
    wait(0.5);
    encoder0.reset();
    car.goStraight(100);
    while(encoder0.get_cm()<120) wait_ms(50);
    car.stop();
    printf("finish\r\n");
    led =1;
    car.stop();
    }

