# JsonMapper
A simple template library to map C++ native structure to JSON and Vice versa

----

# Usage

# Serialize to json

For those structs/classes you want to serailize to json, all you need to do is define a 

```C++
template <class Archiver>
bool SerializeToJson(Archiver& ar) const;
```
public member function as shown below, then you can serialize this struct to json with only ONE line of code: 
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

# Deserialize from json

For those structs/classes you want to deserailize from json, all you need to do is define a 

```C++
template <class Archiver>
bool DeserializeFromJson(Archiver& ar);
```
public member function as shown above, then you can deserialize this struct from json with only ONE line of code: 
```C++
jsonmapper::DeserializeFromJsonString(your_struct, the_input_string);
```


A complete example:


```C++

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
```

# Helper macros

In most cases, we may want to define both serialize and deserialize, thus, some helper macros are defined to simplify the process.

## You can use `JM_DEFINE_MAP` in a struct/class

```C++

struct Address {
    std::vector<std::string> street;
    std::shared_ptr<std::string> nullable_string { nullptr };

    JM_DEFINE_MAP(
        JMKVP(street),              // This field must be provided when deserializing
        JMOPTKVP(nullable_string)   // This field is optional
        // You can also use ::jsonmapper::MakeKVPair and ::jsonmapper::MakeOPTKVPair if you want to use another name in json
    )
};

```

## You can use `JM_CLASS` out of a struct/class


```C++

struct Address {
    std::vector<std::string> street;
    std::shared_ptr<std::string> nullable_string { nullptr };
};

JM_CLASS(Address,
    JMKVP2(street),             // This field must be provided when deserializing 
    JMOPTKVP2(nullable_string)  // This field is optional
    // Note that we MUST use JMKVP2 and JMOPTKVP2, instead of JMKVP and JMKVP2
    // You can also use ::jsonmapper::MakeKVPair and ::jsonmapper::MakeOPTKVPair if you want to use another name in json. But, we have to use the form 't.street' since 'this' is not available, and 't' is used to refer 'this'
)

```

# Enums

Enums are also supported

```C++

enum class MyEnum {
    kA = 0,
    kB = 2,
    kC = 10,
};

JM_ENUM(MyEnum,
    JMEKVP(kA), // json string 'kA' == MyEnum::kA
    JMEKVP(kB), // json string 'kB' == MyEnum::kB
    ::jsonmapper::MakeEKVPair("kCCCC", kC), // You can also specify a custom name, in this case, json string 'kCCCC' == MyEnum::kC
);

```

After this, the corresponding string attribute will be parsed to `MyEnum` variable, and `MyEnum` attributes will be store to a string.