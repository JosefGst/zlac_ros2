#ifndef ZLAC8015
#define ZLAC8015

#include <string>
#include <iostream>
#include <chrono>

// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "serial/serial.h"
#include "zlac_ros2/crc_check.h"

class ZLAC
{
protected:
    std::chrono::time_point<std::chrono::steady_clock> start, end;

    uint8_t hex_cmd[8] = {0};
    uint8_t receive_hex[8] = {0};
    uint8_t ID = 0x00;
    uint8_t READ = 0x03;
    uint8_t WRITE = 0x06;
    uint8_t CONTROL_REG[2] = {0X20, 0X31};
    uint8_t ENABLE[2] = {0x00, 0X08};
    uint8_t DISABLE[2] = {0x00, 0X07};
    uint8_t OPERATING_MODE[2] = {0X20, 0X32};
    uint8_t VEL_MODE[2] = {0x00, 0X03};
    uint8_t SET_RPM[2] = {0x20, 0X3A};
    uint8_t GET_RPM[2] = {0x20, 0X2C};
    uint8_t SET_ACC_TIME[2] = {0x20, 0X37};
    uint8_t SET_DECC_TIME[2] = {0x20, 0X38};

    void calculate_crc();
    uint8_t read_hex(uint8_t num_bytes);
    void print_hex_cmd();
    void print_rec_hex();

public:
    serial::Serial _serial;
    void beginn(std::string port, int baudrate, uint8_t _ID = 0x00);
    uint8_t set_vel_mode();
    uint8_t set_acc_time(uint16_t acc_time);
    uint8_t set_decc_time(uint16_t decc_time);
    uint8_t enable();
    uint8_t disable();
    uint8_t set_rpm(int16_t rpm);
    int16_t get_rpm();

    void sleep(unsigned long milliseconds);
    void say_hello();
};

#endif