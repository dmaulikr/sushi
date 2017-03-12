#pragma once

#include "../core/pointer-ownership.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct te_window;

struct ma_application_window_entry {

    SU_PSTRONG(struct te_window)        window;

    void*                               thread;
};

struct ma_application_window_list {

    struct ma_application_window_entry* entries;

    unsigned int                        count;
};


struct ma_application;

struct te_window_driver;
struct na_input_driver;

enum ma_application_flags {

    ma_application_flag_eventLoopThrottled = 0,
};

struct ma_application_driver {

    SU_PSTRONG(struct te_window_driver) window_driver;


    SU_PSTRONG(void)                    graphics_driver;

    SU_PSTRONG(void)                    sound_driver;

    SU_PSTRONG(struct na_input_driver)  input_driver;


    enum ma_application_flags           flags;


    void                                (*initialize)       (SU_PREF(struct ma_application) application, SU_PREF(void) customData);

    void                                (*destroy)          (SU_PREF(struct ma_application) application);

    void                                (*loop)             (SU_PREF(struct ma_application) application);
};


struct ma_application {

    struct ma_application_driver        drivers;


    SU_PSTRONG(void)                    customData;


    SU_PSTRONG(void)                    device_graphics;

    SU_PSTRONG(void)                    device_audio;


    struct ma_application_window_list   windows;
};

#ifdef __cplusplus
}
#endif // __cplusplus
