#!/system/bin/sh
#=========================================
#Author     : Caesar - youku
#Description: save log
#=========================================
# 在init.方案.rc下加入如下语句
# service  catlog /system/bin/busybox  sh  /system/bin/cat_log.sh
#     disabled
#     oneshot
#
# on property:sys.boot_completed=1
#   start catlog
#

echo 1 > /proc/sys/kernel/panic

LOG_DIR="/mnt/sdcard/k1_log"
LAST_LOG_DIR="/mnt/sdcard/k1_log/last"

if [ ! -d "$LOG_DIR" ];then
   mkdir $LOG_DIR
fi

if [ ! -d "$LAST_LOG_DIR" ];then
   mkdir $LAST_LOG_DIR
fi

#保存上次开机之后的log
mv $LOG_DIR/*panic.log $LAST_LOG_DIR/panic.log
mv $LOG_DIR/*kmsg.log $LAST_LOG_DIR/kmsg.log
mv $LOG_DIR/*logcat.log $LAST_LOG_DIR/logcat.log


DATE=$(date +%Y%m%d%H%M)

cat /proc/last_kmsg > $LOG_DIR/"$DATE"_panic.log

echo "------start kmsg log------"
cat /proc/kmsg > $LOG_DIR/"$DATE"_kmsg.log &

echo "------start logcat log------"
logcat -v time -n 1 -f $LOG_DIR/"$DATE"_logcat.log -r10240

