#pragma once

#include "../../JsonMapper.h"
#include <memory>

namespace jsonmapper {

template <class T>
struct SerializerImpl<std::shared_ptr<T>> {
    bool operator()(const std::shared_ptr<T>& t, rapidjson::Value& value, const SerializeContext& context)
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
