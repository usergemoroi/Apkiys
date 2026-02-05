#ifndef ANDROID_INPUT_H
#define ANDROID_INPUT_H

#include <cstdint>
#include <stddef.h>

struct AInputEvent;
typedef struct AInputEvent AInputEvent;

enum {
    AINPUT_EVENT_TYPE_KEY = 1,
    AINPUT_EVENT_TYPE_MOTION = 2,
};

enum {
    AKEY_EVENT_ACTION_DOWN = 0,
    AKEY_EVENT_ACTION_UP = 1,
    AKEY_EVENT_ACTION_MULTIPLE = 2,
};

enum {
    AMETA_CTRL_ON = 0x1000,
    AMETA_SHIFT_ON = 0x1,
    AMETA_ALT_ON = 0x2,
    AMETA_META_ON = 0x10000,
};

enum {
    AMOTION_EVENT_ACTION_MASK = 0xff,
    AMOTION_EVENT_ACTION_DOWN = 0,
    AMOTION_EVENT_ACTION_UP = 1,
    AMOTION_EVENT_ACTION_MOVE = 2,
    AMOTION_EVENT_ACTION_CANCEL = 3,
    AMOTION_EVENT_ACTION_OUTSIDE = 4,
    AMOTION_EVENT_ACTION_POINTER_DOWN = 5,
    AMOTION_EVENT_ACTION_POINTER_UP = 6,
    AMOTION_EVENT_ACTION_HOVER_MOVE = 7,
    AMOTION_EVENT_ACTION_SCROLL = 8,
    AMOTION_EVENT_ACTION_HOVER_ENTER = 9,
    AMOTION_EVENT_ACTION_HOVER_EXIT = 10,
    AMOTION_EVENT_ACTION_BUTTON_PRESS = 11,
    AMOTION_EVENT_ACTION_BUTTON_RELEASE = 12,
    AMOTION_EVENT_ACTION_POINTER_INDEX_MASK = 0xff00,
    AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT = 8,
};

enum {
    AMOTION_EVENT_TOOL_TYPE_UNKNOWN = 0,
    AMOTION_EVENT_TOOL_TYPE_FINGER = 1,
    AMOTION_EVENT_TOOL_TYPE_STYLUS = 2,
    AMOTION_EVENT_TOOL_TYPE_MOUSE = 3,
    AMOTION_EVENT_TOOL_TYPE_ERASER = 4,
};

enum {
    AMOTION_EVENT_BUTTON_PRIMARY = 1,
    AMOTION_EVENT_BUTTON_SECONDARY = 2,
    AMOTION_EVENT_BUTTON_TERTIARY = 4,
};

enum {
    AMOTION_EVENT_AXIS_X = 0,
    AMOTION_EVENT_AXIS_Y = 1,
    AMOTION_EVENT_AXIS_PRESSURE = 2,
    AMOTION_EVENT_AXIS_SIZE = 3,
    AMOTION_EVENT_AXIS_TOUCH_MAJOR = 4,
    AMOTION_EVENT_AXIS_TOUCH_MINOR = 5,
    AMOTION_EVENT_AXIS_TOOL_MAJOR = 6,
    AMOTION_EVENT_AXIS_TOOL_MINOR = 7,
    AMOTION_EVENT_AXIS_ORIENTATION = 8,
    AMOTION_EVENT_AXIS_VSCROLL = 9,
    AMOTION_EVENT_AXIS_HSCROLL = 10,
};

#ifdef __cplusplus
extern "C" {
#endif

int32_t AInputEvent_getType(const AInputEvent* event);
int32_t AKeyEvent_getAction(const AInputEvent* key_event);
int32_t AKeyEvent_getKeyCode(const AInputEvent* key_event);
int32_t AKeyEvent_getScanCode(const AInputEvent* key_event);
int32_t AKeyEvent_getMetaState(const AInputEvent* key_event);
int32_t AMotionEvent_getAction(const AInputEvent* motion_event);
int32_t AMotionEvent_getToolType(const AInputEvent* motion_event, size_t pointer_index);
int32_t AMotionEvent_getButtonState(const AInputEvent* motion_event);
size_t AMotionEvent_getPointerCount(const AInputEvent* motion_event);
int32_t AMotionEvent_getPointerId(const AInputEvent* motion_event, size_t pointer_index);
float AMotionEvent_getX(const AInputEvent* motion_event, size_t pointer_index);
float AMotionEvent_getY(const AInputEvent* motion_event, size_t pointer_index);
float AMotionEvent_getAxisValue(const AInputEvent* motion_event, int32_t axis, size_t pointer_index);

int32_t ANativeWindow_getWidth(void* window);
int32_t ANativeWindow_getHeight(void* window);

#ifdef __cplusplus
}
#endif

#endif
