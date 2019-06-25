/*
  uint32 seq
  time stamp
  string[] frame_id
  float32 field_of_view
  float32 min_range
  float32 max_range
  float32[] range
*/
#include<ros.h>
#include<alt_msgs/alt_range.h>

int pin_trig[12],pin_echo[12];//53,51,33 52,50,32
ros::NodeHandle nh;

alt_msgs::alt_range xyz;
unsigned long duration;//for a 4 m (max range) duration <65536 hence 16bit
float distance;
long int sequence =0;
ros::Publisher data_pub("u_sonic",&xyz);
float range[]={1,2,3,4,5,6,7,8};
int num_of_sensors=3,count=0;
char *temps[]={"us_sensor1","us_sensor2","us_sensor3","us_sensor4","us_sensor5","us_sensor6","us_sensor7","us_sensor8","us_sensor9","us_sensor10","us_sensor11","us_sensor12"};

void getparam()
{
  while(!nh.getParam("num_of_sensors", &num_of_sensors, 1))
   {
    if(count>2)
      break;
    count++;  
   }count=0;
  
   while(!nh.getParam("/trigger_pins",pin_trig,num_of_sensors))
  {
    if(count>2)
      break;
    count++;  
   }count=0;
   
   while(!nh.getParam("/echo_pins",pin_echo,num_of_sensors))
  {
    if(count>2)
      break;
    count++;  
   }count=0;
   
   xyz.range_length=num_of_sensors;
  xyz.frame_id_length=num_of_sensors;
}
void setup() {
  nh.initNode();
  nh.advertise(data_pub);
   getparam();
  
  
  for(int i=0;i<num_of_sensors;i++)
  {
      pinMode(pin_echo[i],INPUT);
      pinMode(pin_trig[i],OUTPUT);
  }
  
  
  
  
  xyz.field_of_view = 3.14;
  xyz.min_range = 0.02;
  xyz.max_range = 4;
  xyz.range_length=num_of_sensors;
  xyz.frame_id_length=num_of_sensors;
  
  
 
  xyz.frame_id=temps;
  
  
  
  
  
  
}

void loop() {
  
   
  for(int j=0;j<num_of_sensors;j++)
  {
  digitalWrite(pin_trig[j],LOW);
  delayMicroseconds(2);

  digitalWrite(pin_trig[j],HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig[j],LOW);
  
 
  duration = pulseInLong(pin_echo[j],HIGH,25000UL);//time in uS
   
  distance = duration*0.00017;
  
  range[j]=distance;
  delayMicroseconds(25000-duration);
  }
 
xyz.range=range;  
xyz.stamp = nh.now();  
xyz.seq= sequence;  
data_pub.publish( &xyz );

nh.spinOnce();

sequence++;

}
