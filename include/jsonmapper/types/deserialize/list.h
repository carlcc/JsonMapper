#pragma once

#include "../../JsonMapper.h"
#include <list>

namespace jsonmapper {

template <class T>
struct DeserializerImpl<std::list<T>> {
    bool operator()(std::list<T>& list, const rapidjson::Value& value, const DeserializeContext& context)
    {
        if (!value.IsArray()) {
            return false;
        }

        list.resize((size_t)value.Size());

        auto listIt = list.begin();
        for (auto it = value.Begin(), endIt = value.End(); it != endIt; ++it) {
            if (!DeserializeFromJson(*listIt++, *it, context)) {
                return false;
            }
        }
        return true;
    }
};

}
