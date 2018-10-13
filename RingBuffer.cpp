
#include "RingBuffer.h"


RingBuffer::RingBuffer() {

}

void RingBuffer::begin() {

}
void RingBuffer::end() {

	// clear any received data
	_rx_buffer_head = _rx_buffer_tail;
}
int RingBuffer::available(void) {
	return ((unsigned int)(RING_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % RING_RX_BUFFER_SIZE;
}
int RingBuffer::availableTX(void) {
	return ((unsigned int)(RING_TX_BUFFER_SIZE + _tx_buffer_head - _tx_buffer_tail)) % RING_TX_BUFFER_SIZE;
}


int RingBuffer::peek(void)
{
	if (_rx_buffer_head == _rx_buffer_tail) {
		return -1;
	}
	else {
		return _rx_buffer[_rx_buffer_tail];
	}
}

int RingBuffer::peekTX(void)
{
	if (_tx_buffer_head == _tx_buffer_tail) {
		return -1;
	}
	else {
		return _tx_buffer[_tx_buffer_tail];
	}
}

int RingBuffer::read(void)
{
	// if the head isn't ahead of the tail, we don't have any characters
	if (_rx_buffer_head == _rx_buffer_tail) {
		return -1;
	}
	else {
		unsigned char c = _rx_buffer[_rx_buffer_tail];
		_rx_buffer_tail = (uint16_t)(_rx_buffer_tail + 1) % RING_RX_BUFFER_SIZE;
		return c;
	}
}
int RingBuffer::readTX(void)
{
	// if the head isn't ahead of the tail, we don't have any characters
	if (_tx_buffer_head == _tx_buffer_tail) {
		return -1;
	}
	else {
		unsigned char c = _tx_buffer[_tx_buffer_tail];
		_tx_buffer_tail = (uint16_t)(_tx_buffer_tail + 1) % RING_TX_BUFFER_SIZE;
		return c;
	}
}

int16_t RingBuffer::readBytes(char *buffer, int16_t length)
{
	int16_t count = 0;
	while (count < length) {
		int c = read();
		if (c < 0) break;
		*buffer++ = (char)c;
		count++;
	}
	return count;
}
int16_t RingBuffer::readBytesTX(char *buffer, int16_t length)
{
	int16_t count = 0;
	while (count < length) {
		int c = readTX();
		if (c < 0) break;
		*buffer++ = (char)c;
		count++;
	}
	return count;
}
int RingBuffer::availableForWrite(void)
{
	uint16_t head = _tx_buffer_head;
	uint16_t tail = _tx_buffer_tail;

	if (head >= tail) return RING_TX_BUFFER_SIZE - 1 - head + tail;
	return tail - head - 1;
}
int RingBuffer::availableForWriteRX(void)
{
	uint16_t head = _rx_buffer_head;
	uint16_t tail = _rx_buffer_tail;

	if (head >= tail) return RING_RX_BUFFER_SIZE - 1 - head + tail;
	return tail - head - 1;
}


int16_t RingBuffer::write(uint8_t c) {

	if (availableForWrite() == 0) {
		return 0;
	}
	int16_t i = (_tx_buffer_head + 1) % RING_TX_BUFFER_SIZE;

	_tx_buffer[_tx_buffer_head] = c;

	_tx_buffer_head = i;

	return i;
}

int16_t RingBuffer::writeRX(uint8_t c) {

	if (availableForWriteRX() == 0) {
		return 0;
	}
	int16_t i = (_rx_buffer_head + 1) % RING_RX_BUFFER_SIZE;

	_rx_buffer[_rx_buffer_head] = c;

	_rx_buffer_head = i;

	return i;
}

