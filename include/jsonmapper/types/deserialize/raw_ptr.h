#pragma once

#include "../../JsonMapper.h"

namespace jsonmapper {

template <class T>
struct DeserializerImpl<T*> {
    bool operator()(T* t, const rapidjson::Value& value, const DeserializeContext& context)
    {
        // Do not use 'static_assert' directly, which will cause compile error on g++/clang even though
        // this specialization does not really happen
        static_assert(sizeof(T*) != sizeof(int*), "Deserialize a raw pointer is not supported yet");
        return false; // Cancel warning on gcc
    }
};

}
