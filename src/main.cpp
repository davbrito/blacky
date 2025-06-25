#include "main.h"
#include "blacky.h"
#include "menu.h"
#include <iostream>
#include <istream>

extern const std::map<Carta, std::string> cartas_map;
int main()
{
    cli_main();
}

struct app
{
    bool end = false;

public:
    const char *title_message;
    const char *error_message;
    const char *exit_message;

    app(const char *title, const char *error, const char *exit_msg)
        : title_message(title), error_message(error), exit_message(exit_msg)
    {
    }

    void stop()
    {
        end = true;
    }

    bool is_running() const
    {
        return !end;
    }

    template <typename... Option>
    void run(Option &&...option) const
    {
        menu<Option...> m{title_message, error_message, std::forward<Option>(option)...};
        while (is_running())
        {
            m();
        }
        fmt::println("{}", exit_message);
    }
};

void cli_main()
{
    auto a = app{
        "Ingrese una opcion:",
        "Opcion invalida. Intente de nuevo.",
        "Adios. Gracias por jugar.",

    };

    a.run(menu_option{'1', "Empezar partida.", [&]()
                      { jugar(); }},
          menu_option{'2', "Instrucciones.", [&]()
                      { instrucciones(); }},
          menu_option{'3', "Salir", [&]()
                      { a.stop(); }});
}
