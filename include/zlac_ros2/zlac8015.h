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
    const uint8_t READ = 0x03;
    const uint8_t WRITE = 0x06;
    const uint8_t CONTROL_REG[2] = {0X20, 0X31};
    const uint8_t ENABLE[2] = {0x00, 0X08};
    const uint8_t DISABLE[2] = {0x00, 0X07};
    const uint8_t OPERATING_MODE[2] = {0X20, 0X32};
    const uint8_t VEL_MODE[2] = {0x00, 0X03};
    const uint8_t SET_RPM[2] = {0x20, 0X3A};
    const uint8_t GET_RPM[2] = {0x20, 0X2C};
    const uint8_t SET_ACC_TIME[2] = {0x20, 0X37};
    const uint8_t SET_DECC_TIME[2] = {0x20, 0X38};
    const uint8_t SET_KP[2] = {0x20, 0X1D};
    const uint8_t SET_KI[2] = {0x20, 0X1E};
    const uint8_t INITIAL_SPEED[2] = {0X20, 0X08};
    const uint8_t MAX_SPEED[2] = {0X20, 0X0A};
    const uint8_t ACTUAL_POSITION_H[2] = {0X20, 0X2A};
    const uint8_t ACTUAL_POSITION_L[2] = {0X20, 0X2B};

    /**
     * @brief calculates the crc and stores it in the hex_cmd array, so there is no return value
     */
    void calculate_crc();

    /**
     * @brief reads from the serial port and saves the string into the receive_hex array
     * @param num_bytes how many bytes to read from the buffer
     * @return return 0 when OK, 1 if crc error
     */
    uint8_t read_hex(uint8_t num_bytes);

    /**
     * @brief print the hex command for debugging
     */
    void print_hex_cmd() const;

    /**
     * @brief print received hex for debugging
     */
    void print_rec_hex() const;

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
     * @return 0 when OK. 1 if crc error
     */
    uint8_t set_acc_time(uint16_t acc_time_ms);

    /**
     * @param decc_time_ms decceleration time in ms eg. 500
     * @return 0 when OK. 1 if crc error
     */
    uint8_t set_decc_time(uint16_t decc_time_ms);

    /**
     * @param proportional_gain Speed Proportional Gain. Default: 500
     * @return 0 when OK. 1 if crc error
     */
    uint8_t set_kp(uint16_t proportional_gain);

    /**
     * @param integral_gain Speed Integral Gain. Default: 100
     * @return 0 when OK. 1 if crc error
     */
    uint8_t set_ki(uint16_t integral_gain);

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

    /**
     * @return The ini tial speed when moti on begins.
     */
    uint8_t initial_speed(uint16_t rpm);

    /**
     * @return Max operating speed of motor.
     */
    uint8_t max_speed(uint16_t rpm);

    void sleep(unsigned long milliseconds);
    void say_hello();
};

#endif