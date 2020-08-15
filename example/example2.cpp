#include <cstdint>
#include <iostream>
#include <jsonmapper/JsonMapper.h>
#include <jsonmapper/types/deserialize/shared_ptr.h>
#include <jsonmapper/types/deserialize/string.h>
#include <jsonmapper/types/deserialize/unordered_map.h>
#include <jsonmapper/types/deserialize/vector.h>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Address {
    std::vector<std::string> street;
    // NOTE: Deserialize from raw pointer is not supported for memory issue
    std::shared_ptr<std::string> nullable_string { nullptr };

    template <class Archiver>
    bool DeserializeFromJson(Archiver& ar)
    {
        return ar(JMKVP(street), JMKVP(nullable_string));
    }
};

struct Student {
    std::unordered_map<std::string, Address> address;
    std::string name;
    int age;

    template <class Archiver>
    bool DeserializeFromJson(Archiver& ar)
    {
        return ar(JMKVP(address), JMKVP(name), JMKVP(age));
    }
};

const std::string kJsonString =
    R"({
    "address": {
        "Home": {
            "street": [
                "ShangHai",
                "China",
                "Asia"
            ],
            "nullable_string": "A nullable string"
        },
        "School": {
            "street": [
                "Beijing",
                "China",
                "Asia"
            ],
            "nullable_string": null
        }
    },
    "name": "Bill",
    "age": 44
})";

int main(int argc, char** argv)
{
    Student stu;
    jsonmapper::DeserializeFromJsonString(stu, kJsonString);
    // Here, the struct `stu` is filled

    return 0;
}
