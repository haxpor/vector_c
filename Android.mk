LOCAL_PATH := $(call my-dir)

###########################
#
# vector shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := vector

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := src/vector.c

LOCAL_CFLAGS += -Wall -std=c99
LOCAL_LDLIBS := 

ifeq ($(NDK_DEBUG),1)
    cmd-strip :=
endif

include $(BUILD_SHARED_LIBRARY)

###########################
#
# vector static library
#
###########################

LOCAL_MODULE := vector_static

LOCAL_MODULE_FILENAME := libvector

LOCAL_CFLAGS := -Wall -std=c99
LOCAL_LDLIBS := 
LOCAL_EXPORT_LDLIBS := 

include $(BUILD_STATIC_LIBRARY)
