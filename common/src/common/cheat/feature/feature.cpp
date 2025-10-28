#include "feature.h"

common::feature::feature(const std::string_view& name, image* icon) : name(name), icon(icon) {}

common::feature::~feature() = default;
