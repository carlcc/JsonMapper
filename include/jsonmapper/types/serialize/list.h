#pragma once

#include "../../JsonMapper.h"
#include <list>

namespace jsonmapper {

template <class T>
struct SerializerImpl<std::list<T>> {
    bool operator()(const std::list<T>& list, rapidjson::Value& value, const SerializeContext& context)
    {
        value.SetArray();
        value.Reserve((rapidjson::SizeType)list.size(), context.allocator);
        for (auto& e : list) {
            rapidjson::Value ele;
            if (!SerializeToJson(e, ele, context)) {
                return false;
            }
            value.PushBack(std::move(ele), context.allocator);
        }
        return true;
    }
};

}
