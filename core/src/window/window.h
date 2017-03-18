#pragma once

#include <uv.h>
#include <stdbool.h>

#include "../core/rect.h"
#include "../core/str-methods.h"
#include "../core/pointer-ownership.h"
#include "../core/pointer-attribute.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct ma_application;
struct ma_application_driver;

struct te_window;

struct na_input;

enum te_window_flags {

    te_window_flag_windowSizeFullscreen         = 0x0100,
    te_window_flag_windowSizeBorderless         ,
    te_window_flag_windowSizeRegular            ,

    te_window_flag_renderSurfaceTransparent     = 0x0200,

    te_window_flag_windowPosFreeform            = 0x0300,
    te_window_flag_windowPosCentered            ,

    te_window_flag_takesNoInput                 = 0x0400,
};

enum te_window_event_messages {

    te_window_event_message_resized,

    te_window_event_message_activated,

    te_window_event_message_changeTitle,
};

struct te_window_driver {

    void                                (*initialize)   (SU_PREF(struct ma_application), SU_PREF(struct te_window));

    void                                (*destroy)      (SU_PREF(struct ma_application), SU_PREF(struct te_window));


    void                                (*dispatch)     (SU_PREF(struct ma_application), SU_PREF(struct te_window), unsigned int message, SU_PREF(void) data);
};

struct te_window_events {

    void                                (*activated)    (SU_PREF(struct ma_application), SU_PREF(struct te_window), bool value);

    void                                (*resized)      (SU_PREF(struct ma_application), SU_PREF(struct te_window), struct su_scalar2 value);
};

struct te_window_event {

    SU_PWEAK(struct te_window)          ref_window;


    enum te_window_event_messages       event;

    SU_ABSREF void*                     paramLow;


    SU_PSTRONG(struct te_window_event)  toNext;
};

struct te_window {

    SU_PSTRONG(struct su_string)        title;

    struct su_rect                      position;


    struct te_window_events             events;

    SU_PWEAK(struct te_window_driver)   driver;

    SU_PWEAK(struct ma_application)     ref_application;


    uv_thread_t                         thread;

    uv_loop_t                           threadLoop;


    uv_async_t                          dispatch_windowEvents;

    uv_mutex_t                          locker_windowEvents;


    SU_PSTRONG(void)                    customData;


    SU_PSTRONG(void)                    scope_graphics;

    SU_PSTRONG(void)                    scope_sound;


    SU_PSTRONG(struct na_input)         dispatch_input;
};

#ifdef __cplusplus
}
#endif // __cplusplus
