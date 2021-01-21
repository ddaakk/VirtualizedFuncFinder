#include <cstdint>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "StreamReader.hpp"

static constexpr const int32_t image_base = 0x00400000;

namespace {
    std::vector<int32_t> GetFunctionList(const std::string& text_file_name)
    {
        std::ifstream is(text_file_name);
        if (is.is_open() == false) {
            throw std::runtime_error("file open fail");
        }
        std::vector<std::string> all_lines;
        std::string temp;
        while (is.eof() == false) {
            std::getline(is, temp);
            all_lines.emplace_back(temp);
        }
        is.close();

        std::vector<int32_t> result;

        for (size_t i = 0; i < all_lines.size(); ++i)
        {
            std::vector<std::string> strs;
            boost::split(strs, all_lines[i], boost::is_any_of("*"));
            if (strs.size() > 0) {
                if (strs[0].find("sub_") != std::string::npos &&
                    strs[0][0] != 'n') {
                    int32_t value;
                    std::stringstream ss;
                    ss << std::hex << strs[0].data() + 4;
                    ss >> value;
                    result.emplace_back(value);
                }
            }
        }
        return result;
    }

    std::vector<int32_t> GetVirtualizedFunctionList(std::vector<int32_t>&& data)
    {
        std::ifstream is("FileName.exe", std::ios::binary);
        if (is.is_open() == false) {
            throw std::runtime_error("file open fail");
        }
        is.seekg(0, std::ios_base::end);
        size_t file_size = is.tellg();

        is.seekg(0, std::ios_base::beg);
        std::vector<char> file_data;

        file_data.resize(file_size);
        is.read(reinterpret_cast<char*>(file_data.data()), file_size);
        is.close();

        StreamReader reader(file_data.data(), file_size, 0);

        std::vector<int32_t> result;
        int32_t opcode = 0;
        int32_t operand = 0;

        for (int32_t memory_addr : data)
        {
            int32_t local_addr = memory_addr - image_base;

            reader.setOffset(local_addr);
            opcode = (reader.ReadInt8() & 0xFF);
            if (opcode == 0xE9) // jmp
            {
                operand = reader.ReadInt32();
                int32_t jmp_addr = memory_addr + operand + 5;
                if (jmp_addr > 0x00B00000) {
                    result.emplace_back(memory_addr);
                }
            }
        }
        return result;
    }

}

int main()
{
    try {
        auto data = GetVirtualizedFunctionList(GetFunctionList("data.txt"));
        std::cout << std::hex << std::uppercase;
        for (int32_t virtualized_addr : data)
        {
            std::cout << "0x" << virtualized_addr << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "Press Enter to Exit\n";
    getchar();
    getchar();
    getchar();
    getchar();

    return 0;
}
