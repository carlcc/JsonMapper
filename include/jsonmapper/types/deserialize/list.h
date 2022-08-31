#pragma once

#include "../../JsonMapper.h"
#include <list>

namespace jsonmapper {

template <class T>
struct DeserializerImpl<std::list<T>> {
    bool operator()(std::list<T>& list, const rapidjson::Value& value, DeserializeContext& context)
    {
        if (!value.IsArray()) {
            context.SetError(std::string("Not a value of list"));
            return false;
        }

        list.resize((size_t)value.Size());

        auto listIt = list.begin();
        size_t i = 0;
        for (auto it = value.Begin(), endIt = value.End(); it != endIt; ++it) {
            if (!DeserializeFromJson(*listIt++, *it, context)) {
                context.SetError("Failed to deserialize element[" + std::to_string(i) + "]");
                return false;
            }
            ++i;
        }
        return true;
    }
};

}
