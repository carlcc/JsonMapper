#pragma once

#include "../../JsonMapper.h"

namespace jsonmapper {

template <class T>
struct DeserializerImpl<T*> {
    bool operator()(T* t, const rapidjson::Value& value, const DeserializeContext& context)
    {
        static_assert(false, "Deserialize a raw pointer is not supported yet");
    }
};

}
