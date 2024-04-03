#include <iostream>                                                                                                 //Code made by Zach Kofoed
#include <unordered_map>
#include <iomanip>



//code doesnt work fully, tried my best :/
class MemoryManager 
{
private:
    std::unordered_map<int, int> page_table; //page Table to map logical page numbers to physical frame numbers

public:
    //constructor to initialize the page table
    MemoryManager() 
    {
        //mapping from unordered map
        page_table[0x0D] = 0x1A;
        page_table[0x2B] = 0x2F;
        page_table[0x15] = 0x3C;
    }

    //method to translate logical addresses to physical addresses
    void translate_address(int logical_address) 
    {                                  //think my error is somewhere in this function....
        int page_number = (logical_address >> 4) & 0xFF; //extracting page number
        int offset = logical_address & 0x0F; //extracting offset

        auto it = page_table.find(page_number); //looking up the page number in the page table

        if (it != page_table.end()) { //page found in memory
            int frame_number = it->second;
            int physical_address = (frame_number << 4) | offset; //constructing physical address
            std::cout << "Logical Address: 0x" << std::hex << logical_address
                << " => Page Number: 0x" << std::setw(2) << std::setfill('0') << page_number
                << ", Offset: 0x" << std::setw(2) << std::setfill('0') << offset
                << " => Physical Address: 0x" << std::setw(2) << std::setfill('0') << physical_address << std::endl;
        }
        else {
            std::cerr << "Page fault occurred. Page number 0x" << std::hex << std::setw(2) << std::setfill('0') << page_number << " not found in memory." << std::endl;
        }
    }
};

int main() 
{
    MemoryManager memory_manager;

    //sample logical addresses
    int logical_addresses[] = { 0x3A7F, 0xABCD, 0x5678 };

    //translate each logical address
    for (int address : logical_addresses) {
        memory_manager.translate_address(address);
    }

    return 0;
}
