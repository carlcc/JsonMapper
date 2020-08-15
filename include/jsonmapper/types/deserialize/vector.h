#pragma once

#include "../../JsonMapper.h"
#include <vector>

namespace jsonmapper {

template <class T>
struct DeserializerImpl<std::vector<T>> {
    bool operator()(std::vector<T>& vec, const rapidjson::Value& value, const DeserializeContext& context)
    {
        if (!value.IsArray()) {
            return false;
        }

        vec.resize((size_t)value.Size());
        size_t i = 0;
        for (auto it = value.Begin(), endIt = value.End(); it != endIt; ++it) {
            if (!DeserializeFromJson(vec[i++], *it, context)) {
                return false;
            }
        }
        return true;
    }
};

}
