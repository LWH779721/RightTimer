# RightTimer
实现一个Linux 平台上精准的应用层定时器模块

# 定时器的重点
* 时间间隔的准确性

# 定时器实现的方式
* Linux Api 定时器 例如：alarm，settimer ... 
* 自己实现时间的判断,循环延时，获取时间和判断时间是否到期，性能肯定会差些，定时器的精准度依赖于延时的精准度

## 延时函数的精度
* 测试发现不同平台（window，Linux）甚至同一个平台 Linux，不同cpu（电脑，arm设备）延时函数的精度都是不同的。
* sleep, usleep, select, 等延时函数

# RightTimer
* RightTimer 采用Linux机制 timerfd，在内核中定时，测试精准度好于延时函数

## 采用技术
* timerfd, epoll, STL map

## 需求
1. 实现绝对时间定时，例如：2019/07/28 12:30 通知我
2. 实现定时器，例如：每隔10s 通知我； 10s 后通知我