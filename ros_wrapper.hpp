

#include <forsyde.hpp>

#ifndef ROS_WRAPPERS_HPP
#define ROS_WRAPPERS_HPP

#include <iostream>
#include <ros/ros.h>
#include "std_msgs/String.h"
#include "sy_process.hpp"
#include "abst_ext.hpp"
#include <stdio.h>

/*void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}*/


namespace ForSyDe
{

namespace SY
{

using namespace sc_core;

template <typename T0, typename T1>
class roswrap : public sy_process

{
public:
    SY_in<T1>  iport1;       
    SY_out<T0> oport1; 
         
roswrap(const sc_module_name& _name, const std::string& topic_name) : 
sy_process(_name), iport1("iport1"), oport1("oport1"), topic_name(topic_name)

    {
#ifdef FORSYDE_INTROSPECTION
        arg_vec.push_back(std::make_tuple("topic_name",topic_name));
#endif
    }

    std::string forsyde_kind() const {return "SY::roswrap";}

private:

std::string topic_name;
std::string _name;
abst_ext<T1>* ival1;

T0* oval;
std::istringstream ival1_str;
ros::Publisher chatter_pub;


   
    void init()
    {

      oval = new T0;
      ival1 = new abst_ext<T1>;
      int argc;
		  char **argv;

      ival1_str.str(topic_name);
      
		  ros::init(argc, argv, "talker");
      ros::NodeHandle n;
      chatter_pub = n.advertise<std_msgs::String>(ival1_str.str(), 1000);
      //ros::Rate loop_rate(10);
      //loop_rate.sleep();
      //ros::init(argc, argv, "receiver");
      
      
      
		  //ros::Subscriber sub ;
    }
    
    void prep()
    {
      ros::Rate loop_rate(0.5);
      while(ros::ok())
      {

      
      *ival1 = iport1.read();
      std_msgs::String msg; 
      std::stringstream ss;
      ss << *ival1;
      msg.data = ss.str(); 
      ROS_INFO("%s", msg.data.c_str());

      chatter_pub.publish(msg);
      ros::spinOnce();
      loop_rate.sleep();
      wait(SC_ZERO_TIME);
      
      }
      
      
      
      //ival_str<<unsafe_from_abst_ext(*ival1);

		  //sub = n.subscribe("receive", 1000, chatterCallback);
      
      
    }
    
    void exec() {}
    
    void prod()
    {
    
      WRITE_MULTIPORT(oport1, abst_ext<T0>(*oval))
    }
    
    void clean()
    {
      delete ival1;
      delete oval;
      ros::shutdown();
    }
    
};



template <class T0, template <class> class OIf,
          class T1, template <class> class I1If>
inline roswrap<T0,T1>* make_roswrap(const std::string& pName,
    const std::string& tName,
    OIf<T0>& outS,
    I1If<T1>& inp1S
    )
{
    auto p = new roswrap<T0,T1>(pName.c_str(), tName);
    
    (*p).iport1(inp1S);
    (*p).oport1(outS);
    
    return p;
}




}
}

#endif












