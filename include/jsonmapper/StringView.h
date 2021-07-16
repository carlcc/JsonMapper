#pragma once

#include <cstddef>
#include <cstring>
#include <string>
#if __cplusplus >= 201703L
#include <string_view>
#endif

namespace jsonmapper {

class StringView {
public:
    StringView() = default;
    StringView(const char* ptr) //  NOLINT(google-explicit-constructor)
        : ptr_ { ptr }
        , size_ { strlen(ptr) }
    {
    }

    StringView(const char* ptr, size_t len)
        : ptr_ { ptr }
        , size_ { len }
    {
    }

    StringView(const std::string& s) // NOLINT(google-explicit-constructor)
        : ptr_ { s.data() }
        , size_ { s.length() }
    {
    }

#if __cplusplus >= 201703L
    StringView(const std::string_view& s) // NOLINT(google-explicit-constructor)
        : ptr_ { s.data() }
        , size_ { s.length() }
    {
    }
#endif

    const char* data() const
    {
        return ptr_;
    }
    size_t size() const { return size_; }
    size_t length() const { return size_; }

private:
    const char* ptr_ { "" };
    size_t size_ { 0 };
};

}