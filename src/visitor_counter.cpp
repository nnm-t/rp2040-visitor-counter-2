#include "visitor_counter.h"

VisitorCounter* VisitorCounter::_instance;

void VisitorCounter::begin()
{
    // LED
    _led_red.begin();
    _led_yellow.begin();
    _led_green.begin();

    _led_red.on();
    _led_yellow.on();
    _led_green.on();

    // Switch
    _switch_1.begin();
    _switch_2.begin();

    // Buzzer
    _buzzer.begin();

    // I2C
    Wire.setSDA(i2c0_sda);
    Wire.setSCL(i2c0_scl);

    // SPI
    SPI.setSCK(spi0_clk);
    SPI.setCS(spi0_ss);
    SPI.setRX(spi0_miso);
    SPI.setTX(spi0_mosi);

    // UART
    // USB
    Serial.begin(uart_baud);
    // UART0
    Serial1.setRX(uart0_rx);
    Serial1.setTX(uart0_tx);
    Serial1.begin(uart_baud);

    // PCF8563
    _pcf8563.begin();
    if (_pcf8563.lostPower())
    {
        // 時刻未設定
        Serial.println("RTC is not configured time.");
        return;
    }

    _is_rtc_configured = true;

    _led_red.off();

    // SDカード初期化
    init_sd();
}

void VisitorCounter::update(const uint32_t delay_ms)
{
    // USB CDC読み込み時刻設定
    read_serial();

    // これ以下は要RTC設定
    if (!_is_rtc_configured)
    {
        return;
    }

    if (_power_count < 50)
    {
        _led_yellow.on();
    }
    else
    {
        _led_yellow.off();
    }

    _power_count += delay_ms;

    if (_power_count >= 3000)
    {
        _power_count = 0;
    }

    if (_switch_1_pressed)
    {
        if (_switch_count == 0)
        {
            // SW1押した直後
            _led_red.on();
            _buzzer.beep(buzzer_frequency_hz, buzzer_duration_ms);

            // CSV出力
            write_csv(SwitchNumber::Switch1);
        }

        if (_switch_count >= 1000)
        {
            // 1s経過後
            _switch_count = 0;
            _switch_1_pressed = false;
            _led_red.off();
        }
        else
        {
            _switch_count += delay_ms;
        }
    }

    if (_switch_2_pressed)
    {
        if (_switch_count == 0)
        {
            // SW2押した直後
            _led_green.on();
            _buzzer.beep(buzzer_frequency_hz, buzzer_duration_ms);

            // CSV出力
            write_csv(SwitchNumber::Switch2);
        }

        if (_switch_count >= 1000)
        {
            // 1s経過後
            _switch_count = 0;
            _switch_2_pressed = false;
            _led_green.off();
        }
        else
        {
            _switch_count += delay_ms;
        }
    }
}

void VisitorCounter::on_switch_1_pressed()
{
    if (_instance->_switch_2_pressed)
    {
        return;
    }

    _instance->_switch_1_pressed = true;
}

void VisitorCounter::on_switch_2_pressed()
{
    if (_instance->_switch_1_pressed)
    {
        return;
    }

    _instance->_switch_2_pressed = true;
}

void VisitorCounter::read_serial()
{
    bool enter_command = false;

    while (Serial.available())
    {
        // USB CDC 文字列読み込み
        const char c = Serial.read();

        if (c == 0x08 && _str_current > 0)
        {
            // BackSpace
            _str_buffer[_str_current - 1] = '\0';
            _str_current--;
        }
        else if (c == '\n')
        {
            // Enter
            enter_command = true;
            break;
        }
        else if (c >= 0x20 && c < 0x7F && _str_current <= str_buffer_size - 1)
        {
            // 文字列
            _str_buffer[_str_current] = c;
            _str_current++;
        }
    }

    if (enter_command)
    {
        // コマンド解釈
        if (strstr(_str_buffer, "get") != nullptr)
        {
            // get
            // 時刻取得
            const DateTime date_time = _pcf8563.now();

            Serial.printf("%04d/%02d/%02d %02d:%02d:%02d\n", date_time.year(), date_time.month(), date_time.day(), date_time.hour(), date_time.minute(), date_time.second());
        }
        else if (strstr(_str_buffer, "set") != nullptr)
        {
            // set
            // 時刻設定
            int32_t years = 2000;
            int32_t months = 1;
            int32_t days = 1;
            int32_t hours = 0;
            int32_t minutes = 0;
            int32_t seconds = 0;

            sscanf(_str_buffer + 4, "%d/%d/%d %d:%d:%d", &years, &months, &days, &hours, &minutes, &seconds);

            Serial.println("Adjust to RTC...");

            const DateTime date_time(years, months, days, hours, minutes, seconds);
            _pcf8563.adjust(date_time);

            if (!_pcf8563.lostPower())
            {
                // 設定完了
                Serial.println("RTC configure OK.");

                _is_rtc_configured = true;

                _led_red.off();

                // SDカード初期化
                init_sd();
            }
        }
        else
        {
            Serial.println("Invalid command.");
        }

        // バッファリセット
        memset(_str_buffer, 0x00, str_buffer_size);
        _str_current = 0;
    }
}

void VisitorCounter::init_sd()
{
    if (_is_csv_opened)
    {
        return;
    }

    // SD
    const bool sd_initialized = SD.begin(spi0_ss);

    if (!sd_initialized)
    {
        Serial.println("TF init failed.");
        return;
    }

    _led_green.off();

    // 時刻取得
    const DateTime date_time = _pcf8563.now();
    // ファイル名生成
    char file_name[24] = { 0 };
    snprintf(file_name, sizeof(file_name), "/%04d_%02d_%02d.csv", date_time.year(), date_time.month(), date_time.day());
    // 日付の名前でファイルを開く
    // 無ければ新規作成、有れば末尾に追記
    _file = SD.open(file_name, FILE_WRITE);

    char message[41] = { 0 };

    if (!_file)
    {
        // ファイル開けなかった
        snprintf(message, sizeof(message), "File %s open failed.", file_name);
        Serial.println(message);
        return;
    }

    _is_csv_opened = true;

    // ファイル開いた
    snprintf(message, sizeof(message), "Write data to %s.", file_name);
    Serial.println(message);

    _led_yellow.off();

    // GPIO割り込み有効化
    init_gpio_interrupt();
}

void VisitorCounter::init_gpio_interrupt()
{
    // Switch 割り込み有効化
    _switch_1.attach_interrupt(on_switch_1_pressed, LOW);
    _switch_2.attach_interrupt(on_switch_2_pressed, LOW);
}

void VisitorCounter::write_csv(const SwitchNumber switch_number)
{
    if (!_is_csv_opened || !_is_rtc_configured || !_file)
    {
        return;
    }

    const DateTime date_time = _pcf8563.now();

    char str[36] = { 0 };
    snprintf(str, sizeof(str), "%04d/%02d/%02d %02d:%02d:%02d,%d", date_time.year(), date_time.month(), date_time.day(), date_time.hour(), date_time.minute(), date_time.second(), static_cast<uint8_t>(switch_number));

    Serial.println(str);

    _file.println(str);
    _file.flush();
}