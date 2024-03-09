#include "Key.h"

Key::Key() {
    kchar = NO_KEY;
    kstate = IDLE;
    stateChanged = false;
}

Key::Key(char userKeyChar) {
    kchar = userKeyChar;
    kcode = -1;
    kstate = IDLE;
    stateChanged = false;
}

void Key::key_update (char userKeyChar, KeyState userState, boolean userStatus) {
    kchar = userKeyChar;
    kstate = userState;
    stateChanged = userStatus;
}
