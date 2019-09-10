
#include "Particle.h"
#include "MR44V100A-FRAM.h"

MR44V100A::MR44V100A(int addr) : addr(addr)
{
}

MR44V100A::~MR44V100A()
{
}

void MR44V100A::begin()
{
}

bool MR44V100A::erase()
{
	size_t framAddr = 0;
	size_t totalLen = MEMORY_SIZE;

	uint8_t zero[32];
	memset(zero, 0, sizeof(zero));

	while (totalLen > 0)
	{
		bool result = writeData(framAddr, zero, sizeof(zero));
		if (!result)
		{
			return false;
		}

		totalLen -= sizeof(zero);
		framAddr += sizeof(zero);
	}
	return true;
}

bool MR44V100A::readData(size_t framAddr, uint8_t *data, size_t dataLen)
{
	bool result = true;

	while (dataLen > 0)
	{
		Wire.beginTransmission((uint8_t)(addr | DEVICE_ADDR | (framAddr >> 16 & 0x1)));
		Wire.write(framAddr >> 8);
		Wire.write(framAddr);
		int stat = Wire.endTransmission(false);
		if (stat != 0)
		{
			Serial.printlnf("   --- read set address failed %d", stat);
			result = false;
			break;
		}

		size_t bytesToRead = dataLen;
		if (bytesToRead > 32)
		{
			bytesToRead = 32;
		}

		Wire.requestFrom((uint8_t)(addr | DEVICE_ADDR | (framAddr >> 16 & 0x1)), (uint8_t)bytesToRead, true);
		if (Wire.available() < (int)bytesToRead)
		{
			result = false;
			break;
		}

		for (size_t ii = 0; ii < bytesToRead; ii++)
		{
			*data++ = Wire.read(); // receive a byte as character
			framAddr++;
			dataLen--;
		}
	}
	return result;
}

bool MR44V100A::writeData(size_t framAddr, const uint8_t *data, size_t dataLen)
{
	bool result = true;
	uint8_t addrJoined = addr;
	addrJoined |= DEVICE_ADDR;
	addrJoined |= framAddr >> 16 & 0x1;

	while (dataLen > 0)
	{
		Wire.beginTransmission(addrJoined);
		Wire.write(framAddr >> 8);
		Wire.write(framAddr);

		for (size_t ii = 0; ii < 30 && dataLen > 0; ii++)
		{
			Wire.write(*data);
			framAddr++;
			data++;
			dataLen--;
		}

		int stat = Wire.endTransmission(true);
		if (stat != 0)
		{
			Serial.printlnf("   --- write failed %d", stat);
			result = false;
			break;
		}
	}
	return result;
}
