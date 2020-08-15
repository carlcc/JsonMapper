#pragma once

#include "../../JsonMapper.h"
#include <vector>

namespace jsonmapper {

template <class T>
struct SerializerImpl<std::vector<T>> {
    bool operator()(const std::vector<T>& vec, rapidjson::Value& value, const SerializeContext& context)
    {
        value.SetArray();
        value.Reserve((rapidjson::SizeType)vec.size(), context.allocator);
        for (auto& e : vec) {
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
