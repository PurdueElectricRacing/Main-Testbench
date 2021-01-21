#ifndef MANUAL_CONTROLS_H
#define MANUAL_CONTROLS_H

#include <QObject>
#include <QSlider>
#include <QDoubleSpinBox>


// TODO change this to be in a config file somewhere i guess?


class ManualControlsDefaults
{
public:
  static bool initDefaults(double _max_volt);
  inline static double getMaxVolts();

private:
  static double max_volt;
};

// static ManualControlsDefaults g_man_defaults;

void updateSliderFromCombobox(QSlider * slider, QDoubleSpinBox * combobox);
void updateComboboxFromSlider(QSlider * slider, QDoubleSpinBox * combobox);


#endif // MANUAL_CONTROLS_H
