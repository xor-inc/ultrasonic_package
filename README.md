# ultrasonic_package
#installation
  1.download and catkin_make "rosserial" package in your workspace(not included)
  2.place the 'alt_msgs' and 'visrviz' in your catkin workspace and catkin_make
  3.with "ros rosserial_arduino make_libraries.py <sketchbook>/libraries/" command all ros files will be made for arduino.
  4.place the generated headers in step 3.(mostly with a folder name 'ros_lib') in arduino libraray
  5.burn the 'us_rosnode_mega' to arduino
  6.roslaunch rosserial_python serialnode.py
  
  to run code without error burn the arduino code each time as the parameters are changed
  
  
