#pragma once

#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stream.h"
#include "rapidjson/writer.h"
#include <string_view>

namespace jsonmapper {

struct DeserializeContext {
};

template <class T>
bool DeserializeFromJson(T& t, const rapidjson::Value& value, const DeserializeContext& context);

}

#include "types/deserialize/basic_types.h"

namespace jsonmapper {

class Deserializer {
public:
    const rapidjson::Value& value_;
    const DeserializeContext& context_;

    template <class T>
    bool operator()(const KVPair<T>& kvp)
    {
        auto it = value_.FindMember(kvp.key);
        if (it == value_.MemberEnd()) {
            return false;
        }
        if (!DeserializeFromJson(kvp.value, it->value, context_)) {
            return false;
        }

        return true;
    }
    template <class T>
    bool operator()(const OptKVPair<T>& kvp)
    {
        auto it = value_.FindMember(kvp.key);
        if (it == value_.MemberEnd()) {
            return true;
        }
        if (!DeserializeFromJson(kvp.value, it->value, context_)) {
            return false;
        }

        return true;
    }

    template <class ARG1, class... ARGS>
    bool operator()(const ARG1& arg1, const ARGS&... args)
    {
        return operator()(arg1) && operator()(args...);
    }
};

template <class T>
struct DeserializerImpl {
    bool operator()(T& t, const rapidjson::Value& value, const DeserializeContext& context)
    {
        if (!value.IsObject()) {
            return false;
        }
        Deserializer d { value, context };
        return t.DeserializeFromJson(d);
    }
};

template <class T>
bool DeserializeFromJson(T& t, const rapidjson::Value& value, const DeserializeContext& context)
{
    return DeserializerImpl<T>()(t, value, context);
}

template <class T>
bool DeserializeFromJsonString(T& t, std::string_view string)
{
    rapidjson::Document root;
    root.Parse(string.data(), (rapidjson::SizeType)string.length());
    if (root.HasParseError()) {
        return false;
    }
    if (!DeserializeFromJson<T>(t, root, {})) {
        return false;
    }

    return true;
}

}
