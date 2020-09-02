#if !defined(MENU_H)
#define MENU_H

#include "tools.h"

template <typename... T>
struct get_first;

template <typename T, typename... Tn>
struct get_first<T, Tn...>
{
    using type = remove_reference_t<T>;
};

template <typename... T>
struct get_index_type
{
    using type = typename get_first<T...>::type::index_type;
};

template <typename... T>
using get_first_t = typename get_first<T...>::type;

template <typename... T>
using get_index_type_t = typename get_index_type<T...>::type;

template <typename T, typename Tuple>
constexpr bool tuple_contains(const T &x, Tuple &&t)
{
    return apply([&x](auto &&... element) -> bool { return ((element == x) || ...); }, forward<Tuple>(t));
}

template <typename Idx>
struct choice
{
    using index_type = Idx;
    Idx index;
    string description;

    choice(const Idx &i, const string &desc) : index{i}, description{desc} {}

    friend bool operator==(const choice &lho, const choice &rho) { return lho.index == rho.index; }
    friend bool operator==(const index_type &lho, const choice &rho) { return lho == rho.index; }
    friend bool operator==(const choice &lho, const index_type &rho) { return lho.index == rho; }

    friend ostream &operator<<(ostream &os, const choice &mo)
    {
        return os << mo.index << ". " << mo.description;
    }
};

template <typename... Choice>
constexpr auto choice_selector(const string &msj, const string &err, Choice &&... c)
{
    using index_type = get_index_type_t<Choice...>;
    return [msj, err, choices = tuple(forward<Choice>(c)...)]() {
        cout << msj << endl;
        apply([](const auto &... c) { (cout << ... << c); }, choices);

        index_type opc;
    ask_opc:
        try
        {
            while (opc = input<index_type>(), !tuple_contains(opc, choices))
                cout << err << endl;
        }
        catch (const ios::failure &)
        {
            cin.clear();
            std::string line;
            std::getline(std::cin, line);
            cout << err << endl;
            goto ask_opc;
        }
        return opc;
    };
}

template <typename Idx, typename Operation>
struct menu_option
{
    using index_type = Idx;
    choice<Idx> ch;
    Operation op;

    menu_option(const Idx &idx, const string &desc, Operation &&oper)
        : ch{idx, desc}, op{forward<Operation>(oper)}
    {
    }

    template <typename... Arg>
    auto operator()(Arg &&... arg) const { return invoke(op, forward<Arg>(arg)...); }

    friend bool operator==(const menu_option &lho, const menu_option &rho) { return lho.ch == rho.ch; }
    friend bool operator==(const index_type &lho, const menu_option &rho) { return lho == rho.ch; }
    friend bool operator==(const menu_option &lho, const index_type &rho) { return lho.ch == rho; }
    friend ostream &operator<<(ostream &os, const menu_option &mo) { return os << mo.ch; }
};

template <typename T, typename U>
bool invoke_if_match(const T &key, const U &callable)
{
    if (key == callable)
    {
        callable();
        return true;
    }
    return false;
}

template <size_t I, typename T, typename Tuple>
bool invoke_if_match(const T &x, Tuple &&t)
{
    if (x == get<I>(t))
    {
        get<I>(t)();
        return true;
    }
    return false;
}

template <size_t... I, typename... Option>
constexpr auto menu(const string &msj, const string &err, Option &&... option)
{
    using index_type = get_index_type_t<Option...>;
    return [msj, err, option...]() {
        auto cs = choice_selector(msj, err, option...);
        index_type choice = cs();
        invoke([&](auto &&... op) { (invoke_if_match(choice, op) || ...); },
               option...);
    };
}

#endif // MENU_H
