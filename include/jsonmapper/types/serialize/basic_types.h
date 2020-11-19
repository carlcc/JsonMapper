#pragma once

#include "../../JsonMapper.h"
#include <string>

namespace jsonmapper {

template <>
inline bool SerializeToJson<bool>(const bool& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetBool(v);
    return true;
}

template <>
inline bool SerializeToJson<int8_t>(const int8_t& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetInt64(v);
    return true;
}

template <>
inline bool SerializeToJson<int16_t>(const int16_t& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetInt64(v);
    return true;
}

template <>
inline bool SerializeToJson<int32_t>(const int32_t& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetInt64(v);
    return true;
}

template <>
inline bool SerializeToJson<int64_t>(const int64_t& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetInt64(v);
    return true;
}

template <>
inline bool SerializeToJson<uint8_t>(const uint8_t& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetUint64(v);
    return true;
}

template <>
inline bool SerializeToJson<uint16_t>(const uint16_t& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetUint64(v);
    return true;
}

template <>
inline bool SerializeToJson<uint32_t>(const uint32_t& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetUint64(v);
    return true;
}

template <>
inline bool SerializeToJson<uint64_t>(const uint64_t& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetUint64(v);
    return true;
}

template <>
inline bool SerializeToJson<float>(const float& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetFloat(v);
    return true;
}

template <>
inline bool SerializeToJson<double>(const double& v, rapidjson::Value& value, const SerializeContext& context)
{
    (void)context;
    value.SetDouble(v);
    return true;
}

}
