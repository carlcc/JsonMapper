#pragma once

#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stream.h"
#include "rapidjson/writer.h"

namespace jsonmapper {

struct DeserializeContext {
};

template <class T>
bool DeserializeFromJson(T& t, const rapidjson::Value& value, const DeserializeContext& context);

}

#include "types/basic_types.h"

namespace jsonmapper {

class Deserializer {
public:
    rapidjson::Value& value_;
    const DeserializeContext& context_;

    template <class T>
    bool operator()(const KVPair<T>& kvp)
    {
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
    bool operator()(const T& t, rapidjson::Value& value, const DeserializeContext& context)
    {
    }
};

template <class T>
bool DeserializeFromJson(const T& t, rapidjson::Value& value, const DeserializeContext& context)
{
    return DeserializerImpl<T>()(t, value, context);
}

}
