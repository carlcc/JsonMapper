#pragma once

namespace jsonmapper {

template <class T>
struct KVPair {
    const char* key;
    T& value;
};

template <class T>
KVPair<T> MakeKVPair(const char* key, T& value)
{
    return KVPair<T> { key, value };
}

template <class T>
struct OptKVPair {
    const char* key;
    T& value;
};

template <class T>
OptKVPair<T> MakeOptKVPair(const char* key, T& value)
{
    return OptKVPair<T> { key, value };
}

#define JMKVP(field) ::jsonmapper::MakeKVPair(#field, field)

#define JMOPTKVP(field) ::jsonmapper::MakeOptKVPair(#field, field)

} // namespace jsonmapper

#include "DeserializeFromJson.h"
#include "SerializeToJson.h"
