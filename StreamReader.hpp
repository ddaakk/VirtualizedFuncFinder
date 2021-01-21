#pragma once
#include <cstdint>
#include <string>

class StreamReader
{
public:
	StreamReader();
	StreamReader(char* buffer, uint32_t length, uint32_t offset);

	char* getBuffer();
	void setBuffer(char* buffer, uint32_t length);
	void setOffset(uint32_t offset);
	size_t getLength();
	size_t getCurrOffset();

	int8_t ReadInt8();
	void ReadInt8(int8_t& data);

	int16_t ReadInt16();
	void ReadInt16(int16_t& data);

	int32_t ReadInt32();
	void ReadInt32(int32_t& data);

	int64_t ReadInt64();
	void ReadInt64(int64_t& data);

	float ReadFloat32();
	void ReadFloat32(float& data);

	double ReadFloat64();
	void ReadFloat64(double& data);

	std::string ReadString();
	std::string ReadString(size_t size);

	void Skip(size_t length);
private:
	char* bytes_array_;
	size_t stream_length_;
	size_t current_offset_;
};