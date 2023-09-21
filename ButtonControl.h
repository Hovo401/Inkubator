class ButtonControl {
  private:
    MenuModule& menuModule;
    PinTimerModule& pin_timer;

    Pin& pinLight;

    Button menuBut;
    Button kursor;
    Button plus;
    Button minus;
  public:
    ButtonControl(MenuModule& menuModule_, PinTimerModule& pin_timer_, Pin& pinLight_) : 
    menuModule(menuModule_), 
    pin_timer(pin_timer_), 
    pinLight(pinLight_),
    menuBut(9), kursor(10), plus(11), minus(12) 
    {}
    
    void ee(){
         menuModule.setMenu(0);
      }
    
    void update() {
      if( menuBut.isPressed(false) ){
        menuModule.next();
      }
      switch (menuModule.getMenu()){
        case 0:
          menu_0();
          break;
        case 1:
          menu_1();
          break;
        case 2:
          menu_2();
          break;
      }
      

      if(Button::newActivityCall > 0){
        timer.deliteTimeoutById(0);
        if(menuModule.getMenu() != 0){
          static MenuModule& menuModule__ = menuModule ;
            timer.setTimeout( [](){
               menuModule__.setMenu(0);
            }, 6000, 0);
        }
        Button::newActivityCall = 0;
      }
    }

    void menu_0(){
      if( plus.isPressed(false) || minus.isPressed(false) ){
        pinLight.setPinClick();
        data.setInkubatorLight(pinLight.getPinStatus());
      }
    }
    void menu_1(){

      if( menuModule.kursor == 2 ){
        if( plus.isPressed(true, 42) ){
          data.setSave_temperature(data.getSave_temperature() + 0.1); 
        }
        if( minus.isPressed(true, 42) ){
          data.setSave_temperature(data.getSave_temperature() - 0.1); 
        }
      }
      
      if(menuModule.kursor == 3){
        if( plus.isPressed(true, 100)){
          data.setSave_humidity(data.getSave_humidity() + 1); 
        }
        if( minus.isPressed(true, 100) ){
          data.setSave_humidity(data.getSave_humidity() - 1); 
        }
      }

      if(kursor.isPressed() ){
        if(menuModule.kursor != 2){
          menuModule.kursor = 2;
        }else{
          menuModule.kursor = 3;
        }
      }
    }
    void menu_2(){
      if(menuModule.kursor == 1){
        if(plus.isPressed() || minus.isPressed()){
          pin_timer.timer_on_ = !pin_timer.timer_on_;
          data.setPinTimer_on_( pin_timer.timer_on_ );
        }
      }
      else if(menuModule.kursor == 2){
        if( plus.isPressed() &&  pin_timer.time_pin_off + 1800000 <= 86400000){
          data.setPinTime_pin_off(pin_timer.time_pin_off + 1800000);
          pin_timer.setTime_pin_off( data.getPinTime_pin_off() );
          
        }
        if( minus.isPressed() &&  pin_timer.time_pin_off - 1800000 >= 1800000){
          data.setPinTime_pin_off(pin_timer.time_pin_off - 1800000);
          pin_timer.setTime_pin_off( data.getPinTime_pin_off() );
        }
      }
      if(kursor.isPressed() ){
        if(menuModule.kursor != 1){
          menuModule.kursor = 1;
        }else{
          menuModule.kursor = 2;
        }
      }
    }
};



