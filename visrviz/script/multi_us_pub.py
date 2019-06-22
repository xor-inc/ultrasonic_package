#!/usr/bin/env python

import rospy
from visualization_msgs.msg import MarkerArray
from visualization_msgs.msg import Marker
from geometry_msgs.msg import Point
from alt_msgs.msg import alt_range

dist=[0,0,0,0,0,0,0,0]
frame_id=["us_sensor1","us_sensor2","us_sensor3","us_sensor4","us_sensor5","us_sensor6","us_sensor7","us_sensor8"]


def transform_callback(data):
    global dist
    dist = data.range
    

    
    

def line_pub():
    
    
    marker = Marker()
    markerarray=MarkerArray()
    

    # Publish the Marker
    
    rospy.Subscriber('/u_sonic', alt_range, transform_callback)
    
    while not rospy.is_shutdown():
    	marker = Marker()
	numofsensors=rospy.get_param("num_of_sensors")
	for i in range(numofsensors):
    		marker = Marker()
    		global dist
		global frame_id
		marker.header.frame_id = frame_id[i]
    		marker.type = marker.LINE_STRIP
    		marker.action = marker.ADD
		rospy.loginfo(i)
    

    # marker scale
    		marker.scale.x = 0.03
    		marker.scale.y = 0.03
    		marker.scale.z = 0.03

    # marker color
   		marker.color.a = 1.0
    		marker.color.r = 1.0
    		marker.color.g = 1.0
    		marker.color.b = 0.0
		marker.ns=frame_id[i]
		marker.id=i

    # marker orientaiton
    		marker.pose.orientation.x = 0.0
    		marker.pose.orientation.y = 0.0
    		marker.pose.orientation.z = 0.0
    		marker.pose.orientation.w = 1.0

    # marker position
    		marker.pose.position.x = 0.0
    		marker.pose.position.y = 0.0
    		marker.pose.position.z = 0.0
    
    # marker line points
    		marker.points = []
    # first point
    		first_line_point = Point()
    		first_line_point.x = dist[i]
    		first_line_point.y = -(dist[i]*(0.527/4))
    		first_line_point.z = 0.0
    		marker.points.append(first_line_point)
    # second point
   		second_line_point = Point()
    		second_line_point.x = dist[i]
    		second_line_point.y = dist[i]*(0.527/4)
    		second_line_point.z = 0.0
    		marker.points.append(second_line_point)
		markerarray.markers.append(marker)
   		pub_line_min_dist.publish(marker)
	rospy.loginfo("published markerArray")
	 	
    	rospy.sleep(0.01)
if __name__ == '__main__':
    try:
        rospy.init_node('line_pub_example')
        pub_line_min_dist = rospy.Publisher('~line_min_dist', Marker, queue_size=1)
        rospy.loginfo('Publishing example line')
        line_pub()
        	
    except rospy.ROSInterruptException:
        pass
