#include "themeutils.h"

FakePaintDevice::FakePaintDevice() = default;

QPaintEngine *FakePaintDevice::paintEngine() const
{
    return nullptr;
}

void FakePaintDevice::setHidpi(bool value)
{
    _hidpi = value;
}

int FakePaintDevice::metric(QPaintDevice::PaintDeviceMetric metric) const
{
    switch (metric) {
    case QPaintDevice::PdmDevicePixelRatio:
        if (_hidpi) {
            return 2;
        }
        return 1;
    default:
        return QPaintDevice::metric(metric);
    }
}
