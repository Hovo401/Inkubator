class Pin{
  private:
    bool pin_on ;
    unsigned char pin;
  public:
    Pin(unsigned char pin_, bool pin_on_ = false){
      pin = pin_;
      pin_on = pin_on_;
      pinMode(pin, OUTPUT);
      digitalWrite(pin, pin_on);
    }
    // -------------------- set value --------------------
    void setPinON(){
      pin_on = true;
      digitalWrite(pin, pin_on);
    }
    void setPinOff(){
      pin_on = false;
      digitalWrite(pin, pin_on);
    }
    void setPinClick(){
      pin_on = !pin_on;
      digitalWrite(pin, pin_on);
    }
    // ===================================================

    // ----- get value -----
    bool getPinStatus(){
      return pin_on;
    }
    // =====================
};