#pragma once

#include "StringView.h"
#include <unordered_map>

namespace jsonmapper {

template <class T>
struct KVPair {
    const char* key;
    T& value;
};

template <class T>
inline KVPair<T> MakeKVPair(const char* key, T& value)
{
    return KVPair<T> { key, value };
}

template <class T>
struct OptKVPair {
    const char* key;
    T& value;
};

template <class T>
inline OptKVPair<T> MakeOptKVPair(const char* key, T& value)
{
    return OptKVPair<T> { key, value };
}

template <class T>
struct EKVPair {
    const char* key;
    T value;
};

template <typename T>
inline EKVPair<T> MakeEKVPair(const char* key, T value)
{
    return EKVPair<T> { key, value };
}

template <typename Enum, typename... ARGS>
const auto& getToEnumMap(ARGS... args)
{
    static std::unordered_map<StringView, Enum> map {
        { args.key, args.value }...
    };
    return map;
}

template <typename Enum, typename... ARGS>
const auto& getFromEnumMap(ARGS... args)
{
    static std::unordered_map<Enum, StringView> map {
        { args.value, args.key }...
    };
    return map;
}

#define JMKVP(field) ::jsonmapper::MakeKVPair(#field, field)

#define JMOPTKVP(field) ::jsonmapper::MakeOptKVPair(#field, field)

#define JMKVP2(field) ::jsonmapper::MakeKVPair(#field, t.field)

#define JMOPTKVP2(field) ::jsonmapper::MakeOptKVPair(#field, t.field)

#define JMEKVP(enum_) ::jsonmapper::MakeEKVPair(#enum_, enum_)

} // namespace jsonmapper

#include "DeserializeFromJson.h"
#include "SerializeToJson.h"

#define JM_DEFINE_MAP(...)                            \
public:                                               \
    template <class Archiver>                         \
    bool SerializeToJson(Archiver& ar) const noexcept \
    {                                                 \
        return ar(__VA_ARGS__);                       \
    }                                                 \
    template <class Archiver>                         \
    bool DeserializeFromJson(Archiver& ar) noexcept   \
    {                                                 \
        return ar(__VA_ARGS__);                       \
    }

#define JM_ENUM(clazz, ...)                                                                   \
    template <>                                                                               \
    struct ::jsonmapper::SerializerImpl<clazz> {                                              \
        bool operator()(clazz t, rapidjson::Value& value, const SerializeContext& context)    \
        {                                                                                     \
            using enum clazz;                                                                 \
            auto& map = getFromEnumMap<clazz>(__VA_ARGS__);                                   \
            auto it = map.find(t);                                                            \
            if (it == map.end()) {                                                            \
                return false;                                                                 \
            }                                                                                 \
            auto& v = it->second;                                                             \
            value.SetString(v.data(), (rapidjson::SizeType)v.length(), context.allocator);    \
            return true;                                                                      \
        }                                                                                     \
    };                                                                                        \
    template <>                                                                               \
    struct ::jsonmapper::DeserializerImpl<clazz> {                                            \
        bool operator()(clazz& t, const rapidjson::Value& value, DeserializeContext& context) \
        {                                                                                     \
            using enum clazz;                                                                 \
            if (!value.IsString()) {                                                          \
                context.SetError("Is not a string!");                                         \
                return false;                                                                 \
            }                                                                                 \
            auto& map = getToEnumMap<clazz>(__VA_ARGS__);                                     \
            ::jsonmapper::StringView key(value.GetString(), (size_t)value.GetStringLength()); \
            auto it = map.find(key);                                                          \
            if (it == map.end()) {                                                            \
                context.SetError("Invalid enum name");                                        \
                return false;                                                                 \
            }                                                                                 \
            t = it->second;                                                                   \
            return true;                                                                      \
        }                                                                                     \
    };

#define JM_CLASS(clazz, ...)                                                                      \
    template <>                                                                                   \
    struct ::jsonmapper::SerializerImpl<clazz> {                                                  \
        bool operator()(const clazz& t, rapidjson::Value& value, const SerializeContext& context) \
        {                                                                                         \
            jsonmapper::Serializer s { value, context };                                          \
            value.SetObject();                                                                    \
            return s(__VA_ARGS__);                                                                \
        }                                                                                         \
    };                                                                                            \
    template <>                                                                                   \
    struct ::jsonmapper::DeserializerImpl<clazz> {                                                \
        bool operator()(clazz& t, const rapidjson::Value& value, DeserializeContext& context)     \
        {                                                                                         \
            jsonmapper::Deserializer d { value, context };                                        \
            return d(__VA_ARGS__);                                                                \
        }                                                                                         \
    };