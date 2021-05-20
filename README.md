# forsyde_wrapper
## command to compile:
g++ -I. -I/home/mohammad/Ros_Project/wrapper_ros/ForSyDe-SystemC/src -I/opt/ros/noetic/include -L/opt/ros/noetic/lib -Wl,-rpath=/opt/ros/noetic/lib main.cpp -o main -lsystemc -lm -lroscpp -lrosconsole -lrostime -lroscpp_serialization
