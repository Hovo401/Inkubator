class TH_Controller{
  private:
    unsigned char t_Pin;
    unsigned char h_Pin;
  public:
    TH_Controller(unsigned char t_Pin_, unsigned char h_Pin_){
      t_Pin = t_Pin_;
      h_Pin = h_Pin_;
      pinMode(t_Pin, OUTPUT);
      pinMode(h_Pin, OUTPUT);
    }
    void loop(){
      if(data.getSave_temperature() < 37.7){
        digitalWrite(t_Pin, HIGH);
      }else{
        digitalWrite(t_Pin, LOW);
      }
    }
};