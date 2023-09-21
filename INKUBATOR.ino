#include "Data.h"
Data data;

#include <DHT22.h>
DHT22 dht22(7);

float t = 0;
float h = 0;

// ---- my libry ----
#include "Timer.h"
Timer timer;
#include "Button.h"
#include "Pin.h"
// =================

#include "App.h"
App app;

void setup() {
  Serial.begin(9600);
  app.setup();
}

void loop() {
  t = dht22.getTemperature();
  h = dht22.getHumidity();

  app.loop();
  timer.update();
}


// SetInterval creat id = 0; rotation_interval
// SetInterval creat id = 1; flicker cursor 
// setInterval creat id = 2; canvas loop

// setTimeout creat id = 0; beck to glavni menu 