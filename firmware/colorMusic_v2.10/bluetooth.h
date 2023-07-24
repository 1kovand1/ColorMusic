#if defined DEBUG && BLUETOOTH_IFACE == Serial && BLUETOOTH_RATE != DEBUG_RATE
#error Bluetooth and debug can't use the same interface with different rates
#endif

void processBluetooth(byte *mode, *brightness)
{
    if (int len = BLUETOOTH_IFACE.available())
    {
        char* str = new char[len + 1];
        BLUETOOTH_IFACE.readBytes(str, len);
        str[len] = '\0';
        if (str[0] == 'b')
        {
            int val = atoi(str);
            if (val >= 0 && val <= 255)
            {
                *brightness = val;
                BLUETOOTH_IFACE.print(F("Brightness = "));
                BLUETOOTH_IFACE.println(val);
            }
            else
                BLUETOOTH_IFACE.printn(F("Incorrect value"));
        }
        else if (str[0] >= '0' && str[0] <= '9')
        {
            int val = atoi(str);
            if (val >= 0 && val < MODE_AMOUNT)
            {
                *mode = val;
                BLUETOOTH_IFACE.print(F("Mode = "));
                BLUETOOTH_IFACE.println(val);
            }
            else
                BLUETOOTH_IFACE.println(F("Incorrect value"));
        }
        delete[] str;
    }
}
