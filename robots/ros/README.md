
# ROS 1

## 1. Concept
### 1.1. Core Architecture
![ROS master](.images/README-ros-master.png)

(ROS Master, roscore and nodes)
- package: (what is node)
- node: (what is node)

### 1.2. Catkin
```bash
(how to construct a ROS project)
```

### 1.3. Node
![ROS Node](.images/README-node.png)
(describe what node is)
- nodes can be written in either python or cpp
- python scripts should contain #!/usr/bin/env python
## 2. Guide

### 2.1. Create a workspace

### 2.2. Development Cycle
```bash
# 1. create a workspace
catkin_make
source devel/setup.zsh

# 2. create a package
# catkin_create_pkg <pkg name> <dependencies>
cd src
catkin_create_pkg <package name> roscpp rospy std_msgs

# 3. create nodes
cd noetic
mkdir scripts
# write nodes in .py or .cpp

# 4. build nodes
cd <workspace>
catkin_make
source devel/setup.zsh

# 5. run nodes
rosrun <package name> <node name>

# 6. view nodes
rosnode list
rosnode info /node_name
```


 