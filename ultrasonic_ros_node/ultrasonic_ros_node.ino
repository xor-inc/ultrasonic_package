/* sensor_msgs/Range
 *  uint8 ULTRASOUND=0
    uint8 INFRARED=1
    std_msgs/Header header
      uint32 seq
      time stamp
      string frame_id
    uint8 radiation_type
    float32 field_of_view
    float32 min_range
    float32 max_range
    float32 range
 * with 'roscore' running  
 * 'rosrun rosserial_python serial_node.py /dev/ttyUSB0'
 * publishes range with topic 'u_sonic'
 * !!!!float32 field_of_view and uint8 radiation_type !!! are to be studied
 */

#include <ros.h>
#include <sensor_msgs/Range.h>
const int pin_trig = 6,pin_echo=7;
unsigned short int duration;//for a 4 m (max range) duration <65536 hence 16bit
float distance;
char frame[12]="UltraSonic";

ros::NodeHandle  nh;

sensor_msgs::Range data;
ros::Publisher data_pub("u_sonic", &data);
 int sequence =0;



void setup()
{
  nh.initNode();
  nh.advertise(data_pub);
  pinMode(pin_trig,OUTPUT);
  pinMode(pin_echo,INPUT);
 
  data.header.frame_id=frame;
 
  data.field_of_view = 3.14;
  data.min_range = 0.02;
  data.max_range = 3.5;
  
  
}

void loop()
{ data.header.seq = sequence;
  data.header.stamp = nh.now();
  digitalWrite(pin_trig,LOW);
  delayMicroseconds(2);

  digitalWrite(pin_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig,LOW);
  delayMicroseconds(15);
 
  duration = pulseIn(pin_echo,HIGH);//time in uS
  distance = duration*0.00034/2;
  data.range=distance;
  
  data_pub.publish( &data );
  nh.spinOnce();
  delay(200);
  sequence++;
}
