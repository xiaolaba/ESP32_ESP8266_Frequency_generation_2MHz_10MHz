/*
 * xiaolaba 2022-OCT-09
 * adaptoped to 2MHz signal generator,
 * Arduino 1.8.16 / esp32 WROOM NodeMCU ESP-32S, test, ok.
 * Sketch uses 238337 bytes (18%) of program storage space. Maximum is 1310720 bytes.
 * Global variables use 16328 bytes (4%) of dynamic memory, leaving 311352 bytes for local variables. Maximum is 327680 bytes.
 * 
 * https://blog.csdn.net/tx1991427/article/details/124799571
 * https://blog.csdn.net/believe666/article/details/124363078

*/

// original code, ref https://forum.arduino.cc/t/4mhz-esp32-output-with-ledcsetup-0-4-0e6-1/992801/11

//  Calculation of settings for each frequency band
//  Resolution = log2(Clock(80MHz)/f) + 1   ex: 50.000 HZ = 80.0000/50.000 = 1.600 log2(1600) = 10 + 1 = 11
//  Duty 50%  = (2**Resolution)/2       ex: 2**11 = 2048   2048/2 = 1024

#include "driver/ledc.h"


#define LEDC_HS_CH0_GPIO      GPIO_NUM_18                                 // Ledc pulse output, oscillator output 2MHz

#define LINE_PULSE_GPIO       5                                 // next above pin, 1200dpi 8.8ms /line pules
#define LINE_PULSE_INVERT_GPIO      17                          // next above pin, 1200dpi 8.8ms /line pules

#define LED_GPIO      2                          // ESP-32S onbroad LED


#define LEDC_HS_CH0_CHANNEL   LEDC_CHANNEL_0                              // LEDC channel 0
#define LEDC_HS_MODE          LEDC_HIGH_SPEED_MODE                        // LEDC in high speed
#define LEDC_HS_TIMER         LEDC_TIMER_0                                // Use timer0 ledc

uint32_t        resolution    = 0;                                        // Resolution var
//uint32_t        oscilator     = 4000000;                                  // Frequency  4MHz
//uint32_t        oscilator     = 2000000;                                  // Frequency  3.6MHz
uint32_t        oscilator     = 1000000;                                  // Frequency  1MHz
uint32_t        mDuty         = 0;                                        // Calc ledc duty var
//------------------------------------------------------------------------
void ledcInit ()
{
  resolution = log((80000000 / oscilator) + 1) / log(2);                  // Ledc resolution  calc
  if (resolution > 20) resolution = 20;                                   // Max resolution is 20
  mDuty = (pow(2, resolution)) / 2;                                       // Calc ledc duty
  //  Serial.println(mDuty);                                              // Print

  ledc_timer_config_t ledc_timer = {};                                    // Instantiate the ledc timer setting

  ledc_timer.duty_resolution = (ledc_timer_bit_t) + resolution;           // Config resolution
  ledc_timer.freq_hz    = oscilator;                                      // Frequency
  ledc_timer.speed_mode = LEDC_HIGH_SPEED_MODE;                           // Oper Mode high speed
  ledc_timer.timer_num = LEDC_TIMER_0;                                    // Use timer0
  ledc_timer_config(&ledc_timer);                                         // Config ledc timer

  ledc_channel_config_t ledc_channel = {};                                // Instantiates the ledc channel configuration

  ledc_channel.channel    = LEDC_HS_CH0_CHANNEL;                          // Config channel
  ledc_channel.duty       = mDuty;                                        // Calc duty  %
  ledc_channel.gpio_num   = LEDC_HS_CH0_GPIO;                             // Output GPIO
  ledc_channel.intr_type  = LEDC_INTR_DISABLE;                            // Disabledc interrupt de ledc
  ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;                         // Oper high speed
  ledc_channel.timer_sel  = LEDC_TIMER_0;                                 // Use timer0

  ledc_channel_config(&ledc_channel);                                     // Config ledc channel
}

void init_io ()
{
  pinMode(LINE_PULSE_GPIO, OUTPUT);
  pinMode(LINE_PULSE_INVERT_GPIO, OUTPUT);
  pinMode(LED_GPIO, OUTPUT);    

  digitalWrite(LINE_PULSE_GPIO, LOW);
  digitalWrite(LINE_PULSE_INVERT_GPIO, HIGH);
  digitalWrite(LED_GPIO, LOW);  

}

void line_scan()
{

  digitalWrite(LINE_PULSE_GPIO, HIGH);
  digitalWrite(LINE_PULSE_INVERT_GPIO, LOW);
  digitalWrite(LED_GPIO, HIGH);

  delayMicroseconds(50);  //50us pulse
//  delay(500);  // 10 ms
  
  digitalWrite(LINE_PULSE_GPIO, LOW);
  digitalWrite(LINE_PULSE_INVERT_GPIO, HIGH);
  digitalWrite(LED_GPIO, LOW);

  delay(10);  // 10 ms

  
}

//------------------------------------------------------------------------
void setup() {
  init_io ();
  
  ledcInit();
  Serial.begin(115200); // use the serial port
  Serial.println("\nStarting ...\nESP32_Frequency_generation_2MHz_10MHz_pin18\n");
  Serial.println("pin5, pules, pin17 inverted pulse, GPIO2, onbroad LED\n");
}
//------------------------------------------------------------------------
void loop()
{
  line_scan();
}
