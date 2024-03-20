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
    motorR.set_kp(500);
    motorR.set_ki(100);
    motorR.set_kf(1000);
    motorR.max_speed(80);
    motorR.set_feedforward_output_smoothing(100);
    motorR.set_vel_smoothing(1000);
    // motorR.initial_speed(40);

    motorL.set_vel_mode();
    motorL.enable();
    motorL.set_acc_time(500);
    motorL.set_decc_time(500);
    motorL.set_ki(100);
    motorL.set_kp(500);
    motorL.set_kf(1000);
    motorL.max_speed(80);
    motorL.set_feedforward_output_smoothing(100);
    motorL.set_vel_smoothing(1000);
    // motorL.initial_speed(40);

    // motorL.set_rpm(100);
    // for (int i = 0; i < 100; i++)
    motorL.disable();
    while (1)
    {
        // motorL.set_rpm(i);
        // motorR.set_rpm(i * FLIP);
        if (!motorL.read_motor())
        {
            printf("read pos L: %d \n", motorL.get_position());
            printf("read rpm L: %f \n", motorL.get_rpm());
            printf("read torque L: %f \n", motorL.get_torque());
            printf("read error L: %d \n", motorL.get_error());
        }

        // printf("i: %d read rpm L: %f \n", i, motorL.get_rpm());
    }
    motorR.disable();
    motorL.disable();
    // for (int i = 0; i < 100; i++)
    // {
    //     printf("i: %d read rpm R: %f \n", i, motorR.get_rpm() * FLIP);
    //     printf("i: %d read rpm L: %f \n", i, motorL.get_rpm());
    // }
    // motorR.enable();
    // motorL.enable();
    // motorL.set_rpm(-100);
    // motorR.set_rpm(-100 * FLIP);
    // for (int i = 0; i < 100; i++)
    // {
    //     printf("i: %d read rpm R: %f \n", i, motorR.get_rpm() * FLIP);
    //     printf("i: %d read rpm L: %f \n", i, motorL.get_rpm());
    // }
    // motorR.disable();
    // motorL.disable();
}
