#pragma once

#include "StringView.h"
#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stream.h"
#include "rapidjson/writer.h"
#include <sstream>

namespace jsonmapper {

struct SerializeContext {
    rapidjson::Value::AllocatorType& allocator;
};

template <class T>
bool SerializeToJson(const T& t, rapidjson::Value& value, const SerializeContext& context);

}

#include "types/serialize/basic_types.h"

namespace jsonmapper {

class Serializer {
public:
    rapidjson::Value& value_;
    const SerializeContext& context_;

    template <class T>
    bool operator()(const KVPair<T>& kvp)
    {
        rapidjson::Value key(kvp.key, context_.allocator);
        rapidjson::Value value;
        if (!SerializeToJson(kvp.value, value, context_)) {
            return false;
        }
        value_.AddMember(key, std::move(value), context_.allocator);

        return true;
    }

    template <class T>
    bool operator()(const OptKVPair<T>& kvp)
    {
        rapidjson::Value key(kvp.key, context_.allocator);
        rapidjson::Value value;
        if (!SerializeToJson(kvp.value, value, context_)) {
            return false;
        }
        value_.AddMember(key, std::move(value), context_.allocator);

        return true;
    }

    template <class ARG1, class... ARGS>
    bool operator()(const ARG1& arg1, const ARGS&... args)
    {
        return operator()(arg1) && operator()(args...);
    }
};

template <class T>
struct SerializerImpl {
    bool operator()(const T& t, rapidjson::Value& value, const SerializeContext& context)
    {
        Serializer s { value, context };
        value.SetObject();
        return t.SerializeToJson(s);
    }
};

template <class T>
inline bool SerializeToJson(const T& t, rapidjson::Value& value, const SerializeContext& context)
{
    return SerializerImpl<T>()(t, value, context);
}

template <class T>
inline bool SerializeToJsonString(const T& t, std::string& string, bool pretty = false)
{
    rapidjson::Document root;
    if (!SerializeToJson<T>(t, root, { root.GetAllocator() })) {
        return false;
    }

    // TODO: move the following logic into cpp a file
    std::stringstream ss;
    rapidjson::OStreamWrapper osw(ss);
    if (pretty) {
        rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
        root.Accept(writer);
        string = ss.str();
    } else {
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
        root.Accept(writer);
        string = ss.str();
    }
    return true;
}

}
