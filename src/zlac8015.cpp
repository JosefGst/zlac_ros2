#include "zlac_ros2/zlac8015.h"

void ZLAC::beginn(std::string port, int baudrate, uint8_t _ID)
{
    ID = _ID;
    _serial.setPort(port);
    _serial.setBaudrate(baudrate);
    serial::Timeout timeout = serial::Timeout::simpleTimeout(200);
    _serial.setTimeout(timeout);

    _serial.open();
    _serial.flushInput();
    std::cout << "SERIAL OK!" << std::endl;
}

uint8_t ZLAC::set_rpm(int16_t rpm)
{
    // memset(hex_cmd, 0, sizeof(hex_cmd));
    hex_cmd[0] = ID;
    hex_cmd[1] = WRITE;
    hex_cmd[2] = SET_RPM[0];
    hex_cmd[3] = SET_RPM[1];

    hex_cmd[4] = (rpm >> 8) & 0xFF;
    hex_cmd[5] = rpm & 0xFF;

    calculate_crc();
    _serial.write(hex_cmd, 8);
    read_hex(8);
    return 0;
}

int16_t ZLAC::get_rpm()
{
    // memset(hex_cmd, 0, sizeof(hex_cmd));
    hex_cmd[0] = ID;
    hex_cmd[1] = READ;
    hex_cmd[2] = GET_RPM[0];
    hex_cmd[3] = GET_RPM[1];

    hex_cmd[4] = 0x00;
    hex_cmd[5] = 0x01;

    calculate_crc();
    // print_hex_cmd();
    _serial.write(hex_cmd, 8);
    // print_rec_hex();
    read_hex(7);
    int16_t rpm_thenth = receive_hex[4] + (receive_hex[3] << 8);
    return rpm_thenth / 10;
}

uint8_t ZLAC::enable()
{
    memset(hex_cmd, 0, sizeof(hex_cmd));
    hex_cmd[0] = ID;
    hex_cmd[1] = WRITE;
    hex_cmd[2] = CONTROL_REG[0];
    hex_cmd[3] = CONTROL_REG[1];

    hex_cmd[4] = ENABLE[0];
    hex_cmd[5] = ENABLE[1];

    calculate_crc();
    _serial.write(hex_cmd, 8);
    read_hex(8);
    return 0;
}

uint8_t ZLAC::disable()
{
    // memset(hex_cmd, 0, sizeof(hex_cmd));
    hex_cmd[0] = ID;
    hex_cmd[1] = WRITE;
    hex_cmd[2] = CONTROL_REG[0];
    hex_cmd[3] = CONTROL_REG[1];

    hex_cmd[4] = DISABLE[0];
    hex_cmd[5] = DISABLE[1];

    calculate_crc();
    _serial.write(hex_cmd, 8);
    read_hex(8);
    return 0;
}

uint8_t ZLAC::set_vel_mode()
{
    // memset(hex_cmd, 0, sizeof(hex_cmd));
    hex_cmd[0] = ID;
    hex_cmd[1] = WRITE;
    hex_cmd[2] = OPERATING_MODE[0];
    hex_cmd[3] = OPERATING_MODE[1];

    hex_cmd[4] = VEL_MODE[0];
    hex_cmd[5] = VEL_MODE[1];

    calculate_crc();
    _serial.write(hex_cmd, 8);
    read_hex(8);
    return 0;
}

uint8_t ZLAC::set_acc_time(uint16_t acc_time)
{
    // memset(hex_cmd, 0, sizeof(hex_cmd));
    hex_cmd[0] = ID;
    hex_cmd[1] = WRITE;
    hex_cmd[2] = SET_ACC_TIME[0];
    hex_cmd[3] = SET_ACC_TIME[1];

    hex_cmd[4] = (acc_time >> 8) & 0xFF;
    hex_cmd[5] = acc_time & 0xFF;

    calculate_crc();
    _serial.write(hex_cmd, 8);
    read_hex(8);
    return 0;
}

uint8_t ZLAC::set_decc_time(uint16_t decc_time)
{
    // memset(hex_cmd, 0, sizeof(hex_cmd));
    hex_cmd[0] = ID;
    hex_cmd[1] = WRITE;
    hex_cmd[2] = SET_ACC_TIME[0];
    hex_cmd[3] = SET_ACC_TIME[1];

    hex_cmd[4] = (decc_time >> 8) & 0xFF;
    hex_cmd[5] = decc_time & 0xFF;

    calculate_crc();
    _serial.write(hex_cmd, 8);
    read_hex(8);
    return 0;
}

// HELPER Functions *************************************************************

void ZLAC::sleep(unsigned long milliseconds)
{
#ifdef _WIN32
    Sleep(milliseconds); // 100 ms
#else
    usleep(milliseconds * 1000); // 100 ms
#endif
}

void ZLAC::calculate_crc()
{
    // calculate crc and append to hex cmd
    unsigned short result = crc16(hex_cmd, sizeof(hex_cmd) - 2);
    hex_cmd[6] = result & 0xFF;
    hex_cmd[7] = (result >> 8) & 0xFF;
}

uint8_t ZLAC::read_hex(uint8_t num_bytes)
{
    std::string line = _serial.read(num_bytes);

    // convert string to hex
    for (uint8_t i = 0; i < uint8_t(line.size()); i++)
    {
        receive_hex[i] = uint8_t(line[i]);
        // printf("rec %d, %02x\n", i, receive_hex[i]);
    }

    // crc check of received data
    if (crc16(receive_hex, num_bytes) != 0)
    {
        printf("crc checking error\n");
        return 1;
    }
    return 0;
}

void ZLAC::print_hex_cmd()
{
    // print
    for (int i = 0; i < 8; i++)
    {
        printf("%d, %02x\n", i, hex_cmd[i]);
    }
}

void ZLAC::print_rec_hex()
{
    // print
    for (int i = 0; i < 8; i++)
    {
        printf("rec: %d, %02x\n", i, receive_hex[i]);
    }
}
