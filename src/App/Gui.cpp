
#include <somegames/somegames.hpp>

#include <cmath>
#include <fstream>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// GameDialog
///////////////////////////////////////////////////////////////////////////////

GameDialog::GameDialog(Gui & rGui, Gtk::Window & win) :
  _rGui(rGui)
{
    
  set_destroy_with_parent(true);
  set_title("Change game...");
  set_default_size(200, 200);
  set_transient_for(win);
  set_modal();
  set_hide_on_close();

  auto pVBox0 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  set_child(*pVBox0);

  auto mkHandler = [this](GameType gt) {
      this->_rGui.changeGame(gt);
      this->set_visible(false);
  };


  Gtk::Button * pButton;

  pButton = Gtk::make_managed<Gtk::Button>("Tictactoe");
  pButton->signal_clicked().connect(std::bind(mkHandler, GameType::Tictactoe));
  pVBox0->append(*pButton);

  pButton = Gtk::make_managed<Gtk::Button>("Connect four");
  pButton->signal_clicked().connect(std::bind(mkHandler, GameType::Connectfour));
  pVBox0->append(*pButton);

  pButton = Gtk::make_managed<Gtk::Button>("Gomoku 8x8");
  pButton->signal_clicked().connect(std::bind(mkHandler, GameType::Gomoku8x8));
  pVBox0->append(*pButton);

  pButton = Gtk::make_managed<Gtk::Button>("Gomoku 7x9");
  pButton->signal_clicked().connect(std::bind(mkHandler, GameType::Gomoku7x9));
  pVBox0->append(*pButton);

  pButton = Gtk::make_managed<Gtk::Button>("Reversi");
  pButton->signal_clicked().connect(std::bind(mkHandler, GameType::Reversi));
  pVBox0->append(*pButton);

}

///////////////////////////////////////////////////////////////////////////////
// BotDialog
///////////////////////////////////////////////////////////////////////////////

BotDialog::BotDialog(Gui & rGui, Gtk::Window & win) :
  _rGui(rGui)
{
    
  set_destroy_with_parent(true);
  set_title("Change bot...");
  set_default_size(200, 200);
  set_transient_for(win);
  set_modal();
  set_hide_on_close();

  auto pVBox0 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  set_child(*pVBox0);

  auto mkHandler = [this](BotType gt) {
      this->_rGui.changeBot(gt);
      this->set_visible(false);
  };

  Gtk::Button * pButton;

  pButton = Gtk::make_managed<Gtk::Button>("Random");
  pButton->signal_clicked().connect(std::bind(mkHandler, BotType::Random));
  pVBox0->append(*pButton);

  pButton = Gtk::make_managed<Gtk::Button>("Monte Carlo 1k");
  pButton->signal_clicked().connect(std::bind(mkHandler, BotType::Mc1k));
  pVBox0->append(*pButton);

  pButton = Gtk::make_managed<Gtk::Button>("Monte Carlo 100k");
  pButton->signal_clicked().connect(std::bind(mkHandler, BotType::Mc100k));
  pVBox0->append(*pButton);

  pButton = Gtk::make_managed<Gtk::Button>("Human");
  pButton->signal_clicked().connect(std::bind(mkHandler, BotType::Human));
  pVBox0->append(*pButton);

}


///////////////////////////////////////////////////////////////////////////////
// MyWindow
///////////////////////////////////////////////////////////////////////////////

MyWindow::MyWindow(Gui & rGui) :
  _rGui(rGui),
  _gameDialog(rGui, *this),
  _botDialog(rGui, *this)
{

  // main horinzontal box
  auto pHBox0 = Gtk::make_managed<Gtk::Box>();
  set_child(*pHBox0);

  /////////////////////////////////////
  // left hand side: canevas
  /////////////////////////////////////
  _canevas.set_draw_func(sigc::mem_fun(*this, &MyWindow::drawCanevas));
  _canevas.set_expand(true);
  pHBox0->append(_canevas);

  auto source = Gtk::GestureClick::create();
  _canevas.add_controller(source);
  source->signal_released().connect(sigc::mem_fun(*this, &MyWindow::handleClick));

  /////////////////////////////////////
  // right hand side: buttons
  /////////////////////////////////////
  auto pVBox1 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  pVBox1->set_size_request(200);
  pHBox0->append(*pVBox1);

  // quit button
  auto pButtonQuit = Gtk::make_managed<Gtk::Button>("Quit");
  pButtonQuit->signal_clicked().connect(sigc::mem_fun(_rGui, &Gui::quit));
  pVBox1->append(*pButtonQuit);

  // reset button
  auto pButtonReset = Gtk::make_managed<Gtk::Button>("Reset");
  pButtonReset->signal_clicked().connect([this]() {
      this->_rGui.gameReset();
      this->refresh();
    });
  pVBox1->append(*pButtonReset);

  // change game button
  auto pButtonChangeGame = Gtk::make_managed<Gtk::Button>("Change game");
  pButtonChangeGame->signal_clicked().connect([this]() {
      _gameDialog.set_visible(true);
    });
  pVBox1->append(*pButtonChangeGame);
  _gameDialog.signal_hide().connect([this](){
      this->_rGui.gameReset();
      this->updateTitle();
      this->refresh();
    });

  // change bot button
  auto pButtonChangeBot = Gtk::make_managed<Gtk::Button>("Change bot");
  pButtonChangeBot->signal_clicked().connect([this]() {
      _botDialog.set_visible(true);
    });
  pVBox1->append(*pButtonChangeBot);
  _botDialog.signal_hide().connect([this](){
      this->updateTitle();
    });

  // export button
  auto pButtonExport = Gtk::make_managed<Gtk::Button>("Export");
  pButtonExport->signal_clicked().connect(
      sigc::mem_fun(*this, &MyWindow::on_export_button_clicked));
  pVBox1->append(*pButtonExport);

  // status label
  _label.set_margin_top(10);
  pVBox1->append(_label);

  // finalize main window
  set_default_size(800, 600);
  updateTitle();
  updateStatus();
}

void MyWindow::updateTitle() {
  set_title("somegames (" + _rGui.gameName() + ", " + _rGui.botName() + ")");
}

void MyWindow::drawCanevas(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
  
  cr->save();
  if (_rGui.gameIsRunning())
    cr->set_source_rgba(0.3, 0.6, 0.1, 1.0);
  else
    cr->set_source_rgba(0.6, 0.6, 0.6, 1.0);
  cr->paint();
  cr->restore();

  const auto [ni, nj] = _rGui.gameGetSize();

  const double sizeI = height / double(ni);
  const double sizeJ = width / double(nj);

  // draw grid
  cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);

  for (int i=1; i<ni; i++) {
    const double y = i * sizeI;
    cr->move_to(0, y);
    cr->line_to(width, y);
  }

  for (int j=1; j<nj; j++) {
    const double x = j * sizeJ;
    cr->move_to(x, 0);
    cr->line_to(x, height);
  }

  cr->stroke();

  // draw cells
  const double margin = 10.0;
  const double deltaI = sizeI / 2.0;
  const double deltaJ = sizeJ / 2.0;
  const double radius0 = std::min(deltaI, deltaJ);
  const double radius = std::max(margin, radius0 - margin);

  for (const auto [i, j] : _rGui.gameGetRedPositions()) {
    cr->set_source_rgba(1.0, 0.0, 0.0, 1.0);
    cr->arc(j*sizeJ + deltaJ, (ni-i-1)*sizeI + deltaI, radius, 0.0, 2 * M_PI);
    cr->fill();
  }

  for (const auto [i, j] : _rGui.gameGetBluePositions()) {
    cr->set_source_rgba(0.0, 0.0, 1.0, 1.0);
    cr->arc(j*sizeJ + deltaJ, (ni-i-1)*sizeI + deltaI, radius, 0.0, 2 * M_PI);
    cr->fill();
  }

  /*
  for (int i=0; i<ni; i++) {
    for (int j=0; j<nj; j++) {
      const Cell c = _rGui.gameGetCell({i, j});
      if (c == Cell::Red) {
        cr->set_source_rgba(1.0, 0.0, 0.0, 1.0);
        cr->arc(j*sizeJ + deltaJ, (ni-i-1)*sizeI + deltaI, radius, 0.0, 2 * M_PI);
        cr->fill();
      }
      else if (c == Cell::Blue) {
        cr->set_source_rgba(0.0, 0.0, 1.0, 1.0);
        cr->arc(j*sizeJ + deltaJ, (ni-i-1)*sizeI + deltaI, radius, 0.0, 2 * M_PI);
        cr->fill();
      }
    }
  }
  */

}

void MyWindow::updateStatus() {
  const Status s = _rGui.gameGetStatus();
  const std::string str = _rGui.fmtStatus(s);
  _label.set_text(str);
}

void MyWindow::handleClick(int, double x, double y) {

  if (_rGui.gameIsRunning()) {

    const auto [ni, nj] = _rGui.gameGetSize();
    const double width = _canevas.get_allocated_width();
    const double height = _canevas.get_allocated_height();
    const int ii = ni * y / double(height);
    const int i = ni - ii - 1;
    const int j = nj * x / double(width);
    const Status status = _rGui.gameGetStatus();

    if (status == Status::RedPlay or _rGui.botIsHuman()) {
      _rGui.gamePlay({i, j});
      refresh();
    }

    while (_rGui.gameGetStatus() == Status::BluePlay and not _rGui.botIsHuman()) {
      const Position p = _rGui.botGenMove();
      _rGui.gamePlay(p);
      refresh();
    }

  }

}

void MyWindow::refresh() {
  _canevas.queue_draw();
  updateStatus();
}

void MyWindow::on_export_button_clicked() {

  // filters
  auto filters = Gio::ListStore<Gtk::FileFilter>::create();

  auto filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Txt files");
  filter_text->add_suffix("txt");
  filters->append(filter_text);

  auto filter_json = Gtk::FileFilter::create();
  filter_json->set_name("JSON files");
  filter_json->add_mime_type("application/json");
  filters->append(filter_json);
  
  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  filters->append(filter_any);

  auto filter_all = Gtk::FileFilter::create();

  // dialog
  auto dialog = Gtk::FileDialog::create();
  dialog->set_modal();
  dialog->set_filters(filters);
  dialog->save(*this, sigc::bind(sigc::mem_fun(
    *this, &MyWindow::on_export_dialog_finish), dialog));

}

void MyWindow::on_export_dialog_finish(
  const std::shared_ptr<Gio::AsyncResult>& result, 
  const std::shared_ptr<Gtk::FileDialog>& dialog)
{

  try {
    auto file = dialog->save_finish(result);
    const std::string filename = file->get_path();
    std::cout << "exporting to " <<  filename << std::endl;
    if (filename.ends_with(".txt")) {
      GameData gd = _rGui.gameGetData();
      std::ofstream ofs(filename);
      exportTxt(ofs, gd);
    }
    else if (filename.ends_with(".json")) {
      GameData gd = _rGui.gameGetData();
      std::ofstream ofs(filename);
      exportJson(ofs, gd);
    }
    else {
      std::cout << "unknown file format " << std::endl;
    }
  }
  catch (...) {
    std::cout << "export skipped" << std::endl;
  }

}


///////////////////////////////////////////////////////////////////////////////
// Gui
///////////////////////////////////////////////////////////////////////////////

Gui::Gui() : 
  _pApp(Gtk::Application::create()) 
{
    changeGame(GameType::Tictactoe);
    changeBot(BotType::Mc1k);
}

int Gui::run() {
  return _pApp->make_window_and_run<MyWindow>(0, nullptr, *this);
}

void Gui::quit() {
  auto pWin = _pApp->get_run_window();
  _pApp->remove_window(*pWin);
  _pApp->quit();
}

Position Gui::gameGetSize() const {
  return _pGame->getSize();
}

Status Gui::gameGetStatus() const {
  return _pGame->getStatus();
}

bool Gui::gameIsRunning() const {
  return _pGame->isRunning();
}

void Gui::gameReset() {
  _pGame->reset();
}

const PosSet & Gui::gameGetRedPositions() const {
  return _pGame->getRedPositions();
}

const PosSet & Gui::gameGetBluePositions() const {
  return _pGame->getBluePositions();
}

void Gui::gamePlay(const Position & p) {
  const bool ok = _pGame->play(p);
  if (not ok) {
    const auto [i, j] = p;
    std::cout << "cannot play " << i << " " << j << std::endl;
  }
}

const std::string & Gui::gameName() const {
  return _pGame->getName();
}

const std::string & Gui::botName() const {
  return _pBot->getName();
}

void Gui::changeGame(GameType gt) {
  switch (gt) {
    case GameType::Tictactoe: 
      _pGame = std::make_unique<Tictactoe>(); break;
    case GameType::Connectfour:
      _pGame = std::make_unique<Connectfour>(); break;
    case GameType::Gomoku8x8:
      _pGame = std::make_unique<Gomoku<8, 8>>(); break;
    case GameType::Gomoku7x9:
      _pGame = std::make_unique<Gomoku<7, 9>>(); break;
    case GameType::Reversi:
      _pGame = std::make_unique<Reversi>(); break;
  }
}

void Gui::changeBot(BotType bt) {
  switch (bt) {
    case BotType::Random:
      _pBot = std::make_unique<Random>(); break;
    case BotType::Mc1k:
      _pBot = std::make_unique<Montecarlo>(1000); break;
    case BotType::Mc100k:
      _pBot = std::make_unique<Montecarlo>(100000); break;
    case BotType::Human:
      _pBot = std::make_unique<Human>(); break;
  }
}

GameData Gui::gameGetData() const {
  return mkGameData(*_pGame);
}

Position Gui::botGenMove() {
  return _pBot->genMove(*_pGame);
}

bool Gui::botIsHuman() const {
  return _pBot->isHuman();
}


