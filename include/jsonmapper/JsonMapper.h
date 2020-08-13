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

#define JMKVP(field) ::jsonmapper::MakeKVPair(#field, field)

} // namespace jsonmapper

#include "SerializeToJson.h"
