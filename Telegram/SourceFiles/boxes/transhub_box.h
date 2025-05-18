/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/layers/box_content.h"

namespace Main
{
  class Session;
} // namespace Main

namespace Window
{
  class SessionController;
} // namespace Window

namespace Ui
{
  class VerticalLayout;
} // namespace Ui

namespace Boxes
{

  class TransHubBox : public Ui::BoxContent
  {
  public:
    TransHubBox(
        QWidget *,
        not_null<Window::SessionController *> controller);

  private:
    void prepare() override;

    const not_null<Window::SessionController *> _controller;
  };

  void ShowTransHubBox(
      not_null<Window::SessionController *> controller);

} // namespace Boxes