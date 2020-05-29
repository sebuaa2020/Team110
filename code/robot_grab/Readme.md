# 抓取和放置调用方法

### 命令行调用

启动模拟器

调整机器人位置至待抓取物体之前

执行 “roslaunch	robot_grab	grab_action.launch” 启动抓取模块

执行 “rosrun	robot_grab	grab_client" 开始抓取任务

执行 ”roslaunch	robo_grab	pass_action.lauch" 启动放置模块

执行 “rosrun	robot_grab	grab_client" 开始放置任务



### ros文件内调用

发布指令至话题 ”/wpb_home/behaviors“上

抓取指令为 ”grab start"

放置指令为 “pass start”

可在相应的 "/wpb_home/pass_result"， "/wpb_home/grab_result" 监听流程结果