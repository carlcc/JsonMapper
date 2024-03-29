#pragma once

#include "../../JsonMapper.h"
#include <string>

namespace jsonmapper {

template <>
inline bool DeserializeFromJson<bool>(bool& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsBool()) {
        context.SetError(std::string("Not a value of bool"));
        return false;
    }
    v = value.GetBool();
    return true;
}

template <>
inline bool DeserializeFromJson<int8_t>(int8_t& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsInt64()) {
        context.SetError(std::string("Not a value of int8"));
        return false;
    }
    v = (int8_t)value.GetInt64();
    return true;
}

template <>
inline bool DeserializeFromJson<int16_t>(int16_t& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsInt64()) {
        context.SetError(std::string("Not a value of int16"));
        return false;
    }
    v = (int16_t)value.GetInt64();
    return true;
}

template <>
inline bool DeserializeFromJson<int32_t>(int32_t& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsInt64()) {
        context.SetError(std::string("Not a value of int32"));
        return false;
    }
    v = (int32_t)value.GetInt64();
    return true;
}

template <>
inline bool DeserializeFromJson<int64_t>(int64_t& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsInt64()) {
        context.SetError(std::string("Not a value of int64"));
        return false;
    }
    v = value.GetInt64();
    return true;
}

template <>
inline bool DeserializeFromJson<uint8_t>(uint8_t& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsUint64()) {
        context.SetError(std::string("Not a value of uint8"));
        return false;
    }
    v = (uint8_t)value.GetUint64();
    return true;
}

template <>
inline bool DeserializeFromJson<uint16_t>(uint16_t& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsUint64()) {
        context.SetError(std::string("Not a value of uint16"));
        return false;
    }
    v = (uint16_t)value.GetUint64();
    return true;
}

template <>
inline bool DeserializeFromJson<uint32_t>(uint32_t& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsUint64()) {
        context.SetError(std::string("Not a value of uint32"));
        return false;
    }
    v = (uint32_t)value.GetUint64();
    return true;
}

template <>
inline bool DeserializeFromJson<uint64_t>(uint64_t& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsUint64()) {
        context.SetError(std::string("Not a value of uint64"));
        return false;
    }
    v = value.GetUint64();
    return true;
}

template <>
inline bool DeserializeFromJson<float>(float& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsFloat()) {
        context.SetError(std::string("Not a value of float"));
        return false;
    }
    v = value.GetFloat();
    return true;
}

template <>
inline bool DeserializeFromJson<double>(double& v, const rapidjson::Value& value, DeserializeContext& context)
{
    (void)context;
    if (!value.IsDouble()) {
        context.SetError(std::string("Not a value of double"));
        return false;
    }
    v = value.GetDouble();
    return true;
}

}
