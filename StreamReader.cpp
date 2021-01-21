#include "StreamReader.hpp"
#include <algorithm>
#include <stdexcept>
#include <sstream>


StreamReader::StreamReader()
	: StreamReader(nullptr, 0, 0)
{
}

StreamReader::StreamReader(char* buffer, uint32_t length, uint32_t offset)
	: bytes_array_(buffer), stream_length_(length), current_offset_(offset)
{

}

void StreamReader::setBuffer(char* buffer, uint32_t length)
{
	bytes_array_ = buffer;
	stream_length_ = length;
}

size_t StreamReader::getLength() {
	return stream_length_;
}

char* StreamReader::getBuffer() {
	return bytes_array_;
}

void StreamReader::setOffset(uint32_t offset) {
	current_offset_ = offset;
}

size_t StreamReader::getCurrOffset() {
	return current_offset_;
}

int8_t StreamReader::ReadInt8() {
	int8_t data = *reinterpret_cast<int8_t*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(int8_t);
	return data;
}

void StreamReader::ReadInt8(int8_t& data) {
	data = *reinterpret_cast<int8_t*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(int8_t);
}

int16_t StreamReader::ReadInt16() {
	int16_t data = *reinterpret_cast<int16_t*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(int16_t);
	return data;
}

void StreamReader::ReadInt16(int16_t& data) {
	data = *reinterpret_cast<int16_t*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(int16_t);
}

int32_t StreamReader::ReadInt32() {
	int32_t data = *reinterpret_cast<int32_t*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(int32_t);
	return data;
}

void StreamReader::ReadInt32(int32_t& data) {
	data = *reinterpret_cast<int32_t*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(int32_t);
}

int64_t StreamReader::ReadInt64() {
	int64_t data = *reinterpret_cast<int64_t*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(int64_t);
	return data;
}

void StreamReader::ReadInt64(int64_t& data) {
	data = *reinterpret_cast<int64_t*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(int64_t);
}

float StreamReader::ReadFloat32() {
	float data = *reinterpret_cast<float*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(float);
	return data;
}

void StreamReader::ReadFloat32(float& data) {
	data = *reinterpret_cast<float*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(float);
}

double StreamReader::ReadFloat64() {
	float data = *reinterpret_cast<double*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(double);
	return data;
}

void StreamReader::ReadFloat64(double& data) {
	data = *reinterpret_cast<double*>(bytes_array_ + current_offset_);
	current_offset_ += sizeof(double);
}

std::string StreamReader::ReadString()
{
	char* data = reinterpret_cast<char*>(bytes_array_ + current_offset_);
	size_t length = strlen(data) + 1;
	std::string str(data);
	current_offset_ += length;
	return str;
}

std::string StreamReader::ReadString(size_t size)
{
	char data[512] = { 0, };
	if (size > 512) {
		std::stringstream ss;
		ss << __FUNCSIG__ << " Buffer Overflow... size: " << size << '\n';
		std::runtime_error(ss.str().c_str());
	}
	memcpy(data, bytes_array_ + current_offset_, size);
	auto begin = std::begin(data);
	std::string str(begin, begin + strlen(data));
	current_offset_ += size;
	return str;
}

void StreamReader::Skip(size_t length)
{
	current_offset_ += length;
}
