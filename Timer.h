
class Timer {
private:

    struct Timeout {
        short id;
        unsigned long delayValue;
        unsigned long startTime;
        unsigned long *delay;
        void (*callback)();
    };

    struct Interval {
        short id;
        unsigned long intervalValue;
        unsigned long lastExecutionTime;
        unsigned long *interval;
        void (*callback)();
    };

    static const int MAX_TIMERS = 5; // Максимальное количество таймеров
    Timeout timeouts[MAX_TIMERS];
    Interval intervals[MAX_TIMERS];
    int timeoutCount = 0;
    int intervalCount = 0;

    void creatErrorMessege(String tip, int Count, short id, unsigned long interval_delay){
      // tip == Timeout || Interval
      Serial.print("error "+ tip);
      if(Count == MAX_TIMERS){
        Serial.print(": limit full;  id = ");
      }else{
        Serial.print(" с таким ID уже существует ;  id = ");
      }
      Serial.print(String(id));
      if(tip == "Timeout"){
        Serial.print(", Timeout Count = "+ String(timeoutCount) +"; delay = ");
        
      }else{
        Serial.print(", Interval Count = "+ String(intervalCount) +"; interval = ");
      }
      Serial.println(interval_delay);
    }

public:

    void update() {
        unsigned long currentTime = millis();

        for (int i = 0; i < timeoutCount; i++) {
            Timeout &timeout = timeouts[i];
            if (currentTime - timeout.startTime >= *timeout.delay) {
                timeout.callback();
                deliteTimeout(i);
                i--;
            }
            else if(currentTime < timeout.startTime){
              timeout.startTime = currentTime;
            }
        }

        for (int i = 0; i < intervalCount; i++) {
            Interval &interval = intervals[i];
            
            if (currentTime - interval.lastExecutionTime >= *interval.interval) {
                interval.callback();
                interval.lastExecutionTime = currentTime;
            }
            else if(currentTime < interval.lastExecutionTime){
                interval.lastExecutionTime = currentTime;
            }
        }
    }

    // --------------------------------------------------------------------------- create -set -----------------

    void setTimeout(void (*callback)(), unsigned long delay, short id = -2) {
        if (timeoutCount < MAX_TIMERS && ( getTimeoutIndexById(id) == -1.0 || id == -2)) {
            timeouts[timeoutCount].id = id;
            timeouts[timeoutCount].startTime = millis();
            timeouts[timeoutCount].delayValue = delay;
            timeouts[timeoutCount].delay = &timeouts[timeoutCount].delayValue;
            timeouts[timeoutCount].callback = callback;
            timeoutCount++;
        }else{
          creatErrorMessege("Timeout", timeoutCount, id, delay);
        }
    }
    void setTimeoutDynamic(void (*callback)(), unsigned long *delay, short id = -2) {
        if (timeoutCount < MAX_TIMERS && ( getTimeoutIndexById(id) == -1.0 || id == -2)) {
          timeouts[timeoutCount].id = id;
          timeouts[timeoutCount].startTime = millis();
          timeouts[timeoutCount].delay = delay;
          timeouts[timeoutCount].callback = callback;
          timeoutCount++;
        }else{
          creatErrorMessege("Timeout", timeoutCount, id, delay);
        }
    }
 
    void setInterval(void (*callback)(), unsigned long interval, short id = -2) {
        if (intervalCount < MAX_TIMERS && ( getIntervalTimeById(id) == -1.0 || id == -2) ){
          intervals[intervalCount].id = id;
          intervals[intervalCount].lastExecutionTime = millis();
          intervals[intervalCount].intervalValue = interval;
          intervals[intervalCount].interval = &intervals[intervalCount].intervalValue;
          intervals[intervalCount].callback = callback;
          intervalCount++;
        }else{
          creatErrorMessege("Interval", intervalCount, id, interval);
        }
    }
    void setIntervalDynamic(void (*callback)(), unsigned long *interval, short id = -2) {
        if (intervalCount < MAX_TIMERS && ( getIntervalTimeById(id) == -1.0 || id == -2) ){
          intervals[intervalCount].id = id;
          intervals[intervalCount].lastExecutionTime = millis();
          intervals[intervalCount].interval = interval;
          intervals[intervalCount].callback = callback;
          intervalCount++;
        }else{
          creatErrorMessege("Interval", intervalCount, id, interval);
        }
    }
    // =========================================================================================================

    // ---- set -------

    bool setintervalLastExecutionTimeById(int id){
      intervals[getIntervalIndexById(id)].lastExecutionTime = millis();
    } 

    // ================

    // -------------------- Delite --------------------

    bool deliteTimeoutById(int id){
      return deliteTimeout(getTimeoutIndexById(id));
    }
    bool deliteIntervalById(int id){
      return deliteInterval(getIntervalIndexById(id));
    }

    bool deliteTimeout(int index){
      // Удаление таймера путем сдвига всех следующих таймеров влево
      if(index > timeoutCount-1 || index < 0){
        return false;
      }
      for (int j = index; j < timeoutCount - 1; j++) {
          timeouts[j] = timeouts[j + 1];
      }
      timeoutCount--;
      return true;
    }

    bool deliteInterval(int index){
      // Удаление таймера путем сдвига всех следующих таймеров влево
      if(index > intervalCount-1 || index < 0){
        return false;
      }
      for (int j = index; j < intervalCount - 1; j++) {
          intervals[j] = intervals[j + 1];
      }
      intervalCount--;
      return true;
    }

    // ================================================

    // -------- get index -------

    int getTimeoutIndexById (short id){
      if(id < 0 || id > timeoutCount-1){
        return -1;
      }
      for (int i = 0; i < timeoutCount; i++) {
          Timeout &timeout = timeouts[i];
          if(timeout.id == id){
            return i;
          }
       }
      return -1;
    }

    int getIntervalIndexById(short id){
      if(id < 0 || id > intervalCount - 1){
        return -1;
      }
      for (int i = 0; i < intervalCount; i++) {
          Interval &interval = intervals[i];
          if(interval.id == id){
            return i;
          }
       }
       return -1;
    }

    // =====================

    // ---------- get time -----------
    
    float getIntervalTimeById (short id){
      int index = getIntervalIndexById(id); 
      if(index == -1){
        return -1.0;
      }
      if( *intervals[index].interval < millis() - intervals[index].lastExecutionTime){
        return 0.00;
      }
      return *intervals[index].interval - (millis() - intervals[index].lastExecutionTime);
    }

    // ===============================

    static String getDateString(unsigned long mill){
      round(mill/1000);
      unsigned long jam = round(mill/1000/60/60);
      unsigned long jam_00 = round(jam - round(jam/100)*100); // ставим ограничение верхнего предела
      unsigned long min = round(mill/1000/60 - jam*60);
      unsigned long sec = round(mill/1000 - min * 60 - jam*60*60);
      String out ;
      if(jam_00 < 10){
         out += '0';
      }
      out += String(jam_00) + ':';

      if(min < 10){
         out += '0';
      }
      out += String(min) + ':';

      if(sec < 10){
         out += '0';
      }
      out += String(sec);

      return out ;
    }
};










