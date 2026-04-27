# ROS 1

Concise ROS 1 / Noetic notes for this catkin workspace.

## 1. Concepts
### 1.1. Core Architecture

![ROS master](.images/README-ros-master.png)

- **ROS Master**: registry where nodes find each other. Started by `roscore`.
- **roscore**: starts the master, parameter server, and `/rosout`.
- **Package**: unit of ROS code distribution. Contains nodes, dependencies, build config, messages, services, and launch files.
- **Node**: one running process in the ROS graph. Nodes register with the master, then communicate directly.
- **Topic**: named publish/subscribe message stream.
- **Service**: request/response call.
- **Parameter**: runtime config stored on the parameter server.

`roscore` usually listens on port `11311`. Nodes also expose XML-RPC URIs on dynamic ports, so seeing a random port such as `39625` is normal.

### 1.2. Catkin
Catkin is the ROS 1 build system.

```text
workspace/
  src/
    package_name/
      package.xml
      CMakeLists.txt
      scripts/
      src/
  build/
  devel/
```

- `package.xml`: package metadata and dependencies.
- `CMakeLists.txt`: build rules for C++ nodes, Python scripts, messages, services, and libraries.
- `devel/setup.zsh`: generated environment setup file.

### 1.3. Nodes
![ROS Node](.images/README-node.png)

- Python scripts usually live in `scripts/`, use `#!/usr/bin/env python3`, and must be executable.
- C++ nodes must be added to `CMakeLists.txt`, linked to `${catkin_LIBRARIES}`, and built with `catkin_make`.
- `rosrun` uses the executable name exactly: Python keeps `.py`; compiled C++ usually does not.

## 2. Quick Start
### 2.1. Create Workspace and Package
```bash
mkdir -p ~/workspace/src
cd ~/workspace
catkin_make
source devel/setup.zsh

cd src
catkin_create_pkg tutorial roscpp rospy std_msgs
```

```text
src/tutorial/
  package.xml
  CMakeLists.txt
  scripts/
```

### 2.2. Build and Source
```bash
# from the workspace root
catkin_make
source devel/setup.zsh
```

Use `setup.zsh` for zsh. Use `setup.bash` for bash.

Re-run `source devel/setup.zsh` when opening a new terminal, after creating a package, or after changing package dependencies/interfaces. Normal node code edits do not usually need re-sourcing.

### 2.3. Run Nodes
```bash
# terminal 1
roscore
```

```bash
# terminal 2
# from this workspace root
source devel/setup.zsh

# Python node
chmod +x src/tutorial/scripts/first_node.py
rosrun tutorial first_node.py

# C++ node
catkin_make
rosrun tutorial second_node
```

```cmake
# src/tutorial/CMakeLists.txt
add_executable(second_node scripts/second_node.cpp)
target_link_libraries(second_node ${catkin_LIBRARIES})
```

### 2.4. Inspect ROS
```bash
# packages
rospack list
rospack find tutorial

# nodes
rosnode list
rosnode info /first_node
```

## 3. Communication (Topic)
Topics use a publish/subscribe model. Publishers send typed messages to a topic; subscribers register callbacks for messages on that topic.

### 3.1. With Nodes
#### Python
```python
from std_msgs.msg import String

publisher = rospy.Publisher("chatter_py", String, queue_size=10)
subscriber = rospy.Subscriber("chatter_py", String, callback)

def callback(msg):
    rospy.loginfo(msg.data)
```

#### C++

```cpp
#include <std_msgs/String.h>

ros::NodeHandle nh;  // Creates publishers/subscribers connected to the ROS graph.
ros::Publisher publisher = nh.advertise<std_msgs::String>("chatter_cpp", 10);
ros::Subscriber subscriber = nh.subscribe("chatter_cpp", 10, chatterCallback);

void chatterCallback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("%s", msg->data.c_str());
}
```

#### Spinning and Loops
Use `rospy.spin()` / `ros::spin()` for nodes that mostly wait for callbacks. Use `while not rospy.is_shutdown()` / `while (ros::ok())` with `Rate` for nodes that publish or do repeated work. In C++, call `ros::spinOnce()` inside the loop if the same node also needs to process callbacks.

#### Inspect Topics
```bash
rostopic list
rostopic info /chatter_cpp
rostopic echo /chatter_cpp
```

#### Anonymous Nodes
Node names must be unique. If you want to run multiple copies of the same Python node, use `anonymous=True`:

```python
rospy.init_node("publisher", anonymous=True)
```

In C++, use `ros::init_options::AnonymousName`:

```cpp
ros::init(argc, argv, "publisher_cpp", ros::init_options::AnonymousName);
```

### 3.2. With Services

## 4. Customization

## 5. Common Issues
### `rosrun` cannot find a node
```bash
rosrun tutorial first_node.py   # Python script filename
rosrun tutorial second_node     # C++ executable name
chmod +x src/tutorial/scripts/first_node.py
```

### `/usr/bin/env: 'python': No such file or directory`
```python
#!/usr/bin/env python3
```

### VS Code cannot find `<ros/ros.h>`
ROS include paths come from catkin/CMake, not from the `.cpp` file alone. A C++ file should be bound to a CMake target:

```cmake
add_executable(testone scripts/testone.cpp)
target_link_libraries(testone ${catkin_LIBRARIES})
```

Then rebuild so the IDE/build system sees the target:

```bash
catkin_make -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

Then set:

```json
"C_Cpp.default.compileCommands": "${workspaceFolder}/build/compile_commands.json"
```

### `sudo: unable to resolve host noetic`
This is a container hostname warning from `sudo`, not a ROS error. Avoid `sudo` for files owned by your user:

```bash
chmod +x src/tutorial/scripts/first_node.py
```
