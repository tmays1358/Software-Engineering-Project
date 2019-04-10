#ifndef JOIN_WINDOW
#define JOIN_WINDOW

#include <string>

class Join_window
{
    public:
        Join_window();
        void on_ok_select();
        void on_cancel_select();
        void show();
        void update();
    private:
        string room_name;
        int room_key;
};

#endif
