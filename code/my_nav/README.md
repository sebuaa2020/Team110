### My_Nav Package使用方法

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

