#pragma once

#include "../../JsonMapper.h"
#include <string>

namespace jsonmapper {

template <>
bool DeserializeFromJson<bool>(bool& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsBool()) {
        return false;
    }
    v = value.GetBool();
    return true;
}

template <>
bool DeserializeFromJson<int8_t>(int8_t& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsInt64()) {
        return false;
    }
    v = (int8_t)value.GetInt64();
    return true;
}

template <>
bool DeserializeFromJson<int16_t>(int16_t& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsInt64()) {
        return false;
    }
    v = (int16_t)value.GetInt64();
    return true;
}

template <>
bool DeserializeFromJson<int32_t>(int32_t& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsInt64()) {
        return false;
    }
    v = (int32_t)value.GetInt64();
    return true;
}

template <>
bool DeserializeFromJson<int64_t>(int64_t& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsInt64()) {
        return false;
    }
    v = value.GetInt64();
    return true;
}

template <>
bool DeserializeFromJson<uint8_t>(uint8_t& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsUint64()) {
        return false;
    }
    v = (uint8_t)value.GetUint64();
    return true;
}

template <>
bool DeserializeFromJson<uint16_t>(uint16_t& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsUint64()) {
        return false;
    }
    v = (uint16_t)value.GetUint64();
    return true;
}

template <>
bool DeserializeFromJson<uint32_t>(uint32_t& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsUint64()) {
        return false;
    }
    v = (uint32_t)value.GetUint64();
    return true;
}

template <>
bool DeserializeFromJson<uint64_t>(uint64_t& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsUint64()) {
        return false;
    }
    v = value.GetUint64();
    return true;
}

template <>
bool DeserializeFromJson<float>(float& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsFloat()) {
        return false;
    }
    v = value.GetFloat();
    return true;
}

template <>
bool DeserializeFromJson<double>(double& v, const rapidjson::Value& value, const DeserializeContext& context)
{
    (void)context;
    if (!value.IsDouble()) {
        return false;
    }
    v = value.GetDouble();
    return true;
}

}
