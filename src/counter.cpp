#include "counter.h"

void Counter::increment(const SwitchNumber switch_number)
{
    switch (switch_number)
    {
        case SwitchNumber::Switch1:
            _switch_1++;
            _tm1627.clearDisplayDigit(4, 7);
            _tm1627.setDisplay(_switch_1, 3);
            break;
        case SwitchNumber::Switch2:
            _switch_2++;
            _tm1627.clearDisplayDigit(0, 3);
            _tm1627.setDisplay(_switch_2, 7);
            break;
        break;
    }
}

void Counter::clear_7seg()
{
    _tm1627.clearDisplay();
}

void Counter::read_json()
{
    // 時刻取得
    const DateTime date_time = _pcf8563.now();
    // ファイル名生成
    snprintf(_file_name, sizeof(_file_name), "/%04d_%02d_%02d.json", date_time.year(), date_time.month(), date_time.day());
    // ファイル存在確認
    if (!SD.exists(_file_name))
    {
        Serial.printf("File %s is not exist.\n", _file_name);
        return;
    }

    File file = SD.open(_file_name, FILE_READ);
    
    if (!file)
    {
        Serial.printf("File %s open failed.\n", _file_name);
        return;
    }

    // deserialize
    JsonDocument json_document;
    DeserializationError error = deserializeJson(json_document, file);

    if (error != DeserializationError::Ok)
    {
        Serial.println("JSON deserialization error.");
        return;
    }

    _switch_1 = json_document["switch_1"].as<uint32_t>();
    _switch_2 = json_document["switch_2"].as<uint32_t>();
}

void Counter::write_json()
{
    JsonDocument json_document;
    json_document["switch_1"] = _switch_1;
    json_document["switch_2"] = _switch_2;

    // 上書きするAPIがないので、ファイル存在する場合は一旦削除
    if (SD.exists(_file_name))
    {
        SD.remove(_file_name);
    }

    File file = SD.open(_file_name, FILE_WRITE);

    if (!file)
    {
        Serial.printf("File %s open failed.\n", _file_name);
        return;
    }

    serializeJson(json_document, file);
}