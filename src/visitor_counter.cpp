#include "visitor_counter.h"

VisitorCounter* VisitorCounter::_instance;
uint32_t VisitorCounter::_last_pressed_ms = 0;

void VisitorCounter::begin()
{
    _main_state.write_csv_func = [&] (const SwitchNumber switch_number) { write_csv(switch_number); };
    _state_selector.main_state = &_main_state;
    _state_selector.battery_state = &_battery_state;
    _state_selector.adjust_state = &_adjust_state;
    _state_selector.begin();

    analogReadResolution(12);

    // LED
    _led_red.begin();
    _led_yellow.begin();
    _led_green.begin();
    _led_blue.begin();

    _led_red.off();
    _led_yellow.off();
    _led_green.off();
    _led_blue.off();

    // Switch
    _switch_1.begin();
    _switch_2.begin();
    _switch_3.begin();
    _switch_4.begin();
    _switch_5.begin();

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

    // TM1627
    _tm1627.begin(1);
    _tm1627.clearDisplay();

    // PCF8563
    _pcf8563.begin();
    if (_pcf8563.lostPower())
    {
        // 時刻未設定
        // todo: USB給電を切ると電池があってもフラグが立ってしまう
        Serial.println("RTC is not configured time.");
        _led_red.on();
        delay(100);
        _led_red.off();
        delay(100);
        _led_red.on();
        delay(100);
        _led_red.off();
        delay(100);
        _led_red.on();
        delay(100);
    }

    _led_red.off();
    _led_yellow.on();
    _led_blue.on();

    // SDカード初期化
    init_sd();

    // 日時表示
    const DateTime date_time = _pcf8563.now();
    _tm1627.setDisplay(date_time.year(), 3);
    _tm1627.setDisplay(date_time.year(), 7);
    delay(300);
    _tm1627.clearDisplay();
    delay(100);
    _tm1627.setDisplay(date_time.month() * 100 + date_time.day(), 3);
    delay(300);
    _tm1627.clearDisplay();
    delay(100);
    _tm1627.setDisplay(date_time.hour() * 100 + date_time.minute(), 7);
    delay(300);
    _tm1627.clearDisplay();
    delay(100);
}

void VisitorCounter::update(const uint32_t delay_ms)
{
    // USB CDC読み込み時刻設定
    read_serial();

    // LED周期処理
    _led_red.update();
    _led_yellow.update();
    _led_green.update();
    _led_blue.update();

    // state処理
    _state_selector.update();
}

bool VisitorCounter::anti_chattering()
{
    if (millis() < _last_pressed_ms + chattering_interval_ms)
    {
        return false;
    }

    _last_pressed_ms = millis();
    return true;
}

void VisitorCounter::on_switch_1_pressed()
{
    if (!anti_chattering())
    {
        return;
    }

    _instance->_state_selector.on_switch_1_pressed();
}

void VisitorCounter::on_switch_2_pressed()
{
    if (!anti_chattering())
    {
        return;
    }

    _instance->_state_selector.on_switch_2_pressed();
}

void VisitorCounter::on_switch_3_pressed()
{
    if (!anti_chattering())
    {
        return;
    }

    _instance->_state_selector.on_switch_3_pressed();
}

void VisitorCounter::on_switch_4_pressed()
{
    if (!anti_chattering())
    {
        return;
    }

    _instance->_state_selector.on_switch_4_pressed();
}

void VisitorCounter::on_switch_5_pressed()
{
    if (!anti_chattering())
    {
        return;
    }

    _instance->_state_selector.on_switch_5_pressed();
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
    if (_file)
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

    _led_blue.off();

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

    // ファイル開いた
    snprintf(message, sizeof(message), "Write data to %s.", file_name);
    Serial.println(message);

    _led_yellow.blink(50, 2950);

    // GPIO割り込み有効化
    init_gpio_interrupt();
}

void VisitorCounter::init_gpio_interrupt()
{
    // Switch 割り込み有効化
    _switch_1.attach_interrupt(on_switch_1_pressed, FALLING);
    _switch_2.attach_interrupt(on_switch_2_pressed, FALLING);
    _switch_3.attach_interrupt(on_switch_3_pressed, FALLING);
    _switch_4.attach_interrupt(on_switch_4_pressed, FALLING);
    _switch_5.attach_interrupt(on_switch_5_pressed, FALLING);
}

void VisitorCounter::write_csv(const SwitchNumber switch_number)
{
    if (!_file)
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