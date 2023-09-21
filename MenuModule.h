#include "Canvas.h" 

class MenuModule {
  private:
    Canvas canvas;
    int menu = 0;
    
  public:
    static bool fliker ;
    unsigned char kursor = 2;
    PinTimerModule& pin_timer;
    

    MenuModule(PinTimerModule& pin_timer_,  Pin& pinLight_): 
    pin_timer(pin_timer_), 
    canvas( &MenuModule::fliker, pin_timer_, &kursor, pinLight_ )  
    {}

    // ---- get ----
    int getMenu(){ return menu; }
    bool getFliker(){ return MenuModule::fliker; }
    // =============

    // ---------------- metode управление ---------------
    // ---- set ----
    bool setMenu(int num){ 
      if(0 <= num && num <= canvas.max_menu ){
        if(num == 1){
          kursor = 2;
        }else if(num == 2){
          kursor = 1;
        }
        menu = num;
        return true;
      }
      return false;
    }
    // =============
    void next(){
      if(menu + 1 > canvas.max_menu){
        setMenu(0);
      }else{
        setMenu(menu + 1);
      }
    }
    // ==================================================

    void setup(){
      canvas.init();
      timer.setInterval([](){
        MenuModule::fliker = !MenuModule::fliker;
      }, 400, 1);

      static int& menu__asha123123 = menu;
      static Canvas& canvas__asha123123 = canvas;
      timer.setInterval([](){
        canvas__asha123123.Rednder(menu__asha123123);
      }, 100, 2);
    }

};
bool MenuModule::fliker = false;