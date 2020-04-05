#!/bin/bash

pid=`ps -la | grep 21sh | awk -F" " '{print $2}'`
echo $pid
pid=`echo $pid | awk -F" " '{print $1}'`
echo $pid
leaks $pid