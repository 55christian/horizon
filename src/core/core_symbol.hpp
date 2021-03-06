#pragma once
#include "core.hpp"
#include "pool/pool.hpp"
#include "pool/symbol.hpp"
#include <deque>
#include <iostream>
#include <memory>
#include "document/idocument_symbol.hpp"

namespace horizon {
class CoreSymbol : public Core, public IDocumentSymbol {
public:
    CoreSymbol(const std::string &filename, Pool &pool);
    bool has_object_type(ObjectType ty) const override;
    Symbol *get_symbol() override;

    Junction *get_junction(const UUID &uu) override;
    Line *get_line(const UUID &uu) override;
    SymbolPin *get_symbol_pin(const UUID &uu) override;
    Arc *get_arc(const UUID &uu) override;

    Junction *insert_junction(const UUID &uu) override;
    void delete_junction(const UUID &uu) override;
    Line *insert_line(const UUID &uu) override;
    void delete_line(const UUID &uu) override;
    Arc *insert_arc(const UUID &uu) override;
    void delete_arc(const UUID &uu) override;

    SymbolPin *insert_symbol_pin(const UUID &uu) override;
    void delete_symbol_pin(const UUID &uu) override;

    class LayerProvider *get_layer_provider() override;

    std::vector<Line *> get_lines() override;
    std::vector<Arc *> get_arcs() override;
    std::vector<const Pin *> get_pins() override;

    void rebuild(bool from_undo = false) override;

    bool set_property(ObjectType type, const UUID &uu, ObjectProperty::ID property,
                      const class PropertyValue &value) override;
    bool get_property(ObjectType type, const UUID &uu, ObjectProperty::ID property,
                      class PropertyValue &value) override;
    bool get_property_meta(ObjectType type, const UUID &uu, ObjectProperty::ID property,
                           class PropertyMeta &meta) override;

    std::string get_display_name(ObjectType type, const UUID &uu) override;

    const Symbol *get_canvas_data();
    std::pair<Coordi, Coordi> get_bbox() override;

    bool can_search_for_object_type(ObjectType type) const override;
    std::list<SearchResult> search(const SearchQuery &q) override;

    void reload_pool() override;

    void set_pin_display_mode(Symbol::PinDisplayMode mode);

    const std::string &get_filename() const override;

private:
    std::map<UUID, Text> *get_text_map() override;
    std::map<UUID, Polygon> *get_polygon_map() override;

    Symbol sym;
    std::string m_filename;
    Symbol::PinDisplayMode pin_display_mode = Symbol::PinDisplayMode::PRIMARY;

    class HistoryItem : public Core::HistoryItem {
    public:
        HistoryItem(const Symbol &s) : sym(s)
        {
        }
        Symbol sym;
    };
    void history_push() override;
    void history_load(unsigned int i) override;
    void save(const std::string &suffix) override;
    void delete_autosave() override;
};
} // namespace horizon
