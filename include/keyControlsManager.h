#ifndef KEY_CONTROLS_H
#define KEY_CONTROLS_H

class KeyControlsManager
{
public:
    static KeyControlsManager *instance()
    {
        static KeyControlsManager *obj = new KeyControlsManager();
        return obj;
    }

    bool shouldQuit;
    bool isPeekMode;
    bool isMovingForward;

private:
    KeyControlsManager()
    {
        shouldQuit = false;
        isPeekMode = false;
        isMovingForward = false;
    }
};

#endif