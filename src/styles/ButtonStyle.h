#include <QString>

namespace ButtonStyle
{
    inline QString buttonNormalColor()
    {
        return R"(
            QPushButton {
                background-color: #216988 ;
                color: white;
                padding: 8px 12px;
                border-radius: 4px;
                font-weight: bold;
            }

            QPushButton:hover {
                background-color: #185D7B ;
            }

            QPushButton:pressed {
                background-color: #176180;
            }
        )";
    };

    inline QString buttonNavBarColor()
    {
        return R"(
        QPushButton {
            background-color: none;
            border:  none;
            }
        QPushButton:hover {
            background-color: #454545;
        }
        )";
    }
}
