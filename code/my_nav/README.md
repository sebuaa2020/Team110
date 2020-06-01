### My_Nav Package使用方法

* 手动建图

```
roslaunch my_nav my_slam.launch
```

通过该launch文件进行手动建图，运行launch文件后会打开rviz界面，接着：

```
rosrun wpr_simualtion keyboard_vel_ctrl
```

使用该命令通过手动控制机器人移动，在移动过程中在rviz上显示扫描的地图

当地图扫描完毕后，运行：

```
rosrun map_server map_saver -f src/my_nav/maps/map
```

将map文件保存在my_nav包中的maps目录下，文件名为map.pgm和map.yaml

* 设定航点

首先运行

```
roslaunch my_nav add_waypoints.launch
```

在rviz界面上，点击addwaypoint按钮在地图上设置航点

航点设置完毕后，运行

```
rosrun my_nav save_waypoints
```

保存航点，保存文件为waypoints.xml，默认路径为本包的目录下（可在源文件中修改）

#### 导航部分

在使用定向移动和定点移动功能前，需要运行my_navigation.launch文件

```
roslaunch my_nav my_navigation.launch
```

* 定向移动

控制机器人向某个方向移动一定的距离

示例：

```
rosrun my_nav simple_move direction [meters]
```

其中参数direction为方向，取值为1，2，3，4中的一个，分别代表上下左右四个方向，

参数meters为可选参数，表示移动的距离（单位：m），如果不输入该参数则默认为1米

* 定点移动

给定点的坐标等信息，控制机器人向该点避障移动

示例：

```
rosrun my_nav move_to_goal wp_name
```

其中，wp_name为该点的名称，点的名称储存在waypoint.xml文件中

