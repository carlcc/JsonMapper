#pragma once

#include "../../JsonMapper.h"
#include <unordered_map>

namespace jsonmapper {

template <class T>
struct SerializerImpl<std::unordered_map<std::string, T>> {
    bool operator()(const std::unordered_map<std::string, T>& vec, rapidjson::Value& value, const SerializeContext& context)
    {
        value.SetObject();
        for (auto& entry : vec) {
            rapidjson::Value key(entry.first.c_str(), entry.first.length(), context.allocator);
            rapidjson::Value ele;
            if (!SerializeToJson(entry.second, ele, context)) {
                return false;
            }
            value.AddMember(key, std::move(ele), context.allocator);
        }
        return true;
    }
};

}
