# iotgateway

基于 Qt Widgets 的物联网网关桌面程序。程序会每 5 秒模拟生成一组传感器数据，在界面中显示实时数据和温度曲线，同时写入 SQLite 数据库，并尝试通过本机 MQTT Broker 上报数据和接收控制命令。

## 功能概览

- 实时数据：温度、湿度、烟雾、人体红外状态。
- 历史数据：从 SQLite 数据库查询历史记录并绘制曲线。
- 设备控制：界面按钮或 MQTT 指令控制 LED、蜂鸣器的模拟状态。
- MQTT：连接 `localhost:1883`，发布传感器数据到 `home/sensors`，订阅 `home/led/set` 和 `home/buzzer/set`。

## 项目结构

```text
/home/my/Qt/iot
├── iotgateway/                                      # 源码目录
│   ├── iotgateway.pro                               # qmake 工程文件
│   ├── main.cpp
│   ├── mainwindow.*
│   ├── realtimepage.*
│   ├── historypage.*
│   ├── controlpage.*
│   ├── databasemanager.*
│   ├── mqttmanager.*
│   └── sensorthread.*
└── build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug/
    ├── iotgateway                                   # 已构建好的可执行文件
    └── gateway.db                                   # 运行时 SQLite 数据库
```

## 环境要求

推荐使用当前机器已有的 Qt 5.12.9：

```bash
/home/my/Qt5.12.9/5.12.9/gcc_64/bin/qmake --version
```

工程使用的 Qt 模块：

- `core`
- `gui`
- `widgets`
- `charts`
- `sql`
- `mqtt`

还需要：

- C++ 编译器，例如 `g++`
- `make`
- Qt SQLite 驱动 `libqsqlite.so`
- 可选：MQTT Broker，例如 Mosquitto

## 直接启动已有构建

如果只是运行项目，直接进入已有构建目录启动：

```bash
cd /home/my/Qt/iot/build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug
./iotgateway
```

建议在构建目录中启动，因为程序使用相对路径 `gateway.db`，这样会继续使用：

```text
/home/my/Qt/iot/build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug/gateway.db
```

如果从其他目录启动，`gateway.db` 会生成在当时的工作目录下。

## 从源码重新构建并启动

从仓库根目录执行：

```bash
cd /home/my/Qt/iot
mkdir -p build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug
cd build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug
/home/my/Qt5.12.9/5.12.9/gcc_64/bin/qmake ../iotgateway/iotgateway.pro -spec linux-g++ CONFIG+=debug
make -j$(nproc)
./iotgateway
```

如果你想使用系统默认 `qmake`，需要确认默认 Qt 也安装了 `Qt Charts`、`Qt SQL` 和 `Qt MQTT`：

```bash
qmake --version
qmake ../iotgateway/iotgateway.pro
make -j$(nproc)
./iotgateway
```

当前已构建的可执行文件链接到 `/home/my/Qt5.12.9/5.12.9/gcc_64` 下的 Qt 5.12.9，所以优先使用上面的完整 qmake 路径更稳。

## 用 Qt Creator 启动

1. 打开 Qt Creator。
2. 选择 `Open Project`，打开：

```text
/home/my/Qt/iot/iotgateway/iotgateway.pro
```

3. Kit 选择 `Desktop Qt 5.12.9 GCC 64bit`。
4. 构建目录选择或保持：

```text
/home/my/Qt/iot/build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug
```

5. 点击 `Build`，再点击 `Run`。

## MQTT 可选配置

程序启动时会自动尝试连接：

```text
localhost:1883
```

没有 MQTT Broker 时，界面仍可运行，实时模拟数据和数据库保存仍会工作，但终端会看到 MQTT 连接错误和重连日志。

如果需要完整测试 MQTT，可以启动 Mosquitto：

```bash
sudo apt install mosquitto mosquitto-clients
sudo systemctl enable --now mosquitto
```

查看程序上报的传感器数据：

```bash
mosquitto_sub -h localhost -t 'home/sensors'
```

发送 LED 控制命令：

```bash
mosquitto_pub -h localhost -t 'home/led/set' -m on
mosquitto_pub -h localhost -t 'home/led/set' -m off
```

发送蜂鸣器控制命令：

```bash
mosquitto_pub -h localhost -t 'home/buzzer/set' -m on
mosquitto_pub -h localhost -t 'home/buzzer/set' -m off
```

## 数据库说明

数据库文件名是：

```text
gateway.db
```

程序启动时会自动创建表：

```sql
CREATE TABLE IF NOT EXISTS sensor_data (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    type TEXT NOT NULL,
    value REAL NOT NULL
);
```

每次模拟采集会写入 4 条记录：

- `temperature`
- `humidity`
- `smoke`
- `pir`

## 常见问题

### 启动后提示找不到 Qt 库

优先从构建目录运行：

```bash
cd /home/my/Qt/iot/build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug
./iotgateway
```

如果仍然缺少 Qt 库，设置 Qt 5.12.9 的库路径后再启动：

```bash
export LD_LIBRARY_PATH=/home/my/Qt5.12.9/5.12.9/gcc_64/lib:$LD_LIBRARY_PATH
./iotgateway
```

### 编译时报 Unknown module(s) in QT: mqtt 或 charts

说明当前 qmake 对应的 Qt 没有安装 `Qt MQTT` 或 `Qt Charts`。使用当前机器已有的 Qt 5.12.9：

```bash
/home/my/Qt5.12.9/5.12.9/gcc_64/bin/qmake ../iotgateway/iotgateway.pro -spec linux-g++ CONFIG+=debug
make -j$(nproc)
```

### 数据库文件在哪里

数据库路径取决于启动程序时的当前目录。推荐在构建目录启动，数据库就在：

```text
/home/my/Qt/iot/build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug/gateway.db
```

### 没有真实传感器能不能运行

可以。当前 `SensorThread` 会随机生成模拟数据，不依赖真实硬件。

### 没有 MQTT 能不能运行

可以。MQTT 连接失败只影响上报和远程控制，实时页面、历史数据和本地控制按钮仍可使用。
