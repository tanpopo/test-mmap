LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#http://developer.android.com/intl/ja/ndk/guides/application_mk.html
#Starting from Android 4.1 (API level 16), Android's dynamic linker
#supports position-independent executables (PIE). From Android 5.0
# (API level 21), executables require PIE.
APP_PLATFORM := android-16 #if APP_PLATFORM>=16, APP_PIE is set to true
#APP_PLATFORM := android-21
APP_ABI := armeabi armeabi-v7a

LOCAL_MODULE    := test-mmap
LOCAL_SRC_FILES := test-mmap.c

include $(BUILD_EXECUTABLE)
