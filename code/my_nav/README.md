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
rosrun map_server map_saver -f map
```

将map文件保存在工作区下目录，文件名为map.pgm和map.yaml

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

