#include "WinCan.h"



/// @brief: fetch a list of all connected candlelight devices. 
std::vector<std::string> WindowsCandleDev::getDevices()
{
  uint8_t num_devices = 0;
  candle_handle handle;
  std::vector<std::string> ret;
  // TODO throw exceptions 

  if (!candle_list_scan(&devlist))
  {
    // TODO throw exception because of an error in device scanning
    candle_list_free(devlist);
    return ret;
  }

  candle_list_length(devlist, &num_devices);
  if (num_devices == 0)
  {
    candle_list_free(devlist);
    return ret;
  }

  // TODO have these be optional debug statements
  printf("detected %d candle device(s):\n", num_devices);
  for (unsigned i = 0; i < num_devices; i++)
  {
    if (candle_dev_get(devlist, i, &handle))
    {
      uint8_t channels;
      candle_channel_count(handle, &channels);

      ret.push_back((char *) candle_dev_get_path(handle));

      candle_dev_free(handle);
    }
    else
    {
      printf("error getting info for device %d\n", i);
    }
  }

  return ret;
}




/// @brief: establish a connection to a candle device.
/// @param dev_idx: index of the device in the candle_list to connect to 
///                 default 0
/// @param rate: the baud rate to establish the connection as. default 500k
/// @throws: CanWindowsGetDeviceException if there was an error getting the dev
/// @throws: CanWindowsOpenException if error opening device
/// @throws: CanWindowsOpenException
/// @return: TODO
void WindowsCandleDev::Open(uint8_t dev_idx, uint32_t rate)
{

  // unable to access the device
  if (!candle_dev_get(devlist, dev_idx, &hdev))
  {
    throw CanWindowsGetDeviceException;
  }

  // attempt to open the device;
  if (!candle_dev_open(hdev))
  {
    throw CanWindowsOpenException;
  }


  // attempt to set the baud rate to rate
  try 
  {
    setBaudRate(rate);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what();
    return;
  }

  // actually start the channel
  if (!candle_channel_start(hdev, 0, 0))
  {
    throw CanWindowsOpenException;
  }
}



/// @brief: close a connection to the current candle device.
/// @throws: CanWindowsCloseException on error
/// @return: win_can_close_error if an error was encountered, win_can_no_error on ok
void WindowsCandleDev::Close()
{
  // attempt to close the device connection.
  if (!candle_dev_close(hdev) || !candle_dev_free(hdev))
  {
    throw CanWindowsCloseException;
  }
}



/// @brief: sets the device to the specified baud rate.
///
/// @throws: CanWindowsGetDeviceException if a device error
/// @throws: CanWindowsTimingException if a set timing error
void WindowsCandleDev::setBaudRate(uint32_t rate)
{
  baud = rate;
  candle_devstate_t state;

  if (!candle_dev_get_state(hdev, &state))
  {
    throw CanGenericException;
  }

  if (state == CANDLE_DEVSTATE_INUSE)
  {
    printf("device in use\n");
    // TODO print(?) that the device is in use
  }
  else if (state == CANDLE_DEVSTATE_AVAIL)
  {
    printf("device is available\n");

    if (!candle_channel_set_bitrate(hdev, 0, rate))
    {
      throw CanWindowsTimingException;
    }
  }

}



/// @brief: receive a message from the device.
/// @throws: TODO exception on read error
CanFrame WindowsCandleDev::readCanData()
{
  candle_frame_t frame;
  CanFrame ret;
  
  // read from the device
  if (candle_frame_read(hdev, &frame, 1000))
  {
    // make sure there wasn't an error when reading
    if (candle_frame_type(&frame) == CANDLE_FRAMETYPE_RECEIVE)
    {
      uint8_t dlc = candle_frame_dlc(&frame);
      uint8_t *data = candle_frame_data(&frame);

      printf("ID 0x%08x [%d]", candle_frame_id(&frame), dlc);
      for (int i = 0; i < dlc; i++)
      {
        printf(" %02X", data[i]);
      }
      printf("\n");
    }
  }
  // handle errors
  else
  {
    if (candle_dev_last_error(hdev) == CANDLE_ERR_READ_TIMEOUT)
    {
      printf("timeout occurred\n");
    }
  }

  ret = frame;

  return ret;
}



/// @brief: send a can frame on the bus.
///
/// @return: -1 on error, 0 on success
int16_t WindowsCandleDev::writeCanData(uint16_t id, uint8_t dlc, uint8_t * data)
{
  candle_frame_t frame;
  frame.can_dlc = dlc;
  frame.can_id = id;
  memcpy(frame.data, data, dlc);

 
  if (!candle_frame_send(hdev, 0, &frame))
  {
    return -1;
  }

  return 0;
}




