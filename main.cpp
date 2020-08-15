#include <cstdint>
#include <iostream>
#include <jsonmapper/JsonMapper.h>
#include <jsonmapper/types/deserialize/map.h>
#include <jsonmapper/types/deserialize/raw_ptr.h>
#include <jsonmapper/types/deserialize/set.h>
#include <jsonmapper/types/deserialize/shared_ptr.h>
#include <jsonmapper/types/deserialize/string.h>
#include <jsonmapper/types/deserialize/unordered_map.h>
#include <jsonmapper/types/deserialize/vector.h>
#include <jsonmapper/types/serialize/map.h>
#include <jsonmapper/types/serialize/raw_ptr.h>
#include <jsonmapper/types/serialize/set.h>
#include <jsonmapper/types/serialize/shared_ptr.h>
#include <jsonmapper/types/serialize/string.h>
#include <jsonmapper/types/serialize/unordered_map.h>
#include <jsonmapper/types/serialize/unordered_set.h>
#include <jsonmapper/types/serialize/vector.h>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Address {
    std::vector<std::string> street;
    int number;
    std::set<float> test_field;
    std::string* nullable_string { nullptr };
    std::shared_ptr<std::string> another_nullable_string { nullptr };

    template <class Archiver>
    bool SerializeToJson(Archiver& ar) const
    {
        return ar(
            JMKVP(street),
            JMKVP(number),
            JMKVP(test_field),
            JMKVP(nullable_string), JMKVP(another_nullable_string));
    }
    template <class Archiver>
    bool DeserializeFromJson(Archiver& ar)
    {
        return ar(
            JMKVP(street),
            JMKVP(number),
            JMKVP(test_field),
            // NOTE: Deserialize from raw pointer is no supported for memory issue
            // JMKVP(nullable_string),
            JMKVP(another_nullable_string));
    }
};

struct Student {
    std::unordered_map<std::string, Address> address;
    std::string name;
    int age;
    std::map<std::string, int> scores;

    template <class Archiver>
    bool SerializeToJson(Archiver& ar) const
    {
        return ar(
            JMKVP(address),
            JMKVP(name),
            JMKVP(age),
            JMKVP(scores));
    }
    template <class Archiver>
    bool DeserializeFromJson(Archiver& ar)
    {
        return ar(
            JMKVP(address),
            JMKVP(name),
            JMKVP(age),
            JMKVP(scores));
    }
};

int main(int argc, char** argv)
{
    rapidjson::Document root;

    Student stu;
    std::unique_ptr<std::string> pStr(new std::string("A nullable string"));
    stu.address = {
        {
            "Home",
            {
                { "ShangHai", "China", "Asia" },
                1234,
                {},
                pStr.get(),
                nullptr,
            },
        },
        {
            "School",
            {
                { "Beijing", "China", "Asia" },
                1234,
                { 123, 2.5 },
                nullptr,
                std::make_shared<std::string>("Another nullable string"),
            },
        }
    };
    stu.name = "Bill";
    stu.age = 44;
    stu.scores = {
        { "Math", 100 }, { "Art", 99 }, { "Music", 88 }
    };

    jsonmapper::SerializeContext serializeContext { root.GetAllocator() };
    if (!SerializeToJson(stu, root, serializeContext)) {
        std::cout << " Failed" << std::endl;
        return 1;
    }
    std::cout << "1====!" << std::endl;
    {
        std::stringstream ss;
        rapidjson::OStreamWrapper osw(ss);
        rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
        root.Accept(writer);

        std::cout << ss.str() << std::endl;
    }

    std::cout << "2===!" << std::endl;
    std::string str;
    {
        jsonmapper::SerializeToJsonString(stu, str);
        std::cout << str << std::endl;
    }

    Student stuDeserialize;
    jsonmapper::DeserializeFromJson(stuDeserialize, root, {});

    return 0;
}
