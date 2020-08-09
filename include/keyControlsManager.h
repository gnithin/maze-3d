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
    bool isMovingBackward;
    bool isMovingLeft;
    bool isMovingRight;

    bool isLookingUp;
    bool isLookingDown;

private:
    KeyControlsManager()
    {
        shouldQuit = false;
        isPeekMode = false;

        isMovingForward = false;
        isMovingBackward = false;
        isMovingLeft = false;
        isMovingRight = false;

        isLookingUp = false;
        isLookingDown = false;
    }
};

#endif