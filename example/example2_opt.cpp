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
        // NOTE:
        // The difference between this example and example2 is that the 'address` field is optional,
        // thus, the deserializer just ignores 'address' field when it cannot find 'address' field.
        // NOTE2:
        // The 'address' field is just optional, if there is 'address' field, but it's wrong data,
        // this function will return false then.
        return ar(JMOPTKVP(address), JMKVP(name), JMKVP(age));
    }
};

const std::string kJsonString =
    R"({
    "name": "Bill",
    "age": 44
})";

int main(int argc, char** argv)
{
    Student stu;
    bool succeed = jsonmapper::DeserializeFromJsonString(stu, kJsonString);
    if (succeed) {
        // Here, the struct `stu` is filled
        std::cout << "Succeed" << std::endl;
    } else {
        std::cout << "Failed" << std::endl;
    }

    return 0;
}
