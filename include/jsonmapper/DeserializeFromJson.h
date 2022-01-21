#pragma once

#include "StringView.h"
#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stream.h"
#include "rapidjson/writer.h"
#include <list>
#include <rapidjson/error/en.h>

namespace jsonmapper {

struct DeserializeContext {
public:
    const std::list<std::string>& GetError() const { return errorString_; }
    std::string GetErrorString() const
    {
        std::string err;
        int stackIndex = 0;
        for (auto& s : errorString_) {
            err += std::to_string(stackIndex++);
            err += ": ";
            err += s + '\n';
        }
        return err;
    }
    void SetError(std::string&& err)
    {
        errorString_.push_front(std::move(err));
    }

private:
    std::list<std::string> errorString_;
};

template <class T>
bool DeserializeFromJson(T& t, const rapidjson::Value& value, DeserializeContext& context);

}

#include "types/deserialize/basic_types.h"

namespace jsonmapper {

class Deserializer {
public:
    const rapidjson::Value& value_;
    DeserializeContext& context_;

    template <class T>
    bool operator()(const KVPair<T>& kvp)
    {
        auto it = value_.FindMember(kvp.key);
        if (it == value_.MemberEnd()) {
            context_.SetError(std::string("Field '") + kvp.key + "' is required but not found!");
            return false;
        }
        if (!DeserializeFromJson(kvp.value, it->value, context_)) {
            context_.SetError(std::string("Failed to deserialize field '") + kvp.key + "'");
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
            context_.SetError(std::string("Failed to deserialize field '") + kvp.key + "'");
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
    bool operator()(T& t, const rapidjson::Value& value, DeserializeContext& context)
    {
        if (!value.IsObject()) {
            context.SetError("Json is not an object");
            return false;
        }
        Deserializer d { value, context };
        return t.DeserializeFromJson(d);
    }
};

template <class T>
inline bool DeserializeFromJson(T& t, const rapidjson::Value& value, DeserializeContext& context)
{
    return DeserializerImpl<T>()(t, value, context);
}

template <class T>
inline bool DeserializeFromJsonString(T& t, StringView string)
{
    rapidjson::Document root;
    root.Parse(string.data(), (rapidjson::SizeType)string.length());
    if (root.HasParseError()) {
        return false;
    }
    DeserializeContext context {};
    if (!DeserializeFromJson<T>(t, root, context)) {
        return false;
    }

    return true;
}

template <class T>
inline bool DeserializeFromJsonString(T& t, StringView string, DeserializeContext& context)
{
    rapidjson::Document root;
    root.Parse(string.data(), (rapidjson::SizeType)string.length());
    if (root.HasParseError()) {
        char buf[512];
        sprintf(buf, "Failed to parse json: %s, around offset %zu\n", rapidjson::GetParseError_En(root.GetParseError()), root.GetErrorOffset());
        context.SetError(buf);
        return false;
    }
    if (!DeserializeFromJson<T>(t, root, context)) {
        return false;
    }

    return true;
}

}
