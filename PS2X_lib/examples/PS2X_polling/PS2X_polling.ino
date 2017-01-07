#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you conect the controller,
//or call config_gamepad(pins) again after connecting the controller.
int error = 0;
byte type = 0;
byte vibrate = 0;
int LY, LX, RY, RX, LYold, LXold, RYold, RXold;

void setup(){
  Serial.begin(115200);

  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  delay(500);

  error = ps2x.config_gamepad(A0,11,10,12, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  if(error == 0){
    Serial.println("Found Controller, configured successful");
  }

  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch(type) {
  case 0:
    Serial.println("Unknown Controller type");
    break;
  case 1:
    Serial.println("DualShock Controller Found");
    break;
  case 2:
    Serial.println("GuitarHero Controller Found");
    break;
  }

}

void loop()
{
  ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed

  if(ps2x.ButtonPressed(PSB_PAD_UP))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_UP just pressed");
  if(ps2x.ButtonReleased(PSB_PAD_UP))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_UP just released");

  if(ps2x.ButtonPressed(PSB_PAD_DOWN))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_DOWN just pressed");
  if(ps2x.ButtonReleased(PSB_PAD_DOWN))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_DOWN just released");

  if(ps2x.ButtonPressed(PSB_PAD_LEFT))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_LEFT just pressed");
  if(ps2x.ButtonReleased(PSB_PAD_LEFT))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_LEFT just released");

  if(ps2x.ButtonPressed(PSB_PAD_RIGHT))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_RIGHT just pressed");
  if(ps2x.ButtonReleased(PSB_PAD_RIGHT))             //will be TRUE if button was JUST pressed
    Serial.println("PAD_RIGHT just released");

  if(ps2x.ButtonPressed(PSB_START))             //will be TRUE if button was JUST pressed
    Serial.println("START just pressed");
  if(ps2x.ButtonReleased(PSB_START))             //will be TRUE if button was JUST pressed
    Serial.println("START just released");

  if(ps2x.ButtonPressed(PSB_SELECT))             //will be TRUE if button was JUST pressed
    Serial.println("SELECT just pressed");
  if(ps2x.ButtonReleased(PSB_SELECT))             //will be TRUE if button was JUST pressed
    Serial.println("SELECT just released");

  if(ps2x.ButtonPressed(PSB_TRIANGLE))             //will be TRUE if button was JUST pressed
    Serial.println("Triangle just pressed");
  if(ps2x.ButtonReleased(PSB_TRIANGLE))             //will be TRUE if button was JUST pressed
    Serial.println("Triangle just released");

  if(ps2x.ButtonPressed(PSB_CIRCLE))             //will be TRUE if button was JUST pressed
    Serial.println("Circle just pressed");
  if(ps2x.ButtonReleased(PSB_CIRCLE))             //will be TRUE if button was JUST pressed
    Serial.println("Circle just released");

  if(ps2x.ButtonPressed(PSB_SQUARE))             //will be TRUE if button was JUST pressed
    Serial.println("Square just pressed");
  if(ps2x.ButtonReleased(PSB_SQUARE))             //will be TRUE if button was JUST released
    Serial.println("Square just released");     

  if(ps2x.ButtonPressed(PSB_CROSS))             //will be TRUE if button was JUST pressed
    Serial.println("X just pressed");
  if(ps2x.ButtonReleased(PSB_CROSS))             //will be TRUE if button was JUST released
    Serial.println("X just released");     

  if(ps2x.ButtonPressed(PSB_L1))             //will be TRUE if button was JUST pressed
    Serial.println("L1 just pressed");
  if(ps2x.ButtonReleased(PSB_L1))             //will be TRUE if button was JUST released
    Serial.println("L1 just released");  

  if(ps2x.ButtonPressed(PSB_R1))             //will be TRUE if button was JUST pressed
    Serial.println("R1 just pressed");
  if(ps2x.ButtonReleased(PSB_R1))             //will be TRUE if button was JUST released
    Serial.println("R1 just released");

  if(ps2x.ButtonPressed(PSB_L2))             //will be TRUE if button was JUST pressed
    Serial.println("L2 just pressed");
  if(ps2x.ButtonReleased(PSB_L2))             //will be TRUE if button was JUST released
    Serial.println("L2 just released");  

  if(ps2x.ButtonPressed(PSB_R2))             //will be TRUE if button was JUST pressed
    Serial.println("R2 just pressed");
  if(ps2x.ButtonReleased(PSB_R2))             //will be TRUE if button was JUST released
    Serial.println("R2 just released");

  if(ps2x.ButtonPressed(PSB_L3))             //will be TRUE if button was JUST pressed
    Serial.println("L3 just pressed");
  if(ps2x.ButtonReleased(PSB_L3))             //will be TRUE if button was JUST released
    Serial.println("L3 just released");  

  if(ps2x.ButtonPressed(PSB_R3))             //will be TRUE if button was JUST pressed
    Serial.println("R3 just pressed");
  if(ps2x.ButtonReleased(PSB_R3))             //will be TRUE if button was JUST released
    Serial.println("R3 just released");  

  LY = (int) ps2x.Analog(PSS_LY);
  LX = (int) ps2x.Analog(PSS_LX);
  RY = (int) ps2x.Analog(PSS_RY);
  RX = (int) ps2x.Analog(PSS_RX);

  if(LX != LXold || LY != LYold)
  {
    Serial.print("L Stick Values:");
    Serial.print(LY, DEC);
    Serial.print(",");
    Serial.println(LX, DEC);
  }
  if(RX != RXold || RY != RYold)
  {
    Serial.print("R Stick Values:");
    Serial.print(RY, DEC);
    Serial.print(",");
    Serial.println(RX, DEC);  
  }

  LYold = LY;
  LXold = LX;
  RYold = RY;
  RXold = RX;


  delay(20);

}



