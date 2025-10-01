#ifndef META_PROGRAM_HPP
#define META_PROGRAM_HPP

#include "../networking/packet_types/packet_types.hpp"
#include "../networking/packet_data/packet_data.hpp"
#include "../networking/packet_data/packet_data.hpp"
#include "../sound/sound_types/sound_types.hpp"
#include "../networking/packets/packets.hpp"
#include "../networking/packets/packets.hpp"
#include "../networking/packets/packets.hpp"
#include "../networking/packets/packets.hpp"
#include "../networking/packets/packets.hpp"
#include "../networking/packets/packets.hpp"
#include <optional>
#include "../utility/meta_utils/meta_utils.hpp"
#include "../utility/user_input/user_input.hpp"

namespace meta_program {


class MetaProgram {
public:
        MetaProgram(std::vector<meta_utils::MetaType> concrete_types) : concrete_types(concrete_types) {
        }

public:
    std::vector<meta_utils::MetaType>  concrete_types;
    std::string char_to_string(char &v) {
        return std::to_string(v);

    }
    char string_to_char(std::string &s) {
        return static_cast<char>(s.empty() ? 0 : s[0]);

    }
    std::vector<uint8_t> serialize_char(char &v) {
        std::vector<uint8_t> buf(sizeof(char));   std::memcpy(buf.data(), &v, sizeof(char));   return buf;

    }
    size_t size_when_serialized_char(char &v) {
        return sizeof(char);

    }
    char deserialize_char(std::vector<uint8_t> &buf) {
        char v;   std::memcpy(&v, buf.data(), sizeof(char));   return v;

    }
    std::string int_to_string(int &v) {
        return std::to_string(v);

    }
    int string_to_int(std::string &s) {
        return std::stoi(s);

    }
    std::vector<uint8_t> serialize_int(int &v) {
        std::vector<uint8_t> buf(sizeof(int));   std::memcpy(buf.data(), &v, sizeof(int));   return buf;

    }
    size_t size_when_serialized_int(int &v) {
        return sizeof(int);

    }
    int deserialize_int(std::vector<uint8_t> &buf) {
        int v;   std::memcpy(&v, buf.data(), sizeof(int));   return v;

    }
    std::string unsigned_int_to_string(unsigned int &v) {
        return std::to_string(v);

    }
    unsigned int string_to_unsigned_int(std::string &s) {
        return static_cast<unsigned int>(std::stoul(s));

    }
    std::vector<uint8_t> serialize_unsigned_int(unsigned int &v) {
        std::vector<uint8_t> buf(sizeof(unsigned int));   std::memcpy(buf.data(), &v, sizeof(unsigned int));   return buf;

    }
    size_t size_when_serialized_unsigned_int(unsigned int &v) {
        return sizeof(unsigned int);

    }
    unsigned int deserialize_unsigned_int(std::vector<uint8_t> &buf) {
        unsigned int v;   std::memcpy(&v, buf.data(), sizeof(unsigned int));   return v;

    }
    std::string uint8_t_to_string(uint8_t &v) {
        return std::to_string(v);

    }
    uint8_t string_to_uint8_t(std::string &s) {
        return static_cast<uint8_t>(std::stoul(s));

    }
    std::vector<uint8_t> serialize_uint8_t(uint8_t &v) {
        std::vector<uint8_t> buf(sizeof(uint8_t));   std::memcpy(buf.data(), &v, sizeof(uint8_t));   return buf;

    }
    size_t size_when_serialized_uint8_t(uint8_t &v) {
        return sizeof(uint8_t);

    }
    uint8_t deserialize_uint8_t(std::vector<uint8_t> &buf) {
        uint8_t v;   std::memcpy(&v, buf.data(), sizeof(uint8_t));   return v;

    }
    std::string uint32_t_to_string(uint32_t &v) {
        return std::to_string(v);

    }
    uint32_t string_to_uint32_t(std::string &s) {
        return static_cast<uint32_t>(std::stoul(s));

    }
    std::vector<uint8_t> serialize_uint32_t(uint32_t &v) {
        std::vector<uint8_t> buf(sizeof(uint32_t));   std::memcpy(buf.data(), &v, sizeof(uint32_t));   return buf;

    }
    size_t size_when_serialized_uint32_t(uint32_t &v) {
        return sizeof(uint32_t);

    }
    uint32_t deserialize_uint32_t(std::vector<uint8_t> &buf) {
        uint32_t v;   std::memcpy(&v, buf.data(), sizeof(uint32_t));   return v;

    }
    std::string size_t_to_string(size_t &v) {
        return std::to_string(v);

    }
    size_t string_to_size_t(std::string &s) {
        return static_cast<size_t>(std::stoull(s));

    }
    std::vector<uint8_t> serialize_size_t(size_t &v) {
        std::vector<uint8_t> buf(sizeof(size_t));   std::memcpy(buf.data(), &v, sizeof(size_t));   return buf;

    }
    size_t size_when_serialized_size_t(size_t &v) {
        return sizeof(size_t);

    }
    size_t deserialize_size_t(std::vector<uint8_t> &buf) {
        size_t v;   std::memcpy(&v, buf.data(), sizeof(size_t));   return v;

    }
    std::string float_to_string(float &v) {
        return std::to_string(v);

    }
    float string_to_float(std::string &s) {
        return std::stof(s);

    }
    std::vector<uint8_t> serialize_float(float &v) {
        std::vector<uint8_t> buf(sizeof(float));   std::memcpy(buf.data(), &v, sizeof(float));   return buf;

    }
    size_t size_when_serialized_float(float &v) {
        return sizeof(float);

    }
    float deserialize_float(std::vector<uint8_t> &buf) {
        float v;   std::memcpy(&v, buf.data(), sizeof(float));   return v;

    }
    std::string double_to_string(double &v) {
        return std::to_string(v);

    }
    double string_to_double(std::string &s) {
        return std::stod(s);

    }
    std::vector<uint8_t> serialize_double(double &v) {
        std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf;

    }
    size_t size_when_serialized_double(double &v) {
        return sizeof(double);

    }
    double deserialize_double(std::vector<uint8_t> &buf) {
        double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v;

    }
    std::string short_to_string(short &v) {
        return std::to_string(v);

    }
    short string_to_short(std::string &s) {
        return static_cast<short>(std::stoi(s));

    }
    std::vector<uint8_t> serialize_short(short &v) {
        std::vector<uint8_t> buf(sizeof(short));   std::memcpy(buf.data(), &v, sizeof(short));   return buf;

    }
    size_t size_when_serialized_short(short &v) {
        return sizeof(short);

    }
    short deserialize_short(std::vector<uint8_t> &buf) {
        short v;   std::memcpy(&v, buf.data(), sizeof(short));   return v;

    }
    std::string long_to_string(long &v) {
        return std::to_string(v);

    }
    long string_to_long(std::string &s) {
        return std::stol(s);

    }
    std::vector<uint8_t> serialize_long(long &v) {
        std::vector<uint8_t> buf(sizeof(long));   std::memcpy(buf.data(), &v, sizeof(long));   return buf;

    }
    size_t size_when_serialized_long(long &v) {
        return sizeof(long);

    }
    long deserialize_long(std::vector<uint8_t> &buf) {
        long v;   std::memcpy(&v, buf.data(), sizeof(long));   return v;

    }
    std::string std__string_to_string(std::string &s) {
        return s;

    }
    std::string string_to_std__string(std::string &s) {
        if (s.size() >= 2 && s.front() == '"' && s.back() == '"')     return s.substr(1, s.size() - 2);   return s;

    }
    std::vector<uint8_t> serialize_std__string(std::string &v) {
        std::vector<uint8_t> buf;   size_t len = v.size();   buf.resize(sizeof(size_t) + len);   std::memcpy(buf.data(), &len, sizeof(size_t));   std::memcpy(buf.data() + sizeof(size_t), v.data(), len);   return buf;

    }
    size_t size_when_serialized_std__string(std::string &v) {
        return sizeof(size_t) + v.size();

    }
    std::string deserialize_std__string(std::vector<uint8_t> &buf) {
        if (buf.size() < sizeof(size_t)) return std::string();   size_t len;   std::memcpy(&len, buf.data(), sizeof(size_t));   if (buf.size() < sizeof(size_t) + len) return std::string();   return std::string(reinterpret_cast<const char*>(buf.data() + sizeof(size_t)), len);

    }
    std::string std__filesystem__path_to_string(std::filesystem::path &p) {
        return p.string();

    }
    std::filesystem::path string_to_std__filesystem__path(std::string &s) {
        if (s.size() >= 2 && s.front() == '"' && s.back() == '"')     return std::filesystem::path(s.substr(1, s.size() - 2));   return std::filesystem::path(s);

    }
    std::vector<uint8_t> serialize_std__filesystem__path(std::filesystem::path &p) {
        std::string s = p.string();   std::vector<uint8_t> buf;   size_t len = s.size();   buf.resize(sizeof(size_t) + len);   std::memcpy(buf.data(), &len, sizeof(size_t));   std::memcpy(buf.data() + sizeof(size_t), s.data(), len);   return buf;

    }
    size_t size_when_serialized_std__filesystem__path(std::filesystem::path &p) {
        std::string s = p.string();   return sizeof(size_t) + s.size();

    }
    std::filesystem::path deserialize_std__filesystem__path(std::vector<uint8_t> &buf) {
        if (buf.size() < sizeof(size_t)) return std::filesystem::path();   size_t len;   std::memcpy(&len, buf.data(), sizeof(size_t));   if (buf.size() < sizeof(size_t) + len) return std::filesystem::path();   return std::filesystem::path(std::string(reinterpret_cast<const char*>(buf.data() + sizeof(size_t)), len));

    }
    std::string bool_to_string(bool &v) {
        return v ? "true" : "false";

    }
    bool string_to_bool(std::string &s) {
        return s == "true";

    }
    std::vector<uint8_t> serialize_bool(bool &v) {
        std::vector<uint8_t> buf(1);   buf[0] = v ? 1 : 0;   return buf;

    }
    size_t size_when_serialized_bool(bool &v) {
        return sizeof(uint8_t);

    }
    bool deserialize_bool(std::vector<uint8_t> &buf) {
        return buf[0] != 0;

    }
    std::string meta_utils__MetaType_to_string() {
        return "";

    }
    meta_utils::MetaType string_to_meta_utils__MetaType() {

    }
    std::vector<uint8_t> serialize_meta_utils__MetaType() {

    }
    size_t size_when_serialized_meta_utils__MetaType(meta_utils::MetaType &v) {
        return sizeof(meta_utils::MetaType);

    }
    meta_utils::MetaType deserialize_meta_utils__MetaType() {

    }
    std::string PacketType_to_string(PacketType value) {
        switch(value) {
                case PacketType::MOUSE_UPDATE: return "PacketType::MOUSE_UPDATE";
                case PacketType::GAME_UPDATE: return "PacketType::GAME_UPDATE";
                case PacketType::SOUND_UPDATE: return "PacketType::SOUND_UPDATE";
                default: return "<unknown PacketType>";
            }

    }
    PacketType string_to_PacketType(std::string &s) {
        if (s == "PacketType::MOUSE_UPDATE") return PacketType::MOUSE_UPDATE;
            if (s == "PacketType::GAME_UPDATE") return PacketType::GAME_UPDATE;
            if (s == "PacketType::SOUND_UPDATE") return PacketType::SOUND_UPDATE;
            return static_cast<PacketType>(0); // default fallback

    }
    std::vector<uint8_t> serialize_PacketType(PacketType value) {
        std::vector<uint8_t> buffer(sizeof(uint8_t));
            uint8_t raw = static_cast<uint8_t>(value);
            std::memcpy(buffer.data(), &raw, sizeof(uint8_t));
            return buffer;

    }
    size_t size_when_serialized_PacketType(PacketType &obj) {
        return sizeof(uint8_t);

    }
    PacketType deserialize_PacketType(std::vector<uint8_t> &buffer) {
        if (buffer.size() < sizeof(uint8_t)) return static_cast<PacketType>(0);
            uint8_t raw = 0;
            std::memcpy(&raw, buffer.data(), sizeof(uint8_t));
            return static_cast<PacketType>(raw);

    }
    std::string PacketHeader_to_string(PacketHeader obj) {
        std::ostringstream oss;
            oss << "{";
            { auto conv = [=](PacketType value) -> std::string {
            switch(value) {
                case PacketType::MOUSE_UPDATE: return "PacketType::MOUSE_UPDATE";
                case PacketType::GAME_UPDATE: return "PacketType::GAME_UPDATE";
                case PacketType::SOUND_UPDATE: return "PacketType::SOUND_UPDATE";
                default: return "<unknown PacketType>";
            }
        };
              oss << "type=" << conv(obj.type); }
            oss << ", ";
            { auto conv = [](const uint32_t &v) { return std::to_string(v); };
              oss << "size_of_data_without_header=" << conv(obj.size_of_data_without_header); }
            oss << "}";
            return oss.str();

    }
    PacketHeader string_to_PacketHeader(std::string &s) {
        PacketHeader obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> PacketType {
            if (s == "PacketType::MOUSE_UPDATE") return PacketType::MOUSE_UPDATE;
            if (s == "PacketType::GAME_UPDATE") return PacketType::GAME_UPDATE;
            if (s == "PacketType::SOUND_UPDATE") return PacketType::SOUND_UPDATE;
            return static_cast<PacketType>(0); // default fallback
        };
                    obj.type = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<uint32_t>(std::stoul(s)); };
                    obj.size_of_data_without_header = conv(value_str);
                }
            }
            return obj;

    }
    std::vector<uint8_t> serialize_PacketHeader(PacketHeader obj) {
        std::vector<uint8_t> buffer;
            { auto ser = [=](PacketType value) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer(sizeof(uint8_t));
            uint8_t raw = static_cast<uint8_t>(value);
            std::memcpy(buffer.data(), &raw, sizeof(uint8_t));
            return buffer;
        };
              auto bytes = ser(obj.type);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const uint32_t &v) {   std::vector<uint8_t> buf(sizeof(uint32_t));   std::memcpy(buf.data(), &v, sizeof(uint32_t));   return buf; };
              auto bytes = ser(obj.size_of_data_without_header);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;

    }
    size_t size_when_serialized_PacketHeader(PacketHeader obj) {
        size_t total = 0;
            { auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              total += size_fn(obj.type); }
            { auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              total += size_fn(obj.size_of_data_without_header); }
            return total;

    }
    PacketHeader deserialize_PacketHeader(std::vector<uint8_t> &buffer) {
        PacketHeader obj;
            size_t offset = 0;
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> PacketType {
            if (buffer.size() < sizeof(uint8_t)) return static_cast<PacketType>(0);
            uint8_t raw = 0;
            std::memcpy(&raw, buffer.data(), sizeof(uint8_t));
            return static_cast<PacketType>(raw);
        };
              auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              size_t len = size_fn(obj.type);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.type = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   uint32_t v;   std::memcpy(&v, buf.data(), sizeof(uint32_t));   return v; };
              auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              size_t len = size_fn(obj.size_of_data_without_header);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.size_of_data_without_header = deser(slice);
              offset += len;
            }
            return obj;

    }
    std::string PacketWithSize_to_string(PacketWithSize obj) {
        std::ostringstream oss;
            oss << "{";
            { auto conv = [=](const std::vector<char>& vec) -> std::string {
            std::ostringstream oss;
            oss << "{";
            auto conversion = [](const char &v) { return std::to_string(v); };
        
            for (size_t i = 0; i < vec.size(); ++i) {
                oss << conversion(vec[i]);
                if (i + 1 < vec.size())
                    oss << ", ";
            }
        
            oss << "}";
            return oss.str();
        };
              oss << "data=" << conv(obj.data); }
            oss << ", ";
            { auto conv = [](const size_t &v) { return std::to_string(v); };
              oss << "size=" << conv(obj.size); }
            oss << "}";
            return oss.str();

    }
    PacketWithSize string_to_PacketWithSize(std::string &s) {
        PacketWithSize obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &input) -> std::vector<char> {
            std::string trimmed = input;
            if (!trimmed.empty() && trimmed.front() == '{' && trimmed.back() == '}') {
                trimmed = trimmed.substr(1, trimmed.size() - 2);
            }
        
            std::vector<char> result;
            std::regex element_re(R"('(?:[^'\\]|\\.)')");
            auto begin = std::sregex_iterator(trimmed.begin(), trimmed.end(), element_re);
            auto end = std::sregex_iterator();
        
            for (auto it = begin; it != end; ++it) {
                try {
                    auto conversion = [](const std::string &s) { return static_cast<char>(s.empty() ? 0 : s[0]); };
                    result.push_back(conversion(it->str()));
                } catch (...) {
                    // Ignore malformed elements
                }
            }
            return result;
        };
                    obj.data = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<size_t>(std::stoull(s)); };
                    obj.size = conv(value_str);
                }
            }
            return obj;

    }
    std::vector<uint8_t> serialize_PacketWithSize(PacketWithSize obj) {
        std::vector<uint8_t> buffer;
            { auto ser = [=](const std::vector<char>& vec) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer;
            size_t count = vec.size();
            buffer.resize(sizeof(size_t));
            std::memcpy(buffer.data(), &count, sizeof(size_t));
        
            auto element_serializer = [](const char &v) {   std::vector<uint8_t> buf(sizeof(char));   std::memcpy(buf.data(), &v, sizeof(char));   return buf; };
            if (!vec.empty()) {
                size_t elem_size = sizeof(char);
                buffer.resize(buffer.size() + vec.size() * elem_size);
                std::memcpy(buffer.data() + sizeof(size_t), vec.data(), vec.size() * elem_size);
            }
            return buffer;
        };
              auto bytes = ser(obj.data);
              size_t len = bytes.size();
              buffer.resize(buffer.size() + sizeof(size_t));
              std::memcpy(buffer.data() + buffer.size() - sizeof(size_t), &len, sizeof(size_t));
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const size_t &v) {   std::vector<uint8_t> buf(sizeof(size_t));   std::memcpy(buf.data(), &v, sizeof(size_t));   return buf; };
              auto bytes = ser(obj.size);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;

    }
    size_t size_when_serialized_PacketWithSize(PacketWithSize obj) {
        size_t total = 0;
            { auto size_fn = [=](const std::vector<char>& vec) -> size_t {
            size_t total_size = sizeof(size_t); // space for storing count
            if (!vec.empty()) {
                total_size += vec.size() * [](const char &v) { return sizeof(char); }(vec[0]);
            }
            return total_size;
        };
              total += sizeof(size_t); // length prefix
              total += size_fn(obj.data); }
            { auto size_fn = [](const size_t &v) { return sizeof(size_t); };
              total += size_fn(obj.size); }
            return total;

    }
    PacketWithSize deserialize_PacketWithSize(std::vector<uint8_t> &buffer) {
        PacketWithSize obj;
            size_t offset = 0;
            { auto deser = [=](const std::vector<uint8_t>& buffer) -> std::vector<char> {
            std::vector<char> result;
            if (buffer.size() < sizeof(size_t)) return result;
            size_t count;
            std::memcpy(&count, buffer.data(), sizeof(size_t));
        
            size_t offset = sizeof(size_t);
            auto element_deserializer = [](const std::vector<uint8_t> &buf) {   char v;   std::memcpy(&v, buf.data(), sizeof(char));   return v; };
            size_t elem_size = sizeof(char);
            if (offset + count * elem_size > buffer.size()) return result; // safety check
            for (size_t i = 0; i < count; ++i) {
                std::vector<uint8_t> elem_buf(buffer.begin() + offset, buffer.begin() + offset + elem_size);
                char elem = element_deserializer(elem_buf);
                result.push_back(elem);
                offset += elem_size;
            }
            return result;
        };
              if (offset + sizeof(size_t) > buffer.size()) return obj;
              size_t len = 0;
              std::memcpy(&len, buffer.data() + offset, sizeof(size_t));
              offset += sizeof(size_t);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.data = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   size_t v;   std::memcpy(&v, buf.data(), sizeof(size_t));   return v; };
              auto size_fn = [](const size_t &v) { return sizeof(size_t); };
              size_t len = size_fn(obj.size);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.size = deser(slice);
              offset += len;
            }
            return obj;

    }
    std::string SoundType_to_string(SoundType value) {
        switch(value) {
                case SoundType::CLIENT_HIT: return "SoundType::CLIENT_HIT";
                case SoundType::CLIENT_MISS: return "SoundType::CLIENT_MISS";
                case SoundType::SERVER_HIT: return "SoundType::SERVER_HIT";
                case SoundType::SERVER_MISS: return "SoundType::SERVER_MISS";
                case SoundType::UI_HOVER: return "SoundType::UI_HOVER";
                case SoundType::UI_CLICK: return "SoundType::UI_CLICK";
                case SoundType::UI_SUCCESS: return "SoundType::UI_SUCCESS";
                default: return "<unknown SoundType>";
            }

    }
    SoundType string_to_SoundType(std::string &s) {
        if (s == "SoundType::CLIENT_HIT") return SoundType::CLIENT_HIT;
            if (s == "SoundType::CLIENT_MISS") return SoundType::CLIENT_MISS;
            if (s == "SoundType::SERVER_HIT") return SoundType::SERVER_HIT;
            if (s == "SoundType::SERVER_MISS") return SoundType::SERVER_MISS;
            if (s == "SoundType::UI_HOVER") return SoundType::UI_HOVER;
            if (s == "SoundType::UI_CLICK") return SoundType::UI_CLICK;
            if (s == "SoundType::UI_SUCCESS") return SoundType::UI_SUCCESS;
            return static_cast<SoundType>(0); // default fallback

    }
    std::vector<uint8_t> serialize_SoundType(SoundType value) {
        std::vector<uint8_t> buffer(sizeof(int));
            int raw = static_cast<int>(value);
            std::memcpy(buffer.data(), &raw, sizeof(int));
            return buffer;

    }
    size_t size_when_serialized_SoundType(SoundType &obj) {
        return sizeof(int);

    }
    SoundType deserialize_SoundType(std::vector<uint8_t> &buffer) {
        if (buffer.size() < sizeof(int)) return static_cast<SoundType>(0);
            int raw = 0;
            std::memcpy(&raw, buffer.data(), sizeof(int));
            return static_cast<SoundType>(raw);

    }
    std::string MouseUpdate_to_string(MouseUpdate obj) {
        std::ostringstream oss;
            oss << "{";
            { auto conv = [](const unsigned int &v) { return std::to_string(v); };
              oss << "mouse_pos_update_number=" << conv(obj.mouse_pos_update_number); }
            oss << ", ";
            { auto conv = [](const unsigned int &v) { return std::to_string(v); };
              oss << "last_applied_game_update_number=" << conv(obj.last_applied_game_update_number); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "x_pos=" << conv(obj.x_pos); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "y_pos=" << conv(obj.y_pos); }
            oss << ", ";
            { auto conv = [](const bool &v) { return v ? "true" : "false"; };
              oss << "fire_pressed=" << conv(obj.fire_pressed); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "sensitivity=" << conv(obj.sensitivity); }
            oss << "}";
            return oss.str();

    }
    MouseUpdate string_to_MouseUpdate(std::string &s) {
        MouseUpdate obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<unsigned int>(std::stoul(s)); };
                    obj.mouse_pos_update_number = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<unsigned int>(std::stoul(s)); };
                    obj.last_applied_game_update_number = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.x_pos = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.y_pos = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return s == "true"; };
                    obj.fire_pressed = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.sensitivity = conv(value_str);
                }
            }
            return obj;

    }
    std::vector<uint8_t> serialize_MouseUpdate(MouseUpdate obj) {
        std::vector<uint8_t> buffer;
            { auto ser = [](const unsigned int &v) {   std::vector<uint8_t> buf(sizeof(unsigned int));   std::memcpy(buf.data(), &v, sizeof(unsigned int));   return buf; };
              auto bytes = ser(obj.mouse_pos_update_number);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const unsigned int &v) {   std::vector<uint8_t> buf(sizeof(unsigned int));   std::memcpy(buf.data(), &v, sizeof(unsigned int));   return buf; };
              auto bytes = ser(obj.last_applied_game_update_number);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.x_pos);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.y_pos);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const bool &v) {   std::vector<uint8_t> buf(1);   buf[0] = v ? 1 : 0;   return buf; };
              auto bytes = ser(obj.fire_pressed);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.sensitivity);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;

    }
    size_t size_when_serialized_MouseUpdate(MouseUpdate obj) {
        size_t total = 0;
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.mouse_pos_update_number); }
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.last_applied_game_update_number); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.x_pos); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.y_pos); }
            { auto size_fn = [](const bool &v) { return sizeof(uint8_t); };
              total += size_fn(obj.fire_pressed); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.sensitivity); }
            return total;

    }
    MouseUpdate deserialize_MouseUpdate(std::vector<uint8_t> &buffer) {
        MouseUpdate obj;
            size_t offset = 0;
            { auto deser = [](const std::vector<uint8_t> &buf) {   unsigned int v;   std::memcpy(&v, buf.data(), sizeof(unsigned int));   return v; };
              auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              size_t len = size_fn(obj.mouse_pos_update_number);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.mouse_pos_update_number = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   unsigned int v;   std::memcpy(&v, buf.data(), sizeof(unsigned int));   return v; };
              auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              size_t len = size_fn(obj.last_applied_game_update_number);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.last_applied_game_update_number = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.x_pos);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.x_pos = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.y_pos);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.y_pos = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   return buf[0] != 0; };
              auto size_fn = [](const bool &v) { return sizeof(uint8_t); };
              size_t len = size_fn(obj.fire_pressed);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.fire_pressed = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.sensitivity);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.sensitivity = deser(slice);
              offset += len;
            }
            return obj;

    }
    std::string GameUpdate_to_string(GameUpdate obj) {
        std::ostringstream oss;
            oss << "{";
            { auto conv = [](const unsigned int &v) { return std::to_string(v); };
              oss << "last_processed_mouse_pos_update_number=" << conv(obj.last_processed_mouse_pos_update_number); }
            oss << ", ";
            { auto conv = [](const unsigned int &v) { return std::to_string(v); };
              oss << "update_number=" << conv(obj.update_number); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "yaw=" << conv(obj.yaw); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "pitch=" << conv(obj.pitch); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "target_x_pos=" << conv(obj.target_x_pos); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "target_y_pos=" << conv(obj.target_y_pos); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "target_z_pos=" << conv(obj.target_z_pos); }
            oss << "}";
            return oss.str();

    }
    GameUpdate string_to_GameUpdate(std::string &s) {
        GameUpdate obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<unsigned int>(std::stoul(s)); };
                    obj.last_processed_mouse_pos_update_number = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<unsigned int>(std::stoul(s)); };
                    obj.update_number = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.yaw = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.pitch = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.target_x_pos = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.target_y_pos = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.target_z_pos = conv(value_str);
                }
            }
            return obj;

    }
    std::vector<uint8_t> serialize_GameUpdate(GameUpdate obj) {
        std::vector<uint8_t> buffer;
            { auto ser = [](const unsigned int &v) {   std::vector<uint8_t> buf(sizeof(unsigned int));   std::memcpy(buf.data(), &v, sizeof(unsigned int));   return buf; };
              auto bytes = ser(obj.last_processed_mouse_pos_update_number);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const unsigned int &v) {   std::vector<uint8_t> buf(sizeof(unsigned int));   std::memcpy(buf.data(), &v, sizeof(unsigned int));   return buf; };
              auto bytes = ser(obj.update_number);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.yaw);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.pitch);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.target_x_pos);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.target_y_pos);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.target_z_pos);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;

    }
    size_t size_when_serialized_GameUpdate(GameUpdate obj) {
        size_t total = 0;
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.last_processed_mouse_pos_update_number); }
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.update_number); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.yaw); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.pitch); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.target_x_pos); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.target_y_pos); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.target_z_pos); }
            return total;

    }
    GameUpdate deserialize_GameUpdate(std::vector<uint8_t> &buffer) {
        GameUpdate obj;
            size_t offset = 0;
            { auto deser = [](const std::vector<uint8_t> &buf) {   unsigned int v;   std::memcpy(&v, buf.data(), sizeof(unsigned int));   return v; };
              auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              size_t len = size_fn(obj.last_processed_mouse_pos_update_number);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.last_processed_mouse_pos_update_number = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   unsigned int v;   std::memcpy(&v, buf.data(), sizeof(unsigned int));   return v; };
              auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              size_t len = size_fn(obj.update_number);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.update_number = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.yaw);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.yaw = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.pitch);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.pitch = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.target_x_pos);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.target_x_pos = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.target_y_pos);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.target_y_pos = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.target_z_pos);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.target_z_pos = deser(slice);
              offset += len;
            }
            return obj;

    }
    std::string SoundUpdate_to_string(SoundUpdate obj) {
        std::ostringstream oss;
            oss << "{";
            { auto conv = [=](SoundType value) -> std::string {
            switch(value) {
                case SoundType::CLIENT_HIT: return "SoundType::CLIENT_HIT";
                case SoundType::CLIENT_MISS: return "SoundType::CLIENT_MISS";
                case SoundType::SERVER_HIT: return "SoundType::SERVER_HIT";
                case SoundType::SERVER_MISS: return "SoundType::SERVER_MISS";
                case SoundType::UI_HOVER: return "SoundType::UI_HOVER";
                case SoundType::UI_CLICK: return "SoundType::UI_CLICK";
                case SoundType::UI_SUCCESS: return "SoundType::UI_SUCCESS";
                default: return "<unknown SoundType>";
            }
        };
              oss << "sound_to_play=" << conv(obj.sound_to_play); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "x=" << conv(obj.x); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "y=" << conv(obj.y); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "z=" << conv(obj.z); }
            oss << "}";
            return oss.str();

    }
    SoundUpdate string_to_SoundUpdate(std::string &s) {
        SoundUpdate obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> SoundType {
            if (s == "SoundType::CLIENT_HIT") return SoundType::CLIENT_HIT;
            if (s == "SoundType::CLIENT_MISS") return SoundType::CLIENT_MISS;
            if (s == "SoundType::SERVER_HIT") return SoundType::SERVER_HIT;
            if (s == "SoundType::SERVER_MISS") return SoundType::SERVER_MISS;
            if (s == "SoundType::UI_HOVER") return SoundType::UI_HOVER;
            if (s == "SoundType::UI_CLICK") return SoundType::UI_CLICK;
            if (s == "SoundType::UI_SUCCESS") return SoundType::UI_SUCCESS;
            return static_cast<SoundType>(0); // default fallback
        };
                    obj.sound_to_play = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.x = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.y = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.z = conv(value_str);
                }
            }
            return obj;

    }
    std::vector<uint8_t> serialize_SoundUpdate(SoundUpdate obj) {
        std::vector<uint8_t> buffer;
            { auto ser = [=](SoundType value) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer(sizeof(int));
            int raw = static_cast<int>(value);
            std::memcpy(buffer.data(), &raw, sizeof(int));
            return buffer;
        };
              auto bytes = ser(obj.sound_to_play);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.x);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.y);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.z);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;

    }
    size_t size_when_serialized_SoundUpdate(SoundUpdate obj) {
        size_t total = 0;
            { auto size_fn = [=](const SoundType &obj) -> size_t {
            return sizeof(int);
        };
              total += size_fn(obj.sound_to_play); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.x); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.y); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.z); }
            return total;

    }
    SoundUpdate deserialize_SoundUpdate(std::vector<uint8_t> &buffer) {
        SoundUpdate obj;
            size_t offset = 0;
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> SoundType {
            if (buffer.size() < sizeof(int)) return static_cast<SoundType>(0);
            int raw = 0;
            std::memcpy(&raw, buffer.data(), sizeof(int));
            return static_cast<SoundType>(raw);
        };
              auto size_fn = [=](const SoundType &obj) -> size_t {
            return sizeof(int);
        };
              size_t len = size_fn(obj.sound_to_play);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.sound_to_play = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.x);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.x = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.y);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.y = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.z);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.z = deser(slice);
              offset += len;
            }
            return obj;

    }
    std::string MouseUpdatePacket_to_string(MouseUpdatePacket obj) {
        std::ostringstream oss;
            oss << "{";
            { auto conv = [=](const PacketHeader& obj) -> std::string {
            std::ostringstream oss;
            oss << "{";
            { auto conv = [=](PacketType value) -> std::string {
            switch(value) {
                case PacketType::MOUSE_UPDATE: return "PacketType::MOUSE_UPDATE";
                case PacketType::GAME_UPDATE: return "PacketType::GAME_UPDATE";
                case PacketType::SOUND_UPDATE: return "PacketType::SOUND_UPDATE";
                default: return "<unknown PacketType>";
            }
        };
              oss << "type=" << conv(obj.type); }
            oss << ", ";
            { auto conv = [](const uint32_t &v) { return std::to_string(v); };
              oss << "size_of_data_without_header=" << conv(obj.size_of_data_without_header); }
            oss << "}";
            return oss.str();
        };
              oss << "header=" << conv(obj.header); }
            oss << ", ";
            { auto conv = [=](const MouseUpdate& obj) -> std::string {
            std::ostringstream oss;
            oss << "{";
            { auto conv = [](const unsigned int &v) { return std::to_string(v); };
              oss << "mouse_pos_update_number=" << conv(obj.mouse_pos_update_number); }
            oss << ", ";
            { auto conv = [](const unsigned int &v) { return std::to_string(v); };
              oss << "last_applied_game_update_number=" << conv(obj.last_applied_game_update_number); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "x_pos=" << conv(obj.x_pos); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "y_pos=" << conv(obj.y_pos); }
            oss << ", ";
            { auto conv = [](const bool &v) { return v ? "true" : "false"; };
              oss << "fire_pressed=" << conv(obj.fire_pressed); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "sensitivity=" << conv(obj.sensitivity); }
            oss << "}";
            return oss.str();
        };
              oss << "mouse_update=" << conv(obj.mouse_update); }
            oss << "}";
            return oss.str();

    }
    MouseUpdatePacket string_to_MouseUpdatePacket(std::string &s) {
        MouseUpdatePacket obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> PacketHeader {
            PacketHeader obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> PacketType {
            if (s == "PacketType::MOUSE_UPDATE") return PacketType::MOUSE_UPDATE;
            if (s == "PacketType::GAME_UPDATE") return PacketType::GAME_UPDATE;
            if (s == "PacketType::SOUND_UPDATE") return PacketType::SOUND_UPDATE;
            return static_cast<PacketType>(0); // default fallback
        };
                    obj.type = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<uint32_t>(std::stoul(s)); };
                    obj.size_of_data_without_header = conv(value_str);
                }
            }
            return obj;
        };
                    obj.header = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> MouseUpdate {
            MouseUpdate obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<unsigned int>(std::stoul(s)); };
                    obj.mouse_pos_update_number = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<unsigned int>(std::stoul(s)); };
                    obj.last_applied_game_update_number = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.x_pos = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.y_pos = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return s == "true"; };
                    obj.fire_pressed = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.sensitivity = conv(value_str);
                }
            }
            return obj;
        };
                    obj.mouse_update = conv(value_str);
                }
            }
            return obj;

    }
    std::vector<uint8_t> serialize_MouseUpdatePacket(MouseUpdatePacket obj) {
        std::vector<uint8_t> buffer;
            { auto ser = [=](const PacketHeader& obj) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer;
            { auto ser = [=](PacketType value) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer(sizeof(uint8_t));
            uint8_t raw = static_cast<uint8_t>(value);
            std::memcpy(buffer.data(), &raw, sizeof(uint8_t));
            return buffer;
        };
              auto bytes = ser(obj.type);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const uint32_t &v) {   std::vector<uint8_t> buf(sizeof(uint32_t));   std::memcpy(buf.data(), &v, sizeof(uint32_t));   return buf; };
              auto bytes = ser(obj.size_of_data_without_header);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;
        };
              auto bytes = ser(obj.header);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [=](const MouseUpdate& obj) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer;
            { auto ser = [](const unsigned int &v) {   std::vector<uint8_t> buf(sizeof(unsigned int));   std::memcpy(buf.data(), &v, sizeof(unsigned int));   return buf; };
              auto bytes = ser(obj.mouse_pos_update_number);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const unsigned int &v) {   std::vector<uint8_t> buf(sizeof(unsigned int));   std::memcpy(buf.data(), &v, sizeof(unsigned int));   return buf; };
              auto bytes = ser(obj.last_applied_game_update_number);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.x_pos);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.y_pos);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const bool &v) {   std::vector<uint8_t> buf(1);   buf[0] = v ? 1 : 0;   return buf; };
              auto bytes = ser(obj.fire_pressed);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.sensitivity);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;
        };
              auto bytes = ser(obj.mouse_update);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;

    }
    size_t size_when_serialized_MouseUpdatePacket(MouseUpdatePacket obj) {
        size_t total = 0;
            { auto size_fn = [=](const PacketHeader& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              total += size_fn(obj.type); }
            { auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              total += size_fn(obj.size_of_data_without_header); }
            return total;
        };
              total += size_fn(obj.header); }
            { auto size_fn = [=](const MouseUpdate& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.mouse_pos_update_number); }
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.last_applied_game_update_number); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.x_pos); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.y_pos); }
            { auto size_fn = [](const bool &v) { return sizeof(uint8_t); };
              total += size_fn(obj.fire_pressed); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.sensitivity); }
            return total;
        };
              total += size_fn(obj.mouse_update); }
            return total;

    }
    MouseUpdatePacket deserialize_MouseUpdatePacket(std::vector<uint8_t> &buffer) {
        MouseUpdatePacket obj;
            size_t offset = 0;
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> PacketHeader {
            PacketHeader obj;
            size_t offset = 0;
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> PacketType {
            if (buffer.size() < sizeof(uint8_t)) return static_cast<PacketType>(0);
            uint8_t raw = 0;
            std::memcpy(&raw, buffer.data(), sizeof(uint8_t));
            return static_cast<PacketType>(raw);
        };
              auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              size_t len = size_fn(obj.type);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.type = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   uint32_t v;   std::memcpy(&v, buf.data(), sizeof(uint32_t));   return v; };
              auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              size_t len = size_fn(obj.size_of_data_without_header);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.size_of_data_without_header = deser(slice);
              offset += len;
            }
            return obj;
        };
              auto size_fn = [=](const PacketHeader& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              total += size_fn(obj.type); }
            { auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              total += size_fn(obj.size_of_data_without_header); }
            return total;
        };
              size_t len = size_fn(obj.header);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.header = deser(slice);
              offset += len;
            }
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> MouseUpdate {
            MouseUpdate obj;
            size_t offset = 0;
            { auto deser = [](const std::vector<uint8_t> &buf) {   unsigned int v;   std::memcpy(&v, buf.data(), sizeof(unsigned int));   return v; };
              auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              size_t len = size_fn(obj.mouse_pos_update_number);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.mouse_pos_update_number = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   unsigned int v;   std::memcpy(&v, buf.data(), sizeof(unsigned int));   return v; };
              auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              size_t len = size_fn(obj.last_applied_game_update_number);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.last_applied_game_update_number = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.x_pos);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.x_pos = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.y_pos);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.y_pos = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   return buf[0] != 0; };
              auto size_fn = [](const bool &v) { return sizeof(uint8_t); };
              size_t len = size_fn(obj.fire_pressed);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.fire_pressed = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.sensitivity);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.sensitivity = deser(slice);
              offset += len;
            }
            return obj;
        };
              auto size_fn = [=](const MouseUpdate& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.mouse_pos_update_number); }
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.last_applied_game_update_number); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.x_pos); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.y_pos); }
            { auto size_fn = [](const bool &v) { return sizeof(uint8_t); };
              total += size_fn(obj.fire_pressed); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.sensitivity); }
            return total;
        };
              size_t len = size_fn(obj.mouse_update);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.mouse_update = deser(slice);
              offset += len;
            }
            return obj;

    }
    std::string GameUpdatePacket_to_string(GameUpdatePacket obj) {
        std::ostringstream oss;
            oss << "{";
            { auto conv = [=](const PacketHeader& obj) -> std::string {
            std::ostringstream oss;
            oss << "{";
            { auto conv = [=](PacketType value) -> std::string {
            switch(value) {
                case PacketType::MOUSE_UPDATE: return "PacketType::MOUSE_UPDATE";
                case PacketType::GAME_UPDATE: return "PacketType::GAME_UPDATE";
                case PacketType::SOUND_UPDATE: return "PacketType::SOUND_UPDATE";
                default: return "<unknown PacketType>";
            }
        };
              oss << "type=" << conv(obj.type); }
            oss << ", ";
            { auto conv = [](const uint32_t &v) { return std::to_string(v); };
              oss << "size_of_data_without_header=" << conv(obj.size_of_data_without_header); }
            oss << "}";
            return oss.str();
        };
              oss << "header=" << conv(obj.header); }
            oss << ", ";
            { auto conv = [=](const GameUpdate& obj) -> std::string {
            std::ostringstream oss;
            oss << "{";
            { auto conv = [](const unsigned int &v) { return std::to_string(v); };
              oss << "last_processed_mouse_pos_update_number=" << conv(obj.last_processed_mouse_pos_update_number); }
            oss << ", ";
            { auto conv = [](const unsigned int &v) { return std::to_string(v); };
              oss << "update_number=" << conv(obj.update_number); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "yaw=" << conv(obj.yaw); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "pitch=" << conv(obj.pitch); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "target_x_pos=" << conv(obj.target_x_pos); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "target_y_pos=" << conv(obj.target_y_pos); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "target_z_pos=" << conv(obj.target_z_pos); }
            oss << "}";
            return oss.str();
        };
              oss << "game_update=" << conv(obj.game_update); }
            oss << "}";
            return oss.str();

    }
    GameUpdatePacket string_to_GameUpdatePacket(std::string &s) {
        GameUpdatePacket obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> PacketHeader {
            PacketHeader obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> PacketType {
            if (s == "PacketType::MOUSE_UPDATE") return PacketType::MOUSE_UPDATE;
            if (s == "PacketType::GAME_UPDATE") return PacketType::GAME_UPDATE;
            if (s == "PacketType::SOUND_UPDATE") return PacketType::SOUND_UPDATE;
            return static_cast<PacketType>(0); // default fallback
        };
                    obj.type = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<uint32_t>(std::stoul(s)); };
                    obj.size_of_data_without_header = conv(value_str);
                }
            }
            return obj;
        };
                    obj.header = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> GameUpdate {
            GameUpdate obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<unsigned int>(std::stoul(s)); };
                    obj.last_processed_mouse_pos_update_number = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<unsigned int>(std::stoul(s)); };
                    obj.update_number = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.yaw = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.pitch = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.target_x_pos = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.target_y_pos = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.target_z_pos = conv(value_str);
                }
            }
            return obj;
        };
                    obj.game_update = conv(value_str);
                }
            }
            return obj;

    }
    std::vector<uint8_t> serialize_GameUpdatePacket(GameUpdatePacket obj) {
        std::vector<uint8_t> buffer;
            { auto ser = [=](const PacketHeader& obj) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer;
            { auto ser = [=](PacketType value) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer(sizeof(uint8_t));
            uint8_t raw = static_cast<uint8_t>(value);
            std::memcpy(buffer.data(), &raw, sizeof(uint8_t));
            return buffer;
        };
              auto bytes = ser(obj.type);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const uint32_t &v) {   std::vector<uint8_t> buf(sizeof(uint32_t));   std::memcpy(buf.data(), &v, sizeof(uint32_t));   return buf; };
              auto bytes = ser(obj.size_of_data_without_header);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;
        };
              auto bytes = ser(obj.header);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [=](const GameUpdate& obj) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer;
            { auto ser = [](const unsigned int &v) {   std::vector<uint8_t> buf(sizeof(unsigned int));   std::memcpy(buf.data(), &v, sizeof(unsigned int));   return buf; };
              auto bytes = ser(obj.last_processed_mouse_pos_update_number);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const unsigned int &v) {   std::vector<uint8_t> buf(sizeof(unsigned int));   std::memcpy(buf.data(), &v, sizeof(unsigned int));   return buf; };
              auto bytes = ser(obj.update_number);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.yaw);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.pitch);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.target_x_pos);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.target_y_pos);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.target_z_pos);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;
        };
              auto bytes = ser(obj.game_update);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;

    }
    size_t size_when_serialized_GameUpdatePacket(GameUpdatePacket obj) {
        size_t total = 0;
            { auto size_fn = [=](const PacketHeader& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              total += size_fn(obj.type); }
            { auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              total += size_fn(obj.size_of_data_without_header); }
            return total;
        };
              total += size_fn(obj.header); }
            { auto size_fn = [=](const GameUpdate& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.last_processed_mouse_pos_update_number); }
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.update_number); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.yaw); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.pitch); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.target_x_pos); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.target_y_pos); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.target_z_pos); }
            return total;
        };
              total += size_fn(obj.game_update); }
            return total;

    }
    GameUpdatePacket deserialize_GameUpdatePacket(std::vector<uint8_t> &buffer) {
        GameUpdatePacket obj;
            size_t offset = 0;
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> PacketHeader {
            PacketHeader obj;
            size_t offset = 0;
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> PacketType {
            if (buffer.size() < sizeof(uint8_t)) return static_cast<PacketType>(0);
            uint8_t raw = 0;
            std::memcpy(&raw, buffer.data(), sizeof(uint8_t));
            return static_cast<PacketType>(raw);
        };
              auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              size_t len = size_fn(obj.type);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.type = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   uint32_t v;   std::memcpy(&v, buf.data(), sizeof(uint32_t));   return v; };
              auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              size_t len = size_fn(obj.size_of_data_without_header);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.size_of_data_without_header = deser(slice);
              offset += len;
            }
            return obj;
        };
              auto size_fn = [=](const PacketHeader& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              total += size_fn(obj.type); }
            { auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              total += size_fn(obj.size_of_data_without_header); }
            return total;
        };
              size_t len = size_fn(obj.header);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.header = deser(slice);
              offset += len;
            }
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> GameUpdate {
            GameUpdate obj;
            size_t offset = 0;
            { auto deser = [](const std::vector<uint8_t> &buf) {   unsigned int v;   std::memcpy(&v, buf.data(), sizeof(unsigned int));   return v; };
              auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              size_t len = size_fn(obj.last_processed_mouse_pos_update_number);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.last_processed_mouse_pos_update_number = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   unsigned int v;   std::memcpy(&v, buf.data(), sizeof(unsigned int));   return v; };
              auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              size_t len = size_fn(obj.update_number);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.update_number = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.yaw);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.yaw = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.pitch);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.pitch = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.target_x_pos);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.target_x_pos = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.target_y_pos);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.target_y_pos = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.target_z_pos);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.target_z_pos = deser(slice);
              offset += len;
            }
            return obj;
        };
              auto size_fn = [=](const GameUpdate& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.last_processed_mouse_pos_update_number); }
            { auto size_fn = [](const unsigned int &v) { return sizeof(unsigned int); };
              total += size_fn(obj.update_number); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.yaw); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.pitch); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.target_x_pos); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.target_y_pos); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.target_z_pos); }
            return total;
        };
              size_t len = size_fn(obj.game_update);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.game_update = deser(slice);
              offset += len;
            }
            return obj;

    }
    std::string SoundUpdatePacket_to_string(SoundUpdatePacket obj) {
        std::ostringstream oss;
            oss << "{";
            { auto conv = [=](const PacketHeader& obj) -> std::string {
            std::ostringstream oss;
            oss << "{";
            { auto conv = [=](PacketType value) -> std::string {
            switch(value) {
                case PacketType::MOUSE_UPDATE: return "PacketType::MOUSE_UPDATE";
                case PacketType::GAME_UPDATE: return "PacketType::GAME_UPDATE";
                case PacketType::SOUND_UPDATE: return "PacketType::SOUND_UPDATE";
                default: return "<unknown PacketType>";
            }
        };
              oss << "type=" << conv(obj.type); }
            oss << ", ";
            { auto conv = [](const uint32_t &v) { return std::to_string(v); };
              oss << "size_of_data_without_header=" << conv(obj.size_of_data_without_header); }
            oss << "}";
            return oss.str();
        };
              oss << "header=" << conv(obj.header); }
            oss << ", ";
            { auto conv = [=](const SoundUpdate& obj) -> std::string {
            std::ostringstream oss;
            oss << "{";
            { auto conv = [=](SoundType value) -> std::string {
            switch(value) {
                case SoundType::CLIENT_HIT: return "SoundType::CLIENT_HIT";
                case SoundType::CLIENT_MISS: return "SoundType::CLIENT_MISS";
                case SoundType::SERVER_HIT: return "SoundType::SERVER_HIT";
                case SoundType::SERVER_MISS: return "SoundType::SERVER_MISS";
                case SoundType::UI_HOVER: return "SoundType::UI_HOVER";
                case SoundType::UI_CLICK: return "SoundType::UI_CLICK";
                case SoundType::UI_SUCCESS: return "SoundType::UI_SUCCESS";
                default: return "<unknown SoundType>";
            }
        };
              oss << "sound_to_play=" << conv(obj.sound_to_play); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "x=" << conv(obj.x); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "y=" << conv(obj.y); }
            oss << ", ";
            { auto conv = [](const double &v) { return std::to_string(v); };
              oss << "z=" << conv(obj.z); }
            oss << "}";
            return oss.str();
        };
              oss << "sound_update=" << conv(obj.sound_update); }
            oss << "}";
            return oss.str();

    }
    SoundUpdatePacket string_to_SoundUpdatePacket(std::string &s) {
        SoundUpdatePacket obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> PacketHeader {
            PacketHeader obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> PacketType {
            if (s == "PacketType::MOUSE_UPDATE") return PacketType::MOUSE_UPDATE;
            if (s == "PacketType::GAME_UPDATE") return PacketType::GAME_UPDATE;
            if (s == "PacketType::SOUND_UPDATE") return PacketType::SOUND_UPDATE;
            return static_cast<PacketType>(0); // default fallback
        };
                    obj.type = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return static_cast<uint32_t>(std::stoul(s)); };
                    obj.size_of_data_without_header = conv(value_str);
                }
            }
            return obj;
        };
                    obj.header = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> SoundUpdate {
            SoundUpdate obj;
            std::string trimmed = s.substr(1, s.size() - 2); // remove {}
            std::istringstream iss(trimmed);
            std::string token;
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [=](const std::string &s) -> SoundType {
            if (s == "SoundType::CLIENT_HIT") return SoundType::CLIENT_HIT;
            if (s == "SoundType::CLIENT_MISS") return SoundType::CLIENT_MISS;
            if (s == "SoundType::SERVER_HIT") return SoundType::SERVER_HIT;
            if (s == "SoundType::SERVER_MISS") return SoundType::SERVER_MISS;
            if (s == "SoundType::UI_HOVER") return SoundType::UI_HOVER;
            if (s == "SoundType::UI_CLICK") return SoundType::UI_CLICK;
            if (s == "SoundType::UI_SUCCESS") return SoundType::UI_SUCCESS;
            return static_cast<SoundType>(0); // default fallback
        };
                    obj.sound_to_play = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.x = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.y = conv(value_str);
                }
            }
            if (std::getline(iss, token, ',')) {
                auto pos = token.find('=');
                if (pos != std::string::npos) {
                    std::string value_str = token.substr(pos + 1);
                    auto conv = [](const std::string &s) { return std::stod(s); };
                    obj.z = conv(value_str);
                }
            }
            return obj;
        };
                    obj.sound_update = conv(value_str);
                }
            }
            return obj;

    }
    std::vector<uint8_t> serialize_SoundUpdatePacket(SoundUpdatePacket obj) {
        std::vector<uint8_t> buffer;
            { auto ser = [=](const PacketHeader& obj) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer;
            { auto ser = [=](PacketType value) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer(sizeof(uint8_t));
            uint8_t raw = static_cast<uint8_t>(value);
            std::memcpy(buffer.data(), &raw, sizeof(uint8_t));
            return buffer;
        };
              auto bytes = ser(obj.type);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const uint32_t &v) {   std::vector<uint8_t> buf(sizeof(uint32_t));   std::memcpy(buf.data(), &v, sizeof(uint32_t));   return buf; };
              auto bytes = ser(obj.size_of_data_without_header);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;
        };
              auto bytes = ser(obj.header);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [=](const SoundUpdate& obj) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer;
            { auto ser = [=](SoundType value) -> std::vector<uint8_t> {
            std::vector<uint8_t> buffer(sizeof(int));
            int raw = static_cast<int>(value);
            std::memcpy(buffer.data(), &raw, sizeof(int));
            return buffer;
        };
              auto bytes = ser(obj.sound_to_play);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.x);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.y);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            { auto ser = [](const double &v) {   std::vector<uint8_t> buf(sizeof(double));   std::memcpy(buf.data(), &v, sizeof(double));   return buf; };
              auto bytes = ser(obj.z);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;
        };
              auto bytes = ser(obj.sound_update);
              buffer.insert(buffer.end(), bytes.begin(), bytes.end()); }
            return buffer;

    }
    size_t size_when_serialized_SoundUpdatePacket(SoundUpdatePacket obj) {
        size_t total = 0;
            { auto size_fn = [=](const PacketHeader& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              total += size_fn(obj.type); }
            { auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              total += size_fn(obj.size_of_data_without_header); }
            return total;
        };
              total += size_fn(obj.header); }
            { auto size_fn = [=](const SoundUpdate& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [=](const SoundType &obj) -> size_t {
            return sizeof(int);
        };
              total += size_fn(obj.sound_to_play); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.x); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.y); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.z); }
            return total;
        };
              total += size_fn(obj.sound_update); }
            return total;

    }
    SoundUpdatePacket deserialize_SoundUpdatePacket(std::vector<uint8_t> &buffer) {
        SoundUpdatePacket obj;
            size_t offset = 0;
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> PacketHeader {
            PacketHeader obj;
            size_t offset = 0;
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> PacketType {
            if (buffer.size() < sizeof(uint8_t)) return static_cast<PacketType>(0);
            uint8_t raw = 0;
            std::memcpy(&raw, buffer.data(), sizeof(uint8_t));
            return static_cast<PacketType>(raw);
        };
              auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              size_t len = size_fn(obj.type);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.type = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   uint32_t v;   std::memcpy(&v, buf.data(), sizeof(uint32_t));   return v; };
              auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              size_t len = size_fn(obj.size_of_data_without_header);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.size_of_data_without_header = deser(slice);
              offset += len;
            }
            return obj;
        };
              auto size_fn = [=](const PacketHeader& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [=](const PacketType &obj) -> size_t {
            return sizeof(uint8_t);
        };
              total += size_fn(obj.type); }
            { auto size_fn = [](const uint32_t &v) { return sizeof(uint32_t); };
              total += size_fn(obj.size_of_data_without_header); }
            return total;
        };
              size_t len = size_fn(obj.header);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.header = deser(slice);
              offset += len;
            }
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> SoundUpdate {
            SoundUpdate obj;
            size_t offset = 0;
            { auto deser = [=](const std::vector<uint8_t> &buffer) -> SoundType {
            if (buffer.size() < sizeof(int)) return static_cast<SoundType>(0);
            int raw = 0;
            std::memcpy(&raw, buffer.data(), sizeof(int));
            return static_cast<SoundType>(raw);
        };
              auto size_fn = [=](const SoundType &obj) -> size_t {
            return sizeof(int);
        };
              size_t len = size_fn(obj.sound_to_play);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.sound_to_play = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.x);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.x = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.y);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.y = deser(slice);
              offset += len;
            }
            { auto deser = [](const std::vector<uint8_t> &buf) {   double v;   std::memcpy(&v, buf.data(), sizeof(double));   return v; };
              auto size_fn = [](const double &v) { return sizeof(double); };
              size_t len = size_fn(obj.z);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.z = deser(slice);
              offset += len;
            }
            return obj;
        };
              auto size_fn = [=](const SoundUpdate& obj) -> size_t {
            size_t total = 0;
            { auto size_fn = [=](const SoundType &obj) -> size_t {
            return sizeof(int);
        };
              total += size_fn(obj.sound_to_play); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.x); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.y); }
            { auto size_fn = [](const double &v) { return sizeof(double); };
              total += size_fn(obj.z); }
            return total;
        };
              size_t len = size_fn(obj.sound_update);
              if (offset + len > buffer.size()) return obj;
              std::vector<uint8_t> slice(buffer.begin() + offset, buffer.begin() + offset + len);
              obj.sound_update = deser(slice);
              offset += len;
            }
            return obj;

    }
    void list_all_available_functions() {

    }
};



} // namespace meta_program

#endif // META_PROGRAM_HPP
