#ifndef INFO_TAB_WINDOW
#define INFO_TAB_WINDOW

class Info_tab_window
{
    public:
        Info_tab_window();
        void on_join_select();
        void on_manage_select();
        void on_leave_select();
    private:
        Join_window join_win;
        Message_window message_win;
};

#endif
