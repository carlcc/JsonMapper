//
// Copyright (c) 2020 Carl Chen. All rights reserved.
//
#include <cstdint>
#include <cstring>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/rapidjson.h>
#include <string>
#include <vector>

#define JM_KVP(var) ::jsonmapper::MakeKVP(#var, var)

namespace jsonmapper {

template <class T>
struct KVP {
    const char* key;
    T& value;
};

template <class T>
KVP<T> MakeKVP(const char* key, T& value)
{
    return KVP<T> { key, value };
}

template <class JsonValue, bool isSerialize, class T>
bool Map(JsonValue& root, T& v);

template <class JsonValue, bool isSerialize, class T>
struct GenericMapper {
    JsonValue& root_;
    explicit GenericMapper(JsonValue& obj)
        : root_(obj)
    {
    }

    bool operator()(T& i)
    {
        if constexpr (isSerialize) {
            if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<T, bool> || std::is_same_v<T, std::string>) {
                root_ = i;
                return true;
            } else {
                return Map<JsonValue, isSerialize>(root_, i);
            }
        } else {
            if constexpr (std::is_integral_v<T>) {
                if (!root_.IsNumber()) {
                    return false;
                }
                i = root_.AsInt64();
                return true;
            } else if constexpr (std::is_floating_point_v<T>) {
                if (!root_.IsNumber()) {
                    return false;
                }
                i = root_.AsDouble();
                return true;
            } else if constexpr (std::is_same_v<T, bool>) {
                if (!root_.IsBool()) {
                    return false;
                }
                i = root_.AsBool();
                return true;
            } else {
                return Map<JsonValue, isSerialize>(root_, i);
            }
        }
    }
};

template <class JsonValue, bool isSerialize>
struct GenericMapper<JsonValue, isSerialize, std::string> {
    JsonValue& root_;
    explicit GenericMapper(JsonValue& obj)
        : root_(obj)
    {
    }

    bool operator()(std::string& s)
    {
        if constexpr (isSerialize) {
            root_ = s;
            return true;
        } else {
            if (!root_.IsString()) {
                return false;
            }
            s = root_.AsString();
            return true;
        }
    }
};

template <class JsonValue, bool isSerialize, class T>
struct GenericMapper<JsonValue, isSerialize, std::vector<T>> {
    JsonValue& root_;
    explicit GenericMapper(JsonValue& obj)
        : root_(obj)
    {
    }

    bool operator()(std::vector<T>& v)
    {
        if constexpr (isSerialize) {
            int index = 0;
            for (auto& t : v) {
                auto child = root_[index++];
                if (!GenericMapper<JsonValue, isSerialize, T>(child)(t)) {
                    return false;
                }
            }
            return true;
        } else {
            if (!root_.IsArray()) {
                return false;
            }
            int size = root_.Size();
            v.resize(size);
            int index = 0;
            for (int index = 0; index < size; ++index) {
                auto child = root_.ArrayChild(index);
                if (!GenericMapper<JsonValue, isSerialize, T>(child)(v[index])) {
                    return false;
                }
            }
            return true;
        }
    }
};

template <class JsonValue, bool isSerialize, bool isAllFieldRequired = false>
class Mapper {
public:
    JsonValue& root_;
    explicit Mapper(JsonValue& obj)
        : root_(obj)
    {
    }

    template <class Arg>
    bool operator()(Arg& arg)
    {
        return GenericMapper<JsonValue, isSerialize, Arg>(root_)(arg);
    }

    template <class Arg>
    bool operator()(const KVP<Arg>& arg)
    {
        if constexpr (isSerialize) {
            auto child = root_[arg.key];
            return GenericMapper<JsonValue, isSerialize, Arg>(child)(arg.value);
        } else {
            if (root_.HasMember(arg.key)) {
                auto child = root_[arg.key];
                return GenericMapper<JsonValue, isSerialize, Arg>(child)(arg.value);
            }
            return !isAllFieldRequired;
        }
    }

    template <class Arg, class... Args>
    bool operator()(const KVP<Arg>& arg, const KVP<Args>&... args)
    {
        return operator()(arg) && operator()(args...);
    }
};

template <class JsonValue>
using SerializeMapper = Mapper<JsonValue, true>;
template <class JsonValue>
using DeserializeMapper = Mapper<JsonValue, false>;

template <class JsonValue, bool isSerialize, class T>
bool Map(JsonValue& root, T& v)
{
    Mapper<JsonValue, isSerialize> mapper(root);
    return v.MapJson(mapper);
}

}

struct Student {
    std::string name;
    int age;
    std::vector<float> scores;

    template <class Mapper>
    bool MapJson(Mapper& mapper)
    {
        return mapper(JM_KVP(name), JM_KVP(age), JM_KVP(scores));
    }
};

struct ClassRoom {
    std::vector<Student> students;
    int grade;
    int clazz;

    template <class Mapper>
    bool MapJson(Mapper& mapper)
    {
        return mapper(JM_KVP(students), JM_KVP(grade), JM_KVP(clazz));
    }
};

inline bool operator==(const Student& a, const Student& b)
{
    if (a.scores.size() != b.scores.size()) {
        return false;
    }
    for (size_t i = 0; i < a.scores.size(); ++i) {
        if (a.scores[i] != b.scores[i]) {
            return false;
        }
    }
    return a.name == b.name && a.age == b.age;
}
inline bool operator==(const ClassRoom& a, const ClassRoom& b)
{
    if (a.students.size() != b.students.size()) {
        return false;
    }
    for (size_t i = 0; i < a.students.size(); ++i) {
        if (!(a.students[i] == b.students[i])) {
            return false;
        }
    }
    return a.grade == b.grade && a.clazz == b.clazz;
}

struct JsonValueWrapper {
    rapidjson::Value& root_;
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& allocator_;

    JsonValueWrapper& operator=(int i)
    {
        root_.SetInt(i);
        return *this;
    }
    JsonValueWrapper& operator=(int64_t i)
    {
        root_.SetInt64(i);
        return *this;
    }
    JsonValueWrapper& operator=(double i)
    {
        root_.SetDouble(i);
        return *this;
    }
    JsonValueWrapper& operator=(float i)
    {
        root_.SetFloat(i);
        return *this;
    }
    JsonValueWrapper& operator=(bool i)
    {
        root_.SetBool(i);
        return *this;
    }
    JsonValueWrapper& operator=(const std::string& i)
    {
        root_.SetString(i.c_str(), i.length());
        return *this;
    }

    std::string AsString() const
    {
        return root_.GetString();
    }

    int64_t AsInt64() const
    {
        return root_.GetInt64();
    }

    int32_t AsInt32() const
    {
        return root_.GetInt();
    }

    double AsDouble() const
    {
        return root_.GetDouble();
    }

    bool AsBool() const
    {
        return root_.GetBool();
    }

    bool IsString() const { return root_.IsString(); }
    bool IsInt64() const { return root_.IsInt64(); }
    bool IsInt32() const { return root_.IsInt(); }
    bool IsNumber() const { return root_.IsNumber(); }
    bool IsDouble() const { return root_.IsDouble(); }
    bool IsBool() const { return root_.IsBool(); }
    bool IsArray() const { return root_.IsArray(); }

    bool HasMember(const std::string& key) const
    {
        if (!root_.IsObject()) {
            root_.SetObject();
        }
        return root_.HasMember(key.c_str());
    }

    int Size() const
    {
        return root_.Size();
    }

    JsonValueWrapper ArrayChild(int index)
    {
        return JsonValueWrapper { root_[index], allocator_ };
    }

    JsonValueWrapper operator[](int index)
    {
        if (!root_.IsArray()) {
            root_.SetArray();
        }
        if (index >= root_.Size()) {
            root_.GetArray().PushBack(rapidjson::Value(), allocator_);
        }
        return JsonValueWrapper { root_[index], allocator_ };
    }

    JsonValueWrapper operator[](const std::string& s)
    {
        if (!root_.IsObject()) {
            root_.SetObject();
        }
        auto it = root_.FindMember(s.c_str());
        rapidjson::Value *pValue = nullptr;
        if (it == root_.MemberEnd()) {
            rapidjson::Value key;
            key.SetString(s.c_str(), s.length());
            pValue = &root_.AddMember(std::move(key), rapidjson::Value(rapidjson::kObjectType), allocator_);
        } else {
            pValue = &it->value;
        }
        return JsonValueWrapper { *pValue, allocator_ };
    }
};

int main()
{
    ClassRoom room;
    room.clazz = 3;
    room.grade = 5;
    room.students = {
        { "Bill", 12, { 99, 98, 85.5 } },
        { "Sam", 13, { 99, 98, 84.5 } },
        { "Alice", 11, { 88, 98, 84.5 } },
    };

    rapidjson::Document root(rapidjson::kObjectType);
    JsonValueWrapper wrapperRoot { root, root.GetAllocator() };
    jsonmapper::SerializeMapper<JsonValueWrapper> mapper(wrapperRoot);

    room.MapJson(mapper);

    rapidjson::OStreamWrapper osw(std::cout);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    root.Accept(writer);

    std::cout << std::endl;

    ClassRoom room_dup;
    jsonmapper::DeserializeMapper<JsonValueWrapper> demapper(wrapperRoot);
    room_dup.MapJson(demapper);

    std::cout << (room_dup == room) << std::endl;

    return 0;
}