#include "ci2c.h"

using namespace std;

Ci2c::Ci2c(char i2cBus,int addr)
{
    char filename[11] = "/dev/i2c-";
    filename[strlen(filename)] = i2cBus;
    filename[strlen(filename)] = '\0';
    fileI2c = open(filename, O_RDWR);
    addrSlave = addr;
    ioctl(fileI2c, I2C_SLAVE, addrSlave);
}

Ci2c::~Ci2c()
{}


int Ci2c::readFromI2C(unsigned char *buffer, int length)
{
    return read(fileI2c, buffer, length);
}

int Ci2c::writeToI2C(unsigned char *buffer, int length)
{

     return write(fileI2c, buffer, length);

}
