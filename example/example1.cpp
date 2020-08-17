#include <cstdint>
#include <iostream>
#include <jsonmapper/JsonMapper.h>
#include <jsonmapper/types/serialize/raw_ptr.h>
#include <jsonmapper/types/serialize/string.h>
#include <jsonmapper/types/serialize/unordered_map.h>
#include <jsonmapper/types/serialize/vector.h>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Address {
    std::vector<std::string> street;
    std::string* nullable_string { nullptr };

    template <class Archiver>
    bool SerializeToJson(Archiver& ar) const
    {
        return ar(JMKVP(street), JMKVP(nullable_string));
    }
};

struct Student {
    std::unordered_map<std::string, Address> address;
    std::string name;
    int age;

    template <class Archiver>
    bool SerializeToJson(Archiver& ar) const
    {
        return ar(JMKVP(address), JMKVP(name), JMKVP(age));
    }
};

int main(int argc, char** argv)
{
    rapidjson::Document root;

    Student stu;
    std::unique_ptr<std::string> pStr(new std::string("A nullable string"));
    stu.address = {
        { "Home", { { "ShangHai", "China", "Asia" }, pStr.get() } },
        { "School", { { "Beijing", "China", "Asia" }, nullptr } }
    };
    stu.name = "Bill";
    stu.age = 44;

    {
        std::string str;
        jsonmapper::SerializeToJsonString(stu, str, true);
        std::cout << str << std::endl;
    }

    return 0;
}
