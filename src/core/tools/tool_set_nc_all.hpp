#pragma once
#include "core/tool.hpp"
#include <forward_list>

namespace horizon {

class ToolSetNotConnectedAll : public ToolBase {
public:
    ToolSetNotConnectedAll(IDocument *c, ToolID tid);
    ToolResponse begin(const ToolArgs &args) override;
    ToolResponse update(const ToolArgs &args) override;
    bool can_begin() override;
    bool is_specific() override
    {
        return true;
    }

private:
};
} // namespace horizon
