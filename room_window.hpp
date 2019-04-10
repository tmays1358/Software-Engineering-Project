#ifndef ROOM_WINDOW
#define ROOM_WINDOW

class Room_window
{
    public:
        Message_window();
        void on_room_select_enter(int room_num);
        void show();
        void update();
    private:
        int current_room_select();
};

#endif
