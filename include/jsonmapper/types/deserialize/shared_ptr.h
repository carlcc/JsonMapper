#pragma once

#include "../../JsonMapper.h"
#include <memory>

namespace jsonmapper {

template <class T>
struct DeserializerImpl<std::shared_ptr<T>> {
    bool operator()(std::shared_ptr<T>& t, const rapidjson::Value& value, DeserializeContext& context)
    {
        if (value.IsNull()) {
            t = nullptr;
            return true;
        } else {
            t = std::make_shared<T>();
            return DeserializeFromJson(*t, value, context);
        }
    }
};

}
