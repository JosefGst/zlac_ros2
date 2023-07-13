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

    /**
     * @brief calculates the crc and stores it in the hex_cmd array, so there is no return value
     */
    void calculate_crc();

    /**
     * @param num_bytes how many bytes to read from the buffer
     * @return return 0 when OK, 1 if crc error
     */
    uint8_t read_hex(uint8_t num_bytes);

    /**
     * @brief print the hex command for debugging
     */
    void print_hex_cmd();

    /**
     * @brief print received hex for debugging
     */
    void print_rec_hex();

public:
    serial::Serial _serial;

    /**
     * @brief open serial port communication
     * @param port COM port eg. "/dev/ttyUSB0"
     * @param baudRate default baudrate is 115200
     * @param _ID Set the modbus ID of the motor driver in HEX, default 0x00
     */
    void begin(std::string port, int baudrate = 15200, uint8_t ID = 0x00);
    uint8_t set_vel_mode();

    /**
     * @param acc_time_ms acceleration time in ms eg. 500
     */
    uint8_t set_acc_time(uint16_t acc_time_ms);

    /**
     * @param decc_time_ms decceleration time in ms eg. 500
     */
    uint8_t set_decc_time(uint16_t decc_time_ms);

    /**
     * @return 0 when OK. 1 if crc error
     */
    uint8_t enable();

    /**
     * @brief when motor disabled wheel can spin freely but still can read the rpm
     * @return 0 when OK. 1 if crc error
     */
    uint8_t disable();

    /**
     * @param rpm
     * @return alwasy 0
     */
    uint8_t set_rpm(int16_t rpm);

    /**
     * @return rpm measured from wheel
     */
    float get_rpm();

    void sleep(unsigned long milliseconds);
    void say_hello();
};

#endif