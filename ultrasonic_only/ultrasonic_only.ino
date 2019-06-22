/*for a distance for 4m the time input in microsec <65,535 hence unsigned short int
 * should be callibrated according to temperature
 */
const int pin_trig = 6,pin_echo=7;
unsigned short int duration;
float distance;
void setup() {

pinMode(pin_trig,OUTPUT);
pinMode(pin_trig,INPUT);
Serial.begin(115200);
}
void loop()
{
  digitalWrite(pin_trig,LOW);
  delayMicroseconds(2);

  digitalWrite(pin_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig,LOW);
 
  duration = pulseIn(pin_echo,HIGH);//time in uS
  distance = duration*0.00034/2;
  
  Serial.print("D=:");
  Serial.println(distance);
  Serial.print("t=:");
  Serial.println(duration);
 

  
}
