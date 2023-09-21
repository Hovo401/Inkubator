#include "PinTimerModule.h"
#include "MenuModule.h"
#include "ButtonControl.h"
#include "TH_Controller.h"
    
class Inkubator_MiniApp{// grafic interfase + user input set settings
  public:
    PinTimerModule pin_timer;
    Pin Pin13;
    MenuModule menuModule;
    ButtonControl buttonControl;
    
    TH_Controller th_Controller;

    Inkubator_MiniApp(): 
    pin_timer(4, data.getPinTime_pin_on(), data.getPinTime_pin_off(), data.getPinTimer_on_()),
    Pin13(13, data.getInkubatorLight()),
    menuModule(pin_timer, Pin13),
    buttonControl(menuModule, pin_timer, Pin13),
    th_Controller(6, 5)
    {}

    void setup() {
      menuModule.setup();
    }
    void loop() {
      pin_timer.loop();
      buttonControl.update();
      th_Controller.loop();
    }
};