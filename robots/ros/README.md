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

## 2. Guide
### 2.1. Create Workspace and Package
```bash
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws
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
source devel/setup.zsh
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
rospack list-names
rospack find tutorial

# nodes
rosnode list
rosnode info /first_node

# master
echo $ROS_MASTER_URI
```

## 3. Common Issues
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
