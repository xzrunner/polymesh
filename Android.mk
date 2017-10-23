INNER_SAVED_LOCAL_PATH := $(LOCAL_PATH)

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := polymesh

LOCAL_C_INCLUDES := \
	${CLIB_PATH} \
	${POLYMESH_SRC_PATH}/include \
	${POLYMESH_SRC_PATH}/include/polymesh \
	${SM_SRC_PATH} \
	${DS_SRC_PATH} \
	${MEMMGR_SRC_PATH}/include \

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,,$(shell find $(LOCAL_PATH) -name "*.cpp" -print)) \

include $(BUILD_STATIC_LIBRARY)	

LOCAL_PATH := $(INNER_SAVED_LOCAL_PATH)