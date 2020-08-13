#pragma once

#include "../../JsonMapper.h"

namespace jsonmapper {

template <class T>
struct SerializerImpl<T*> {
    bool operator()(const T* t, rapidjson::Value& value, const SerializeContext& context)
    {
        if (t == nullptr) {
            value.SetNull();
            return true;
        } else {
            return SerializeToJson(*t, value, context);
        }
    }
};

}
