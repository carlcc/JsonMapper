#pragma once

#include "../../JsonMapper.h"
#include <string>

namespace jsonmapper {

template <>
bool DeserializeFromJson<std::string>(std::string& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    if (!value.IsString()) {
        return false;
    }
    v = std::string(value.GetString(), (size_t)value.GetStringLength());
    return true;
}

}
