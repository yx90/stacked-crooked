#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <stdint.h>
#include <sys/time.h>

struct NetworkData
{
    uint64_t a, b, c;
};

double GetCurrentTime()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return double (tv.tv_sec) + 0.000001 * tv.tv_usec;
}


std::size_t counter = 0; // prevent GCC from optimizating the entire program away


struct copier_stdcopy
{
    static const char * name() { return "std::copy"; }

    void operator()(uint8_t * src) const
    {
        NetworkData hdr;
        uint8_t * dst = reinterpret_cast<uint8_t*>(&hdr);
        std::copy(src, src + sizeof(hdr), dst);
        counter += hdr.b;
    }

};

struct copier_memcpy
{
    static const char * name() { return "memcpy"; }

    void operator()(uint8_t * src) const
    {
        NetworkData hdr;
        memcpy(&hdr, src, sizeof(hdr));
        counter += hdr.b;
    }

};

struct copier_assign
{
    static const char * name() { return "assign"; }

    void operator()(uint8_t * src) const
    {
        NetworkData hdr = *reinterpret_cast<NetworkData*>(src);
        counter += hdr.b;
    }

};


const std::size_t iterations = 100000;
const uint64_t millisecond = uint64_t(1000);
const uint64_t microseconds = uint64_t(1000) * uint64_t(1000);
const uint64_t nanosecond = uint64_t(1000) * microseconds;


std::vector<uint8_t> GetBuffer()
{
    std::vector<uint8_t> buffer(sizeof(long) + iterations * sizeof(NetworkData));
    for (std::vector<uint8_t>::size_type i = 0; i != buffer.size(); ++i)
    {
        buffer[i] = uint8_t(buffer.size());
    }
    return buffer;
}


template<typename CopyFunction>
unsigned test(const CopyFunction & inCopyFunction, unsigned alignOffset)
{
    // Generate buffer large buffer
    std::vector<uint8_t> buffer = GetBuffer();

    auto startTime = GetCurrentTime();
    for (std::size_t i = 0; i != iterations; ++i)
    {
        inCopyFunction(buffer.data() + (i * sizeof(NetworkData)) + alignOffset);
    }
    return unsigned(0.5 + ((100 * 1000) * (GetCurrentTime() - startTime)));
}


int main()
{
    std::cout << "\nTest with good alignment" << std::endl;

    for (unsigned alignmentOffset = 0; alignmentOffset < (sizeof(long) / 2); ++alignmentOffset)
    {
        std::cout << "Alignment offset is now " << alignmentOffset << std::endl;
        std::cout << "std::copy: "   << test(copier_stdcopy(), alignmentOffset)
                  << "\nmemcpy   : " << test(copier_memcpy(),  alignmentOffset)
                  << "\nassign   : " << test(copier_assign(),  alignmentOffset)
                  << std::endl << std::endl;
    }
    std::cout << "optimization prevention counter: " << counter << std::endl;

}
