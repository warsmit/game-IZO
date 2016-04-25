TEMPLATE = app
CONFIG -= console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
TARGET = gameIZO

LIBS += -LC:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:/SFML/include
DEPENDPATH += C:/SFML/include

SOURCES += main.cpp \
    Block.cpp \
    Game.cpp \
    Level.cpp \
    Player.cpp \
    TextureManager.cpp \
    Tile.cpp

HEADERS += \
    Block.hpp \
    Game.hpp \
    Identifiers.hpp \
    Level.hpp \
    TextureManager.hpp \
    Tile.hpp \
    Player.hpp
