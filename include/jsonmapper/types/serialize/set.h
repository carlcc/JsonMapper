#pragma once

#include "../../JsonMapper.h"
#include <set>

namespace jsonmapper {

template <class T>
struct SerializerImpl<std::set<T>> {
    bool operator()(const std::set<T>& set, rapidjson::Value& value, const SerializeContext& context)
    {
        value.SetArray();
        for (auto& e : set) {
            rapidjson::Value ele;
            if (!SerializeToJson(e, ele, context)) {
                return false;
            }
            value.PushBack(std::move(ele), context.allocator);
        }
        return true;
    }
};

}
