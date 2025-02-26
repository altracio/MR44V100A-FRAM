#ifndef MR44V100A_FRAM_H
#define MR44V100A_FRAM_H


class MR44V100A {
public:
	/**
	 * You typically create one of these objects as a global variable
	 *
	 * The first argument is typically Wire (pins D0 and D1). On the Electron it can also be Wire1 (pins C4 and C5)
	 *
	 * The addr argument is the address 0-7 based on the setting of A0, A1 and A2.
	 */
	MR44V100A(int addr = 0);
	virtual ~MR44V100A();

	/**
	 * Typically called during setup() to start the Wire interface.
	 */
	void begin();

	inline size_t length() { return MEMORY_SIZE; }

	bool erase();

    template <typename T> T &get(size_t framAddr, T &t) {
        readData(framAddr, (uint8_t *)&t, sizeof(T));
        return t;
    }

    template <typename T> const T &put(size_t framAddr, const T &t) {
        writeData(framAddr, (const uint8_t *)&t, sizeof(T));
        return t;
    }

	bool readData(size_t framAddr, uint8_t *data, size_t dataLen);
	bool writeData(size_t framAddr, const uint8_t *data, size_t dataLen);

	static const uint8_t DEVICE_ADDR = 0b1010000;
	static const size_t MEMORY_SIZE = 131072;

protected:
	int addr; // This is just 0-7, the (0b1010000 of the 7-bit address is ORed in later)

};

#endif /* MR44V100A_FRAM */
