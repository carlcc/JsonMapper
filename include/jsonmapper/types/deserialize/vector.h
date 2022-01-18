#pragma once

#include "../../JsonMapper.h"
#include <vector>

namespace jsonmapper {

template <class T>
struct DeserializerImpl<std::vector<T>> {
    bool operator()(std::vector<T>& vec, const rapidjson::Value& value, DeserializeContext& context)
    {
        if (!value.IsArray()) {
            context.SetError("Not a value of array");
            return false;
        }

        vec.resize((size_t)value.Size());
        size_t i = 0;
        for (auto it = value.Begin(), endIt = value.End(); it != endIt; ++it) {
            if (!DeserializeFromJson(vec[i], *it, context)) {
                context.SetError("Failed to deserialize element[" + std::to_string(i) + "]");
                return false;
            }
            ++i;
        }
        return true;
    }
};

}
