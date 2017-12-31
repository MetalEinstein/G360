
// We include the necessary libraries
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "geometry_msgs/Twist.h" // The topic msg type

ros::Publisher vel_pub; // We publish a topic called vel_pub

// To move the turtlebot we set up a function that can be reference outside the main function
void move(double speed, double distance, bool goingForward); // Move forward
char awnser = 'w';

using namespace std;

int main(int argc, char *argv[]){

  ros::init(argc, argv, "turtlebot_goto"); // we initialize a node called "turtlebot_goto"
  ros::NodeHandle n;                           // Name of the topic
  vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/navi", 100);

  cout << "Let's see how fast this thing can go\n" << '\n';
  cout << "Press w when you are ready:  ";
  cin >> awnser;

  while(awnser = 'w'){
    move(1000, 1000, 1);
  }

}

void move(double speed, double distance, bool goingForward){

  geometry_msgs::Twist message; // We define the msg and assign a reference

  // If goingForward == True we move the robot forward.
   if (goingForward){
	   message.linear.x =abs(speed);
   }

   // Else we move it backwards
   else{
	   message.linear.x =-abs(speed);
   }

     message.linear.y =0;
     message.linear.z =0;

   // We set a random angular velocity in the y-axis
     message.angular.x = 0;
     message.angular.y = 0;
     message.angular.z = 0;

   double t0 = ros::Time::now().toSec();
   double current_distance = 0.0;
   ros::Rate loop_rate(100);
   do{
	   vel_pub.publish(message);
	   double t1 = ros::Time::now().toSec();
	   current_distance = speed * (t1-t0);
	   ros::spinOnce();
	   loop_rate.sleep();

   }while(current_distance<distance);
   message.linear.x = 0;
   vel_pub.publish(message);
}
