#pragma once
#include "block/component.hpp"
#include "core/tool.hpp"
#include "imp/imp_interface.hpp"
#include <forward_list>

namespace horizon {

class ToolEditParameterProgram : public ToolBase {
public:
    ToolEditParameterProgram(IDocument *c, ToolID tid);
    ToolResponse begin(const ToolArgs &args) override;
    ToolResponse update(const ToolArgs &args) override;
    bool can_begin() override;

private:
};
} // namespace horizon
