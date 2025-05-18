/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "boxes/transhub_box.h"

#include "lang/lang_keys.h"
#include "ui/widgets/labels.h"
#include "ui/wrap/vertical_layout.h"
#include "styles/style_boxes.h"
#include "styles/style_layers.h"
#include "ui/widgets/buttons.h"
#include "window/window_session_controller.h"
#include "main/main_session.h"

namespace Boxes
{

  TransHubBox::TransHubBox(
      QWidget *,
      not_null<Window::SessionController *> controller)
      : _controller(controller)
  {
  }

  void TransHubBox::prepare()
  {
    setTitle(tr::lng_transhub_title());

    const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);

    // Add TransHub feature UI controls here
    const auto info = content->add(
        object_ptr<Ui::FlatLabel>(
            content,
            tr::lng_transhub_info(),
            st::boxLabel),
        st::boxPadding);

    widthValue() | rpl::start_with_next([=](int width)
                                        { content->resizeToWidth(width); }, content->lifetime());

    setDimensions(st::boxWidth, st::boxPadding.top() + info->height() + st::boxPadding.bottom());
  }

  void ShowTransHubBox(
      not_null<Window::SessionController *> controller)
  {
    controller->show(
        Box<TransHubBox>(controller));
  }

} // namespace Boxes