#ifndef RingBuffer_h
#define RingBuffer_h

#include <inttypes.h>

#define RING_RX_BUFFER_SIZE 1024
#define RING_TX_BUFFER_SIZE 1024



class RingBuffer {
protected:
	int16_t _rx_buffer_head;
	int16_t _rx_buffer_tail;
	int16_t _tx_buffer_head;
	int16_t _tx_buffer_tail;

	unsigned char _rx_buffer[RING_RX_BUFFER_SIZE];
	unsigned char _tx_buffer[RING_TX_BUFFER_SIZE];

public:
	RingBuffer();
	void begin();
	void end();

	int available(void);
	int peek(void);

	int read(void);
	int16_t readBytes(char *buffer, int16_t length);

	int availableTX(void);
	int peekTX(void);

	int readTX(void);
	int16_t readBytesTX(char *buffer, int16_t length);

	int availableForWrite(void);

	int16_t write(unsigned long n) {
		return write((uint8_t)n);
	}
	int16_t write(long n) {
		return write((uint8_t)n);
	}
	int16_t write(unsigned int n) {
		return write((uint8_t)n);
	}
	int16_t write(int n) {
		return write((uint8_t)n);
	}
	int16_t write(const uint8_t *buffer, int16_t size) {
		int16_t n = 0;
		while (size--) {
			if (write(*buffer++)) n++;
			else break;
		}
		return n;
	}
	int16_t write(uint8_t);


	int availableForWriteRX(void);

	int16_t writeRX(uint8_t);
	int16_t writeRX(unsigned long n) {
		return writeRX((uint8_t)n);
	}
	int16_t writeRX(long n) {
		return writeRX((uint8_t)n);
	}
	int16_t writeRX(unsigned int n) {
		return writeRX((uint8_t)n);
	}
	int16_t writeRX(int n) {
		return writeRX((uint8_t)n);
	}
	int16_t writeRX(const uint8_t *buffer, int16_t size) {
		int16_t n = 0;
		while (size--) {
			if (writeRX(*buffer++)) n++;
			else break;
		}
		return n;
	}
};

#endif

