#pragma once

#include "../../JsonMapper.h"
#include <unordered_map>

namespace jsonmapper {

template <class T>
struct DeserializerImpl<std::unordered_map<std::string, T>> {
    bool operator()(std::unordered_map<std::string, T>& map, const rapidjson::Value& value, const DeserializeContext& context)
    {
        if (!value.IsObject()) {
            return false;
        }
        for (auto it = value.MemberBegin(), endIt = value.MemberEnd(); it != endIt; ++it) {
            if (!DeserializeFromJson(map[it->name.GetString()], it->value, context)) {
                return false;
            }
        }
        return true;
    }
};

}
