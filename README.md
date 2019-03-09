# [README.md](http://readme.md) IniFile

# **IniFile**

---

IniFile is an INI file parser writen in C++.

INI files are initialization files with a simple syntax.

You can find INI syntax in `.ini`, `.config`, `.conf`, `.cnf`, `.cft`, `.cf`...

This parser does not care about the extension of the file until you respect the INI syntax.

# **Inplementation:**

---

make

    #include "IniFile.hpp"

# **Usage:**

---

The IniFile class transform the INI file into a map. The map is defined like this:

    std::map<std::string, std::map<std::string, std::string>>
             Section               Key          Value

A value can be obtained like this:

    std::string value = configMap["section"]["key"];

## **Constructor:**

---

The constructor take the file path as parameter.

    IniFile config("filepath");

Then, the `getMap()` methods should be called to get the map of the INI file.

    auto configMap = config.getMap();

## Conversion:

---

**To get a value as an int:**

    int value = config.getInt("sectionName", "key");

**To get a value as a bool:**

    bool value = config.getBool("sectionName", "key");

You can see examples in the example folder.

## **Types:**

---

**int:**

It must be between intMin and intMax.

    size = 42

Get the int value by doing :

    int value = config.getInt("sectionName", "key");

**string:**

Stored as `std::string`

    name = John Doe

Get the string value by doing :

    std::string value = configMap["section"]["key"];

**bool:**

Can be written as `true` / `flase` or `1` / `0`

    enabled = true
    enabled = 1

Get a bool value by doing :

    bool value = config.getBool("sectionName", "key");

## **Syntax:**

### **Properties:**

A property is composed of a key and a value separated by a `=` or a `:`.

It's the basic element of an INI file.

    key = value
    key : value

A value can be written outside or inside quote (`"` or `'`).

    name = John Doe
    name = "John Doe"
    name = 'John Doe'

### **Section:**

A section is a name used to group multiple keys together. This name must be written between square brackets `[]`.

    [section name]

Evey keys written below a section is part of this section until another section is declared.

Keys who do not belong to any sections are called 'global property' and are stored in the golbal section

You can access it like that:

    `yourMap["global"]["key"].`

### **Comment:**

All text after a comment character is ignored.

`;` and `#` characters can be used as a line comment and inline comment.

    ;this is a line comment
    Key = value ;this is an inline comment

[Escape characters:](https://www.notion.so/975d3c93bb1a49f899b42ac9aebb40d0)

### **Reference to previous key:**

To give a value described in a previous key use `$` followed by the key name between curly brackets `{}`.

    lastName = Doe
    full name = John ${lastName}

Or simply by using `$`.

    fullName = John $lastName

### Good to know:

---

### **Case sensitivity:**

Keys and sections name are case sensitive.

    name = John Doe
    Name = John Doe ;Name != name

### **Blank lines:**

Blank lines are allowed.

    [player]
    
    name = John Doe

### **Duplicate key:**

If a key name is duplicate inside of the same section, the last value will overwrite the first.

    name = John
    name = John Doe ;the name key will have the value "John Doe"

### **Trailing spaces:**

Spaces between key, `=`/`:` and value are ignored.

    name = John
    name=John
    name  =    John

### **Spaces in key name:**

Spaces in a key name will be removed.

    last name = Doe ;will become lastname

### **Line break:**

You can write a value on multiple lines using the \ character.

    name = John \
    Doe
    
    name = John \
    			 Doe

### Call other ini file: