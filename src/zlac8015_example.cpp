#include "zlac_ros2/zlac8015.h"

#define FLIP -1

int main()
{
    ZLAC motorL;
    motorL.beginn("/dev/zlac", 115200, 0x01);

    ZLAC motorR;
    motorR.beginn("/dev/zlac", 115200, 0x02);

    motorR.set_vel_mode();
    motorR.enable();
    motorR.set_acc_time(500);
    motorR.set_decc_time(500);

    motorL.set_vel_mode();
    motorL.enable();
    motorL.set_acc_time(500);
    motorL.set_decc_time(500);

    motorL.set_rpm(100);
    motorR.set_rpm(100 * FLIP);
    for (int i = 0; i < 100; i++)
    {
        printf("%d read rpm R: %d \n", i, motorR.get_rpm(1) * FLIP);
        printf("%d read rpm L: %d \n", i, motorL.get_rpm(1));
    }
    motorR.disable();
    motorL.disable();
}
