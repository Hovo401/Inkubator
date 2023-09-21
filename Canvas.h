#include <LCD_I2C.h>

class Canvas {
  private:
    bool* flicker;
    LCD_I2C lcd;
    int this_position_menu = 0;
    PinTimerModule& pin_timer;
    unsigned char* kursor;
    Pin& pinLight;
  public:
    
    Canvas( bool* flicker_, PinTimerModule& pin_timer_, unsigned char* kursor_, Pin& pinLight_): 
    pin_timer(pin_timer_), lcd(0x27, 16, 4), pinLight(pinLight_)  {
      flicker = flicker_;
      kursor = kursor_;
    }
    int max_menu = 2;

    void init() {
        lcd.begin();
        lcd.backlight();
    }

    void clear(){
      lcd.clear();
    }

    void Rednder(int menu){
      if(this_position_menu != menu){
        lcd.clear();
        this_position_menu = menu;
      }
      switch (menu){
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
    }

    void menu_0(){
        lcd.setCursor(0, 0);
        lcd.print(" Temperature = ");lcd.print(t, 1);
        lcd.setCursor(0, 1);
        lcd.print(" Humidity    = ");lcd.print(h, 1);

        lcd.setCursor(0, 2);
        lcd.print("->light ");
        if(pinLight.getPinStatus()){
          lcd.print("on ");
        }else{
          lcd.print("off");
        }

        lcd.setCursor(12, 2);
        // lcd.print( Timer::getDateString( pin_timer.time_pin_off ).substring(0, 5).c_str());
  
        lcd.setCursor(0, 3); 
        if(pin_timer.getTime_pin_off_real()  > 0){
          lcd.print("timer ");
          lcd.print( Timer::getDateString( pin_timer.time_pin_off ).substring(0, 5).c_str());
        }
        else if(*flicker){
          lcd.print(" rotating  ");
        }else{
          lcd.print("           ");
        }

        lcd.setCursor(12, 3); 
        if(pin_timer.timer_on_){
          lcd.print( Timer::getDateString(pin_timer.getTime_pin_off_real() ));
        }else{
          lcd.print("    off  ");
        }
    }

    void menu_1(){
        lcd.setCursor(0, 0);
        lcd.print("      Controll");
        lcd.setCursor(2, 2);
        lcd.print("Save Temp. = ");lcd.print(data.getSave_temperature(), 1);
        lcd.setCursor(2, 3);
        lcd.print("Save hum . = ");lcd.print(data.getSave_humidity(), 1);
        if(*kursor == 2){
          lcd.setCursor(0, 3);
          lcd.print("  ");
          lcd.setCursor(0, 2);
          lcd.print("->");
        }else if(*kursor == 3){
          lcd.setCursor(0, 2);
          lcd.print("  ");
          lcd.setCursor(0, 3);
          lcd.print("->");
        }
    }

    void menu_2(){
      lcd.setCursor(0, 0);
      lcd.print("   timer controll");
      lcd.setCursor(2, 1);
      lcd.print("Enabled: ");
      if(pin_timer.timer_on_){
        lcd.print("on ");
      }else{
        lcd.print("off");
      }
      lcd.setCursor(2, 2);
      lcd.print( Timer::getDateString( pin_timer.time_pin_off));
      if(*kursor == 1){
          lcd.setCursor(0, 2);
          lcd.print("  ");
          lcd.setCursor(0, 1);
          lcd.print("->");
      }else if(*kursor == 2){
          lcd.setCursor(0, 1);
          lcd.print("  ");
          lcd.setCursor(0, 2);
          lcd.print("->");
      }

      lcd.setCursor(0, 3); 
      if(pin_timer.getTime_pin_off_real()  > 0){
        lcd.print("  timer =  ");
      }
      else if(*flicker){
        lcd.print("  rotating");
      }else{
        lcd.print("          ");
      }
      lcd.setCursor(11, 3); 
      lcd.print( Timer::getDateString(pin_timer.getTime_pin_off_real() ));
    }

};






