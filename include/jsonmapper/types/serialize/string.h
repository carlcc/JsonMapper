#pragma once

#include "../../JsonMapper.h"
#include <string>

namespace jsonmapper {

template <>
bool SerializeToJson<std::string>(const std::string& v, rapidjson::Value& value, const SerializeContext& context)
{
    value.SetString(v.c_str(), v.length(), context.allocator);
    return true;
}

}
