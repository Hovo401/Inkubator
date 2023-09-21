
class Button {
private:
  unsigned char pin;
  bool prevState = false;
  unsigned long debounceDelay;
  unsigned char delay = 40;
  unsigned short int DelayBeforeRepeat = 500;
  unsigned long RepeatRateDelayDate;
public:
  static int newActivityCall ;
  Button(unsigned char buttonPin ) {
    pin = buttonPin;
    debounceDelay = millis();
    RepeatRateDelayDate = millis();
    pinMode(pin, INPUT);
    digitalWrite(pin, HIGH); // Включить внутренний подтягивающий резистор
  }

  bool isPressed(bool Repeat = true, unsigned char RepeatRateDelay = 80) {
    unsigned long date = millis();
    if(debounceDelay > date){
        debounceDelay = date;
    }
    bool reading = digitalRead(pin);
      
      if (reading != prevState) {
        if( debounceDelay + delay > date){
          return false;
        }
        prevState = reading;
        if (reading == HIGH) {
          debounceDelay = date;
          Button::newActivityCall ++ ;
          return true;
        }
      }else if(Repeat && reading && debounceDelay + DelayBeforeRepeat <= date){
        if(RepeatRateDelay > date){
          RepeatRateDelay = date;
        } 
        if(RepeatRateDelayDate + RepeatRateDelay <= date){
            RepeatRateDelayDate = date;
            Button::newActivityCall ++ ;
            return true;
        }
      }
    return false;
  }
};
int Button::newActivityCall = 0;