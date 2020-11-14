#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Joy
from drive.msg import drive_msg
from numpy import interp


 #if turned on the direction is reversed

pwm=[0,0,0,0]
 
drivex=drive_msg()

def find_pwmtest4(msg):
    factor = 0.7
    if(msg.buttons[6]==0):
        
        if(msg.axes[2]<1):
            pwmtotal=interp(msg.axes[2],[1,-1],[0,255])
        else:
            pwmtotal=(-1*interp(msg.axes[5],[1,-1],[0,255]))

        #pwmdir=interp(msg.axes[0],[-1,1],[-155,155])
	    if (msg.buttons[3] == 1):
	        factor = 1
	    pwmdir=(msg.axes[0] * pwmtotal * factor * -1)
        #rospy.loginfo(pwmdir)
        #rospy.loginfo(pwmtotal)
        pwm[2]=0
        pwm[3]=0
        pwm[0]=0
        pwm[1]=0
        if(pwmtotal>=0):
            leftpwm=pwmtotal+pwmdir
            rightpwm=pwmtotal-pwmdir
        else:
            leftpwm=pwmtotal-pwmdir
            rightpwm=pwmtotal+pwmdir
        if(leftpwm<0):
            pwm[0]=1
            leftpwm = leftpwm * -1
        if(rightpwm<0):
            pwm[1]=1
            rightpwm = rightpwm * -1
        if(rightpwm>255):
            rightpwm=255
        if(leftpwm>255):
            leftpwm=255
        pwm[2] = leftpwm 
        pwm[3] = rightpwm
    
        '''if(pwmtotal<0):
            pwm[2]=1
	    pwm[3]=1
	    pwmtotal=pwmtotal*-1
        if(pwmdir>=0):
            pwm[0] = pwmtotal - pwmdir
            pwm[1]= pwmtotal
	if(pwmdir<0):
	    pwm[0]= pwmtotal
	    pwm[1]= pwmtotal + pwmdir'''

	    if(msg.buttons[4]==1):
	        pwm[0]=200
	        pwm[1]=200	
	        pwm[2]=1
	        pwm[3]=0	
	    if(msg.buttons[5]==1):
	        pwm[0]=200
	        pwm[1]=200
	        pwm[2]=0
	        pwm[3]=1
    else:
	    pwm[0]=0
        pwm[1]=0	
	    pwm[2]=0
	    pwm[3]=0

    #rospy.loginfo("left  pwm %f",pwm[0])
    #rospy.loginfo("right pwm %f",pwm[1])
    rospy.loginfo(pwm)

def find_pwmtest3(msg):
    '''dir_n = 0 
   
    pwm[2] = dir_n 
    pwmtotal=interp(msg.axes[2],[-1,1],[-255,255])
    
    if (pwmtotal < 0):
	dir_n = 1
 	pwm[2] = dir_n  
        pwmtotal=pwmtotal*-1
    if (msg.buttons[4] == 1):
       pwm[0]=pwmtotal
    if (msg.buttons[4] == 0):
       pwm[0]=0   
    if (msg.buttons[5] == 1):
       pwm[1]=pwmtotal
    if (msg.buttons[5] == 0):
       pwm[1]=0
      '''
    factor = 0.7
    if(msg.buttons[6]==0):
        pwndir=0
        pwmtotal=interp(msg.axes[1],[-1,1],[-255,255])
        #pwmdir=interp(msg.axes[0],[-1,1],[-155,155])
	if (msg.buttons[0] == 1):
	   factor = 1
	pwmdir=msg.axes[0] * pwmtotal * factor
        #rospy.loginfo(pwmdir)
        #rospy.loginfo(pwmtotal)
        pwm[2]=0
        pwm[3]=0
        if(pwmtotal<0):
            pwm[2]=1
	    pwm[3]=1
	    pwmtotal=pwmtotal*-1
        if(pwmdir>=0):
            pwm[0] = pwmtotal - pwmdir
            pwm[1]= pwmtotal
	if(pwmdir<0):
	    pwm[0]= pwmtotal
	    pwm[1]= pwmtotal + pwmdir
	if(msg.buttons[4]==1):
	    pwm[0]=200
	    pwm[1]=200	
	    pwm[2]=1
	    pwm[3]=0	
	if(msg.buttons[5]==1):
	    pwm[0]=200
	    pwm[1]=200
	    pwm[2]=0
	    pwm[3]=1
    else:
	    pwm[0]=0
            pwm[1]=0	
	    pwm[2]=0
	    pwm[3]=0

    #rospy.loginfo("left  pwm %f",pwm[0])
    #rospy.loginfo("right pwm %f",pwm[1])
    rospy.loginfo(pwm)

def find_pwmtest2(msg):
    dir_n = 0 
   
    pwm[2] = dir_n 
    pwmtotal=interp(msg.axes[2],[-1,1],[-255,255])
    
    if (pwmtotal < 0):
	dir_n = 1
 	pwm[2] = dir_n  
        pwmtotal=pwmtotal*-1
    if (msg.buttons[4] == 1):
        pwm[0]=pwmtotal
    if (msg.buttons[4] == 0):
        pwm[0]=0   
    if (msg.buttons[5] == 1):
        pwm[1]=pwmtotal
    if (msg.buttons[5] == 0):
        pwm[1]=0
      
    #rospy.loginfo("left  pwm %f",pwm[0])
    #rospy.loginfo("right pwm %f",pwm[1])
    rospy.loginfo(pwm)
	

def find_pwmtest1(msg): #1st case when 2 pwm valus are send for left ans right seperately
    pwm=[0,0]
    valL= msg.axes[1]
    valR= msg.axes[2]
    pwm[0]=interp(valL,[0,1],[0,255])
    pwm[1]=interp(valR,[0,1],[0,255])
    rospy.loginfo("left  pwm %f",pwm[0])
    rospy.loginfo("right pwm %f",pwm[1])

#def transform(a):
#    point.x = pwm[0] 
#    point.y = pwm[1]
#    point.z = pwm[2]  

def callback(msg):
    rate = rospy.Rate(100)
    find_pwmtest4(msg)
    drivex.lpwm = pwm[0] 
    drivex.rpwm = pwm[1]
    drivex.ldir = bool(pwm[2])
    drivex.rdir = bool(pwm[3])
    pub = rospy.Publisher('rover_drive', drive_msg ,queue_size=10)  
    pub.publish(drivex)
    rate.sleep()
    #rospy.loginfo("I heard %f",msg.buttons[])
    

def listener():
    rospy.init_node('listener_joy', anonymous=True)
    rospy.Subscriber("joy_for_drive", Joy, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
