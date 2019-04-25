#!/bin/bash
cd ~/catkin_ws/build/choreonoid_ros/build/choreonoid-master
make -j4 install
ls -lt ~/catkin_ws/devel/lib/lib*
