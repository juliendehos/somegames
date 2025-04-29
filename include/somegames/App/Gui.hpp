#pragma once

#include "App.hpp"
#include "../Export/Export.hpp"
#include "../Game/Game.hpp"

#include <gtkmm.h>

class Gui;

enum class GameType { Tictactoe, Connectfour, Gomoku8x8, Gomoku7x9, Reversi };

enum class BotType { Random, Mc1k, Mc100k, Human };

///////////////////////////////////////////////////////////////////////////////
// GameDialog
///////////////////////////////////////////////////////////////////////////////

class GameDialog : public Gtk::Window {
  private:
    Gui & _rGui;

  public:
    explicit GameDialog(Gui & rGui, Gtk::Window & win);
};

///////////////////////////////////////////////////////////////////////////////
// BotDialog
///////////////////////////////////////////////////////////////////////////////

class BotDialog : public Gtk::Window {
  private:
    Gui & _rGui;

  public:
    explicit BotDialog(Gui & rGui, Gtk::Window & win);
};

///////////////////////////////////////////////////////////////////////////////
// MyWindow
///////////////////////////////////////////////////////////////////////////////

class MyWindow : public Gtk::Window {
  private:
    Gui & _rGui;
    Gtk::DrawingArea _canevas;
    Gtk::Label _label;
    GameDialog _gameDialog;
    BotDialog _botDialog;

  public:
    explicit MyWindow(Gui & rGui);

  private:
    void drawCanevas(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void handleClick(int, double x, double y);

    void updateStatus();
    void updateTitle();
    void refresh();

    void on_export_button_clicked();
    void on_export_dialog_finish(
        const std::shared_ptr<Gio::AsyncResult>& result, 
        const std::shared_ptr<Gtk::FileDialog>& dialog);
};

///////////////////////////////////////////////////////////////////////////////
// Gui
///////////////////////////////////////////////////////////////////////////////

class Gui : public App {
  private:
    std::shared_ptr<Gtk::Application> _pApp;

  public:
    explicit Gui();
    int run() override;

    void quit();
    void changeGame(GameType gt);
    void changeBot(BotType bt);

    Position gameGetSize() const;
    bool gameIsRunning() const;
    Status gameGetStatus() const;
    void gameReset();
    const PosSet & gameGetRedPositions() const;
    const PosSet & gameGetBluePositions() const;
    void gamePlay(const Position & p);
    Position botGenMove();
    const std::string & gameName() const;
    GameData gameGetData() const;
    bool botIsHuman() const;
    const std::string & botName() const;

};


