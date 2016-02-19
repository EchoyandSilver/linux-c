#include "TeleController.h"
#include "Television.h"

        void TeleController::VolumeUp(Television& tv)
        {
                tv.volume_ += 1;
        }

        void TeleController::VolumeDown(Television& tv)
        {
                tv.volume_ -= 1;
        }

        void TeleController::chanelUp(Television& tv)
        {
                tv.chanel_ += 1;
        }

        void TeleController::chanelDown(Television& tv)
        {
                tv.chanel_ -= 1;
        }


