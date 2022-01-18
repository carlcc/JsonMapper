#pragma once

#include "../../JsonMapper.h"
#include <string>

namespace jsonmapper {

template <>
inline bool DeserializeFromJson<std::string>(std::string& v, const rapidjson::Value& value, DeserializeContext& context)
{
    if (!value.IsString()) {
        context.SetError("Is not a string!");
        return false;
    }
    v = std::string(value.GetString(), (size_t)value.GetStringLength());
    return true;
}

}
