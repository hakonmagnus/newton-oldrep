// Copyright (c) 2022 Hákon Hjaltalín.
//
// This project is licensed under the MIT license. Please see LICENSE
// or go to https://opensource.org/licenses/MIT for more information.

#include "newton/newton.h"
using namespace newton;

#include <string>
#include <iostream>
#include <sstream>

static NtJSONObject* NtParseJSONObject(std::string& str, int& line, int& pos);
static NtJSONArray* NtParseJSONArray(std::string& str, int& line, int& pos);

static void NtJSONTrim(std::string& str, int& line, int& pos)
{
    if (pos >= str.size()) {
        return;
    }

    while (str[pos] == ' ' ||
            str[pos] == '\r' ||
            str[pos] == '\b' ||
            str[pos] == '\n') {
        if (str[pos] == '\n')
            ++line;

        ++pos;
    }
}

static std::string NtParseJSONString(std::string& str, int& line, int& pos)
{
    std::string ret = "";

    if (pos >= str.size()) {
        std::stringstream ss;
        ss << "Line " << line << ": Invalid JSON string.";
        throw NtSyntaxError(ss.str());
    }

    if (str[pos] == '"') {
        ++pos;
    }

    if (pos >= str.size()) {
        std::stringstream ss;
        ss << "Line " << line << ": Unterminated JSON string.";
        throw NtSyntaxError(ss.str());
    }

    while (pos <= str.size() && str[pos] != '"') {
        if (str[pos] == '\\') {
            ++pos;

            if (pos <= str.size()) {
                std::stringstream ss;
                ss << "Line " << line << ": Unterminated escape sequence.";
                throw NtSyntaxError(ss.str());
            }

            switch (str[pos]) {
            case '"':
                ret += '"';
                break;
            case '\\':
                ret += '\\';
                break;
            case '/':
                ret += '/';
                break;
            case 'b':
                ret += '\b';
                break;
            case 'f':
                ret += '\f';
                break;
            case 'n':
                ret += '\n';
                break;
            case 'r':
                ret += '\r';
                break;
            case 't':
                ret += '\t';
                break;
            case 'u':
                {
                    ++pos;

                    if (pos + 4 >= str.size()) {
                        std::stringstream ss;
                        ss << "Line " << line << ": Invalid hex sequence.";
                        throw NtSyntaxError(ss.str());
                    }

                    std::string hex = str.substr(pos, 4);
                    pos += 3;

                    std::stringstream ss;
                    ss << std::hex << hex;
                    uint16_t c;
                    ss >> c;
                    ret += c;
                }
                break;
            default:
                {
                    std::stringstream ss;
                    ss << "Line " << line << ": Invalid escape sequence.";
                    throw NtSyntaxError(ss.str());
                }
                break;
            }

            ++pos;
        } else {
            ret += str[pos++];
        }
    }

    if (str[pos] == '"') {
        ++pos;
    }

    return ret;
}

static double NtParseJSONNumber(std::string& str, int& line, int& pos)
{
    double num = 0.0;
    bool isDouble = false;
    std::string part = "";

    while (pos <= str.size() && (
                str[pos] == '0' ||
                str[pos] == '1' ||
                str[pos] == '2' ||
                str[pos] == '3' ||
                str[pos] == '4' ||
                str[pos] == '5' ||
                str[pos] == '6' ||
                str[pos] == '7' ||
                str[pos] == '8' ||
                str[pos] == '9' ||
                str[pos] == '.' ||
                str[pos] == 'e' ||
                str[pos] == 'E' ||
                str[pos] == '-' ||
                str[pos] == '+')) {
        if (str[pos] == '.' ||
                str[pos] == 'e' ||
                str[pos] == 'E' ||
                str[pos] == '-' ||
                str[pos] == '+')
            isDouble = true;
        part += str[pos++];
    }
    
    std::stringstream ss(part);

    if (isDouble) {
        ss >> num;
    } else {
        int i = 0;
        ss >> i;
        num = static_cast<double>(i);
    }

    return num;
}

static NtJSONElement* NtParseJSONElement(std::string& str, int& line, int& pos)
{
    NtJSONTrim(str, line, pos);

    if (pos >= str.size()) {
        std::stringstream ss;
        ss << "Line " << line << ": Invalid JSON value.";
        throw NtSyntaxError(ss.str());
    }

    switch (str[pos]) {
    case '{':
        {
            NtJSONObject* obj = NtParseJSONObject(str, line, pos);
            return static_cast<NtJSONElement*>(obj);
        }
        break;
    case '[':
        {
            NtJSONArray* arr = NtParseJSONArray(str, line, pos);
            return static_cast<NtJSONElement*>(arr);
        }
        break;
    case '"':
        {
            std::string strn = NtParseJSONString(str, line, pos);
            NtJSONString* strobj = new NtJSONString(strn);
            return static_cast<NtJSONElement*>(strobj);
        }
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
    case '-':
        {
            double num = NtParseJSONNumber(str, line, pos);
            std::cout << "number " << num << std::endl;
            NtJSONNumber* numobj = new NtJSONNumber(num);
            return static_cast<NtJSONElement*>(numobj);
        }
        break;
    case 't':
    case 'f':
    case 'n':
        {
            if (pos + 4 > str.size()) {
                std::stringstream ss;
                ss << "Line " << line << ": Invalid JSON value.";
                throw NtSyntaxError(ss.str());
            }

            std::string sub = str.substr(pos, 4);
            
            if (sub == "true") {
                pos += 4;
                NtJSONBoolean* b = new NtJSONBoolean(true);
                return static_cast<NtJSONElement*>(b);
            } else if (sub == "null") {
                pos += 4;
                NtJSONNull* n = new NtJSONNull();
                return static_cast<NtJSONElement*>(n);
            } else {
                if (pos + 5 <= str.size()) {
                    sub = str.substr(pos, 5);

                    if (sub == "false") {
                        pos += 5;
                        NtJSONBoolean* b = new NtJSONBoolean(false);
                        return static_cast<NtJSONElement*>(b);
                    }
                }
            }

            std::stringstream ss;
            ss << "Line " << line << ": Invalid JSON value.";
            throw NtSyntaxError(ss.str());
        }
        break;
    default:
        {
            std::stringstream ss;
            ss << "Line " << line << ": Invalid JSON value.";
            throw NtSyntaxError(ss.str());
        }
        break;
    }
    
    return nullptr;
}

static NtJSONArray* NtParseJSONArray(std::string& str, int& line, int& pos)
{
    NtJSONTrim(str, line, pos);

    if (pos >= str.size()) {
        std::stringstream ss;
        ss << "Line " << line << ": Invalid JSON object.";
        throw NtSyntaxError(ss.str());
    }

    NtJSONArray* arr = new NtJSONArray();

    if (str[pos] == '[')
        ++pos;

    while (pos <= str.size() && str[pos] != ']') {
        NtJSONTrim(str, line, pos);

        if (str[pos] == ']') {
            break;
        }

        NtJSONElement* elmt = NtParseJSONElement(str, line, pos);

        if (elmt) {
            arr->add(elmt);
        }

        if (str[pos] == ',') {
            ++pos;
        }
    }

    if (str[pos] != ']') {
        std::stringstream ss;
        ss << "Line " << line << ": Invalid termination of JSON array.";
        throw NtSyntaxError(ss.str());
    }

    ++pos;
    return arr;
}

static NtJSONObject* NtParseJSONObject(std::string& str, int& line, int& pos)
{
    NtJSONTrim(str, line, pos);

    if (pos >= str.size()) {
        std::stringstream ss;
        ss << "Line " << line << ": Invalid JSON object.";
        throw NtSyntaxError(ss.str());
    }

    NtJSONObject* obj = new NtJSONObject();

    if (str[pos] == '{')
        ++pos;

    while (pos <= str.size() && str[pos] != '}') {
        NtJSONTrim(str, line, pos);

        if (str[pos] == '}') {
            break;
        }

        if (str[pos] == '"') {
            std::string name = NtParseJSONString(str, line, pos);
            NtJSONTrim(str, line, pos);

            if (str[pos] != ':') {
                std::stringstream ss;
                ss << "Line " << line << ": Member name must be followed by ':' colon character.";
                throw NtSyntaxError(ss.str());
            }

            ++pos;

            if (pos >= str.size()) {
                std::stringstream ss;
                ss << "Line " << line << ": Invalid object member.";
                throw NtSyntaxError(ss.str());
            }

            NtJSONElement* elm = NtParseJSONElement(str, line, pos);

            if (elm) {
                obj->add(name, elm);
            }

            if (str[pos] == ',') {
                ++pos;
            }

            continue;
        } else {
            std::stringstream ss;
            ss << "Line " << line << ": Invalid member in JSON object.";
            throw NtSyntaxError(ss.str());
        }

        ++pos;
    }

    if (str[pos] != '}') {
        std::stringstream ss;
        ss << "Line " << line << ": Invalid termination of JSON object.";
        throw NtSyntaxError(ss.str());
    }

    ++pos;
    return obj;
}

NtJSONObject* newton::NtParseJSON(const char* json)
{
    int pos = 0;
    int line = 1;
    std::string str = json;

    if (str.size() == 0) {
        return new NtJSONObject();
    }

    NtJSONTrim(str, line, pos);

    if (str[pos] != '{') {
        std::stringstream ss;
        ss << "Line " << line << ": JSON file must be a valid JSON object.";
        throw NtSyntaxError(ss.str());
    }

    return NtParseJSONObject(str, line, pos);
}
