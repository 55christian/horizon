#pragma once
#include <array>
#include <gtkmm.h>
#include <set>
#include "util/window_state_store.hpp"
#include "block/bom.hpp"
#include "util/changeable.hpp"
#include "util/export_file_chooser.hpp"
#include "pool/pool_parametric.hpp"

namespace horizon {

class BOMExportWindow : public Gtk::Window, public Changeable {
    friend class OrderableMPNSelector;

public:
    BOMExportWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &x, class Block *block,
                    class BOMExportSettings *settings, class Pool &pool, const std::string &project_dir);
    static BOMExportWindow *create(Gtk::Window *p, class Block *block, class BOMExportSettings *settings,
                                   class Pool &pool, const std::string &project_dir);

    void set_can_export(bool v);
    void generate();
    void update_preview();
    void update_orderable_MPNs();
    void update();

private:
    class Block *block;
    class BOMExportSettings *settings;
    class Pool &pool;
    PoolParametric pool_parametric;

    void update_concrete_parts();

    class MyExportFileChooser : public ExportFileChooser {
    protected:
        void prepare_chooser(Glib::RefPtr<Gtk::FileChooser> chooser) override;
        void prepare_filename(std::string &filename) override;
    };
    MyExportFileChooser export_filechooser;

    Gtk::Button *export_button = nullptr;
    Gtk::ComboBoxText *sort_column_combo = nullptr;
    Gtk::ComboBoxText *sort_order_combo = nullptr;
    Gtk::Revealer *done_revealer = nullptr;
    Gtk::Label *done_label = nullptr;
    Gtk::Entry *filename_entry = nullptr;
    Gtk::Button *filename_button = nullptr;
    Gtk::ListBox *orderable_MPNs_listbox = nullptr;

    Glib::RefPtr<Gtk::SizeGroup> sg_manufacturer;
    Glib::RefPtr<Gtk::SizeGroup> sg_MPN;
    Glib::RefPtr<Gtk::SizeGroup> sg_orderable_MPN;

    Gtk::TreeView *meta_parts_tv = nullptr;
    Gtk::Label *concrete_parts_label = nullptr;

    class MetaPartsListColumns : public Gtk::TreeModelColumnRecord {
    public:
        MetaPartsListColumns()
        {
            Gtk::TreeModelColumnRecord::add(MPN);
            Gtk::TreeModelColumnRecord::add(value);
            Gtk::TreeModelColumnRecord::add(manufacturer);
            Gtk::TreeModelColumnRecord::add(qty);
            Gtk::TreeModelColumnRecord::add(uuid);
            Gtk::TreeModelColumnRecord::add(concrete_MPN);
            Gtk::TreeModelColumnRecord::add(concrete_value);
            Gtk::TreeModelColumnRecord::add(concrete_manufacturer);
        }
        Gtk::TreeModelColumn<Glib::ustring> MPN;
        Gtk::TreeModelColumn<Glib::ustring> value;
        Gtk::TreeModelColumn<Glib::ustring> manufacturer;
        Gtk::TreeModelColumn<UUID> uuid;
        Gtk::TreeModelColumn<unsigned int> qty;

        Gtk::TreeModelColumn<Glib::ustring> concrete_MPN;
        Gtk::TreeModelColumn<Glib::ustring> concrete_value;
        Gtk::TreeModelColumn<Glib::ustring> concrete_manufacturer;
    };
    MetaPartsListColumns meta_parts_list_columns;

    Glib::RefPtr<Gtk::ListStore> meta_parts_store;

    Gtk::Box *param_browser_box = nullptr;
    Gtk::RadioButton *rb_tol_10 = nullptr;
    Gtk::RadioButton *rb_tol_1 = nullptr;
    Gtk::Button *button_clear_similar = nullptr;
    Gtk::Button *button_set_similar = nullptr;
    class PoolBrowserParametric *browser_param = nullptr;
    UUID meta_part_current;
    void update_meta_mapping();
    void handle_set_similar();
    void update_similar_button_sensitivity();

    class ListColumns : public Gtk::TreeModelColumnRecord {
    public:
        ListColumns()
        {
            Gtk::TreeModelColumnRecord::add(name);
            Gtk::TreeModelColumnRecord::add(column);
        }
        Gtk::TreeModelColumn<BOMColumn> column;
        Gtk::TreeModelColumn<Glib::ustring> name;
    };
    ListColumns list_columns;

    Glib::RefPtr<Gtk::ListStore> columns_store;
    Glib::RefPtr<Gtk::TreeModelFilter> columns_available;

    Glib::RefPtr<Gtk::ListStore> columns_store_included;

    Gtk::TreeView *cols_available_tv = nullptr;
    Gtk::TreeView *cols_included_tv = nullptr;
    Gtk::TreeView *preview_tv = nullptr;

    Gtk::Button *col_inc_button = nullptr;
    Gtk::Button *col_excl_button = nullptr;
    Gtk::Button *col_up_button = nullptr;
    Gtk::Button *col_down_button = nullptr;

    WindowStateStore state_store;

    void incl_excl_col(bool incl);
    void up_down_col(bool up);
    void update_incl_excl_sensitivity();
    void update_cols_included();

    void flash(const std::string &s);
    sigc::connection flash_connection;

    class ListColumnsPreview : public Gtk::TreeModelColumnRecord {
    public:
        ListColumnsPreview()
        {
            Gtk::TreeModelColumnRecord::add(row);
        }
        Gtk::TreeModelColumn<BOMRow> row;
    };
    ListColumnsPreview list_columns_preview;

    Glib::RefPtr<Gtk::ListStore> bom_store;
};
} // namespace horizon
