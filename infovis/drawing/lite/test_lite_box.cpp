/* -*- C++ -*-
 *
 * Copyright (C) 2002 Jean-Daniel Fekete
 * 
 * This file is part of MillionVis.
 * 
 * MillionVis is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 * 
 * MillionVis is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MillionVis; see the file COPYING.  If not, write to the
 * Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA. 
 */
#include <infovis/drawing/lite/LayoutTable.hpp>
#include <infovis/drawing/lite/LiteBox.hpp>
#include <infovis/drawing/lite/LiteMenu.hpp>
#include <infovis/drawing/lite/LiteFrame.hpp>
#include <infovis/drawing/lite/LiteLabel.hpp>
#include <infovis/drawing/lite/LiteWindow.hpp>
#include <infovis/drawing/lite/LiteButton.hpp>
#include <infovis/drawing/lite/LiteComboBox.hpp>
#include <iostream>
#include <cstdio>
using namespace infovis;

class MyLiteWindow : public LiteWindow
{
protected:
  Interactor3States * inter_;
  LiteMenu * menu_;
public:
  MyLiteWindow(const string& name, const Box& box)
    : LiteWindow(name, box),
      inter_(0), menu_(0)
  {
    setColor(color_half_grey);
  }

  void setMenu(LiteMenu * m) { menu_ = m; }
#if 0
  virtual void doMouse(Button button, ButtonState state, int x, int y) {
    if (state == button_down) {
      if (inter_ == 0) {
	PathList pl;
	pick(Box(x-1, y-1, x+1, y+1), pl);
	List l;
	sortPathList(pl, l);
	for (List::reverse_iterator i = l.rbegin(); i != l.rend(); i++) {
	  inter_ =
	    dynamic_cast<Interactor3States*>((*i)->interactor("3States",
							      mouse_id));
	  if (inter_ != 0) {
	    break;
	  }
	}
	if (inter_ == 0)
	  inter_ = menu_;
      }
      inter_->start(Point(x, y));
    }
    else {
      if (inter_ != 0)
	inter_->finish(Point(x, y));
      //inter_->desactivate();
      inter_ = 0;
    }
    repaint();
  }
  void doMotion(int x, int y) {
    if (inter_ != 0) {
      inter_->drag(Point(x, y));
    }
    repaint();
  }  
#endif
};

class Changer : public ChangeObserver {
public:
  Changer(LiteLabel * lab) : label(lab) { }

  virtual void changed(ChangeObservable * obs) {
    static int change_count;
    char buffer[1024];
    sprintf(buffer, "Hello changed %d times", change_count++);
    label->setLabel(buffer);
    label->repaint();
  }
protected:
  LiteLabel * label;
};

int main(int argc, char *argv[])
{
  LiteWindow::init(argc, argv);
  MyLiteWindow win("test lite box", Box(0, 0, 640, 400));
  Point pt(100, 100);
  LiteBox box;

  LiteLabel lab1("Label 1");
  box.addChild(&lab1);
  LiteLabel lab2("Label 2");
  box.addChild(&lab2);
  LiteLabel lab3("Label 3");
  box.addChild(&lab3);
  LiteLabel lab4("Label 4");
  box.addChild(&lab4);
  LiteLabel lab5("Label 5");
  box.addChild(&lab5);
  box.setPosition(Point(300, 300));
  LiteFrame frm(&box, color_white, 10);

  win.addChild(&frm);

  LiteMenu menu;
  menu.setVisible(false);

  menu.addChild(new LiteLabel("Item 1"));
  menu.addChild(new LiteLabel("Item 2"));
  menu.addChild(new LiteLabel("Item 3"));
  win.addChild(&menu);
  win.setMenu(&menu);

  LiteBox table(new LayoutTable(2));
  table.addChild(new LiteLabel("Cell 1"));
  table.addChild(new LiteLabel("Cell 2"));
  table.addChild(new LiteLabel("Cell 3"));
  table.addChild(new LiteLabel("Cell 4"));
  table.addChild(new LiteLabel("Cell 5"));
  table.addChild(new LiteLabel("Cell 6"));
  table.setPosition(Point(100, 100));
  win.addChild(&table);

  LiteLabel pm("Push Me");
  pm.setPosition(Point(10, 10));
  LiteButton button(&pm);
  Changer changer(&pm);
  button.addChangeObserver(&changer);
  win.addChild(&button);

  LiteMenu menu2;

  menu2.addChild(new LiteLabel("Item 1 - 2"));
  menu2.addChild(new LiteLabel("Item 2 - 2"));
  menu2.addChild(new LiteLabel("Item 3 - 2"));

  LiteComboBox combo(&menu2);
  combo.setPosition(Point(500, 300));
  win.addChild(&combo);

  win.run();
  return 0;
}
