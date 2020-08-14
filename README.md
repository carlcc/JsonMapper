# JsonMapper
A simple template library to map C++ native structure to JSON and Vice versa

----

# Usage

For those structs/classes you want to serailize to json, all you need to do is define a 

```C++
template <class Archiver>
bool SerializeToJson(Archiver& ar) const;
```
public member function as shown above, then you can serialize this struct to json with only ONE line of code: 
```C++
jsonmapper::SerializeToJsonString(your_struct, the_output_string, true_if_you_want_pretty_print);
```


A complete example:

```C++

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


```


The above code will get the output:

```json
{
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
}
```


----

Deserialize from a json to native struct is not yet implemented.
