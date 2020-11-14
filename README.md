# 简介
* TimeWalker -- Time walker(时间行者)
* Linux平台上通过内核机制实现的应用层高精度定时器模块。

# 初始需求
1. 工作中需要实现绝对时间定时器，例如：2020年8月5号，下周五叫我等，但是大部分第三方库都只能实现相对时间定时器，需要自己扩展，因此实现此库

## 简介
* 在Linux平台上实现定时任务，有些任务对精度要求不高，例如：每隔一段时间播放一首歌，任务内容对精准度要求不高，稍微延时一段时间，用户感受也不是非常深刻；
但是有些任务例如：LED灯的循环变幻，如果时间精度不够，LED变幻效果就不流畅，本项目就是想实现一个高精度的定时器模块。
* 高精度定时器的实现重点：延时的准确性

## 定时器实现的方式
* Linux Api 定时器 例如：alarm，settimer ...， 其定时精度是受内核 hz影响
* 自己实现延时时间的判断, 使用延时函数进行延时，获取时间和判断当前时间是否到期，需要做大量判断，性能肯定会差些，定时器的精准度依赖于延时函数的精准度，延时函数的精准度实际上也是受内核 hz影响
* RightTimer 采用Linux机制 timerfd，定时处理由内核实现，本质上是内核层的高精度定时器实现的，由硬件实现，测试精准度远远好于延时函数

## 延时函数的精度
* 测试发现不同平台（window，Linux）甚至同一个平台 Linux，不同cpu（电脑，arm设备）延时函数的精度都是不同的。
* sleep, usleep, select, nanosleep 等延时函数受内核 hz影响

## 涉及技术
* timerfd, epoll, STL map
