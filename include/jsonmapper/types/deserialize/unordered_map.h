#pragma once

#include "../../JsonMapper.h"
#include <unordered_map>

namespace jsonmapper {

template <class T>
struct DeserializerImpl<std::unordered_map<std::string, T>> {
    bool operator()(std::unordered_map<std::string, T>& map, const rapidjson::Value& value, DeserializeContext& context)
    {
        if (!value.IsObject()) {
            context.SetError("Not a value of map type");
            return false;
        }
        for (auto it = value.MemberBegin(), endIt = value.MemberEnd(); it != endIt; ++it) {
            if (!DeserializeFromJson(map[it->name.GetString()], it->value, context)) {
                context.SetError(std::string("Failed to deserialize element[") + it->name.GetString() + "]");
                return false;
            }
        }
        return true;
    }
};

}
