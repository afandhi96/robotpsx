//============================================================
/* 
** DAY 42
** HARD_PRO : HIZBUL JIHAD AFANDI
** SOFT_PRO : RAHMAT HADI
** WIRING   : FIRMAN SASMITO
** LIBRARI.1: LIBRARI STICK PS2 DARI http://www.billporter.info/?p=240
** LIBRARI.2: LIBRARI VirtulWire http://www.open.com.au/mikem/arduino/VirtualWire.pdf UNTUK KOMUNIKASI DATA RF 
*/
//========================== BEGIN ===========================
#include <VirtualWire.h>

const int led_pin = 8;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;

void setup()
{
  delay(1000);
  Serial.begin(9600);	// Debugging only
  Serial.println("setup");

  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec

  vw_rx_start();       // Start the receiver PLL running

  pinMode(led_pin, OUTPUT);
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

    digitalWrite(led_pin, HIGH); // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    Serial.print("Temperature: ");

    for (i = 0; i < buflen; i++)
    {
      //Serial.println(buf[i]);
      Serial.print((int)buf[i]);
    }
    Serial.print(" C");
    Serial.println();
    digitalWrite(led_pin, LOW);
  }
}
