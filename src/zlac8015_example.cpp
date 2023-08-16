#include "zlac_ros2/zlac8015.h"

#define FLIP -1

int main()
{
    ZLAC motorL;
    motorL.begin("/dev/zlac", 115200, 0x01);

    ZLAC motorR;
    motorR.begin("/dev/zlac", 115200, 0x02);

    motorR.set_vel_mode();
    motorR.enable();
    motorR.set_acc_time(500);
    motorR.set_decc_time(500);
    motorR.max_speed(90);
    motorR.initial_speed(40);

    motorL.set_vel_mode();
    motorL.enable();
    motorL.set_acc_time(500);
    motorL.set_decc_time(500);
    motorL.max_speed(90);
    motorL.initial_speed(40);

    motorL.set_rpm(100);
    motorR.set_rpm(100 * FLIP);
    for (int i = 0; i < 100; i++)
    {
        printf("i: %d read rpm R: %f \n", i, motorR.get_rpm() * FLIP);
        printf("i: %d read rpm L: %f \n", i, motorL.get_rpm());
    }
    motorR.disable();
    motorL.disable();
    for (int i = 0; i < 100; i++)
    {
        printf("i: %d read rpm R: %f \n", i, motorR.get_rpm() * FLIP);
        printf("i: %d read rpm L: %f \n", i, motorL.get_rpm());
    }
    motorR.enable();
    motorL.enable();
    motorL.set_rpm(-100);
    motorR.set_rpm(-100 * FLIP);
    for (int i = 0; i < 100; i++)
    {
        printf("i: %d read rpm R: %f \n", i, motorR.get_rpm() * FLIP);
        printf("i: %d read rpm L: %f \n", i, motorL.get_rpm());
    }
    motorR.disable();
    motorL.disable();
}
