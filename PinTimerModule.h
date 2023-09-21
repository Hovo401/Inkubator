class PinTimerModule {
  private:
    short id ;
    unsigned char pin;
    
  public:
    unsigned long timer_interval ;
    unsigned long time_pin_on ;
    unsigned long time_pin_off ; 
    bool pin_on_ = 1;
    bool timer_on_ ;
    
    static short Id ;
    PinTimerModule(unsigned char pin_, unsigned long time_pin_on_ , unsigned long time_pin_off_ , bool timer_on__ = false){
      id = PinTimerModule::Id;
      PinTimerModule::Id ++;
      pin = pin_;
      time_pin_on = time_pin_on_;
      time_pin_off = time_pin_off_;
      timer_interval = time_pin_off + time_pin_on; 
      timer_on_ = timer_on__;

      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
      timer.setIntervalDynamic([](){}, &timer_interval, id);
    }

    // ----- set ------
    bool setTime_pin_on(unsigned long time_pin_on_){
      time_pin_on = time_pin_on_;
      timer_interval = time_pin_off + time_pin_on;
      return true;
    }
    bool setTime_pin_off(unsigned long time_pin_off_){
      time_pin_off = time_pin_off_;
      timer_interval = time_pin_off + time_pin_on;
      return true;
    }
    // ================

    // ----- get ------
    unsigned long getTimer_interval_real(){
      unsigned long out = timer_interval - timer.getIntervalTimeById(id);
      if(out > timer_interval) return 0;
      return out;
    }
    unsigned long getTime_pin_on_real(){
      unsigned long out = timer_interval - timer.getIntervalTimeById(id) - time_pin_on;
      if(out > timer_interval) return 0;
      return out;
    }
    unsigned long getTime_pin_off_real(){
      unsigned long out = timer.getIntervalTimeById(id) - time_pin_on  ;
      if(out > timer_interval) return 0;
      return out;
    }
    bool check_pin_on_ (){
      return pin_on_;
    }
    // ================

    void loop(){
      if(!timer_on_){
          timer.setintervalLastExecutionTimeById(id);
      }
      if(timer.getIntervalTimeById(id) - time_pin_on > 0 ){
          pin_on_ = 0;
          digitalWrite(pin, LOW);
      }else {
        pin_on_ = 1;
        digitalWrite(pin, HIGH);
      }
    }

};
short PinTimerModule::Id = 0;
