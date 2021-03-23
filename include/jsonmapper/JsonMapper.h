#pragma once

namespace jsonmapper {

template <class T>
struct KVPair {
    const char* key;
    T& value;
};

template <class T>
inline KVPair<T> MakeKVPair(const char* key, T& value)
{
    return KVPair<T> { key, value };
}

template <class T>
struct OptKVPair {
    const char* key;
    T& value;
};

template <class T>
inline OptKVPair<T> MakeOptKVPair(const char* key, T& value)
{
    return OptKVPair<T> { key, value };
}

#define JM_DEFINE_MAP(...)                   \
public:                                      \
    template <class Archiver>                \
    bool SerializeToJson(Archiver& ar) const \
    {                                        \
        return ar(__VA_ARGS__);              \
    }                                        \
    template <class Archiver>                \
    bool DeserializeFromJson(Archiver& ar)   \
    {                                        \
        return ar(__VA_ARGS__);              \
    }

#define JMKVP(field) ::jsonmapper::MakeKVPair(#field, field)

#define JMOPTKVP(field) ::jsonmapper::MakeOptKVPair(#field, field)

} // namespace jsonmapper

#include "DeserializeFromJson.h"
#include "SerializeToJson.h"
