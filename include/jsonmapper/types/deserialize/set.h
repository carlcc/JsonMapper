#pragma once

#include "../../JsonMapper.h"
#include <set>

namespace jsonmapper {

template <class T>
struct DeserializerImpl<std::set<T>> {
    bool operator()(std::set<T>& set, const rapidjson::Value& value, DeserializeContext& context)
    {
        if (!value.IsArray()) {
            context.SetError("Not a value of array");
            return false;
        }

        size_t elementIndex = 0;
        for (auto it = value.Begin(), endIt = value.End(); it != endIt; ++it) {
            T obj;
            if (!DeserializeFromJson(obj, *it, context)) {
                context.SetError("Failed to deserialize element[" + std::to_string(elementIndex) + "]");
                return false;
            }
            ++elementIndex;
            set.insert(std::move(obj));
        }
        return true;
    }
};

}
