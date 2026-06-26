# iotgateway

基于 Qt Widgets 的物联网网关桌面程序。程序会每 5 秒模拟生成一组传感器数据，在界面中显示实时数据和温度曲线，同时写入 SQLite 数据库，并尝试通过本机 MQTT Broker 上报数据和接收控制命令。

## 功能概览

- 实时数据：温度、湿度、烟雾、人体红外状态。
- 历史数据：从 SQLite 数据库查询历史记录并绘制曲线。
- 设备控制：界面按钮或 MQTT 指令控制 LED、蜂鸣器的模拟状态。
- MQTT：连接 `localhost:1883`，发布传感器数据到 `home/sensors`，订阅 `home/led/set` 和 `home/buzzer/set`。

## 项目结构

```text
iot
├── README.md
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
    ├── iotgateway                                   # Linux 已构建好的可执行文件
    └── gateway.db                                   # 运行时 SQLite 数据库
```

## 环境要求

工程使用 Qt 5，推荐 Qt 5.12.9 或兼容版本。

需要安装的 Qt 模块：

- `core`
- `gui`
- `widgets`
- `charts`
- `sql`
- `mqtt`

还需要：

- C++ 编译器
- qmake
- Qt SQLite 驱动
- 可选：MQTT Broker，例如 Mosquitto

## Linux 下运行

### 方式一：直接运行已有构建

仓库中已有 Linux Debug 构建目录，可以直接运行：

```bash
cd /home/my/Qt/iot/build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug
./iotgateway
```

建议在构建目录中启动，因为程序使用相对路径 `gateway.db`。如果从其他目录启动，`gateway.db` 会生成在当时的工作目录下。

如果提示找不到 Qt 库，先设置 Qt 库路径：

```bash
export LD_LIBRARY_PATH=/home/my/Qt5.12.9/5.12.9/gcc_64/lib:$LD_LIBRARY_PATH
./iotgateway
```

### 方式二：从源码重新构建

```bash
cd /home/my/Qt/iot
mkdir -p build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug
cd build-iotgateway-Desktop_Qt_5_12_9_GCC_64bit-Debug
/home/my/Qt5.12.9/5.12.9/gcc_64/bin/qmake ../iotgateway/iotgateway.pro -spec linux-g++ CONFIG+=debug
make -j$(nproc)
./iotgateway
```

如果系统默认 `qmake` 已安装 `Qt Charts`、`Qt SQL` 和 `Qt MQTT`，也可以使用：

```bash
cd /home/my/Qt/iot
mkdir -p build
cd build
qmake ../iotgateway/iotgateway.pro
make -j$(nproc)
./iotgateway
```

### 方式三：使用 Qt Creator

1. 打开 Qt Creator。
2. 选择 `Open Project`，打开 `iotgateway/iotgateway.pro`。
3. Kit 选择 Linux 桌面 Qt Kit，例如 `Desktop Qt 5.12.9 GCC 64bit`。
4. 点击 `Build`。
5. 点击 `Run`。

## Windows 下运行

Windows 下不能直接运行仓库里的 Linux 可执行文件，需要使用 Windows 版 Qt 重新构建。

### 方式一：使用 Qt Creator

1. 安装 Qt 5.12.9 或兼容版本。
2. 安装并启用这些组件：
   - MinGW 或 MSVC 编译器
   - Qt Charts
   - Qt MQTT
   - Qt SQL
3. 打开 Qt Creator。
4. 选择 `Open Project`，打开：

```text
iotgateway/iotgateway.pro
```

5. Kit 选择 Windows 桌面 Kit，例如：

```text
Desktop Qt 5.12.9 MinGW 64-bit
```

6. 点击 `Configure Project`。
7. 点击 `Build`。
8. 点击 `Run`。

### 方式二：使用命令行构建

先打开 Qt 提供的命令行环境，例如 `Qt 5.12.9 for Desktop (MinGW 64-bit)`，然后进入项目目录：

```bat
cd /d D:\path\to\iot
mkdir build
cd build
qmake ..\iotgateway\iotgateway.pro
mingw32-make
iotgateway.exe
```

如果使用 MSVC Kit，则在对应的 Qt MSVC 命令行中执行：

```bat
cd /d D:\path\to\iot
mkdir build
cd build
qmake ..\iotgateway\iotgateway.pro
nmake
iotgateway.exe
```

其中 `D:\path\to\iot` 替换成你本机实际的项目路径。

### Windows 运行注意事项

- 如果双击运行 `iotgateway.exe` 提示缺少 Qt DLL，优先通过 Qt Creator 运行。
- 如果要单独发布 exe，可以使用 `windeployqt`：

```bat
windeployqt iotgateway.exe
```

- 数据库文件 `gateway.db` 会生成在程序启动时的当前工作目录下。

## MQTT 可选配置

程序启动时会自动尝试连接：

```text
localhost:1883
```

没有 MQTT Broker 时，界面仍可运行，实时模拟数据和数据库保存仍会工作，但终端会看到 MQTT 连接错误和重连日志。

### Linux 安装 Mosquitto

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

### Windows 安装 Mosquitto

1. 从 Mosquitto 官网下载安装包。
2. 安装后启动 Mosquitto 服务，或在 Mosquitto 安装目录中运行：

```bat
mosquitto.exe -v
```

3. 使用 `mosquitto_sub.exe` 和 `mosquitto_pub.exe` 测试主题：

```bat
mosquitto_sub.exe -h localhost -t home/sensors
mosquitto_pub.exe -h localhost -t home/led/set -m on
mosquitto_pub.exe -h localhost -t home/buzzer/set -m off
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

### 编译时报 Unknown module(s) in QT: mqtt 或 charts

说明当前 qmake 对应的 Qt 没有安装 `Qt MQTT` 或 `Qt Charts`。请在 Qt Maintenance Tool 中安装对应模块，或切换到已安装这些模块的 Qt Kit。

### 数据库文件在哪里

数据库路径取决于启动程序时的当前目录。推荐从构建目录或 Qt Creator 启动，数据库会生成在运行工作目录下。

### 没有真实传感器能不能运行

可以。当前 `SensorThread` 会随机生成模拟数据，不依赖真实硬件。

### 没有 MQTT 能不能运行

可以。MQTT 连接失败只影响上报和远程控制，实时页面、历史数据和本地控制按钮仍可使用。
