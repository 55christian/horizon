#pragma once
#include "core/tool.hpp"
#include "tool_helper_merge.hpp"
#include "tool_helper_move.hpp"
#include "nlohmann/json.hpp"

namespace horizon {

class ToolPaste : public ToolHelperMove, public ToolHelperMerge {
public:
    ToolPaste(IDocument *c, ToolID tid);
    ToolResponse begin(const ToolArgs &args) override;
    ToolResponse update(const ToolArgs &args) override;
    bool can_begin() override
    {
        if (tool_id == ToolID::PASTE)
            return true;
        else
            return selection.size();
    }
    bool is_specific() override
    {
        return tool_id == ToolID::DUPLICATE;
    }

private:
    void fix_layer(int &la);
    void apply_shift(Coordi &c, const Coordi &cursor_pos);
    Coordi shift;
    json paste_data;
    ToolResponse begin_paste(const json &j, const Coordi &cursor_pos);
    void update_tip();
};
} // namespace horizon
