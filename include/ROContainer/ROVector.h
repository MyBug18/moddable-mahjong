#pragma once

#include <sol/sol.hpp>
#include <vector>

template <typename T>
class ROVector
{
private:
    std::vector<T>& vector;

public:
    using value_type = std::vector<T>::value_type;
    using iterator = std::vector<T>::const_iterator;
    using size_type = std::vector<T>::size_type;

    iterator begin() const
    {
        return vector.begin();
    }

    iterator end() const
    {
        return vector.end();
    }

    static void BindLua(sol::state& lua)
    {
        static int idCounter = 0;

        auto type = lua.new_usertype<ROVector<T>>("Vector" + idCounter++, sol::no_constructor);
        type["at"] = &ROVector<T>::at;
    }

    explicit ROVector<T>(std::vector<T>& from) : vector{ from }
    {
    }

    explicit ROVector<T>(const std::vector<T>& from) : vector{ const_cast<std::vector<T>&>(from) }
    {
    }

    T at(int index)
    {
        auto result = vector.at(index);
        return vector.at(index);
    }

    size_type size() const
    {
        return vector.size();
    }
};
