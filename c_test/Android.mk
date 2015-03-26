LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= set_recovery_flag.c
LOCAL_SHARED_LIBRARIES := libcutils libcutils liblog
LOCAL_STATIC_LIBRARIES += libmtdutils 

LOCAL_MODULE:= m_recovery

include $(BUILD_EXECUTABLE)
