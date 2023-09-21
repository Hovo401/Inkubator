#include <EEPROM.h>

// ----------------------------- Структура для хранения данных -----------------------------
struct ClimateControlData {
  float save_temperature;
  float save_humidity;
};

struct PinTimerRotationData {
  unsigned long time_pin_on;
  unsigned long time_pin_off;
  bool timer_on_;
};
struct SettingsData {
  bool inkubatorLight;
};

// --- ---
struct Data_ {
  ClimateControlData climateControlData;
  PinTimerRotationData pinTimerRotationData;
  SettingsData settingsData;
};
// ========================================================================================

class Data {
private:
  int address = 0; 
  Data_ data_;
  void addDefault() {
    data_.climateControlData.save_temperature = 37.7;
    data_.climateControlData.save_humidity = 60;
    data_.pinTimerRotationData.time_pin_on = 3000;
    data_.pinTimerRotationData.time_pin_off = 3600000;
    data_.pinTimerRotationData.timer_on_ = false;
    data_.settingsData.inkubatorLight = true;

    // Также обновляем данные в EEPROM, чтобы они отражали обнуленные значения
    EEPROM.put(address, data_);
  }
public:
  Data(){
    EEPROM.get(address, data_); // Читаем данные из EEPROM по указанному адресу
    // Проверяем, были ли данные записаны в EEPROM ранее
    // Если нет, то устанавливаем значения по умолчанию
    if (
      data_.climateControlData.save_temperature != data_.climateControlData.save_temperature || 
      data_.climateControlData.save_humidity != data_.climateControlData.save_humidity ||
      data_.pinTimerRotationData.time_pin_on != data_.pinTimerRotationData.time_pin_on || 
      data_.pinTimerRotationData.time_pin_off != data_.pinTimerRotationData.time_pin_off || 
      data_.pinTimerRotationData.timer_on_ != data_.pinTimerRotationData.timer_on_ ||
      data_.settingsData.inkubatorLight != data_.settingsData.inkubatorLight
    ) {
      addDefault();
    }
  }
  // -------------------------------------------------------- set --------------------------------------------------------
  void setSave_temperature(float temperature) {
    if( 30.0 <= temperature && temperature <= 41.0 ){
      data_.climateControlData.save_temperature = temperature;
      // Сохраняем новое значение в EEPROM
      EEPROM.put(address, data_); // Указываем адрес EEPROM, где хотим сохранить структуру данных
    }
  }
  void setSave_humidity(float humidity) {
    if( 40 <= humidity && humidity <= 95 ){
      data_.climateControlData.save_humidity = humidity;
      // Сохраняем новое значение в EEPROM
      EEPROM.put(address, data_); // Указываем адрес EEPROM для сохранения второй структуры данных
    }
  }

  // -------- pinTimerRotationData ------- 
  void setPinTime_pin_on(unsigned long time_pin_on){
    if( 1800000 <= time_pin_on && time_pin_on <= 86400000 ){
      data_.pinTimerRotationData.time_pin_on = time_pin_on;
      // Сохраняем новое значение в EEPROM
      EEPROM.put(address, data_); // Указываем адрес EEPROM для сохранения третьей структуры данных
    }
  }
  void setPinTime_pin_off(unsigned long time_pin_off){
    if( 1800000 <= time_pin_off && time_pin_off <= 86400000 ){
      data_.pinTimerRotationData.time_pin_off = time_pin_off;
      // Сохраняем новое значение в EEPROM
      EEPROM.put(address, data_); // Указываем адрес EEPROM для сохранения третьей структуры данных
    }
  }
  void setPinTimer_on_(bool timer_on_){
    data_.pinTimerRotationData.timer_on_ = timer_on_;
    // Сохраняем новое значение в EEPROM
    EEPROM.put(address, data_); // Указываем адрес EEPROM для сохранения третьей структуры данных
  }

  // ------------- Settings -------------
  void setInkubatorLight(bool light){
    if(light != data_.settingsData.inkubatorLight){
      data_.settingsData.inkubatorLight = light;
      EEPROM.put(address, data_); // Указываем адрес EEPROM для сохранения третьей структуры данных
    }
  }
  // ==================================================================================================================

  // -------------------------------- get --------------------------------------
  float getSave_temperature() {
    return data_.climateControlData.save_temperature;
  }
  float getSave_humidity() {
    return data_.climateControlData.save_humidity;
  }

  // pinTimerRotationData
  unsigned long getPinTime_pin_on(){
    return data_.pinTimerRotationData.time_pin_on;
  }
  unsigned long getPinTime_pin_off(){
    return data_.pinTimerRotationData.time_pin_off;
  }
  bool getPinTimer_on_(){
    return data_.pinTimerRotationData.timer_on_;
  }

  // ------------- Settings -------------
  bool getInkubatorLight(){
    return data_.settingsData.inkubatorLight;
  }
  // ===========================================================================
};
