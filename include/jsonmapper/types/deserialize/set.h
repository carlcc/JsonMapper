#pragma once

#include "../../JsonMapper.h"
#include <set>

namespace jsonmapper {

template <class T>
struct DeserializerImpl<std::set<T>> {
    bool operator()(std::set<T>& set, const rapidjson::Value& value, const DeserializeContext& context)
    {
        if (!value.IsArray()) {
            return false;
        }

        for (auto it = value.Begin(), endIt = value.End(); it != endIt; ++it) {
            T obj;
            if (!DeserializeFromJson(obj, *it, context)) {
                return false;
            }
            set.insert(std::move(obj));
        }
        return true;
    }
};

}
