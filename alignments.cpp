#include <iostream>
#include <cstdint>
#include <iomanip>
#include <string>

// ==================== DEFAULT ALIGNMENT EXAMPLES ====================

struct DefaultAlignment {
    char byte1;         // 1 byte + 3 padding
    int integer;        // 4 bytes + 4 padding
    double floating;    // 8 bytes
    char byte2;         // 1 byte + 7 padding
};

struct OptimizedAlignment {
    double floating;    // 8 bytes (largest first)
    int integer;        // 4 bytes
    char byte1;         // 1 byte
    char byte2;         // 1 byte + 2 padding
};

// ==================== PRAGMA PACK(1) - NO PADDING ====================

#pragma pack(1)
struct PackedStruct {
    char byte1;         // 1 byte
    int integer;        // 4 bytes
    double floating;    // 8 bytes
    char byte2;         // 1 byte
    short shortValue;   // 2 bytes
};
#pragma pack()

// ==================== PRAGMA PACK(2) - 2-BYTE ALIGNMENT ====================

#pragma pack(2)
struct TwoByteAligned {
    char byte1;         // 1 byte + 1 padding
    int integer;        // 4 bytes
    double floating;    // 8 bytes
    char byte2;         // 1 byte + 1 padding
    short shortValue;   // 2 bytes
};
#pragma pack()

// ==================== PRAGMA PACK(4) - 4-BYTE ALIGNMENT ====================

#pragma pack(4)
struct FourByteAligned {
    char byte1;         // 1 byte + 3 padding
    int integer;        // 4 bytes
    double floating;    // 8 bytes (aligned on 4-byte boundary)
    char byte2;         // 1 byte + 3 padding
    short shortValue;   // 2 bytes + 2 padding
};
#pragma pack()

// ==================== NETWORK PROTOCOL EXAMPLE ====================

#pragma pack(1)
struct NetworkHeader {
    uint8_t version;        // 1 byte
    uint8_t type;          // 1 byte
    uint16_t length;       // 2 bytes
    uint32_t sequence;     // 4 bytes
    uint32_t checksum;     // 4 bytes
    char payload[16];      // 16 bytes
};
#pragma pack()

// ==================== FILE FORMAT EXAMPLE ====================

#pragma pack(1)
struct BitmapHeader {
    uint16_t signature;     // "BM" - 2 bytes
    uint32_t fileSize;      // 4 bytes
    uint16_t reserved1;     // 2 bytes
    uint16_t reserved2;     // 2 bytes  
    uint32_t dataOffset;    // 4 bytes
    uint32_t headerSize;    // 4 bytes
    uint32_t width;         // 4 bytes
    uint32_t height;        // 4 bytes
};
#pragma pack()

// ==================== MIXED ALIGNMENT EXAMPLE ====================

struct MixedTypes {
    bool flag1;             // 1 byte + 7 padding
    double value1;          // 8 bytes
    char flag2;             // 1 byte + 1 padding
    short value2;           // 2 bytes + 4 padding
    long long value3;       // 8 bytes
    char array[3];          // 3 bytes + 5 padding
};

#pragma pack(1)
struct MixedTypesPacked {
    bool flag1;             // 1 byte
    double value1;          // 8 bytes
    char flag2;             // 1 byte
    short value2;           // 2 bytes
    long long value3;       // 8 bytes
    char array[3];          // 3 bytes
};
#pragma pack()

// ==================== ARM VS X86 CONSIDERATIONS ====================

// ARM-friendly structure (4-byte alignment preferred)
#pragma pack(4)
struct ARMOptimized {
    uint32_t armRegister;   // 4 bytes
    uint16_t statusFlags;   // 2 bytes + 2 padding  
    uint32_t dataPointer;   // 4 bytes
    char buffer[8];         // 8 bytes
};
#pragma pack()

// x86-friendly structure (8-byte alignment efficient)
struct X86Optimized {
    uint64_t register64;    // 8 bytes
    uint32_t register32;    // 4 bytes
    uint16_t flags;         // 2 bytes + 2 padding
    char buffer[8];         // 8 bytes
};

// ==================== UTILITY FUNCTIONS ====================

void printStructInfo(const char* name, size_t size) {
    std::cout << std::setw(25) << std::left << name << ": " << std::setw(3) << size << " bytes\n";
}

template<typename T>
void printFieldOffsets(const char* structName) {
    std::cout << "\n" << structName << " field offsets:\n";
    std::cout << "Structure size: " << sizeof(T) << " bytes\n";
}

void printSeparator(const char* title) {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << title << "\n";
    std::cout << std::string(50, '=') << "\n";
}

// ==================== MAIN FUNCTION ====================

int main() {
    std::cout << "MEMORY ALIGNMENT AND #PRAGMA PACK EXAMPLES\n";
    std::cout << std::string(60, '=') << "\n\n";

    // Default vs Optimized Alignment
    printSeparator("DEFAULT VS OPTIMIZED ALIGNMENT");
    printStructInfo("DefaultAlignment", sizeof(DefaultAlignment));
    printStructInfo("OptimizedAlignment", sizeof(OptimizedAlignment));
    
    // Different pack values
    printSeparator("DIFFERENT PRAGMA PACK VALUES");
    printStructInfo("No pack (default)", sizeof(DefaultAlignment));
    printStructInfo("pack(1)", sizeof(PackedStruct));
    printStructInfo("pack(2)", sizeof(TwoByteAligned));
    printStructInfo("pack(4)", sizeof(FourByteAligned));
    
    // Practical examples
    printSeparator("PRACTICAL EXAMPLES");
    printStructInfo("NetworkHeader pack(1)", sizeof(NetworkHeader));
    printStructInfo("BitmapHeader pack(1)", sizeof(BitmapHeader));
    
    // Mixed types comparison
    printSeparator("MIXED TYPES COMPARISON");
    printStructInfo("MixedTypes (default)", sizeof(MixedTypes));
    printStructInfo("MixedTypesPacked", sizeof(MixedTypesPacked));
    
    // Architecture specific
    printSeparator("ARCHITECTURE SPECIFIC");
    printStructInfo("ARMOptimized pack(4)", sizeof(ARMOptimized));
    printStructInfo("X86Optimized (default)", sizeof(X86Optimized));
    
    // Memory layout demonstration
    printSeparator("MEMORY LAYOUT EXAMPLE");
    NetworkHeader netHeader;
    std::cout << "NetworkHeader field addresses:\n";
    std::cout << "version   : " << std::hex << (void*)&netHeader.version << "\n";
    std::cout << "type      : " << std::hex << (void*)&netHeader.type << "\n";
    std::cout << "length    : " << std::hex << (void*)&netHeader.length << "\n";
    std::cout << "sequence  : " << std::hex << (void*)&netHeader.sequence << "\n";
    std::cout << "checksum  : " << std::hex << (void*)&netHeader.checksum << "\n";
    std::cout << "payload   : " << std::hex << (void*)&netHeader.payload << "\n";
    
    // Padding demonstration
    printSeparator("PADDING DEMONSTRATION");
    DefaultAlignment defAlign;
    std::cout << "DefaultAlignment field addresses:\n";
    std::cout << "byte1     : " << std::hex << (void*)&defAlign.byte1 << "\n";
    std::cout << "integer   : " << std::hex << (void*)&defAlign.integer << "\n";
    std::cout << "floating  : " << std::hex << (void*)&defAlign.floating << "\n";
    std::cout << "byte2     : " << std::hex << (void*)&defAlign.byte2 << "\n";
    
    std::cout << std::dec << "\nPadding bytes between fields:\n";
    std::cout << "After byte1   : " << (char*)&defAlign.integer - (char*)&defAlign.byte1 - 1 << " bytes\n";
    std::cout << "After integer : " << (char*)&defAlign.floating - (char*)&defAlign.integer - 4 << " bytes\n";
    std::cout << "After floating: " << (char*)&defAlign.byte2 - (char*)&defAlign.floating - 8 << " bytes\n";
    
    // Performance implications
    printSeparator("PERFORMANCE IMPLICATIONS");
    std::cout << "Aligned access   : Faster on both ARM and x86\n";
    std::cout << "Unaligned access : Slower on ARM, acceptable on x86\n";
    std::cout << "pack(1)          : Smallest size, potential performance cost\n";
    std::cout << "Default packing  : Balance between size and performance\n";
    
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "Memory alignment affects both performance and memory usage!\n";
    std::cout << "Choose alignment strategy based on your specific needs.\n";
    
    system("pause");
    return 0;
}