int pin_trig[]={53,51,33,31,35,49},pin_echo[]={52,50,32,30,34,48};
unsigned  int duration=0;//for a 4 m (max range) duration <65536 hence 16bit
float distance=0;
void setup() {
  // put your setup code here, to run once:
for(int i=0;i<6;i++)
  {
      pinMode(pin_echo[i],INPUT);
      pinMode(pin_trig[i],OUTPUT);
      
  }Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int j=0;j<6;j++)
  {
  digitalWrite(pin_trig[j],LOW);
  delayMicroseconds(30);

  digitalWrite(pin_trig[j],HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig[j],LOW);
  delayMicroseconds(10);
 
  duration = pulseIn(pin_echo[j],HIGH);//time in uS
  if(duration>23429)
    distance=4.1;
  else  
    distance = duration*0.00017;
  Serial.print(j);
  Serial.print(distance);
  Serial.print("\n");
  }
  Serial.println("\n");
  delay(2000);
}
