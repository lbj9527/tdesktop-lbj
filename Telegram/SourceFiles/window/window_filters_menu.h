/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "api/api_chat_filters_remove_manager.h"
#include "base/timer.h"
#include "ui/effects/animations.h"
#include "ui/widgets/side_bar_button.h"
#include "ui/widgets/scroll_area.h"

namespace Data
{
  struct ChatFilterTitle;
} // namespace Data

namespace Ui
{
  class VerticalLayout;
  class VerticalLayoutReorder;
  enum class FilterIcon : uchar;
  class PopupMenu;
} // namespace Ui

namespace Window
{

  class SessionController;

  class FiltersMenu final
  {
  public:
    FiltersMenu(
        not_null<Ui::RpWidget *> parent,
        not_null<SessionController *> session);
    ~FiltersMenu();

  private:
    void setup();
    void setupMainMenuIcon();
    void scrollToButton(not_null<Ui::RpWidget *> widget);
    void refresh();
    void setupList();
    [[nodiscard]] bool premium() const;
    [[nodiscard]] base::unique_qptr<Ui::SideBarButton> prepareAll();
    [[nodiscard]] base::unique_qptr<Ui::SideBarButton> prepareButton(
        not_null<Ui::VerticalLayout *> container,
        FilterId id,
        Data::ChatFilterTitle title,
        Ui::FilterIcon icon,
        bool toBeginning = false);
    void openFiltersSettings();
    void showMenu(QPoint position, FilterId id);
    void applyReorder(
        not_null<Ui::RpWidget *> widget,
        int oldPosition,
        int newPosition);

    const not_null<SessionController *> _session;
    const not_null<Ui::RpWidget *> _parent;
    Ui::RpWidget _outer;
    Ui::SideBarButton _menu;
    Ui::ScrollArea _scroll;
    const not_null<Ui::VerticalLayout *> _container;
    object_ptr<Ui::VerticalLayout> _list = {nullptr};
    std::unique_ptr<Ui::VerticalLayoutReorder> _reorder;
    base::flat_map<FilterId, base::unique_qptr<Ui::SideBarButton>> _filters;
    FilterId _activeFilterId = 0;
    base::unique_qptr<Ui::SideBarButton> _setup;
    base::unique_qptr<Ui::SideBarButton> _transhub;
    base::unique_qptr<Ui::PopupMenu> _popupMenu;
    Api::RemoveComplexChatFilter _removeApi;

    int _reordering = 0;
    bool _ignoreRefresh = false;
    bool _waitingSuggested = false;
    Ui::Animations::Simple _scrollToAnimation;

    struct
    {
      FilterId filterId = -1;
      base::Timer timer;
    } _drag;
  };

} // namespace Window
