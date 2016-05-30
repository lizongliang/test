# Copyright 2005 The Android Open Source Project
#
#

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	res_pack.cpp \
	crc32.cpp

#LOCAL_C_INCLUDES := $(JNI_H_INCLUDE) \
			$(TOP)/frameworks/native/services \
			$(TOP)/frameworks/native/include \
			build/libs/host/include

LOCAL_SHARED_LIBRARIES += libutils  libcutils
#LOCAL_STATIC_LIBRARIES := libhost
LOCAL_MODULE := updatelogo
#LOCAL_MODULE := libupdatelogo
#LOCAL_ACP_UNAVAILABLE := true

#include $(BUILD_SHARED_LIBRARY)
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

