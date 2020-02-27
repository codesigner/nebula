/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#ifndef DATATYPES_VALUE_H_
#define DATATYPES_VALUE_H_

#include "base/Base.h"
#include "thrift/ThriftTypes.h"
#include "datatypes/Date.h"
#include "datatypes/Path.h"

namespace apache {
namespace thrift {

template<class T, class U>
class Cpp2Ops;

}  // namespace thrift
}  // namespace apache


namespace nebula {

struct Map;
struct List;

enum class NullType {
    __NULL__ = 0,
    NaN      = 1,
    BAD_DATA = 2,
    BAD_TYPE = 3
};


struct Value {
    friend class apache::thrift::Cpp2Ops<Value, void>;

    enum class Type {
        __EMPTY__ = 0,
        NULLVALUE = 1,
        BOOL = 2,
        INT = 3,
        FLOAT = 4,
        STRING = 5,
        DATE = 6,
        DATETIME = 7,
        PATH = 8,
        LIST = 9,
        MAP = 10,
    };

    // Constructors
    Value() : type_(Type::__EMPTY__) {}
    Value(Value&& rhs);
    Value(const Value& rhs);

    Value(const NullType& v);       // NOLINT
    Value(NullType&& v);            // NOLINT
    Value(const bool& v);           // NOLINT
    Value(bool&& v);                // NOLINT
    Value(const double& v);         // NOLINT
    Value(double&& v);              // NOLINT
    Value(const std::string& v);    // NOLINT
    Value(std::string&& v);         // NOLINT
    Value(const Date& v);           // NOLINT
    Value(Date&& v);                // NOLINT
    Value(const DateTime& v);       // NOLINT
    Value(DateTime&& v);            // NOLINT
    Value(const Path& v);           // NOLINT
    Value(Path&& v);                // NOLINT
    Value(const List& v);           // NOLINT
    Value(List&& v);                // NOLINT
    Value(const Map& v);            // NOLINT
    Value(Map&& v);                 // NOLINT
    // We need a template here to support multiple integer types
    template<
        typename T,
        typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
    Value(T&& v) {             // NOLINT
        setI(std::forward<T>(v));
    }

    Type type() const noexcept {
        return type_;
    }

    void clear();

    Value& operator=(Value&& rhs);
    Value& operator=(const Value& rhs);

    void setNull(const NullType& v);
    void setNull(NullType&& v);
    void setBool(const bool& v);
    void setBool(bool&& v);
    void setInt(const int64_t& v);
    void setInt(int64_t&& v);
    void setFloat(const double& v);
    void setFloat(double&& v);
    void setStr(const std::string& v);
    void setStr(std::string&& v);
    void setDate(const Date& v);
    void setDate(Date&& v);
    void setDateTime(const DateTime& v);
    void setDateTime(DateTime&& v);
    void setPath(const Path& v);
    void setPath(Path&& v);
    void setList(const List& v);
    void setList(List&& v);
    void setMap(const Map& v);
    void setMap(Map&& v);
    // We need a template here to support multiple integer types
    template<
        typename T,
        typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
    void setInt(T&& v) {
        clear();
        setI(std::forward<T>(v));
    }

    const NullType& getNull() const;
    const bool& getBool() const;
    const int64_t& getInt() const;
    const double& getFloat() const;
    const std::string& getStr() const;
    const Date& getDate() const;
    const DateTime& getDateTime() const;
    const Path& getPath() const;
    const List& getList() const;
    const Map& getMap() const;

    NullType moveNull();
    bool moveBool();
    int64_t moveInt();
    double moveFloat();
    std::string moveStr();
    Date moveDate();
    DateTime moveDateTime();
    Path movePath();
    List moveList();
    Map moveMap();

    NullType& mutableNull();
    bool& mutableBool();
    int64_t& mutableInt();
    double& mutableFloat();
    std::string& mutableStr();
    Date& mutableDate();
    DateTime& mutableDateTime();
    Path& mutablePath();
    List& mutableList();
    Map& mutableMap();

    bool operator==(const Value& rhs) const;

    static const Value& null() noexcept {
        static const Value kNullValue(NullType::__NULL__);
        return kNullValue;
    }

private:
    Type type_;

    union Storage {
        NullType                nVal;
        bool                    bVal;
        int64_t                 iVal;
        double                  fVal;
        std::string             sVal;
        Date                    dVal;
        DateTime                tVal;
        Path                    pVal;
        std::unique_ptr<List>   lVal;
        std::unique_ptr<Map>    mVal;

        Storage() {}
        ~Storage() {}
    } value_;

    template <class T>
    void destruct(T& val) {
        (&val)->~T();
    }

    // Null value
    void setN(const NullType& v);
    void setN(NullType&& v);
    // Bool value
    void setB(const bool& v);
    void setB(bool&& v);
    // Integer value
    void setI(const int64_t& v);
    void setI(int64_t&& v);
    // Double float value
    void setF(const double& v);
    void setF(double&& v);
    // String value
    void setS(const std::string& v);
    void setS(std::string&& v);
    // Date value
    void setD(const Date& v);
    void setD(Date&& v);
    // DateTime value
    void setT(const DateTime& v);
    void setT(DateTime&& v);
    // Path value
    void setP(const Path& v);
    void setP(Path&& v);
    // List value
    void setL(const std::unique_ptr<List>& v);
    void setL(std::unique_ptr<List>&& v);
    void setL(const List& v);
    void setL(List&& v);
    // Map value
    void setM(const std::unique_ptr<Map>& v);
    void setM(std::unique_ptr<Map>&& v);
    void setM(const Map& v);
    void setM(Map&& v);
};

void swap(Value& a, Value& b);

std::ostream& operator<<(std::ostream& os, const Value::Type& type);

}  // namespace nebula
#endif  // DATATYPES_VALUE_H_

