#include "Inkubator_MiniApp.h"

class App{
  private:
    Inkubator_MiniApp Inkubator_MiniApp;
  public:
    App(){}

    void setup() {
      Inkubator_MiniApp.setup();
    }
    void loop() {
      Inkubator_MiniApp.loop();
    }
};