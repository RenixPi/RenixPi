#include <Arduino.h>
#include <SleepyPi2.h>

#include <RenixPower.h>

void setup() {

  Serial.begin(9600);
  Serial.print("starting....\n");

  // put your setup code here, to run once:
  // RenixPower.enableOpenDshPower(false);
  // RenixPower.enableRenixPower(false);
  SleepyPi.enableExtPower(false);
  SleepyPi.enablePiPower(false);
  RenixPower.enableOpenDshPower(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  if(RenixPower.isOpenDshRunning()) {
    Serial.print("opendash is running\n");
    RenixPower.shutdownOpenDsh();
  }
  Serial.print("powered? ");
  Serial.print(RenixPower.isOpenDshPoweredOn());
  Serial.print("\n");
}