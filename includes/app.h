#if !defined(BLACKY_APP_H)
#define BLACKY_APP_H

struct app
{
    bool end = false;

public:
    app() {}

    void stop()
    {
        end = true;
    }

    bool is_running() const
    {
        return !end;
    }

    template <typename Main>
    void run(Main const &fn) const
    {
        while (is_running())
        {
            fn();
        }
    }
};

#endif // BLACKY_APP_H
