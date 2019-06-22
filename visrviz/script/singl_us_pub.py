#!/usr/bin/env python

import rospy
from visualization_msgs.msg import Marker
from geometry_msgs.msg import Point
from sensor_msgs.msg import Range

range=0;


def transform_callback(data):
    global range
    range = data.range
    rospy.loginfo(range)
    
    

def line_pub():
    
    
    marker = Marker()
    marker.header.frame_id = "/us_sensor1"
    marker.type = marker.LINE_STRIP
    marker.action = marker.ADD
    

    # marker scale
    marker.scale.x = 0.03
    marker.scale.y = 0.03
    marker.scale.z = 0.03

    # marker color
    marker.color.a = 1.0
    marker.color.r = 1.0
    marker.color.g = 1.0
    marker.color.b = 0.0

    # marker orientaiton
    marker.pose.orientation.x = 0.0
    marker.pose.orientation.y = 0.0
    marker.pose.orientation.z = 0.0
    marker.pose.orientation.w = 1.0

    # marker position
    marker.pose.position.x = 0.0
    marker.pose.position.y = 0.0
    marker.pose.position.z = 0.0
    

    # Publish the Marker
    
    rospy.Subscriber('/u_sonic', Range, transform_callback)
    
    while not rospy.is_shutdown():
    # do whatever you want here
    	pub_line_min_dist.publish(marker)
    	global range
    # marker line points
    	marker.points = []
    # first point
    	first_line_point = Point()
    	first_line_point.x = range
    	first_line_point.y = -(range*(0.527/4))
    	first_line_point.z = 0.0
    	marker.points.append(first_line_point)
    # second point
   	second_line_point = Point()
    	second_line_point.x = range
    	second_line_point.y = range*(0.527/4)
    	second_line_point.z = 0.0
    	marker.points.append(second_line_point)
    	rospy.loginfo(second_line_point.y)
    	rospy.sleep(0.1)
if __name__ == '__main__':
    try:
        rospy.init_node('line_pub_example')
        pub_line_min_dist = rospy.Publisher('~line_min_dist', Marker, queue_size=1)
        rospy.loginfo('Publishing example line')
        line_pub()
        	
    except rospy.ROSInterruptException:
        pass
