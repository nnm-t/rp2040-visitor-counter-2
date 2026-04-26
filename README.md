# 同人誌即売会 来場者カウンター for 即売会 (小規模量産対応版)

[来場者カウンター for 即売会](https://github.com/nnm-t/rp2040-visitor-counter) の小規模量産対応版。
[STM32G051使用版](https://github.com/nnm-t/stm32g051f8p6-visitor-counter)はカードへの読み書きが安定せず、RP2040を使用して作り直した。

## 発案

しーさいど氏 (@SeasideExp) の[このポスト](https://x.com/SeasideExp/status/1992435754606428389)

## プリント基板

- 72 x 47 x 1.6 mm
  - 秋月C基板と同サイズ。[アクリルパネル](https://akizukidenshi.com/catalog/g/g109852/)の取り付けも可能。
- 表面実装部品を多く使用した。はんだ付けには慣れが必要。
  - 温調はんだごて、はんだの他、フラックス、ピンセット、ルーペを用意して作業する。
- [回路図](pcb/schematic.pdf)
  - [基板配置図](pcb/pcb.png)

## 部品

### 秋月電子で購入

|ID|種別|メーカー|型番|パッケージ|数量|
|:--|:--|:--|:--|:--|--:|
|BT1|電池ホルダー|COMFORTABLE ELECTRONIC|[BC-2001](https://akizukidenshi.com/catalog/g/g106925/)|表面実装|1|
|BZ1|圧電スピーカー|SPL (Hong Kong)|[PT86-091940LMR](https://akizukidenshi.com/catalog/g/g131380/)|表面実装|1|
|C1|積層セラミックコンデンサ (4700pF)|村田製作所|[GRM188B11H472KA01](https://akizukidenshi.com/catalog/g/g105598/)|表面実装 (1608)|1|
|C2|トリマコンデンサ (5-20pF)|SUNTAN TECHNOLOGY|[TSC3S520T1R](https://akizukidenshi.com/catalog/g/g113742/)|表面実装|1|
|C3,C4,C7|積層セラミックコンデンサ (0.1μF)|村田製作所|[GCM188L81H104KA57](https://akizukidenshi.com/catalog/g/g116143/)|表面実装 (1608)|3|
|C5|積層セラミックコンデンサ (10uF)|村田製作所|[GRM188R6YA106MA73](https://akizukidenshi.com/catalog/g/g113161/)|表面実装 (1608)|1|
|D1|TVSダイオード|Panjit|[PEC3824C2A-AU](https://akizukidenshi.com/catalog/g/g129497/)|表面実装 (SOT-23)|1|
|D3|LED (赤)|OptoSupply|[OSHR1608C1A](https://akizukidenshi.com/catalog/g/g103978/)|表面実装 (1608)|1|
|D4|LED (黄)|OptoSupply|[OSYG1608C1A](https://akizukidenshi.com/catalog/g/g103984/)|表面実装 (1608)|1|
|D5|LED (黄緑)|OptoSupply|[OSYG1608C1A](https://akizukidenshi.com/catalog/g/g103980)|表面実装 (1608)|1|
|J1|USB Type-C レセプタクル|Neltron Industrial|[5077CR-16-SMC2-BK-TR](https://akizukidenshi.com/catalog/g/g114356/)|スルーホール|1|
|J2|TFカードスロット|ヒロセ電機|[DM3AT-SF-PEJM5](https://akizukidenshi.com/catalog/g/g102395/)|表面実装|1|
|J3|1.27mmピッチ ピンヘッダ (1x40P)|Neltron Industrial|[2199SA-40G-3015-23](https://akizukidenshi.com/catalog/g/g103865/)|スルーホール (1.27mm)|1|
|J4|PHコネクタ ベース付ポスト (表面実装タイプ) 4P|日本圧着端子製造|[S4B-PH-SM4-TB(LF)(SN)](https://akizukidenshi.com/catalog/g/g115636/)|表面実装|1|
|R3,R4,JP1,JP2|0Ωジャンパー|KOA|[RK73Z1JTTD](https://akizukidenshi.com/catalog/g/g111619//)|表面実装 (1608)|4|
|R5,R11|カーボン抵抗 (1MΩ)|KOA|[RK73B1JTTD105J](https://akizukidenshi.com/catalog/g/g130359/)|表面実装 (1608)|2|
|R6,R7,R8,R9,R10,R15,R16|カーボン抵抗 (10kΩ)|KOA|[RK73B1JTTD103J](https://akizukidenshi.com/catalog/g/g130355/)|表面実装 (1608)|7|
|R12,R13|カーボン抵抗 (470Ω)|KOA|[RK73B1JTTD471J](https://akizukidenshi.com/catalog/g/g130349/)|表面実装 (1608)|2|
|SW1,SW2|タクトスイッチ (12mm)|Switronic Industrial|[1273HIM-160G-G](https://akizukidenshi.com/catalog/g/g102561/)|スルーホール|2|
|SW3|スライドスイッチ|XIAMEN JINBEILI ELECTRONICS|[SS-12D00G3](https://akizukidenshi.com/catalog/g/g115707/)|スルーホール|1|
|U3,U4,U5,U6|理想ダイオード|WCH|[CH213K](https://akizukidenshi.com/catalog/g/g129462/)|SOT-23-3|4|
|U7|低損失レギュレータ (3.3V500mA)|日清紡マイクロデバイス|[NJM2884U1-33](https://akizukidenshi.com/catalog/g/g110673/)|SOT89-5|1|
|Y1|水晶振動子 (32.768kHz)|セイコーエプソン|[FC-135 32.768000KHz12.5](https://akizukidenshi.com/catalog/g/g107195/)|表面実装|1|
|-|1.27mmピッチ ジャンパーピン|Useconn Electronics|[MJ127-3C](https://akizukidenshi.com/catalog/g/g111533/)|-|1|
|-|3mmプラネジ (7mm) + 六角スペーサー (14mm)|OptoSupply|[型番なし](https://akizukidenshi.com/catalog/g/g101861/)|-|1|

- ピンヘッダJ3: 2ピンに切断して実装。ジャンパーピンを取り付ける

### 千石電商で購入

|ID|種別|メーカー|型番|パッケージ|数量|
|:--|:--|:--|:--|:--|--:|
|BT2|電池ケース ピン型 (単4x2)|タカチ|[SN4-2PC](https://www.sengoku.co.jp/mod/sgk_cart/detail.php?code=EEHD-0AMK)|スルーホール|1|
|R1,R2|カーボン抵抗 (5.1kΩ)|KOA|[RK73B1JTTD512J](https://www.sengoku.co.jp/mod/sgk_cart/detail.php?code=EEHD-57GS)|表面実装 (1608)|1|
|R14|カーボン抵抗 (330Ω)|KOA|[RK73B1JTTD331J](https://www.sengoku.co.jp/mod/sgk_cart/detail.php?code=EEHD-57G7)|表面実装 (1608)|1|
|-|M2 x 6mm ポリ皿ネジ|-|-|-|2|
|-|M2 ポリナット|-|-|-|2|

### DigiKeyで購入

マルツを通じて取り寄せ可能

|ID|種別|メーカー|型番|パッケージ|数量|
|:--|:--|:--|:--|:--|--:|
|C6|積層セラミックコンデンサ (0.33uF)|TDK|[C1608X8R1E334K080AC](https://www.digikey.jp/ja/products/detail/tdk-corporation/C1608X8R1E334K080AC/6556503)|表面実装 (1608)|1|
|U2|リアルタイムクロック|NXP|[PCF8563T/5,518](https://www.digikey.jp/ja/products/detail/nxp-usa-inc/PCF8563T-5-518/2606091)|表面実装 (SOP8)|1|

### 海外通販で購入

AliExpressでも調達可能

|ID|種別|メーカー|型番|パッケージ|数量|
|:--|:--|:--|:--|:--|--:|
|U1|マイコンボード|Spotpear|[RP2040-Core-A](https://spotpear.com/index/product/detail/id/1282.html)|端面スルーホール|1|

### 消耗品

- CR2032
- 単4電池 x2
- TFカード (32GBまで)

## 使い方

- 電池ボックスに単4電池2本を入れて電池ボックスのスイッチを入れるか、USB Type-Cポートにケーブルを接続する
  - 試作品と異なり、保護回路があるので電池とUSBから同時に給電しても故障しない
- カードスロットJ2にTFカードを挿入する
- スライドスイッチSW3を動かして電源を入れる
  - バックアップ用のCR2032が挿入済で、電池残量がある限り、電源を切っても時刻は保持される
  - 時刻設定が済んでいない状態 (またはバックアップ用のCR2032が未装着or交換直後) で起動すると、**赤色LED**が点灯する
  - TFカード未挿入で電源を入れたり、読み込めない状態だと、**緑色LED**が点灯する。TFカードを読み込めてもCSVファイルが開けない (作成できない) 場合は**黄色LED**が点灯する
    - 稀にカードの接触が悪く読み込めないことがある。何度か抜き差ししてみる
- 赤色LED、黄色LED、緑色LEDのすべて消灯すれば初期化は完了。黄色LEDが3秒おきに短く点滅する。後述のカウント操作を受け付けるようになる

### 初期設定

- USB Type-CポートでPCと接続する
- 電源投入後、シリアル通信 (115200bps, 改行コード: LF) で時刻設定をする。TFカードの初期化ができていなくても操作を受け付ける
  - 時刻の取得: `get` (Enterキー)
  - 時刻の設定: `set 20XX/XX/XX XX:XX:XX` (Enterキー)
  - 時刻設定が完了すると赤色LEDが消灯する

### カウント操作

- スイッチSW1またはSW2を押すと、TFカードにスイッチを押した時刻とスイッチの種別がCSV形式で1行ずつ記録される
  - CSVファイルは日付別に作成される
  - SW1を押すと赤色LEDが、SW2を押すと緑色LEDが点灯し、1秒後に消灯する。同時にブザーも鳴る
- チャタリング防止機能があり、LEDが消灯するまでは次のスイッチ操作を受け付けない

## その他いろいろ

### コネクタJ4

- JST PHコネクタ (2mmピッチ)
- UART0 (RX=GPIO1, TX=GPIO0) を引き出しているが、本ファームウェアでは使用していない

### ジャンパJP1～JP4

- JP1, JP2 のジャンパーを外して JP3, JP4 にジャンパーを繋ぐと、PCF8563へのI2CバスにI2C1 (SDA=GPIO6, SCL=GPIO7) を使用する。ファームウェアはI2C0 (SDA=GPIO8, SCL=GPIO9) を使用するよう書かれているので、修正が必要

### ファームウェア書込

- RP2040-Core-A上のBOOTボタンを押した状態で、SW3を操作して電源を投入するとファームウェア書込モードで起動する

### 消費電力

- マルチメータでの実測で、待機状態で12mA前後、ボタン押下直後 (LED点灯・カード書込) で20mA前後
  - 省電力機能は使っていないが (RP2040自体に機能はあるがPico C SDKにAPIが無い)、RP2040のクロックを50MHzに落としている
- ピンヘッダJ3に装着されたジャンパーピンを取り外すと回路がオープンになるので、ここにテスターリードを当てて電流測定が可能

## ライセンス

- [RTClib](https://github.com/adafruit/rtclib): MIT
