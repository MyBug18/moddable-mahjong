#pragma once

#include <sol/sol.hpp>
#include <unordered_set>

template <typename T>
class ROSet
{
private:
    std::unordered_set<T>& set;

public:
    using value_type = std::unordered_set<T>::value_type;
    using iterator = std::unordered_set<T>::const_iterator;
    using size_type = std::unordered_set<T>::size_type;

    iterator begin() const
    {
        return set.begin();
    }

    iterator end() const
    {
        return set.end();
    }

    static void BindLua(sol::state& lua)
    {
        static int idCounter = 0;

        auto type = lua.new_usertype<ROSet<T>>("Set" + idCounter++, sol::no_constructor);
        type["contains"] = &ROSet<T>::contains;
    }

    explicit ROSet<T>(std::unordered_set<T>& from) : set{ from }
    {
    }

    explicit ROSet<T>(const std::unordered_set<T>& from) : set{ const_cast<std::unordered_set<T>&>(from) }
    {
    }

    bool contains(const T& member)
    {
        return set.contains(member);
    }

    size_type size() const
    {
        return set.size();
    }
};
