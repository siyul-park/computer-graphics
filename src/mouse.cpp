#include "mouse.h"

void gl::MousePositionOffsetControl::run(gl::MousePosition value) {
    if (first) {
        last = value;
        first = false;
        return;
    }

    gl::MousePositionOffset offset = { .x = value.x = last.x, .y = last.y - value.y };
    for (auto &callback: callbacks) {
        callback->run(offset);
    }

    last = value;
}
