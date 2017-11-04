#include <bitsery/bitsery.h>
#include <bitsery/adapter/buffer.h>
#include <bitsery/traits/vector.h>
#include <bitsery/traits/string.h>

using namespace bitsery;

using Buffer = std::vector<uint8_t>;
using OutputAdapter = OutputBufferAdapter<Buffer>;
using InputAdapter = InputBufferAdapter<Buffer>;

struct MyStruct {
    uint32_t i;
    char str[6];
    std::vector<float> fs;
};

template <typename S>
void serialize(S& s, MyStruct& o) {
    s.value4b(o.i);
    s.text1b(o.str);
    s.container4b(o.fs, 100);
};

int main() {
    MyStruct data{8941, "hello", {15.0f, -8.5f, 0.045f}};
    MyStruct res{};

    Buffer buffer;
    auto writtenSize = quickSerialization<OutputAdapter>(buffer, data);

    auto state = quickDeserialization<InputAdapter>({buffer.begin(), writtenSize}, res);

    assert(state.first == ReaderError::NoError && state.second);
    assert(data.fs == res.fs && data.i == res.i && std::strcmp(data.str, res.str) == 0);

    return 0;
}
