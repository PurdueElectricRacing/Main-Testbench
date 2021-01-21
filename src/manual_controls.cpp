// #include "manual_controls.h"


// bool ManualControlsDefaults::initDefaults(double _max_volt)
// {
//   max_volt = _max_volt;
//   return true;
// }


// inline double ManualControlsDefaults::getMaxVolts()
// {
//   return max_volt;
// }


// /// @brief: Slot for when a spin box's value is changed to update a slider.
// ///
// /// @return: none
// void updateSliderFromSpinBox(QSlider * slider, QDoubleSpinBox * spinbox)
// {
//   int slider_pos = slider->sliderPosition();
//   double spin_val = spinbox->value();

//   // get the number number of increments per volts
//   double slider_increment = slider->maximum() /
//                             ManualControlsDefaults::getMaxVolts();

//   int new_pos = spin_val * slider_increment;

//   slider->setSliderPosition(new_pos);
// }



// /// @brief: Slot for when a slider changes position and the spin box needs 
// ///         updated
// ///
// /// @return: none
// void updateSpinBoxFromSlider(QSlider * slider, QDoubleSpinBox * spinbox)
// {
//   int slider_pos = slider->sliderPosition();
//   double spin_val = spinbox->value();

//   double new_val = ManualControlsDefaults::getMaxVolts() *
//                    ((double)slider->maximum() / (double) slider_pos);

//   spinbox->setValue(new_val);
// }
