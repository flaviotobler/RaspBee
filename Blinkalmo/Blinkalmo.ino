/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care 
  of use the correct LED pin whatever is the board used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
*/

#include <SoftwareSerial.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

volatile int f_wdt=1;


ISR(WDT_vect)
{
  if(f_wdt == 0)
  {
    f_wdt=1;
  }
  else
  {
    Serial.println("WDT Overrun!!!");
  }
}

void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();
  
  /* Now enter sleep mode. */
  sleep_mode();
  
  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */
  
  /* Re-enable the peripherals. */
  power_all_enable();
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(38400);
  Serial.println("setup");
  delay(100);
  /*** Setup the WDT ***/
  
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  /* set new watchdog timeout prescaler value */
  WDTCSR = 1<<WDP1 | 1<<WDP2; /* 1.0 seconds */
  
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
  
  
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("loop");
  delay(100);
  if(f_wdt == 1)
  {
    Serial.println("if");
    delay(100);
    /* Bewegungssensor abfragen und falls bewegung meldung geben */
    boolean move = 0;
    // bewegungsmelderauslesefunktion
    if(move == 1){
      Serial.println("bewegung");
      delay(100); //Allow for serial print to complete.
    }
    /* Don't forget to clear the flag. */
    f_wdt = 0;
    
    /* Re-enter sleep mode. */
    enterSleep();
  }
  else
  {
    Serial.println("else");
    delay(100);
    /* Do nothing. */
  }
}






