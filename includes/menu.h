#if !defined(MENU_H)
#define MENU_H

#include "tools.h"

#include <fmt/format.h>
#include <functional>
#include <tuple>

template <typename... T>
struct get_first;

template <typename T, typename... Tn>
struct get_first<T, Tn...>
{
    using type = std::remove_reference_t<T>;
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

template <typename Idx>
struct choice
{
    using index_type = Idx;
    Idx index;
    const char *description;

    constexpr choice(const Idx &i, const char *desc) : index{i}, description{desc}
    {
    }

    auto get_label() const
    {
        return fmt::format("{}. {}", index, description);
    }

    template <typename T>
    bool invoke_if_match(T &&x)
    {
        if (x == *this)
        {
            (*this)();
            return true;
        }
        return false;
    }

    friend bool operator==(const choice &lho, const choice &rho)
    {
        return lho.index == rho.index;
    }
    friend bool operator==(const index_type &lho, const choice &rho)
    {
        return lho == rho.index;
    }
    friend bool operator==(const choice &lho, const index_type &rho)
    {
        return lho.index == rho;
    }
};

template <typename... Choice>
struct choice_selector
{
    using index_type = get_index_type_t<Choice...>;
    const char *msj;
    const char *err;
    const std::tuple<Choice...> choices;

    constexpr choice_selector(const char *msj, const char *err, Choice &&...choices)
        : msj{msj}, err{err}, choices{std::forward<Choice>(choices)...}
    {
    }
    constexpr choice_selector(const char *msj, const char *err, std::tuple<Choice...> &&choices)
        : msj{msj}, err{err}, choices{std::move<std::tuple<Choice...>>(choices)}
    {
    }

    index_type operator()() const
    {
        fmt::println("{}", msj);
        std::apply(print_choices, choices);

        index_type opc;
    ask_opc:
        try
        {
            while (true)
            {
                opc = input<index_type>();
                bool valid_choice = std::apply(matches_choice, std::tuple_cat(std::make_tuple(opc), choices));
                if (valid_choice)
                    break;
                fmt::println("{}", err);
            }
        }
        catch (const std::ios::failure &)
        {
            std::cin.clear();
            std::string line;
            std::getline(std::cin, line);
            fmt::println("{}", err);
            goto ask_opc;
        }

        return opc;
    }

private:
    static void print_choices(const Choice &...c)
    {
        (fmt::println("{}", c.get_label()), ...);
    }

    static bool matches_choice(const index_type &choice, const Choice &...c) { return ((choice == c) || ...); }
};

template <typename... Arg>
auto choose(const char *msj, const char *err, Arg &&...choices)
{
    return choice_selector(msj, err, std::forward<Arg>(choices)...)();
}

template <typename Idx, typename Operation>
class menu_option
{
    choice<Idx> m_choice;
    Operation op;

public:
    using index_type = Idx;

    constexpr menu_option(const Idx &idx, const char *desc, Operation &&oper) : m_choice{idx, desc}, op{std::forward<Operation>(oper)} {}

    auto get_label() const
    {
        return m_choice.get_label();
    }

    auto operator()() const
    {
        op();
    }

    friend bool operator==(const menu_option &lho, const menu_option &rho)
    {
        return lho.m_choice == rho.m_choice;
    }
    friend bool operator==(const index_type &lho, const menu_option &rho)
    {
        return lho == rho.m_choice;
    }
    friend bool operator==(const menu_option &lho, const index_type &rho)
    {
        return lho.m_choice == rho;
    }
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

template <typename... Options>
class menu
{
private:
    using choice_selector_type = choice_selector<Options...>;
    using index_type = choice_selector_type::index_type;
    using index_sequence_type = std::index_sequence_for<Options...>;
    choice_selector_type m_selector;

public:
    menu(const char *msj, const char *err, Options &&...options)
        : m_selector{msj, err, std::forward<Options>(options)...}
    {
    }

    menu(const char *msj, const char *err, std::tuple<Options...> &&options)
        : m_selector{msj, err, std::move<std::tuple<Options...>>(options)}
    {
    }

    auto operator()() const -> void
    {
        index_type choice = m_selector();

        match_choice(choice, index_sequence_type{});
    }

private:
    template <typename Choice, std::size_t... Is>
    auto match_choice(Choice &&choice, std::index_sequence<Is...>) const
    {

        (invoke_if_match(std::forward<Choice>(choice), std::get<Is>(m_selector.choices)), ...);
    }
};

#endif // MENU_H
